/*
 * arch/arm/mach-ep93xx/include/mach/debug-macro.S
 * Debugging macro include header
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */
#include <mach/ep93xx-regs.h>

<<<<<<< HEAD
		.macro	addruart, rp, rv, tmp
=======
<<<<<<< HEAD
		.macro	addruart, rp, rv, tmp
=======
		.macro	addruart, rp, rv
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ldr	\rp, =EP93XX_APB_PHYS_BASE	@ Physical base
		ldr	\rv, =EP93XX_APB_VIRT_BASE	@ virtual base
		orr	\rp, \rp, #0x000c0000
		orr	\rv, \rv, #0x000c0000
		.endm

#include <asm/hardware/debug-pl01x.S>
