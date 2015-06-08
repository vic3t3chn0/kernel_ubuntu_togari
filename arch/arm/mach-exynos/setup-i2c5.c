/*
<<<<<<< HEAD
 * linux/arch/arm/mach-exynos4/setup-i2c5.c
=======
<<<<<<< HEAD
 * linux/arch/arm/mach-exynos4/setup-i2c5.c
=======
 * linux/arch/arm/mach-exynos/setup-i2c5.c
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *
 * I2C5 GPIO configuration.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

struct platform_device; /* don't need the contents */

#include <linux/gpio.h>
#include <plat/iic.h>
#include <plat/gpio-cfg.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void s3c_i2c5_cfg_gpio(struct platform_device *dev)
{
	s3c_gpio_cfgall_range(EXYNOS4_GPB(6), 2,
			      S3C_GPIO_SFN(3), S3C_GPIO_PULL_UP);
<<<<<<< HEAD
=======
=======
#include <plat/cpu.h>

void s3c_i2c5_cfg_gpio(struct platform_device *dev)
{
	if (soc_is_exynos4210())
		s3c_gpio_cfgall_range(EXYNOS4_GPB(6), 2,
			S3C_GPIO_SFN(3), S3C_GPIO_PULL_UP);
	else if (soc_is_exynos4212())
		s3c_gpio_cfgall_range(EXYNOS4_GPB(2), 2,
			S3C_GPIO_SFN(3), S3C_GPIO_PULL_NONE);
	else
		s3c_gpio_cfgall_range(EXYNOS5_GPA2(2), 2,
			S3C_GPIO_SFN(3), S3C_GPIO_PULL_UP);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
