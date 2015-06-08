/*
 * AD5504 SPI DAC driver
 *
 * Copyright 2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2.
 */

#ifndef SPI_AD5504_H_
#define SPI_AD5504_H_

#define AD5505_BITS			12
#define AD5504_RES_MASK			((1 << (AD5505_BITS)) - 1)

#define AD5504_CMD_READ			(1 << 15)
#define AD5504_CMD_WRITE		(0 << 15)
#define AD5504_ADDR(addr)		((addr) << 12)

/* Registers */
#define AD5504_ADDR_NOOP		0
<<<<<<< HEAD
<<<<<<< HEAD
#define AD5504_ADDR_DAC(x)		((x) + 1)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define AD5504_ADDR_DAC0		1
#define AD5504_ADDR_DAC1		2
#define AD5504_ADDR_DAC2		3
#define AD5504_ADDR_DAC3		4
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define AD5504_ADDR_ALL_DAC		5
#define AD5504_ADDR_CTRL		7

/* Control Register */
#define AD5504_DAC_PWR(ch)		((ch) << 2)
#define AD5504_DAC_PWRDWN_MODE(mode)	((mode) << 6)
#define AD5504_DAC_PWRDN_20K		0
#define AD5504_DAC_PWRDN_3STATE		1

/*
 * TODO: struct ad5504_platform_data needs to go into include/linux/iio
 */

struct ad5504_platform_data {
	u16				vref_mv;
};

/**
 * struct ad5446_state - driver instance specific data
<<<<<<< HEAD
<<<<<<< HEAD
=======
 * @indio_dev:		the industrial I/O device
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @indio_dev:		the industrial I/O device
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @us:			spi_device
 * @reg:		supply regulator
 * @vref_mv:		actual reference voltage used
 * @pwr_down_mask	power down mask
 * @pwr_down_mode	current power down mode
 */

struct ad5504_state {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct iio_dev			*indio_dev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_dev			*indio_dev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct spi_device		*spi;
	struct regulator		*reg;
	unsigned short			vref_mv;
	unsigned			pwr_down_mask;
	unsigned			pwr_down_mode;
};

/**
 * ad5504_supported_device_ids:
 */

enum ad5504_supported_device_ids {
	ID_AD5504,
	ID_AD5501,
};

#endif /* SPI_AD5504_H_ */
