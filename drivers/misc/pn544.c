<<<<<<< HEAD
<<<<<<< HEAD
/* drivers/misc/pn544.c
 *
 * Copyright (C) 2012-2013 Sony Mobile Communications AB.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#include <linux/delay.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/pn544.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/wakelock.h>

#include <mach/gpiomux.h>

#define PN544_WAKE_LOCK_TIMEOUT	(HZ)
#define MAX_FIRMDL_FRAME_SIZE	(3 + 512)
#define MAX_NORMAL_FRAME_SIZE	(1 + 32)
#define MAX_I2C_RETRY_COUNT	5
#define MAX_GPIOMUX_SET_SIZE	4

struct pn544_dev {
	struct list_head		node;
	wait_queue_head_t		wq;
	struct wake_lock		wake_lock;
	struct mutex			lock;
	struct device			*dev;
	struct i2c_client		*i2c_client;
	struct pn544_i2c_platform_data	*pdata;
	struct miscdevice		device;
	enum pn544_state		state;
	bool				busy;
	bool				suspended;
	u8				cmd[MAX_FIRMDL_FRAME_SIZE];
	u8				res[MAX_FIRMDL_FRAME_SIZE];
	u16				res_size;
	u16				res_pos;
	atomic_t			res_ready;
};

static LIST_HEAD(dev_list);
static DEFINE_MUTEX(list_lock);

static void dump_buf(struct pn544_dev *d, u8 *buf, int size)
{
#ifdef DEBUG_DETAIL
	if (d->state == PN544_STATE_ON) {
		int i;
		char s[MAX_NORMAL_FRAME_SIZE * 3];
		int p = 0;

		for (i = 0; i < size; i++)
			p += snprintf(s + p, sizeof(s) - p, "%02x ", buf[i]);
		dev_dbg(d->dev, "%s\n", s);
	}
#endif
}

static struct pn544_dev *get_pn544_dev(struct inode *inode)
{
	int minor = iminor(inode);
	struct pn544_dev *d;

	mutex_lock(&list_lock);
	list_for_each_entry(d, &dev_list, node) {
		if (d->device.minor == minor)
			goto found;
	}
	d = NULL;
found:
	mutex_unlock(&list_lock);
	return d;
}

static int pn544_dev_update_frame(struct pn544_dev *d, size_t size)
{
	int ret;
	int len;
	int offset;
	int maxlen;
	int retry_count = 0;
	bool fwdl;

	atomic_set(&d->res_ready, 0);
	memset(d->res, 0, MAX_FIRMDL_FRAME_SIZE);
	d->res_size = 0;
	d->res_pos = 0;
	fwdl = d->state == PN544_STATE_FWDL;
	offset = fwdl ? size : 1;
	maxlen = fwdl ? MAX_FIRMDL_FRAME_SIZE : MAX_NORMAL_FRAME_SIZE;
retry:
	ret = i2c_master_recv(d->i2c_client, d->res, offset);
	if (ret == -ENODEV || ret == -ENOTCONN || ret == -EIO) {
		retry_count++;
		if (retry_count > MAX_I2C_RETRY_COUNT)
			goto exit;
		usleep_range(10000, 11000);
		dev_err(d->dev, "%s: i2c read err %d, but retry %d\n",
			__func__, ret, retry_count);
		goto retry;
	}

	if (d->res[0] == (d->i2c_client->addr << 1 | 0x01)) {
		dev_dbg(d->dev, "%s: i2c read slave addr, but wait irq\n",
			__func__);
		goto exit;
	}

	if (ret != offset) {
		dev_err(d->dev, "%s: i2c read err %d\n", __func__, ret);
		if (ret > 0)
			ret = -EIO;
		goto exit;
	}

	if (fwdl) {
		dev_dbg(d->dev, "%s: i2c read only once in fwdl", __func__);
		d->res_size = offset;
		dump_buf(d, d->res, d->res_size);
		goto exit;
	}

	len = d->res[0];
	if (len == 0) {
		dev_dbg(d->dev, "%s: parameters length zero\n", __func__);
		d->res_size = offset;
		dump_buf(d, d->res, d->res_size);
		goto exit;
	} else if (len > (maxlen - offset)) {
		dev_err(d->dev, "%s: parameters too long %d\n", __func__, len);
		ret = -EIO;
		goto exit;
	}

	dev_dbg(d->dev, "%s: parameters length %d\n", __func__, len);
	retry_count = 0;

retry_read:
	ret = i2c_master_recv(d->i2c_client, d->res + offset, len);
	if (ret == -EIO) {
		retry_count++;
		if (retry_count > MAX_I2C_RETRY_COUNT)
			goto exit;
		dev_err(d->dev, "%s: i2c read err %d, but retry %d\n",
			__func__, ret, retry_count);
		goto retry_read;
	}

	if (ret != len) {
		dev_err(d->dev, "%s: i2c read err %d\n", __func__, ret);
		if (ret > 0)
			ret = -EIO;
		goto exit;
	}
	d->res_size = len + offset;
	dump_buf(d, d->res, d->res_size);
exit:
	return ret;
}

static int pn544_dev_read_frame(struct pn544_dev *d, char __user *buf,
				size_t size)
{
	int ret;
	int len;

	len = d->res_size - d->res_pos;
	if (len) {
		len = len > size ? size : len;
		ret = copy_to_user(buf, d->res + d->res_pos, len);
		if (ret) {
			dev_err(d->dev, "%s: copy_to_user err %d\n",
				__func__, ret);
			return -EFAULT;
		}
		d->res_pos += len;
	}
	dev_dbg(d->dev, "%s: %d bytes read\n", __func__, len);
	dump_buf(d, d->res + d->res_pos - len, len);
	if (d->res_size == d->res_pos) {
		d->res_size = 0;
		d->res_pos = 0;
	}
	return len;
}

static irqreturn_t pn544_dev_irq_handler(int irq, void *dev_info)
{
	struct pn544_dev *d = dev_info;

	mutex_lock(&d->lock);
	dev_dbg(d->dev, "%s: interruption\n", __func__);
	if (d->suspended) {
		dev_dbg(d->dev, "Interruption during suspend.\n");
		wake_lock_timeout(&d->wake_lock, PN544_WAKE_LOCK_TIMEOUT);
	}
	atomic_set(&d->res_ready, 1);
	wake_up_interruptible(&d->wq);
	mutex_unlock(&d->lock);
	return IRQ_HANDLED;
}

static int pn544_dev_gpio_config_update(struct pn544_dev *d, int gpio,
	int *new_conf, int *old_conf)
{
	int ret;
	ret = msm_gpiomux_write(gpio,
		GPIOMUX_ACTIVE,
		(struct gpiomux_setting *)new_conf,
		(struct gpiomux_setting *)old_conf);
	if (ret < 0) {
		dev_err(d->dev, "%s: GPIOMUX_ACTIVE->%d\n", __func__, ret);
		goto err;
	}
	ret = msm_gpiomux_write(gpio,
		GPIOMUX_SUSPENDED,
		(struct gpiomux_setting *)new_conf,
		(struct gpiomux_setting *)old_conf);
	if (ret < 0)
		dev_err(d->dev, "%s: GPIOMUX_SUSPENDED->%d\n", __func__, ret);
err:
	return ret;
}

static int pn544_dev_chip_config(enum pn544_state state, void *device)
{
	struct pn544_dev *d = (struct pn544_dev *)device;

	switch (state) {
	case PN544_STATE_OFF:
		gpio_set_value_cansleep(d->pdata->fwdl_en_gpio, 0);
		gpio_set_value_cansleep(d->pdata->ven_gpio, 1);
		msleep(50);
		break;
	case PN544_STATE_ON:
		gpio_set_value_cansleep(d->pdata->fwdl_en_gpio, 0);
		gpio_set_value_cansleep(d->pdata->ven_gpio, 0);
		usleep_range(10000, 11000);
		break;
	case PN544_STATE_FWDL:
		gpio_set_value_cansleep(d->pdata->fwdl_en_gpio, 1);
		gpio_set_value_cansleep(d->pdata->ven_gpio, 1);
		usleep_range(10000, 11000);
		gpio_set_value_cansleep(d->pdata->ven_gpio, 0);
		break;
	default:
		dev_err(d->dev, "%s: undefined state %d\n", __func__, state);
		return -EINVAL;
	}
	return 0;
}

static int pn544_parse_dt(struct device *dev,
			 struct pn544_i2c_platform_data *pdata)
{
	struct device_node *np = dev->of_node;
	const unsigned char *buf;
	int i;
	int ret = 0;

	ret = of_get_named_gpio(np, "nxp,irq_gpio", 0);
	if (ret < 0) {
		dev_err(dev, "failed to get \"nxp,irq_gpio\"\n");
		goto err;
	}
	pdata->irq_gpio = ret;

	ret = of_get_named_gpio(np, "nxp,dwld_en", 0);
	if (ret < 0) {
		dev_err(dev, "failed to get \"nxp,dwld_en\"\n");
		goto err;
	}
	pdata->fwdl_en_gpio = ret;

	ret = of_get_named_gpio(np, "nxp,pvdd_en", 0);
	if (ret < 0) {
		dev_err(dev, "failed to get \"nxp,pvdd_en\"\n");
		goto err;
	}
	pdata->pvdd_en_gpio = ret;

	ret = of_get_named_gpio(np, "nxp,ven", 0);
	if (ret < 0) {
		dev_err(dev, "failed to get \"nxp,ven\"\n");
		goto err;
	}
	pdata->ven_gpio = ret;

	buf = of_get_property(np, "gpio_fwdl_enable", NULL);
	if (buf == NULL) {
		dev_dbg(dev, "failed to get \"gpio_fwdl_enable\"\n");
	} else {
		for (i = 0; i < MAX_GPIOMUX_SET_SIZE; i++) {
			pdata->gpio_fwdl_enable[i] = (buf[i * 4] << 3) +
				(buf[i * 4 + 1] << 2) + (buf[i * 4 + 2] << 1) +
				buf[i * 4 + 3];
			dev_dbg(dev, "gpio_fwdl_enable[%d]=%d", i,
				pdata->gpio_fwdl_enable[i]);
		}
	}

	buf = of_get_property(np, "gpio_fwdl_disable", NULL);
	if (buf == NULL) {
		dev_dbg(dev, "failed to get \"gpio_fwdl_disable\"\n");
	} else {
		for (i = 0; i < MAX_GPIOMUX_SET_SIZE; i++) {
			pdata->gpio_fwdl_disable[i] = (buf[i * 4] << 3) +
				(buf[i * 4 + 1] << 2) + (buf[i * 4 + 2] << 1) +
				buf[i * 4 + 3];
			dev_dbg(dev, "gpio_fwdl_disable[%d]=%d", i,
				pdata->gpio_fwdl_disable[i]);
		}
	}

err:
	return ret;
}

static int pn544_gpio_request(struct device *dev,
				struct pn544_i2c_platform_data *pdata)
{
	int ret;

	ret = gpio_request(pdata->pvdd_en_gpio, "pn544_pvdd_en");
	if (ret)
		goto err_pvdd_en;
	ret = gpio_request(pdata->irq_gpio, "pn544_irq");
	if (ret)
		goto err_irq;
	ret = gpio_request(pdata->fwdl_en_gpio, "pn544_fw");
	if (ret)
		goto err_fwdl_en;
	ret = gpio_request(pdata->ven_gpio, "pn544_ven");
	if (ret)
		goto err_ven;
	return 0;

err_ven:
	gpio_free(pdata->fwdl_en_gpio);
err_fwdl_en:
	gpio_free(pdata->irq_gpio);
err_irq:
	gpio_free(pdata->pvdd_en_gpio);
err_pvdd_en:

	dev_err(dev, "%s: gpio request err %d\n", __func__, ret);
	return ret;
}

static void pn544_gpio_release(struct pn544_i2c_platform_data *pdata)
{
	gpio_free(pdata->ven_gpio);
	gpio_free(pdata->irq_gpio);
	gpio_free(pdata->fwdl_en_gpio);
}

static ssize_t pn544_dev_read(struct file *file, char __user *buf,
				size_t size, loff_t *pos)
{
	struct pn544_dev *d = file->private_data;
	int ret = 0;

	mutex_lock(&d->lock);
	if (!d->res_size) {
		/* Read the data from chip */
		ret = pn544_dev_update_frame(d, size);
		if (IS_ERR_VALUE(ret)) {
			dev_err(d->dev, "%s: update frame err %d\n",
				__func__, ret);
			goto exit;
		}
	}
	/* Read the data from buffer and copy data to user space */
	ret = pn544_dev_read_frame(d, buf, size);
	if (IS_ERR_VALUE(ret)) {
		dev_err(d->dev, "%s: read frame err %d\n",
			__func__, ret);
		goto exit;
	}
	*pos += ret;
exit:
	mutex_unlock(&d->lock);
	return ret;
}

unsigned int pn544_dev_poll(struct file *file, struct poll_table_struct *pt)
{
	struct pn544_dev *d = file->private_data;
	int ret = 0;

	dev_dbg(d->dev, "%s: poll_wait enter\n", __func__);
	if (d->res_size) {
		ret = POLLIN | POLLRDNORM;
	} else {
		poll_wait(file, &d->wq, pt);
		if (atomic_read(&d->res_ready))
			ret = POLLIN | POLLRDNORM;
	}
	dev_dbg(d->dev, "%s: poll_wait exit %x\n", __func__, ret);
	return ret;
}

static ssize_t pn544_dev_write(struct file *file, const char __user *buf,
				size_t size, loff_t *pos)
{
	struct pn544_dev *d = file->private_data;
	int ret = 0;
	int maxlen;
	int retry_count = 0;
	bool fwdl;

	mutex_lock(&d->lock);
	fwdl = d->state == PN544_STATE_FWDL;
	maxlen = fwdl ? MAX_FIRMDL_FRAME_SIZE : MAX_NORMAL_FRAME_SIZE;
	if (!size)
		goto exit;
	else if (size > maxlen)
		size = maxlen;
	ret = copy_from_user(d->cmd, buf, size);
	if (ret) {
		dev_err(d->dev, "%s: copy_to_user err %d\n", __func__, ret);
		goto exit;
	}
retry:
	ret = i2c_master_send(d->i2c_client, d->cmd, size);
	if (ret == -ENODEV || ret == -ENOTCONN) {
		retry_count++;
		if (retry_count > MAX_I2C_RETRY_COUNT)
			goto exit;
		usleep_range(10000, 11000);
		dev_err(d->dev, "%s: i2c write err %d, but retry %d\n",
			__func__, ret, retry_count);
		goto retry;
	}

	if (ret < 0) {
		dev_err(d->dev, "%s: i2c err %d\n", __func__, ret);
		goto exit;
	}
	*pos += ret;
	dev_dbg(d->dev, "%s: %d bytes write\n", __func__, ret);
	dump_buf(d, d->cmd, ret);
exit:
	mutex_unlock(&d->lock);
	return ret;
}

static int pn544_dev_open(struct inode *inode, struct file *file)
{
	struct pn544_dev *d = get_pn544_dev(inode);
	int ret = 0;

	if (!d)
		return -ENODEV;

	mutex_lock(&d->lock);
	if (d->busy) {
		ret = -EBUSY;
		dev_err(d->dev, "%s: only one client supported\n", __func__);
	} else {
		if (d->pdata->driver_opened) {
			ret = d->pdata->driver_opened();
			if (IS_ERR_VALUE(ret)) {
				dev_err(d->dev, "%s: cannot open driver\n",
					__func__);
				mutex_unlock(&d->lock);
				return ret;
			}
		}
		d->busy = true;
		file->private_data = d;
	}
	mutex_unlock(&d->lock);
	return ret;
}

static int pn544_dev_release(struct inode *inode, struct file *file)
{
	struct pn544_dev *d = file->private_data;

	mutex_lock(&d->lock);
	if (atomic_read(&d->res_ready))
		dev_dbg(d->dev, "%s: interruption is ignored\n", __func__);
	if (d->pdata->driver_closed)
		d->pdata->driver_closed();
	atomic_set(&d->res_ready, 0);
	memset(d->res, 0, MAX_FIRMDL_FRAME_SIZE);
	d->res_size = 0;
	d->res_pos = 0;
	d->busy = false;
	mutex_unlock(&d->lock);
	return 0;
}

static long pn544_dev_ioctl(struct file *file,
			unsigned int cmd, unsigned long val)
{
	struct pn544_dev *d = file->private_data;
	int ret = 0;
	int state = 0;

	mutex_lock(&d->lock);
	dev_dbg(d->dev, "%s: cmd=%d val=%lu\n", __func__, cmd, val);
	if (atomic_read(&d->res_ready))
		dev_dbg(d->dev, "%s: interruption is ignored\n", __func__);

	disable_irq(d->i2c_client->irq);
	switch (cmd) {
	case PN544_SET_PWR:
		switch (val) {
		case PN544_SET_PWR_OFF:
			state = PN544_STATE_OFF;
			break;
		case PN544_SET_PWR_ON:
			state = PN544_STATE_ON;
			break;
		case PN544_SET_PWR_FWDL:
		default:
			state = PN544_STATE_FWDL;
			break;
		}

		ret = pn544_dev_chip_config(state, (void *)d);
		if (IS_ERR_VALUE(ret)) {
			dev_err(d->dev, "%s: chip config err %d\n",
				__func__, ret);
			goto exit;
		}
		dev_dbg(d->dev, "%s: state -> %d\n", __func__, state);
		if (d->state != state) {
			d->state = state;
			atomic_set(&d->res_ready, 0);
			memset(d->res, 0, MAX_FIRMDL_FRAME_SIZE);
			d->res_size = 0;
			d->res_pos = 0;
		}
		break;
	case PN544_SET_GPIO:
		dev_dbg(d->dev, "%s: update gpio configuration\n", __func__);
		ret = pn544_dev_gpio_config_update(d, d->pdata->fwdl_en_gpio,
			d->pdata->gpio_fwdl_enable,
			d->pdata->gpio_fwdl_disable);
		break;
	default:
		dev_err(d->dev, "%s: command %d not supported\n",
			__func__, cmd);
		ret = -EINVAL;
		break;
	}
exit:
	enable_irq(d->i2c_client->irq);
	mutex_unlock(&d->lock);
	return ret;
}

static const struct file_operations pn544_fops = {
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.read		= pn544_dev_read,
	.write		= pn544_dev_write,
	.open		= pn544_dev_open,
	.release	= pn544_dev_release,
	.unlocked_ioctl	= pn544_dev_ioctl,
	.poll		= pn544_dev_poll,
};

static int pn544_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct pn544_dev *dev;
	struct pn544_i2c_platform_data *pdata;
	int ret = 0;

	pdata = kzalloc(sizeof(struct pn544_i2c_platform_data),
			GFP_KERNEL);
	if (!pdata) {
		dev_err(&client->dev, "failed to allocate memory\n");
		ret = -ENOMEM;
		goto probe_pdata;
	}
	ret = pn544_parse_dt(&client->dev, pdata);
	if (ret < 0) {
		dev_err(&client->dev, "failed to parse device tree: %d\n", ret);
		goto probe_parse_dt;
	}

	ret = pn544_gpio_request(&client->dev, pdata);
	if (ret) {
		dev_err(&client->dev, "failed to request gpio\n");
		goto probe_gpio_request;
	}
	dev_dbg(&client->dev, "%s:\n", __func__);

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "%s: i2c check failed\n", __func__);
		ret = -ENODEV;
		goto probe_i2c;
	}

	dev = kzalloc(sizeof(struct pn544_dev), GFP_KERNEL);
	if (!dev) {
		dev_err(&client->dev, "%s: no memory\n", __func__);
		ret = -ENOMEM;
		goto probe_mem;
	}
	dev->i2c_client = client;
	dev->dev = &client->dev;
	dev->pdata = pdata;
	init_waitqueue_head(&dev->wq);
	wake_lock_init(&dev->wake_lock, WAKE_LOCK_SUSPEND, "pn544");
	mutex_init(&dev->lock);
	i2c_set_clientdata(client, dev);
	dev->state = PN544_STATE_UNKNOWN;

	ret = request_threaded_irq(client->irq, NULL, pn544_dev_irq_handler,
			IRQF_TRIGGER_RISING | IRQF_ONESHOT, client->name, dev);
	if (IS_ERR_VALUE(ret)) {
		dev_err(&client->dev, "%s: irq request err %d\n",
			__func__, ret);
		goto probe_irq;
	}

	dev->device.minor = MISC_DYNAMIC_MINOR;
	dev->device.name = PN544_DEVICE_NAME;
	dev->device.fops = &pn544_fops;
	mutex_lock(&list_lock);
	list_add_tail(&dev->node, &dev_list);
	mutex_unlock(&list_lock);
	ret = misc_register(&dev->device);
	if (IS_ERR_VALUE(ret)) {
		dev_err(&client->dev, "%s: misc_register err %d\n",
			__func__, ret);
		goto probe_misc;
	}
	return ret;

probe_misc:
	mutex_lock(&list_lock);
	list_del(&dev->node);
	mutex_unlock(&list_lock);
	free_irq(client->irq, dev);
probe_irq:
	i2c_set_clientdata(client, NULL);
	wake_lock_destroy(&dev->wake_lock);
	kfree(dev);
probe_mem:
probe_i2c:
	pn544_gpio_release(pdata);
probe_gpio_request:
probe_parse_dt:
	kfree(pdata);
probe_pdata:
	dev_err(&client->dev, "%s: err %d\n", __func__, ret);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Copyright (C) 2010 Trusted Logic S.A.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/pn544.h>

#define MAX_BUFFER_SIZE	512
#define READ_IRQ_MODIFY /* DY_TEST */

#ifdef READ_IRQ_MODIFY /* DY_TEST */
bool do_reading;
static bool cancle_read;
#endif
#define NFC_DEBUG 0

struct pn544_dev {
	wait_queue_head_t read_wq;
	struct mutex read_mutex;
	struct i2c_client *client;
	struct miscdevice pn544_device;
	unsigned int ven_gpio;
	unsigned int firm_gpio;
	unsigned int irq_gpio;
	bool irq_enabled;
	spinlock_t irq_enabled_lock;
};

bool do_reading;

static struct pn544_dev *pn544_dev_imsi;

static void pn544_disable_irq(struct pn544_dev *pn544_dev)
{
	/* unsigned long flags; */
	/* spin_lock_irqsave(&pn544_dev->irq_enabled_lock, flags); */
	if (pn544_dev->irq_enabled) {
		pn544_dev->irq_enabled = false;
		disable_irq_nosync(pn544_dev->client->irq);
	}
	/* spin_unlock_irqrestore(&pn544_dev->irq_enabled_lock, flags); */
}

static irqreturn_t pn544_dev_irq_handler(int irq, void *dev_id)
{
	struct pn544_dev *pn544_dev = dev_id;

	if (!gpio_get_value_cansleep(pn544_dev->irq_gpio)) {
		pr_info("pn544 : pn544_dev_irq_handler error\n");
		return IRQ_HANDLED;
	}
	/* pn544_disable_irq(pn544_dev); */
#ifdef READ_IRQ_MODIFY /* DY_TEST */
	do_reading = 1;
#endif
	/* Wake up waiting readers */
	wake_up(&pn544_dev->read_wq);

#if NFC_DEBUG
	pr_info("pn544 : call\n");
#endif

	return IRQ_HANDLED;
}

static ssize_t pn544_dev_read(struct file *filp, char __user *buf,
		size_t count, loff_t *offset)
{
	struct pn544_dev *pn544_dev = filp->private_data;
	char tmp[MAX_BUFFER_SIZE];
	int ret;

	if (count > MAX_BUFFER_SIZE)
		count = MAX_BUFFER_SIZE;

	pr_debug("%s : reading %zu bytes. irq=%s\n", __func__, count,
		 gpio_get_value_cansleep(pn544_dev->irq_gpio) ? "1" : "0");

#if NFC_DEBUG
	pr_info("pn544 : + r\n");
#endif

	mutex_lock(&pn544_dev->read_mutex);

 /* wait_irq: */
	if (!gpio_get_value_cansleep(pn544_dev->irq_gpio)) {
		if (filp->f_flags & O_NONBLOCK) {
			pr_info("%s : O_NONBLOCK\n", __func__);
			ret = -EAGAIN;
			goto fail;
		}

		pn544_dev->irq_enabled = true;
#ifdef READ_IRQ_MODIFY /* DY_TEST */
		do_reading = 0;
#endif
		enable_irq(pn544_dev->client->irq);

		if (gpio_get_value_cansleep(pn544_dev->irq_gpio)) {
			pn544_disable_irq(pn544_dev);
		} else {
#ifdef READ_IRQ_MODIFY
			ret = wait_event_interruptible(pn544_dev->read_wq,
				do_reading);
#else
			ret = wait_event_interruptible(pn544_dev->read_wq,
				gpio_get_value(pn544_dev->irq_gpio));
#endif
			/* gpio_get_value(pn544_dev->irq_gpio)); */
			/* pr_info("pn544 : h\n"); */
			pn544_disable_irq(pn544_dev);

#if NFC_DEBUG
			pr_info("pn544: h\n");
#endif
#ifdef READ_IRQ_MODIFY /* DY_TEST */
			if (cancle_read == true) {
				cancle_read = false;
				ret = -1;
				goto fail;
			}
#endif

			if (ret)
				goto fail;
		}
	}
	/* Read data */
	ret = i2c_master_recv(pn544_dev->client, tmp, count);
	mutex_unlock(&pn544_dev->read_mutex);

	if (ret < 0) {
		pr_err("%s: i2c_master_recv returned %d\n", __func__, ret);
		return ret;
	}
	if (ret > count) {
		pr_err("%s: received too many bytes from i2c (%d)\n",
			__func__, ret);
		return -EIO;
	}
	if (copy_to_user(buf, tmp, ret)) {
		pr_err("%s : failed to copy to user space\n", __func__);
		return -EFAULT;
	}

	return ret;

 fail:
	mutex_unlock(&pn544_dev->read_mutex);
	pr_err("%s : wait_event_interruptible fail\n", __func__);

	return ret;
}

static ssize_t pn544_dev_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *offset)
{
	struct pn544_dev *pn544_dev;
	char tmp[MAX_BUFFER_SIZE];
	int ret;

	pn544_dev = filp->private_data;

#if NFC_DEBUG
	pr_info("pn544 : + w\n");
#endif

	if (count > MAX_BUFFER_SIZE)
		count = MAX_BUFFER_SIZE;

	if (copy_from_user(tmp, buf, count)) {
		pr_err("%s : failed to copy from user space\n", __func__);
		return -EFAULT;
	}

	pr_debug("%s : writing %zu bytes.\n", __func__, count);
	/* Write data */
	ret = i2c_master_send(pn544_dev->client, tmp, count);

#if NFC_DEBUG
	pr_info("pn544 : - w\n");
#endif

	if (ret != count) {
		pr_err("%s : i2c_master_send returned %d\n", __func__, ret);
		ret = -EIO;
	}

	return ret;
}

static int pn544_dev_open(struct inode *inode, struct file *filp)
{
/*
	struct pn544_dev *pn544_dev = container_of(filp->private_data,
						struct pn544_dev,
						pn544_device);
*/
	filp->private_data = pn544_dev_imsi;

	pr_debug("%s : %d,%d\n", __func__, imajor(inode), iminor(inode));

	return 0;
}

static long pn544_dev_ioctl(struct file *filp,
		unsigned int cmd, unsigned long arg)
{
	struct pn544_dev *pn544_dev = filp->private_data;

	switch (cmd) {
	case PN544_SET_PWR:
		if (arg == 2) {
			/* power on with firmware download (requires hw reset)
			 */
			pr_info("%s power on with firmware\n", __func__);
			gpio_set_value_cansleep(pn544_dev->ven_gpio, 1);
			gpio_set_value(pn544_dev->firm_gpio, 1);
			usleep_range(10000, 10000);
			gpio_set_value_cansleep(pn544_dev->ven_gpio, 0);
			usleep_range(10000, 10000);
			gpio_set_value_cansleep(pn544_dev->ven_gpio, 1);
			usleep_range(10000, 10000);
		} else if (arg == 1) {
			/* power on */
			pr_info("%s power on\n", __func__);
			gpio_set_value(pn544_dev->firm_gpio, 0);
			gpio_set_value_cansleep(pn544_dev->ven_gpio, 1);
			usleep_range(10000, 10000);
		} else if (arg == 0) {
			/* power off */
			pr_info("%s power off\n", __func__);
			/* printk("irq_gpio :%x ,firm_gpio %x\n",
			   pn544_dev->irq_gpio, pn544_dev->firm_gpio); */
			gpio_set_value(pn544_dev->firm_gpio, 0);
			gpio_set_value_cansleep(pn544_dev->ven_gpio, 0);
			usleep_range(10000, 10000);
#ifdef READ_IRQ_MODIFY
		} else if (arg == 3) { /* DY_TEST */
			pr_info("%s Read Cancle\n", __func__);
			cancle_read = true;
			do_reading = 1;
			wake_up(&pn544_dev->read_wq);
#endif
		} else {
			/* pr_err("%s bad arg %l\n", __func__, arg); */
			return -EINVAL;
		}
		break;
	default:
		pr_err("%s bad ioctl %u\n", __func__, cmd);
		return -EINVAL;
	}

	return 0;
}

static const struct file_operations pn544_dev_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.read = pn544_dev_read,
	.write = pn544_dev_write,
	.open = pn544_dev_open,
	.unlocked_ioctl = pn544_dev_ioctl,
};

static int pn544_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	int ret;
	int irq_num;
	struct pn544_i2c_platform_data *platform_data;
	struct pn544_dev *pn544_dev;

	platform_data = client->dev.platform_data;

	if (platform_data == NULL) {
		pr_err("%s : nfc probe fail\n", __func__);
		return -ENODEV;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("%s : need I2C_FUNC_I2C\n", __func__);
		return -ENODEV;
	}

	ret = gpio_request(platform_data->irq_gpio, "nfc_int");
	if (ret)
		return -ENODEV;
	ret = gpio_request(platform_data->ven_gpio, "nfc_ven");
	if (ret)
		goto err_ven;
	ret = gpio_request(platform_data->firm_gpio, "nfc_firm");
	if (ret)
		goto err_firm;

	pn544_dev = kzalloc(sizeof(*pn544_dev), GFP_KERNEL);
	if (pn544_dev == NULL) {
		dev_err(&client->dev,
			"failed to allocate memory for module data\n");
		ret = -ENOMEM;
		goto err_exit;
	}

	pr_info("%s : IRQ num %d\n", __func__, client->irq);

	pn544_dev->irq_gpio = platform_data->irq_gpio;
	pn544_dev->ven_gpio = platform_data->ven_gpio;
	pn544_dev->firm_gpio = platform_data->firm_gpio;
	pn544_dev->client = client;

	/* printk("irq_gpio :%x ,firm_gpio %x\n",pn544_dev->irq_gpio,
		pn544_dev->firm_gpio); */

	/* init mutex and queues */
	init_waitqueue_head(&pn544_dev->read_wq);
	mutex_init(&pn544_dev->read_mutex);
	spin_lock_init(&pn544_dev->irq_enabled_lock);

	pn544_dev->pn544_device.minor = MISC_DYNAMIC_MINOR;
	pn544_dev->pn544_device.name = "pn544";
	pn544_dev->pn544_device.fops = &pn544_dev_fops;

	ret = misc_register(&pn544_dev->pn544_device);
	if (ret) {
		pr_err("%s : misc_register failed\n", __FILE__);
		goto err_misc_register;
	}

	/* request irq.  the irq is set whenever the chip has data available
	 * for reading.  it is cleared when all data has been read.
	 */
	pr_info("%s : requesting IRQ %d\n", __func__, client->irq);
	pn544_dev->irq_enabled = true;
	gpio_direction_input(pn544_dev->irq_gpio);
	gpio_direction_output(pn544_dev->ven_gpio, 0);
	gpio_direction_output(pn544_dev->firm_gpio, 0);
	irq_num = gpio_to_irq(pn544_dev->irq_gpio);
	client->irq = irq_num;

	ret = request_threaded_irq(irq_num, NULL, pn544_dev_irq_handler,
			IRQF_TRIGGER_RISING, "pn544", pn544_dev);
	if (ret) {
		dev_err(&client->dev, "request_irq failed\n");
		goto err_request_irq_failed;
	}
	pn544_disable_irq(pn544_dev);
#if defined(CONFIG_TARGET_LOCALE_EUR_U1_NFC)
	enable_irq_wake(client->irq);
#endif
	i2c_set_clientdata(client, pn544_dev);
	pn544_dev_imsi = pn544_dev;
	/* printk("pn544 prove success\n"); */

	return 0;

 err_request_irq_failed:
	misc_deregister(&pn544_dev->pn544_device);
 err_misc_register:
	mutex_destroy(&pn544_dev->read_mutex);
	kfree(pn544_dev);
 err_exit:
	gpio_free(platform_data->firm_gpio);
 err_firm:
	gpio_free(platform_data->ven_gpio);
 err_ven:
	gpio_free(platform_data->irq_gpio);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int pn544_remove(struct i2c_client *client)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct pn544_dev *dev = i2c_get_clientdata(client);

	free_irq(client->irq, dev);
	misc_deregister(&dev->device);
	mutex_lock(&list_lock);
	list_del(&dev->node);
	mutex_unlock(&list_lock);
	i2c_set_clientdata(client, NULL);
	wake_lock_destroy(&dev->wake_lock);
	pn544_gpio_release(dev->pdata);
	mutex_destroy(&dev->lock);
	kfree(dev->pdata);
	kfree(dev);
	return 0;
}

static int pn544_pm_suspend(struct device *dev)
{
	int ret;
	struct pn544_dev *d = dev_get_drvdata(dev);

	dev_dbg(d->dev, "%s:\n", __func__);
	if (!mutex_trylock(&d->lock))
		return -EAGAIN;
	if (d->busy) {
		if (atomic_read(&d->res_ready) || d->res_size) {
			wake_lock_timeout(&d->wake_lock,
				PN544_WAKE_LOCK_TIMEOUT);
			mutex_unlock(&d->lock);
			return -EAGAIN;
		}
		ret = irq_set_irq_wake(d->i2c_client->irq, 1);
		if (IS_ERR_VALUE(ret))
			dev_err(dev, "%s: irq wake err %d\n", __func__, ret);
	}
	d->suspended = true;
	mutex_unlock(&d->lock);
	return 0;
}

static int pn544_pm_resume(struct device *dev)
{
	struct pn544_dev *d = dev_get_drvdata(dev);
	int ret;

	dev_dbg(d->dev, "%s:\n", __func__);
	mutex_lock(&d->lock);
	if (d->busy) {
		ret = irq_set_irq_wake(d->i2c_client->irq, 0);
		if (IS_ERR_VALUE(ret))
			dev_err(dev, "%s: irq wake err %d\n", __func__, ret);
	}
	d->suspended = false;
	mutex_unlock(&d->lock);
	return 0;
}

static const struct i2c_device_id pn544_id[] = {
	{ PN544_DEVICE_NAME, 0 },
	{ },
};

static struct of_device_id pn544_match_table[] = {
	{ .compatible = "nxp,pn544", },
	{ },
};

static const struct dev_pm_ops pn544_pm_ops = {
	.suspend	= pn544_pm_suspend,
	.resume		= pn544_pm_resume,
};

static struct i2c_driver pn544_driver = {
	.id_table	= pn544_id,
	.probe		= pn544_probe,
	.remove		= pn544_remove,
	.driver		= {
		.owner		= THIS_MODULE,
		.name		= PN544_DEVICE_NAME,
		.pm		= &pn544_pm_ops,
		.of_match_table	= pn544_match_table,
	},
};

static int __init pn544_dev_init(void)
{
	return i2c_add_driver(&pn544_driver);
}

static void __exit pn544_dev_exit(void)
{
	i2c_del_driver(&pn544_driver);
}

module_init(pn544_dev_init);
module_exit(pn544_dev_exit);

MODULE_DESCRIPTION("NFC PN544 driver");
MODULE_LICENSE("GPL v2");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct pn544_dev *pn544_dev;

	pn544_dev = i2c_get_clientdata(client);

	free_irq(client->irq, pn544_dev);
	misc_deregister(&pn544_dev->pn544_device);
	mutex_destroy(&pn544_dev->read_mutex);
	gpio_free(pn544_dev->irq_gpio);
	gpio_free(pn544_dev->ven_gpio);
	gpio_free(pn544_dev->firm_gpio);
	kfree(pn544_dev);

	return 0;
}

static void pn544_shutdown(struct i2c_client *client)
{
	struct pn544_dev *pn544_dev;

	pn544_dev = i2c_get_clientdata(client);
	pr_info("%s\n", __func__);
	gpio_set_value_cansleep(pn544_dev->ven_gpio, 0);

	free_irq(client->irq, pn544_dev);
	misc_deregister(&pn544_dev->pn544_device);
	mutex_destroy(&pn544_dev->read_mutex);
	gpio_free(pn544_dev->irq_gpio);
	gpio_free(pn544_dev->ven_gpio);
	gpio_free(pn544_dev->firm_gpio);
	kfree(pn544_dev);

}

static const struct i2c_device_id pn544_id[] = {
	{"pn544", 0},
	{}
};

static struct i2c_driver pn544_driver = {
	.id_table = pn544_id,
	.probe = pn544_probe,
	.remove = pn544_remove,
	.shutdown = pn544_shutdown,
	.driver = {
			.owner = THIS_MODULE,
			.name = "pn544",
	},
};

/*
 * module load/unload record keeping
 */

static int __init pn544_dev_init(void)
{
	pr_info("Loading pn544 driver\n");
	return i2c_add_driver(&pn544_driver);
}

module_init(pn544_dev_init);

static void __exit pn544_dev_exit(void)
{
	pr_info("Unloading pn544 driver\n");
	i2c_del_driver(&pn544_driver);
}

module_exit(pn544_dev_exit);

MODULE_AUTHOR("Sylvain Fonteneau");
MODULE_DESCRIPTION("NFC PN544 driver");
MODULE_LICENSE("GPL");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
