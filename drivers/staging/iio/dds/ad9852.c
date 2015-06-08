/*
 * Driver for ADI Direct Digital Synthesis ad9852
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

#define DRV_NAME "ad9852"

#define addr_phaad1 0x0
#define addr_phaad2 0x1
#define addr_fretu1 0x2
#define addr_fretu2 0x3
#define addr_delfre 0x4
#define addr_updclk 0x5
#define addr_ramclk 0x6
#define addr_contrl 0x7
#define addr_optskm 0x8
#define addr_optskr 0xa
#define addr_dacctl 0xb

#define COMPPD		(1 << 4)
#define REFMULT2	(1 << 2)
#define BYPPLL		(1 << 5)
#define PLLRANG		(1 << 6)
#define IEUPCLK		(1)
#define OSKEN		(1 << 5)

#define read_bit	(1 << 7)

/* Register format: 1 byte addr + value */
struct ad9852_config {
	u8 phajst0[3];
	u8 phajst1[3];
	u8 fretun1[6];
	u8 fretun2[6];
	u8 dltafre[6];
	u8 updtclk[5];
	u8 ramprat[4];
	u8 control[5];
	u8 outpskm[3];
	u8 outpskr[2];
	u8 daccntl[3];
};

struct ad9852_state {
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

static ssize_t ad9852_set_parameter(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	int ret;
	struct ad9852_config *config = (struct ad9852_config *)buf;
	struct iio_dev *idev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct ad9852_state *st = iio_priv(idev);
=======
	struct ad9852_state *st = idev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct ad9852_state *st = idev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	xfer.len = 3;
	xfer.tx_buf = &config->phajst0[0];
	mutex_lock(&st->lock);

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 3;
	xfer.tx_buf = &config->phajst1[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 6;
	xfer.tx_buf = &config->fretun1[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 6;
	xfer.tx_buf = &config->fretun2[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 6;
	xfer.tx_buf = &config->dltafre[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 5;
	xfer.tx_buf = &config->updtclk[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 4;
	xfer.tx_buf = &config->ramprat[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 5;
	xfer.tx_buf = &config->control[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 3;
	xfer.tx_buf = &config->outpskm[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 2;
	xfer.tx_buf = &config->outpskr[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

	xfer.len = 3;
	xfer.tx_buf = &config->daccntl[0];

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static IIO_DEVICE_ATTR(dds, S_IWUSR, NULL, ad9852_set_parameter, 0);

static void ad9852_init(struct ad9852_state *st)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	int ret;
	u8 config[5];

	config[0] = addr_contrl;
	config[1] = COMPPD;
	config[2] = REFMULT2 | BYPPLL | PLLRANG;
	config[3] = IEUPCLK;
	config[4] = OSKEN;

	mutex_lock(&st->lock);

	xfer.len = 5;
	xfer.tx_buf = &config;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;

error_ret:
	mutex_unlock(&st->lock);



}

static struct attribute *ad9852_attributes[] = {
	&iio_dev_attr_dds.dev_attr.attr,
	NULL,
};

static const struct attribute_group ad9852_attribute_group = {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.name = DRV_NAME,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.name = DRV_NAME,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.attrs = ad9852_attributes,
};

static const struct iio_info ad9852_info = {
	.attrs = &ad9852_attribute_group,
	.driver_module = THIS_MODULE,
};

static int __devinit ad9852_probe(struct spi_device *spi)
{
	struct ad9852_state *st;
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *idev;
	int ret = 0;

	idev = iio_allocate_device(sizeof(*st));
	if (idev == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	st = iio_priv(idev);
	spi_set_drvdata(spi, idev);
	mutex_init(&st->lock);
	st->sdev = spi;

	idev->dev.parent = &spi->dev;
	idev->info = &ad9852_info;
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

	st->idev->info = &ad9852_info;
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
	ad9852_init(st);
<<<<<<< HEAD
<<<<<<< HEAD

	return 0;

error_free_dev:
	iio_free_device(idev);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;

error_free_dev:
	iio_free_device(st->idev);
error_free_st:
	kfree(st);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
error_ret:
	return ret;
}

static int __devexit ad9852_remove(struct spi_device *spi)
{
<<<<<<< HEAD
<<<<<<< HEAD
	iio_device_unregister(spi_get_drvdata(spi));
	iio_free_device(spi_get_drvdata(spi));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct ad9852_state *st = spi_get_drvdata(spi);

	iio_device_unregister(st->idev);
	kfree(st);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static struct spi_driver ad9852_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = ad9852_probe,
	.remove = __devexit_p(ad9852_remove),
};
<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(ad9852_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static __init int ad9852_spi_init(void)
{
	return spi_register_driver(&ad9852_driver);
}
module_init(ad9852_spi_init);

static __exit void ad9852_spi_exit(void)
{
	spi_unregister_driver(&ad9852_driver);
}
module_exit(ad9852_spi_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Cliff Cai");
MODULE_DESCRIPTION("Analog Devices ad9852 driver");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_ALIAS("spi:" DRV_NAME);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
