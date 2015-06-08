/*
 * Driver for ADI Direct Digital Synthesis ad9850
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

#define DRV_NAME "ad9850"

#define value_mask (u16)0xf000
#define addr_shift 12

/* Register format: 4 bits addr + 12 bits value */
struct ad9850_config {
	u8 control[5];
};

struct ad9850_state {
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

static ssize_t ad9850_set_parameter(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	int ret;
	struct ad9850_config *config = (struct ad9850_config *)buf;
	struct iio_dev *idev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct ad9850_state *st = iio_priv(idev);
=======
	struct ad9850_state *st = idev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct ad9850_state *st = idev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

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

static IIO_DEVICE_ATTR(dds, S_IWUSR, NULL, ad9850_set_parameter, 0);

static struct attribute *ad9850_attributes[] = {
	&iio_dev_attr_dds.dev_attr.attr,
	NULL,
};

static const struct attribute_group ad9850_attribute_group = {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.name = DRV_NAME,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.name = DRV_NAME,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.attrs = ad9850_attributes,
};

static const struct iio_info ad9850_info = {
	.attrs = &ad9850_attribute_group,
	.driver_module = THIS_MODULE,
};

static int __devinit ad9850_probe(struct spi_device *spi)
{
	struct ad9850_state *st;
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
	idev->info = &ad9850_info;
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

	st->idev->info = &ad9850_info;
	st->idev->dev_data = (void *)(st);
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

static int __devexit ad9850_remove(struct spi_device *spi)
{
<<<<<<< HEAD
<<<<<<< HEAD
	iio_device_unregister(spi_get_drvdata(spi));
	iio_free_device(spi_get_drvdata(spi));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct ad9850_state *st = spi_get_drvdata(spi);

	iio_device_unregister(st->idev);
	kfree(st);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static struct spi_driver ad9850_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = ad9850_probe,
	.remove = __devexit_p(ad9850_remove),
};
<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(ad9850_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static __init int ad9850_spi_init(void)
{
	return spi_register_driver(&ad9850_driver);
}
module_init(ad9850_spi_init);

static __exit void ad9850_spi_exit(void)
{
	spi_unregister_driver(&ad9850_driver);
}
module_exit(ad9850_spi_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Cliff Cai");
MODULE_DESCRIPTION("Analog Devices ad9850 driver");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_ALIAS("spi:" DRV_NAME);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
