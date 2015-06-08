/*
 * arch/arm/mach-iop32x/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 * Copyright (C) 1994-1999 Russell King
 * Moved from linux/arch/arm/kernel/debug.S by Ben Dooks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

<<<<<<< HEAD
		.macro	addruart, rp, rv, tmp
=======
<<<<<<< HEAD
		.macro	addruart, rp, rv, tmp
=======
		.macro	addruart, rp, rv
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mov	\rp, #0xfe000000	@ physical as well as virtual
		orr	\rp, \rp, #0x00800000	@ location of the UART
		mov	\rv, \rp
		.endm

#define UART_SHIFT	0
#include <asm/hardware/debug-8250.S>
