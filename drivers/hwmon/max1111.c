/*
 * max1111.c - +2.7V, Low-Power, Multichannel, Serial 8-bit ADCs
 *
 * Based on arch/arm/mach-pxa/corgi_ssp.c
 *
 * Copyright (C) 2004-2005 Richard Purdie
 *
 * Copyright (C) 2008 Marvell International Ltd.
<<<<<<< HEAD
<<<<<<< HEAD
 *	Eric Miao <eric.miao@marvell.com>
=======
 * 	Eric Miao <eric.miao@marvell.com>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * 	Eric Miao <eric.miao@marvell.com>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  publishhed by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/hwmon.h>
#include <linux/hwmon-sysfs.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>

#define MAX1111_TX_BUF_SIZE	1
#define MAX1111_RX_BUF_SIZE	2

/* MAX1111 Commands */
#define MAX1111_CTRL_PD0      (1u << 0)
#define MAX1111_CTRL_PD1      (1u << 1)
#define MAX1111_CTRL_SGL      (1u << 2)
#define MAX1111_CTRL_UNI      (1u << 3)
#define MAX1111_CTRL_SEL_SH   (5)	/* NOTE: bit 4 is ignored */
#define MAX1111_CTRL_STR      (1u << 7)

struct max1111_data {
	struct spi_device	*spi;
	struct device		*hwmon_dev;
	struct spi_message	msg;
	struct spi_transfer	xfer[2];
<<<<<<< HEAD
<<<<<<< HEAD
	uint8_t tx_buf[MAX1111_TX_BUF_SIZE];
	uint8_t rx_buf[MAX1111_RX_BUF_SIZE];
=======
	uint8_t *tx_buf;
	uint8_t *rx_buf;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	uint8_t *tx_buf;
	uint8_t *rx_buf;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mutex		drvdata_lock;
	/* protect msg, xfer and buffers from multiple access */
};

static int max1111_read(struct device *dev, int channel)
{
	struct max1111_data *data = dev_get_drvdata(dev);
	uint8_t v1, v2;
	int err;

	/* writing to drvdata struct is not thread safe, wait on mutex */
	mutex_lock(&data->drvdata_lock);

	data->tx_buf[0] = (channel << MAX1111_CTRL_SEL_SH) |
		MAX1111_CTRL_PD0 | MAX1111_CTRL_PD1 |
		MAX1111_CTRL_SGL | MAX1111_CTRL_UNI | MAX1111_CTRL_STR;

	err = spi_sync(data->spi, &data->msg);
	if (err < 0) {
		dev_err(dev, "spi_sync failed with %d\n", err);
		mutex_unlock(&data->drvdata_lock);
		return err;
	}

	v1 = data->rx_buf[0];
	v2 = data->rx_buf[1];

	mutex_unlock(&data->drvdata_lock);

	if ((v1 & 0xc0) || (v2 & 0x3f))
		return -EINVAL;

	return (v1 << 2) | (v2 >> 6);
}

#ifdef CONFIG_SHARPSL_PM
static struct max1111_data *the_max1111;

int max1111_read_channel(int channel)
{
	return max1111_read(&the_max1111->spi->dev, channel);
}
EXPORT_SYMBOL(max1111_read_channel);
#endif

/*
 * NOTE: SPI devices do not have a default 'name' attribute, which is
 * likely to be used by hwmon applications to distinguish between
 * different devices, explicitly add a name attribute here.
 */
static ssize_t show_name(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "max1111\n");
}

static ssize_t show_adc(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int channel = to_sensor_dev_attr(attr)->index;
	int ret;

	ret = max1111_read(dev, channel);
	if (ret < 0)
		return ret;

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * assume the reference voltage to be 2.048V, with an 8-bit sample,
	 * the LSB weight is 8mV
	 */
	return sprintf(buf, "%d\n", ret * 8);
}

#define MAX1111_ADC_ATTR(_id)		\
	SENSOR_DEVICE_ATTR(in##_id##_input, S_IRUGO, show_adc, NULL, _id)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sprintf(buf, "%d\n", ret);
}

#define MAX1111_ADC_ATTR(_id)		\
	SENSOR_DEVICE_ATTR(adc##_id##_in, S_IRUGO, show_adc, NULL, _id)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static DEVICE_ATTR(name, S_IRUGO, show_name, NULL);
static MAX1111_ADC_ATTR(0);
static MAX1111_ADC_ATTR(1);
static MAX1111_ADC_ATTR(2);
static MAX1111_ADC_ATTR(3);

static struct attribute *max1111_attributes[] = {
	&dev_attr_name.attr,
<<<<<<< HEAD
<<<<<<< HEAD
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&sensor_dev_attr_adc0_in.dev_attr.attr,
	&sensor_dev_attr_adc1_in.dev_attr.attr,
	&sensor_dev_attr_adc2_in.dev_attr.attr,
	&sensor_dev_attr_adc3_in.dev_attr.attr,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	NULL,
};

static const struct attribute_group max1111_attr_group = {
	.attrs	= max1111_attributes,
};

<<<<<<< HEAD
<<<<<<< HEAD
static int __devinit setup_transfer(struct max1111_data *data)
=======
static int setup_transfer(struct max1111_data *data)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int setup_transfer(struct max1111_data *data)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct spi_message *m;
	struct spi_transfer *x;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	data->tx_buf = kmalloc(MAX1111_TX_BUF_SIZE, GFP_KERNEL);
	if (!data->tx_buf)
		return -ENOMEM;

	data->rx_buf = kmalloc(MAX1111_RX_BUF_SIZE, GFP_KERNEL);
	if (!data->rx_buf) {
		kfree(data->tx_buf);
		return -ENOMEM;
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	m = &data->msg;
	x = &data->xfer[0];

	spi_message_init(m);

	x->tx_buf = &data->tx_buf[0];
<<<<<<< HEAD
<<<<<<< HEAD
	x->len = MAX1111_TX_BUF_SIZE;
=======
	x->len = 1;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	x->len = 1;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spi_message_add_tail(x, m);

	x++;
	x->rx_buf = &data->rx_buf[0];
<<<<<<< HEAD
<<<<<<< HEAD
	x->len = MAX1111_RX_BUF_SIZE;
=======
	x->len = 2;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	x->len = 2;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spi_message_add_tail(x, m);

	return 0;
}

static int __devinit max1111_probe(struct spi_device *spi)
{
	struct max1111_data *data;
	int err;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	err = spi_setup(spi);
	if (err < 0)
		return err;

	data = kzalloc(sizeof(struct max1111_data), GFP_KERNEL);
	if (data == NULL) {
		dev_err(&spi->dev, "failed to allocate memory\n");
		return -ENOMEM;
	}

	err = setup_transfer(data);
	if (err)
		goto err_free_data;

	mutex_init(&data->drvdata_lock);

	data->spi = spi;
	spi_set_drvdata(spi, data);

	err = sysfs_create_group(&spi->dev.kobj, &max1111_attr_group);
	if (err) {
		dev_err(&spi->dev, "failed to create attribute group\n");
<<<<<<< HEAD
<<<<<<< HEAD
		goto err_free_data;
=======
		goto err_free_all;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto err_free_all;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	data->hwmon_dev = hwmon_device_register(&spi->dev);
	if (IS_ERR(data->hwmon_dev)) {
		dev_err(&spi->dev, "failed to create hwmon device\n");
		err = PTR_ERR(data->hwmon_dev);
		goto err_remove;
	}

#ifdef CONFIG_SHARPSL_PM
	the_max1111 = data;
#endif
	return 0;

err_remove:
	sysfs_remove_group(&spi->dev.kobj, &max1111_attr_group);
<<<<<<< HEAD
<<<<<<< HEAD
=======
err_free_all:
	kfree(data->rx_buf);
	kfree(data->tx_buf);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
err_free_all:
	kfree(data->rx_buf);
	kfree(data->tx_buf);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
err_free_data:
	kfree(data);
	return err;
}

static int __devexit max1111_remove(struct spi_device *spi)
{
	struct max1111_data *data = spi_get_drvdata(spi);

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&spi->dev.kobj, &max1111_attr_group);
	mutex_destroy(&data->drvdata_lock);
<<<<<<< HEAD
<<<<<<< HEAD
=======
	kfree(data->rx_buf);
	kfree(data->tx_buf);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	kfree(data->rx_buf);
	kfree(data->tx_buf);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	kfree(data);
	return 0;
}

static struct spi_driver max1111_driver = {
	.driver		= {
		.name	= "max1111",
		.owner	= THIS_MODULE,
	},
	.probe		= max1111_probe,
	.remove		= __devexit_p(max1111_remove),
};

<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(max1111_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init max1111_init(void)
{
	return spi_register_driver(&max1111_driver);
}
module_init(max1111_init);

static void __exit max1111_exit(void)
{
	spi_unregister_driver(&max1111_driver);
}
module_exit(max1111_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_DESCRIPTION("MAX1111 ADC Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:max1111");
