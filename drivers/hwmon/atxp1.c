/*
<<<<<<< HEAD
<<<<<<< HEAD
 * atxp1.c - kernel module for setting CPU VID and general purpose
 *	     I/Os using the Attansic ATXP1 chip.
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
    atxp1.c - kernel module for setting CPU VID and general purpose
                     I/Os using the Attansic ATXP1 chip.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/hwmon.h>
#include <linux/hwmon-vid.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("System voltages control via Attansic ATXP1");
MODULE_VERSION("0.6.3");
MODULE_AUTHOR("Sebastian Witt <se.witt@gmx.net>");

#define ATXP1_VID	0x00
#define ATXP1_CVID	0x01
#define ATXP1_GPIO1	0x06
#define ATXP1_GPIO2	0x0a
#define ATXP1_VIDENA	0x20
#define ATXP1_VIDMASK	0x1f
#define ATXP1_GPIO1MASK	0x0f

static const unsigned short normal_i2c[] = { 0x37, 0x4e, I2C_CLIENT_END };

static int atxp1_probe(struct i2c_client *client,
		       const struct i2c_device_id *id);
static int atxp1_remove(struct i2c_client *client);
<<<<<<< HEAD
<<<<<<< HEAD
static struct atxp1_data *atxp1_update_device(struct device *dev);
=======
static struct atxp1_data * atxp1_update_device(struct device *dev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static struct atxp1_data * atxp1_update_device(struct device *dev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int atxp1_detect(struct i2c_client *client, struct i2c_board_info *info);

static const struct i2c_device_id atxp1_id[] = {
	{ "atxp1", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, atxp1_id);

static struct i2c_driver atxp1_driver = {
	.class		= I2C_CLASS_HWMON,
	.driver = {
		.name	= "atxp1",
	},
	.probe		= atxp1_probe,
	.remove		= atxp1_remove,
	.id_table	= atxp1_id,
	.detect		= atxp1_detect,
	.address_list	= normal_i2c,
};

struct atxp1_data {
	struct device *hwmon_dev;
	struct mutex update_lock;
	unsigned long last_updated;
	u8 valid;
	struct {
		u8 vid;		/* VID output register */
		u8 cpu_vid; /* VID input from CPU */
		u8 gpio1;   /* General purpose I/O register 1 */
		u8 gpio2;   /* General purpose I/O register 2 */
	} reg;
	u8 vrm;			/* Detected CPU VRM */
};

<<<<<<< HEAD
<<<<<<< HEAD
static struct atxp1_data *atxp1_update_device(struct device *dev)
=======
static struct atxp1_data * atxp1_update_device(struct device *dev)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static struct atxp1_data * atxp1_update_device(struct device *dev)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct i2c_client *client;
	struct atxp1_data *data;

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {

		/* Update local register data */
		data->reg.vid = i2c_smbus_read_byte_data(client, ATXP1_VID);
<<<<<<< HEAD
<<<<<<< HEAD
		data->reg.cpu_vid = i2c_smbus_read_byte_data(client,
							     ATXP1_CVID);
=======
		data->reg.cpu_vid = i2c_smbus_read_byte_data(client, ATXP1_CVID);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		data->reg.cpu_vid = i2c_smbus_read_byte_data(client, ATXP1_CVID);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		data->reg.gpio1 = i2c_smbus_read_byte_data(client, ATXP1_GPIO1);
		data->reg.gpio2 = i2c_smbus_read_byte_data(client, ATXP1_GPIO2);

		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

<<<<<<< HEAD
<<<<<<< HEAD
	return data;
}

/* sys file functions for cpu0_vid */
static ssize_t atxp1_showvcore(struct device *dev,
			       struct device_attribute *attr, char *buf)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return(data);
}

/* sys file functions for cpu0_vid */
static ssize_t atxp1_showvcore(struct device *dev, struct device_attribute *attr, char *buf)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int size;
	struct atxp1_data *data;

	data = atxp1_update_device(dev);

<<<<<<< HEAD
<<<<<<< HEAD
	size = sprintf(buf, "%d\n", vid_from_reg(data->reg.vid & ATXP1_VIDMASK,
						 data->vrm));
=======
	size = sprintf(buf, "%d\n", vid_from_reg(data->reg.vid & ATXP1_VIDMASK, data->vrm));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	size = sprintf(buf, "%d\n", vid_from_reg(data->reg.vid & ATXP1_VIDMASK, data->vrm));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return size;
}

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t atxp1_storevcore(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
=======
static ssize_t atxp1_storevcore(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static ssize_t atxp1_storevcore(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct atxp1_data *data;
	struct i2c_client *client;
	int vid, cvid;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long vcore;
	int err;
=======
	unsigned int vcore;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	unsigned int vcore;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	client = to_i2c_client(dev);
	data = atxp1_update_device(dev);

<<<<<<< HEAD
<<<<<<< HEAD
	err = kstrtoul(buf, 10, &vcore);
	if (err)
		return err;

=======
	vcore = simple_strtoul(buf, NULL, 10);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	vcore = simple_strtoul(buf, NULL, 10);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	vcore /= 25;
	vcore *= 25;

	/* Calculate VID */
	vid = vid_to_reg(vcore, data->vrm);

	if (vid < 0) {
		dev_err(dev, "VID calculation failed.\n");
		return -1;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * If output enabled, use control register value.
	 * Otherwise original CPU VID
	 */
=======
	/* If output enabled, use control register value. Otherwise original CPU VID */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* If output enabled, use control register value. Otherwise original CPU VID */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (data->reg.vid & ATXP1_VIDENA)
		cvid = data->reg.vid & ATXP1_VIDMASK;
	else
		cvid = data->reg.cpu_vid;

	/* Nothing changed, aborting */
	if (vid == cvid)
		return count;

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(dev, "Setting VCore to %d mV (0x%02x)\n", (int)vcore, vid);

	/* Write every 25 mV step to increase stability */
	if (cvid > vid) {
		for (; cvid >= vid; cvid--)
			i2c_smbus_write_byte_data(client,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	} else {
		for (; cvid <= vid; cvid++)
			i2c_smbus_write_byte_data(client,
						ATXP1_VID, cvid | ATXP1_VIDENA);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev_dbg(dev, "Setting VCore to %d mV (0x%02x)\n", vcore, vid);

	/* Write every 25 mV step to increase stability */
	if (cvid > vid) {
		for (; cvid >= vid; cvid--) {
        		i2c_smbus_write_byte_data(client, ATXP1_VID, cvid | ATXP1_VIDENA);
		}
	}
	else {
		for (; cvid <= vid; cvid++) {
        		i2c_smbus_write_byte_data(client, ATXP1_VID, cvid | ATXP1_VIDENA);
		}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	data->valid = 0;

	return count;
}

<<<<<<< HEAD
<<<<<<< HEAD
/*
 * CPU core reference voltage
 * unit: millivolt
 */
static DEVICE_ATTR(cpu0_vid, S_IRUGO | S_IWUSR, atxp1_showvcore,
		   atxp1_storevcore);

/* sys file functions for GPIO1 */
static ssize_t atxp1_showgpio1(struct device *dev,
			       struct device_attribute *attr, char *buf)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* CPU core reference voltage
    unit: millivolt
*/
static DEVICE_ATTR(cpu0_vid, S_IRUGO | S_IWUSR, atxp1_showvcore, atxp1_storevcore);

/* sys file functions for GPIO1 */
static ssize_t atxp1_showgpio1(struct device *dev, struct device_attribute *attr, char *buf)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int size;
	struct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = sprintf(buf, "0x%02x\n", data->reg.gpio1 & ATXP1_GPIO1MASK);

	return size;
}

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t atxp1_storegpio1(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
	struct atxp1_data *data;
	struct i2c_client *client;
	unsigned long value;
	int err;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t atxp1_storegpio1(struct device *dev, struct device_attribute *attr, const char*buf, size_t count)
{
	struct atxp1_data *data;
	struct i2c_client *client;
	unsigned int value;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	client = to_i2c_client(dev);
	data = atxp1_update_device(dev);

<<<<<<< HEAD
<<<<<<< HEAD
	err = kstrtoul(buf, 16, &value);
	if (err)
		return err;
=======
	value = simple_strtoul(buf, NULL, 16);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	value = simple_strtoul(buf, NULL, 16);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	value &= ATXP1_GPIO1MASK;

	if (value != (data->reg.gpio1 & ATXP1_GPIO1MASK)) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_info(dev, "Writing 0x%x to GPIO1.\n", (unsigned int)value);
=======
		dev_info(dev, "Writing 0x%x to GPIO1.\n", value);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_info(dev, "Writing 0x%x to GPIO1.\n", value);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		i2c_smbus_write_byte_data(client, ATXP1_GPIO1, value);

		data->valid = 0;
	}

	return count;
}

<<<<<<< HEAD
<<<<<<< HEAD
/*
 * GPIO1 data register
 * unit: Four bit as hex (e.g. 0x0f)
 */
static DEVICE_ATTR(gpio1, S_IRUGO | S_IWUSR, atxp1_showgpio1, atxp1_storegpio1);

/* sys file functions for GPIO2 */
static ssize_t atxp1_showgpio2(struct device *dev,
			       struct device_attribute *attr, char *buf)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* GPIO1 data register
    unit: Four bit as hex (e.g. 0x0f)
*/
static DEVICE_ATTR(gpio1, S_IRUGO | S_IWUSR, atxp1_showgpio1, atxp1_storegpio1);

/* sys file functions for GPIO2 */
static ssize_t atxp1_showgpio2(struct device *dev, struct device_attribute *attr, char *buf)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int size;
	struct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = sprintf(buf, "0x%02x\n", data->reg.gpio2);

	return size;
}

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t atxp1_storegpio2(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct atxp1_data *data = atxp1_update_device(dev);
	struct i2c_client *client = to_i2c_client(dev);
	unsigned long value;
	int err;

	err = kstrtoul(buf, 16, &value);
	if (err)
		return err;
	value &= 0xff;

	if (value != data->reg.gpio2) {
		dev_info(dev, "Writing 0x%x to GPIO1.\n", (unsigned int)value);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t atxp1_storegpio2(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct atxp1_data *data;
	struct i2c_client *client;
	unsigned int value;

	client = to_i2c_client(dev);
	data = atxp1_update_device(dev);

	value = simple_strtoul(buf, NULL, 16) & 0xff;

	if (value != data->reg.gpio2) {
		dev_info(dev, "Writing 0x%x to GPIO1.\n", value);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		i2c_smbus_write_byte_data(client, ATXP1_GPIO2, value);

		data->valid = 0;
	}

	return count;
}

<<<<<<< HEAD
<<<<<<< HEAD
/*
 * GPIO2 data register
 * unit: Eight bit as hex (e.g. 0xff)
 */
=======
/* GPIO2 data register
    unit: Eight bit as hex (e.g. 0xff)
*/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/* GPIO2 data register
    unit: Eight bit as hex (e.g. 0xff)
*/
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static DEVICE_ATTR(gpio2, S_IRUGO | S_IWUSR, atxp1_showgpio2, atxp1_storegpio2);

static struct attribute *atxp1_attributes[] = {
	&dev_attr_gpio1.attr,
	&dev_attr_gpio2.attr,
	&dev_attr_cpu0_vid.attr,
	NULL
};

static const struct attribute_group atxp1_group = {
	.attrs = atxp1_attributes,
};


/* Return 0 if detection is successful, -ENODEV otherwise */
static int atxp1_detect(struct i2c_client *new_client,
			struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = new_client->adapter;

	u8 temp;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detect ATXP1, checking if vendor ID registers are all zero */
	if (!((i2c_smbus_read_byte_data(new_client, 0x3e) == 0) &&
	     (i2c_smbus_read_byte_data(new_client, 0x3f) == 0) &&
	     (i2c_smbus_read_byte_data(new_client, 0xfe) == 0) &&
	     (i2c_smbus_read_byte_data(new_client, 0xff) == 0)))
		return -ENODEV;

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * No vendor ID, now checking if registers 0x10,0x11 (non-existent)
	 * showing the same as register 0x00
	 */
=======
	/* No vendor ID, now checking if registers 0x10,0x11 (non-existent)
	 * showing the same as register 0x00 */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* No vendor ID, now checking if registers 0x10,0x11 (non-existent)
	 * showing the same as register 0x00 */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	temp = i2c_smbus_read_byte_data(new_client, 0x00);

	if (!((i2c_smbus_read_byte_data(new_client, 0x10) == temp) &&
	      (i2c_smbus_read_byte_data(new_client, 0x11) == temp)))
		return -ENODEV;

	/* Get VRM */
	temp = vid_which_vrm();

	if ((temp != 90) && (temp != 91)) {
		dev_err(&adapter->dev, "atxp1: Not supporting VRM %d.%d\n",
				temp / 10, temp % 10);
		return -ENODEV;
	}

	strlcpy(info->type, "atxp1", I2C_NAME_SIZE);

	return 0;
}

static int atxp1_probe(struct i2c_client *new_client,
		       const struct i2c_device_id *id)
{
	struct atxp1_data *data;
	int err;

	data = kzalloc(sizeof(struct atxp1_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	/* Get VRM */
	data->vrm = vid_which_vrm();

	i2c_set_clientdata(new_client, data);
	data->valid = 0;

	mutex_init(&data->update_lock);

	/* Register sysfs hooks */
<<<<<<< HEAD
<<<<<<< HEAD
	err = sysfs_create_group(&new_client->dev.kobj, &atxp1_group);
	if (err)
=======
	if ((err = sysfs_create_group(&new_client->dev.kobj, &atxp1_group)))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if ((err = sysfs_create_group(&new_client->dev.kobj, &atxp1_group)))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto exit_free;

	data->hwmon_dev = hwmon_device_register(&new_client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	dev_info(&new_client->dev, "Using VRM: %d.%d\n",
			 data->vrm / 10, data->vrm % 10);

	return 0;

exit_remove_files:
	sysfs_remove_group(&new_client->dev.kobj, &atxp1_group);
exit_free:
	kfree(data);
exit:
	return err;
};

static int atxp1_remove(struct i2c_client *client)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct atxp1_data *data = i2c_get_clientdata(client);
=======
	struct atxp1_data * data = i2c_get_clientdata(client);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct atxp1_data * data = i2c_get_clientdata(client);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&client->dev.kobj, &atxp1_group);

	kfree(data);

	return 0;
};

<<<<<<< HEAD
<<<<<<< HEAD
module_i2c_driver(atxp1_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init atxp1_init(void)
{
	return i2c_add_driver(&atxp1_driver);
};

static void __exit atxp1_exit(void)
{
	i2c_del_driver(&atxp1_driver);
};

module_init(atxp1_init);
module_exit(atxp1_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
