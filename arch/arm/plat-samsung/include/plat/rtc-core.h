/* linux/arch/arm/plat-samsung/include/plat/rtc-core.h
 *
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Copyright (c) 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * Samsung RTC Controller core functions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
<<<<<<< HEAD
=======
=======
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Samsung RTC Device core function
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the term of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifndef __ASM_PLAT_RTC_CORE_H
#define __ASM_PLAT_RTC_CORE_H __FILE__

<<<<<<< HEAD
/* These functions are only for use with the core support code, such as
 * the cpu specific initialisation code
=======
<<<<<<< HEAD
/* These functions are only for use with the core support code, such as
 * the cpu specific initialisation code
=======
/* These function are only for use with the core support code, such as
 * the cpu specific initialization code
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */

/* re-define device name depending on support. */
static inline void s3c_rtc_setname(char *name)
{
<<<<<<< HEAD
#if defined(CONFIG_SAMSUNG_DEV_RTC) || defined(CONFIG_PLAT_S3C24XX)
=======
<<<<<<< HEAD
#if defined(CONFIG_SAMSUNG_DEV_RTC) || defined(CONFIG_PLAT_S3C24XX)
=======
#ifdef CONFIG_S3C_DEV_RTC
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	s3c_device_rtc.name = name;
#endif
}

#endif /* __ASM_PLAT_RTC_CORE_H */
