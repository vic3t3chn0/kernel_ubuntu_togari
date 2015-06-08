/*
<<<<<<< HEAD
 * Driver header for M-5MOLS 8M Pixel camera sensor with ISP
=======
<<<<<<< HEAD
 * Driver header for M-5MOLS 8M Pixel camera sensor with ISP
=======
 * Driver for M5MOLS 8M Pixel camera sensor with ISP
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 *
 * Copyright (C) 2009 Samsung Electronics Co., Ltd.
 * Author: Dongsoo Nathaniel Kim <dongsoo45.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef MEDIA_M5MOLS_H
#define MEDIA_M5MOLS_H

/**
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * struct m5mols_platform_data - platform data for M-5MOLS driver
 * @gpio_reset:	GPIO driving the reset pin of M-5MOLS
 * @reset_polarity: active state for gpio_reset pin, 0 or 1
 * @set_power:	an additional callback to the board setup code
 *		to be called after enabling and before disabling
 *		the sensor's supply regulators
 */
struct m5mols_platform_data {
	int gpio_reset;
	u8 reset_polarity;
	int (*set_power)(struct device *dev, int on);
<<<<<<< HEAD
=======
=======
* struct m5mols_platform_data - platform data for M5MOLS driver
* @irq:   GPIO getting the irq pin of M5MOLS
* @gpio_rst:  GPIO driving the reset pin of M5MOLS
 * @enable_rst:	the pin state when reset pin is enabled
* @set_power:	an additional callback to a board setup code
 *		to be called after enabling and before disabling
*		the sensor device supply regulators
 */
struct m5mols_platform_data {
	int (*set_power)(struct device *dev, int on);
	int irq;
	int	gpio_rst;
	bool	enable_rst;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

#endif	/* MEDIA_M5MOLS_H */
