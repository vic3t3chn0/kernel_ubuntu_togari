/*
 * Driver for ADI Direct Digital Synthesis ad9951
 *
 * Copyright (c) 2010 Analog Devices Inc.
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

#define DRV_NAME "ad9951"

#define CFR1 0x0
#define CFR2 0x1

#define AUTO_OSK	(1)
#define OSKEN		(1 << 1)
#define LOAD_ARR	(1 << 2)

#define AUTO_SYNC	(1 << 7)

#define LSB_FST		(1)
#define SDIO_IPT	(1 << 1)
#define CLR_PHA		(1 << 2)
#define SINE_OPT	(1 << 4)
#define ACLR_PHA	(1 << 5)

#define VCO_RANGE	(1 << 2)

#define CRS_OPT		(1 << 1)
#define HMANU_SYNC	(1 << 2)
#define HSPD_SYNC	(1 << 3)

/* Register format: 1 byte addr + value */
struct ad9951_config {
	u8 asf[3];
	u8 arr[2];
	u8 ftw0[5];
	u8 ftw1[3];
};

struct ad9951_state {
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

static ssize_t ad9951_set_parameter(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	int ret;
	struct ad9951_config *config = (struct ad9951_config *)buf;
	struct iio_dev *idev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct ad9951_state *st = iio_priv(idev);
=======
	struct ad9951_state *st = idev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct ad9951_state *st = idev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	xfer.len = 3;
	xfer.tx_buf = &config->asf[0];
	mutex_lock(&st->lock);

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 2;
	xfer.tx_buf = &config->arr[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 5;
	xfer.tx_buf = &config->ftw0[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 3;
	xfer.tx_buf = &config->ftw1[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static IIO_DEVICE_ATTR(dds, S_IWUSR, NULL, ad9951_set_parameter, 0);

static void ad9951_init(struct ad9951_state *st)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	int ret;
	u8 cfr[5];

	cfr[0] = CFR1;
	cfr[1] = 0;
	cfr[2] = LSB_FST | CLR_PHA | SINE_OPT | ACLR_PHA;
	cfr[3] = AUTO_OSK | OSKEN | LOAD_ARR;
	cfr[4] = 0;

	mutex_lock(&st->lock);

	xfer.len = 5;
	xfer.tx_buf = &cfr;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	cfr[0] = CFR2;
	cfr[1] = VCO_RANGE;
	cfr[2] = HSPD_SYNC;
	cfr[3] = 0;

	xfer.len = 4;
	xfer.tx_buf = &cfr;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

error_ret:
	mutex_unlock(&st->lock);



}

static struct attribute *ad9951_attributes[] = {
	&iio_dev_attr_dds.dev_attr.attr,
	NULL,
};

static const struct attribute_group ad9951_attribute_group = {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.name = DRV_NAME,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.name = DRV_NAME,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.attrs = ad9951_attributes,
};

static const struct iio_info ad9951_info = {
	.attrs = &ad9951_attribute_group,
	.driver_module = THIS_MODULE,
};

static int __devinit ad9951_probe(struct spi_device *spi)
{
	struct ad9951_state *st;
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

	idev->info = &ad9951_info;
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

	st->idev->info = &ad9951_info;
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
	spi->bits_per_word = 8;
	spi_setup(spi);
	ad9951_init(st);
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

static int __devexit ad9951_remove(struct spi_device *spi)
{
<<<<<<< HEAD
<<<<<<< HEAD
	iio_device_unregister(spi_get_drvdata(spi));
	iio_free_device(spi_get_drvdata(spi));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct ad9951_state *st = spi_get_drvdata(spi);

	iio_device_unregister(st->idev);
	kfree(st);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static struct spi_driver ad9951_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = ad9951_probe,
	.remove = __devexit_p(ad9951_remove),
};
<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(ad9951_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static __init int ad9951_spi_init(void)
{
	return spi_register_driver(&ad9951_driver);
}
module_init(ad9951_spi_init);

static __exit void ad9951_spi_exit(void)
{
	spi_unregister_driver(&ad9951_driver);
}
module_exit(ad9951_spi_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Cliff Cai");
MODULE_DESCRIPTION("Analog Devices ad9951 driver");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_ALIAS("spi:" DRV_NAME);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
