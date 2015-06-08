/*
 * Driver for ADI Direct Digital Synthesis ad5930
 *
 * Copyright (c) 2010-2010 Analog Devices Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include "../iio.h"
#include "../sysfs.h"

#define DRV_NAME "ad5930"

#define value_mask (u16)0xf000
#define addr_shift 12

/* Register format: 4 bits addr + 12 bits value */
struct ad5903_config {
	u16 control;
	u16 incnum;
	u16 frqdelt[2];
	u16 incitvl;
	u16 buritvl;
	u16 strtfrq[2];
};

struct ad5930_state {
	struct mutex lock;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct iio_dev *idev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_dev *idev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct spi_device *sdev;
};

static ssize_t ad5930_set_parameter(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	int ret;
	struct ad5903_config *config = (struct ad5903_config *)buf;
	struct iio_dev *idev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct ad5930_state *st = iio_priv(idev);
=======
	struct ad5930_state *st = idev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct ad5930_state *st = idev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	config->control = (config->control & ~value_mask);
	config->incnum = (config->control & ~value_mask) | (1 << addr_shift);
	config->frqdelt[0] = (config->control & ~value_mask) | (2 << addr_shift);
	config->frqdelt[1] = (config->control & ~value_mask) | 3 << addr_shift;
	config->incitvl = (config->control & ~value_mask) | 4 << addr_shift;
	config->buritvl = (config->control & ~value_mask) | 8 << addr_shift;
	config->strtfrq[0] = (config->control & ~value_mask) | 0xc << addr_shift;
	config->strtfrq[1] = (config->control & ~value_mask) | 0xd << addr_shift;

	xfer.len = len;
	xfer.tx_buf = config;
	mutex_lock(&st->lock);

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static IIO_DEVICE_ATTR(dds, S_IWUSR, NULL, ad5930_set_parameter, 0);

static struct attribute *ad5930_attributes[] = {
	&iio_dev_attr_dds.dev_attr.attr,
	NULL,
};

static const struct attribute_group ad5930_attribute_group = {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.name = DRV_NAME,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.name = DRV_NAME,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.attrs = ad5930_attributes,
};

static const struct iio_info ad5930_info = {
	.attrs = &ad5930_attribute_group,
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.driver_module = THIS_MODULE,
};

static int __devinit ad5930_probe(struct spi_device *spi)
{
	struct ad5930_state *st;
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *idev;
	int ret = 0;

	idev = iio_allocate_device(sizeof(*st));
	if (idev == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	spi_set_drvdata(spi, idev);
	st = iio_priv(idev);

	mutex_init(&st->lock);
	st->sdev = spi;
	idev->dev.parent = &spi->dev;
	idev->info = &ad5930_info;
	idev->modes = INDIO_DIRECT_MODE;

	ret = iio_device_register(idev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret = 0;

	st = kzalloc(sizeof(*st), GFP_KERNEL);
	if (st == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	spi_set_drvdata(spi, st);

	mutex_init(&st->lock);
	st->sdev = spi;

	st->idev = iio_allocate_device(0);
	if (st->idev == NULL) {
		ret = -ENOMEM;
		goto error_free_st;
	}
	st->idev->dev.parent = &spi->dev;
	st->idev->dev_data = (void *)(st);
	st->idev->info = &ad5930_info;
	st->idev->modes = INDIO_DIRECT_MODE;

	ret = iio_device_register(st->idev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret)
		goto error_free_dev;
	spi->max_speed_hz = 2000000;
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 16;
	spi_setup(spi);

	return 0;

error_free_dev:
<<<<<<< HEAD
<<<<<<< HEAD
	iio_free_device(idev);
=======
	iio_free_device(st->idev);
error_free_st:
	kfree(st);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	iio_free_device(st->idev);
error_free_st:
	kfree(st);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
error_ret:
	return ret;
}

static int __devexit ad5930_remove(struct spi_device *spi)
{
<<<<<<< HEAD
<<<<<<< HEAD
	iio_device_unregister(spi_get_drvdata(spi));
	iio_free_device(spi_get_drvdata(spi));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct ad5930_state *st = spi_get_drvdata(spi);

	iio_device_unregister(st->idev);
	kfree(st);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static struct spi_driver ad5930_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = ad5930_probe,
	.remove = __devexit_p(ad5930_remove),
};
<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(ad5930_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static __init int ad5930_spi_init(void)
{
	return spi_register_driver(&ad5930_driver);
}
module_init(ad5930_spi_init);

static __exit void ad5930_spi_exit(void)
{
	spi_unregister_driver(&ad5930_driver);
}
module_exit(ad5930_spi_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Cliff Cai");
MODULE_DESCRIPTION("Analog Devices ad5930 driver");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_ALIAS("spi:" DRV_NAME);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
