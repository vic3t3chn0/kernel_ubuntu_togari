/*
 * ADIS16130 Digital Output, High Precision Angular Rate Sensor driver
 *
 * Copyright 2010 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/list.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>

#include "../iio.h"
#include "../sysfs.h"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include "../iio.h"
#include "../sysfs.h"
#include "gyro.h"
#include "../adc/adc.h"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define ADIS16130_CON         0x0
#define ADIS16130_CON_RD      (1 << 6)
#define ADIS16130_IOP         0x1

/* 1 = data-ready signal low when unread data on all channels; */
#define ADIS16130_IOP_ALL_RDY (1 << 3)
#define ADIS16130_IOP_SYNC    (1 << 0) /* 1 = synchronization enabled */
#define ADIS16130_RATEDATA    0x8 /* Gyroscope output, rate of rotation */
#define ADIS16130_TEMPDATA    0xA /* Temperature output */
#define ADIS16130_RATECS      0x28 /* Gyroscope channel setup */
#define ADIS16130_RATECS_EN   (1 << 3) /* 1 = channel enable; */
#define ADIS16130_TEMPCS      0x2A /* Temperature channel setup */
#define ADIS16130_TEMPCS_EN   (1 << 3)
#define ADIS16130_RATECONV    0x30
#define ADIS16130_TEMPCONV    0x32
#define ADIS16130_MODE        0x38
#define ADIS16130_MODE_24BIT  (1 << 1) /* 1 = 24-bit resolution; */

/**
 * struct adis16130_state - device instance specific data
 * @us:			actual spi_device to write data
<<<<<<< HEAD
<<<<<<< HEAD
=======
 * @indio_dev:		industrial I/O device structure
 * @mode:		24 bits (1) or 16 bits (0)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @indio_dev:		industrial I/O device structure
 * @mode:		24 bits (1) or 16 bits (0)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @buf_lock:		mutex to protect tx and rx
 * @buf:		unified tx/rx buffer
 **/
struct adis16130_state {
	struct spi_device		*us;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct iio_dev			*indio_dev;
	u32                             mode;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_dev			*indio_dev;
	u32                             mode;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mutex			buf_lock;
	u8				buf[4] ____cacheline_aligned;
};

<<<<<<< HEAD
<<<<<<< HEAD
static int adis16130_spi_read(struct iio_dev *indio_dev, u8 reg_addr, u32 *val)
{
	int ret;
	struct adis16130_state *st = iio_priv(indio_dev);
	struct spi_message msg;
	struct spi_transfer xfer = {
		.tx_buf = st->buf,
		.rx_buf = st->buf,
		.len = 4,
	};
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int adis16130_spi_write(struct device *dev, u8 reg_addr,
		u8 val)
{
	int ret;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct adis16130_state *st = iio_dev_get_devdata(indio_dev);

	mutex_lock(&st->buf_lock);
	st->buf[0] = reg_addr;
	st->buf[1] = val;

	ret = spi_write(st->us, st->buf, 2);
	mutex_unlock(&st->buf_lock);

	return ret;
}

static int adis16130_spi_read(struct device *dev, u8 reg_addr,
		u32 *val)
{
	int ret;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct adis16130_state *st = iio_dev_get_devdata(indio_dev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&st->buf_lock);

	st->buf[0] = ADIS16130_CON_RD | reg_addr;
<<<<<<< HEAD
<<<<<<< HEAD
	st->buf[1] = st->buf[2] = st->buf[3] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->us, &msg);
	ret = spi_read(st->us, st->buf, 4);

	if (ret == 0)
		*val = (st->buf[1] << 16) | (st->buf[2] << 8) | st->buf[3];
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (st->mode)
		ret = spi_read(st->us, st->buf, 4);
	else
		ret = spi_read(st->us, st->buf, 3);

	if (ret == 0) {
		if (st->mode)
			*val = (st->buf[1] << 16) |
				(st->buf[2] << 8) |
				st->buf[3];
		else
			*val = (st->buf[1] << 8) | st->buf[2];
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_unlock(&st->buf_lock);

	return ret;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int adis16130_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	int ret;
	u32 temp;

	/* Take the iio_dev status lock */
	mutex_lock(&indio_dev->mlock);
	ret =  adis16130_spi_read(indio_dev, chan->address, &temp);
	mutex_unlock(&indio_dev->mlock);
	if (ret)
		return ret;
	*val = temp;
	return IIO_VAL_INT;
}

static const struct iio_chan_spec adis16130_channels[] = {
	{
		.type = IIO_ANGL_VEL,
		.modified = 1,
		.channel2 = IIO_MOD_Z,
		.address = ADIS16130_RATEDATA,
	}, {
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 0,
		.address = ADIS16130_TEMPDATA,
	}
};

static const struct iio_info adis16130_info = {
	.read_raw = &adis16130_read_raw,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t adis16130_val_read(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	u32 val;
	ssize_t ret;

	/* Take the iio_dev status lock */
	mutex_lock(&indio_dev->mlock);
	ret =  adis16130_spi_read(dev, this_attr->address, &val);
	mutex_unlock(&indio_dev->mlock);

	if (ret == 0)
		return sprintf(buf, "%d\n", val);
	else
		return ret;
}

static ssize_t adis16130_bitsmode_read(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct adis16130_state *st = iio_dev_get_devdata(indio_dev);

	if (st->mode == 1)
		return sprintf(buf, "s24\n");
	else
		return sprintf(buf, "s16\n");
}

static ssize_t adis16130_bitsmode_write(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t len)
{
	int ret;
	u8 val;

	if (sysfs_streq(buf, "s16"))
		val = 0;
	else if (sysfs_streq(buf, "s24"))
		val = 1;
	else
		return -EINVAL;

	ret = adis16130_spi_write(dev, ADIS16130_MODE, val);

	return ret ? ret : len;
}
static IIO_DEVICE_ATTR(temp_raw, S_IRUGO, adis16130_val_read, NULL,
		      ADIS16130_TEMPDATA);

static IIO_DEV_ATTR_GYRO_Z(adis16130_val_read, ADIS16130_RATEDATA);

static IIO_DEVICE_ATTR(gyro_z_type, S_IWUSR | S_IRUGO, adis16130_bitsmode_read,
			adis16130_bitsmode_write,
			ADIS16130_MODE);

static IIO_CONST_ATTR(gyro_z_type_available, "s16 s24");

static struct attribute *adis16130_attributes[] = {
	&iio_dev_attr_temp_raw.dev_attr.attr,
	&iio_dev_attr_gyro_z_raw.dev_attr.attr,
	&iio_dev_attr_gyro_z_type.dev_attr.attr,
	&iio_const_attr_gyro_z_type_available.dev_attr.attr,
	NULL
};

static const struct attribute_group adis16130_attribute_group = {
	.attrs = adis16130_attributes,
};

static const struct iio_info adis16130_info = {
	.attrs = &adis16130_attribute_group,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.driver_module = THIS_MODULE,
};

static int __devinit adis16130_probe(struct spi_device *spi)
{
	int ret;
<<<<<<< HEAD
<<<<<<< HEAD
	struct adis16130_state *st;
	struct iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = iio_allocate_device(sizeof(*st));
	if (indio_dev == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	st = iio_priv(indio_dev);
	/* this is only used for removal purposes */
	spi_set_drvdata(spi, indio_dev);
	st->us = spi;
	mutex_init(&st->buf_lock);
	indio_dev->name = spi->dev.driver->name;
	indio_dev->channels = adis16130_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16130_channels);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &adis16130_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = iio_device_register(indio_dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct adis16130_state *st = kzalloc(sizeof *st, GFP_KERNEL);
	if (!st) {
		ret =  -ENOMEM;
		goto error_ret;
	}
	/* this is only used for removal purposes */
	spi_set_drvdata(spi, st);
	st->us = spi;
	mutex_init(&st->buf_lock);
	/* setup the industrialio driver allocated elements */
	st->indio_dev = iio_allocate_device(0);
	if (st->indio_dev == NULL) {
		ret = -ENOMEM;
		goto error_free_st;
	}

	st->indio_dev->name = spi->dev.driver->name;
	st->indio_dev->dev.parent = &spi->dev;
	st->indio_dev->info = &adis16130_info;
	st->indio_dev->dev_data = (void *)(st);
	st->indio_dev->modes = INDIO_DIRECT_MODE;
	st->mode = 1;

	ret = iio_device_register(st->indio_dev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret)
		goto error_free_dev;

	return 0;

error_free_dev:
<<<<<<< HEAD
<<<<<<< HEAD
	iio_free_device(indio_dev);

=======
	iio_free_device(st->indio_dev);
error_free_st:
	kfree(st);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	iio_free_device(st->indio_dev);
error_free_st:
	kfree(st);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
error_ret:
	return ret;
}

/* fixme, confirm ordering in this function */
static int adis16130_remove(struct spi_device *spi)
{
<<<<<<< HEAD
<<<<<<< HEAD
	iio_device_unregister(spi_get_drvdata(spi));
	iio_free_device(spi_get_drvdata(spi));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct adis16130_state *st = spi_get_drvdata(spi);
	struct iio_dev *indio_dev = st->indio_dev;

	iio_device_unregister(indio_dev);
	kfree(st);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static struct spi_driver adis16130_driver = {
	.driver = {
		.name = "adis16130",
		.owner = THIS_MODULE,
	},
	.probe = adis16130_probe,
	.remove = __devexit_p(adis16130_remove),
};
<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(adis16130_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static __init int adis16130_init(void)
{
	return spi_register_driver(&adis16130_driver);
}
module_init(adis16130_init);

static __exit void adis16130_exit(void)
{
	spi_unregister_driver(&adis16130_driver);
}
module_exit(adis16130_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16130 High Precision Angular Rate");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_ALIAS("spi:adis16130");
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
