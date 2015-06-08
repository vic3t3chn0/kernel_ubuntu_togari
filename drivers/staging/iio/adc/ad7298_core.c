/*
 * AD7298 SPI ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2.
 */

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/spi/spi.h>
#include <linux/regulator/consumer.h>
#include <linux/err.h>
#include <linux/delay.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>

#include "../iio.h"
#include "../sysfs.h"
#include "../buffer.h"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include "../iio.h"
#include "../sysfs.h"
#include "../ring_generic.h"
#include "adc.h"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include "ad7298.h"

static struct iio_chan_spec ad7298_channels[] = {
	IIO_CHAN(IIO_TEMP, 0, 1, 0, NULL, 0, 0,
<<<<<<< HEAD
<<<<<<< HEAD
		 IIO_CHAN_INFO_SCALE_SEPARATE_BIT,
		 9, AD7298_CH_TEMP, IIO_ST('s', 32, 32, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 0, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 0, 0, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 1, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 1, 1, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 2, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 2, 2, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 3, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 3, 3, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 4, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 4, 4, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 5, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 5, 5, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 6, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
		 6, 6, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_VOLTAGE, 0, 1, 0, NULL, 7, 0,
		 IIO_CHAN_INFO_SCALE_SHARED_BIT,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 (1 << IIO_CHAN_INFO_SCALE_SEPARATE),
		 9, AD7298_CH_TEMP, IIO_ST('s', 32, 32, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 0, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 0, 0, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 1, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 1, 1, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 2, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 2, 2, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 3, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 3, 3, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 4, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 4, 4, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 5, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 5, 5, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 6, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
		 6, 6, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN(IIO_IN, 0, 1, 0, NULL, 7, 0,
		 (1 << IIO_CHAN_INFO_SCALE_SHARED),
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 7, 7, IIO_ST('u', 12, 16, 0), 0),
	IIO_CHAN_SOFT_TIMESTAMP(8),
};

static int ad7298_scan_direct(struct ad7298_state *st, unsigned ch)
{
	int ret;
	st->tx_buf[0] = cpu_to_be16(AD7298_WRITE | st->ext_ref |
				   (AD7298_CH(0) >> ch));

	ret = spi_sync(st->spi, &st->scan_single_msg);
	if (ret)
		return ret;

	return be16_to_cpu(st->rx_buf[0]);
}

static int ad7298_scan_temp(struct ad7298_state *st, int *val)
{
	int tmp, ret;
<<<<<<< HEAD
<<<<<<< HEAD
	__be16 buf;

	buf = cpu_to_be16(AD7298_WRITE | AD7298_TSENSE |
			  AD7298_TAVG | st->ext_ref);

	ret = spi_write(st->spi, (u8 *)&buf, 2);
	if (ret)
		return ret;

	buf = cpu_to_be16(0);

	ret = spi_write(st->spi, (u8 *)&buf, 2);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	tmp = cpu_to_be16(AD7298_WRITE | AD7298_TSENSE |
			  AD7298_TAVG | st->ext_ref);

	ret = spi_write(st->spi, (u8 *)&tmp, 2);
	if (ret)
		return ret;

	tmp = 0;

	ret = spi_write(st->spi, (u8 *)&tmp, 2);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret)
		return ret;

	usleep_range(101, 1000); /* sleep > 100us */

<<<<<<< HEAD
<<<<<<< HEAD
	ret = spi_read(st->spi, (u8 *)&buf, 2);
	if (ret)
		return ret;

	tmp = be16_to_cpu(buf) & RES_MASK(AD7298_BITS);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = spi_read(st->spi, (u8 *)&tmp, 2);
	if (ret)
		return ret;

	tmp = be16_to_cpu(tmp) & RES_MASK(AD7298_BITS);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * One LSB of the ADC corresponds to 0.25 deg C.
	 * The temperature reading is in 12-bit twos complement format
	 */

	if (tmp & (1 << (AD7298_BITS - 1))) {
		tmp = (4096 - tmp) * 250;
		tmp -= (2 * tmp);

	} else {
		tmp *= 250; /* temperature in milli degrees Celsius */
	}

	*val = tmp;

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int ad7298_read_raw(struct iio_dev *indio_dev,
=======
static int ad7298_read_raw(struct iio_dev *dev_info,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int ad7298_read_raw(struct iio_dev *dev_info,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	int ret;
<<<<<<< HEAD
<<<<<<< HEAD
	struct ad7298_state *st = iio_priv(indio_dev);
=======
	struct ad7298_state *st = iio_priv(dev_info);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct ad7298_state *st = iio_priv(dev_info);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int scale_uv;

	switch (m) {
	case 0:
<<<<<<< HEAD
<<<<<<< HEAD
		mutex_lock(&indio_dev->mlock);
		if (indio_dev->currentmode == INDIO_BUFFER_TRIGGERED) {
			ret = -EBUSY;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mutex_lock(&dev_info->mlock);
		if (iio_ring_enabled(dev_info)) {
			if (chan->address == AD7298_CH_TEMP)
				ret = -ENODEV;
			else
				ret = ad7298_scan_from_ring(dev_info,
							    chan->address);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		} else {
			if (chan->address == AD7298_CH_TEMP)
				ret = ad7298_scan_temp(st, val);
			else
				ret = ad7298_scan_direct(st, chan->address);
		}
<<<<<<< HEAD
<<<<<<< HEAD
		mutex_unlock(&indio_dev->mlock);
=======
		mutex_unlock(&dev_info->mlock);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		mutex_unlock(&dev_info->mlock);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (ret < 0)
			return ret;

		if (chan->address != AD7298_CH_TEMP)
			*val = ret & RES_MASK(AD7298_BITS);

		return IIO_VAL_INT;
<<<<<<< HEAD
<<<<<<< HEAD
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			scale_uv = (st->int_vref_mv * 1000) >> AD7298_BITS;
			*val =  scale_uv / 1000;
			*val2 = (scale_uv % 1000) * 1000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val =  1;
			*val2 = 0;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case (1 << IIO_CHAN_INFO_SCALE_SHARED):
		scale_uv = (st->int_vref_mv * 1000) >> AD7298_BITS;
		*val =  scale_uv / 1000;
		*val2 = (scale_uv % 1000) * 1000;
		return IIO_VAL_INT_PLUS_MICRO;
	case (1 << IIO_CHAN_INFO_SCALE_SEPARATE):
		*val =  1;
		*val2 = 0;
		return IIO_VAL_INT_PLUS_MICRO;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	return -EINVAL;
}

static const struct iio_info ad7298_info = {
	.read_raw = &ad7298_read_raw,
	.driver_module = THIS_MODULE,
};

static int __devinit ad7298_probe(struct spi_device *spi)
{
	struct ad7298_platform_data *pdata = spi->dev.platform_data;
	struct ad7298_state *st;
<<<<<<< HEAD
<<<<<<< HEAD
	int ret;
=======
	int ret, regdone = 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	int ret, regdone = 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct iio_dev *indio_dev = iio_allocate_device(sizeof(*st));

	if (indio_dev == NULL)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = regulator_get(&spi->dev, "vcc");
	if (!IS_ERR(st->reg)) {
		ret = regulator_enable(st->reg);
		if (ret)
			goto error_put_reg;
	}

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad7298_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7298_channels);
	indio_dev->info = &ad7298_info;

	/* Setup default message */

	st->scan_single_xfer[0].tx_buf = &st->tx_buf[0];
	st->scan_single_xfer[0].len = 2;
	st->scan_single_xfer[0].cs_change = 1;
	st->scan_single_xfer[1].tx_buf = &st->tx_buf[1];
	st->scan_single_xfer[1].len = 2;
	st->scan_single_xfer[1].cs_change = 1;
	st->scan_single_xfer[2].rx_buf = &st->rx_buf[0];
	st->scan_single_xfer[2].len = 2;

	spi_message_init(&st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[0], &st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[1], &st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[2], &st->scan_single_msg);

	if (pdata && pdata->vref_mv) {
		st->int_vref_mv = pdata->vref_mv;
		st->ext_ref = AD7298_EXTREF;
	} else {
		st->int_vref_mv = AD7298_INTREF_mV;
	}

	ret = ad7298_register_ring_funcs_and_init(indio_dev);
	if (ret)
		goto error_disable_reg;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = iio_buffer_register(indio_dev,
				  &ad7298_channels[1], /* skip temp0 */
				  ARRAY_SIZE(ad7298_channels) - 1);
	if (ret)
		goto error_cleanup_ring;
	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_unregister_ring;

	return 0;

error_unregister_ring:
	iio_buffer_unregister(indio_dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg;
	regdone = 1;

	ret = iio_ring_buffer_register_ex(indio_dev->ring, 0,
					  &ad7298_channels[1], /* skip temp0 */
					  ARRAY_SIZE(ad7298_channels) - 1);
	if (ret)
		goto error_cleanup_ring;

	return 0;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
error_cleanup_ring:
	ad7298_ring_cleanup(indio_dev);
error_disable_reg:
	if (!IS_ERR(st->reg))
		regulator_disable(st->reg);
error_put_reg:
	if (!IS_ERR(st->reg))
		regulator_put(st->reg);
<<<<<<< HEAD
<<<<<<< HEAD
	iio_free_device(indio_dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (regdone)
		iio_device_unregister(indio_dev);
	else
		iio_free_device(indio_dev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return ret;
}

static int __devexit ad7298_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad7298_state *st = iio_priv(indio_dev);

<<<<<<< HEAD
<<<<<<< HEAD
	iio_device_unregister(indio_dev);
	iio_buffer_unregister(indio_dev);
	ad7298_ring_cleanup(indio_dev);
=======
	iio_ring_buffer_unregister(indio_dev->ring);
	ad7298_ring_cleanup(indio_dev);
	iio_device_unregister(indio_dev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	iio_ring_buffer_unregister(indio_dev->ring);
	ad7298_ring_cleanup(indio_dev);
	iio_device_unregister(indio_dev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!IS_ERR(st->reg)) {
		regulator_disable(st->reg);
		regulator_put(st->reg);
	}
<<<<<<< HEAD
<<<<<<< HEAD
	iio_free_device(indio_dev);
=======
	iio_device_unregister(indio_dev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	iio_device_unregister(indio_dev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static const struct spi_device_id ad7298_id[] = {
	{"ad7298", 0},
	{}
};
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_DEVICE_TABLE(spi, ad7298_id);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static struct spi_driver ad7298_driver = {
	.driver = {
		.name	= "ad7298",
<<<<<<< HEAD
<<<<<<< HEAD
=======
		.bus	= &spi_bus_type,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		.bus	= &spi_bus_type,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		.owner	= THIS_MODULE,
	},
	.probe		= ad7298_probe,
	.remove		= __devexit_p(ad7298_remove),
	.id_table	= ad7298_id,
};
<<<<<<< HEAD
<<<<<<< HEAD
module_spi_driver(ad7298_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static int __init ad7298_init(void)
{
	return spi_register_driver(&ad7298_driver);
}
module_init(ad7298_init);

static void __exit ad7298_exit(void)
{
	spi_unregister_driver(&ad7298_driver);
}
module_exit(ad7298_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("Analog Devices AD7298 ADC");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
<<<<<<< HEAD
=======
MODULE_ALIAS("spi:ad7298");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
MODULE_ALIAS("spi:ad7298");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
