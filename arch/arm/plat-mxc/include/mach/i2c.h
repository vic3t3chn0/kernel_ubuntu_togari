/*
 * i2c.h - i.MX I2C driver header file
 *
 * Copyright (c) 2008, Darius Augulis <augulis.darius@gmail.com>
 *
 * This file is released under the GPLv2
 */

#ifndef __ASM_ARCH_I2C_H_
#define __ASM_ARCH_I2C_H_

/**
 * struct imxi2c_platform_data - structure of platform data for MXC I2C driver
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
 * @init:	Initialise gpio's and other board specific things
 * @exit:	Free everything initialised by @init
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @bitrate:	Bus speed measured in Hz
 *
 **/
struct imxi2c_platform_data {
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	int (*init)(struct device *dev);
	void (*exit)(struct device *dev);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int bitrate;
};

#endif /* __ASM_ARCH_I2C_H_ */
