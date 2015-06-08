<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/debug-macro.S
=======
<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/debug-macro.S
=======
/* linux/arch/arm/mach-exynos/include/mach/debug-macro.S
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Based on arch/arm/mach-s3c6400/include/mach/debug-macro.S
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

/* pull in the relevant register and map files. */

#include <mach/map.h>

	/* note, for the boot process to work we have to keep the UART
	 * virtual address aligned to an 1MiB boundary for the L1
	 * mapping the head code makes. We keep the UART virtual address
	 * aligned and add in the offset when we load the value here.
	 */

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.macro addruart, rp, rv, tmp
		mrc	p15, 0, \tmp, c0, c0, 0
		and	\tmp, \tmp, #0xf0
		teq	\tmp, #0xf0		@@ A15
		ldreq	\rp, =EXYNOS5_PA_UART
		movne	\rp, #EXYNOS4_PA_UART	@@ EXYNOS4
		ldr	\rv, =S3C_VA_UART
<<<<<<< HEAD
=======
=======
	.macro addruart, rp, rv
		ldr	\rp, = S3C_PA_UART
		ldr	\rv, = S3C_VA_UART
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#if CONFIG_DEBUG_S3C_UART != 0
		add	\rp, \rp, #(0x10000 * CONFIG_DEBUG_S3C_UART)
		add	\rv, \rv, #(0x10000 * CONFIG_DEBUG_S3C_UART)
#endif
	.endm

#define fifo_full fifo_full_s5pv210
#define fifo_level fifo_level_s5pv210

#include <plat/debug-macro.S>
