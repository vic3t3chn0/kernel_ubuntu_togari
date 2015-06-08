/*
 * arch/arm/mach-dove/include/mach/debug-macro.S
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <mach/bridge-regs.h>

<<<<<<< HEAD
	.macro	addruart, rp, rv, tmp
=======
<<<<<<< HEAD
	.macro	addruart, rp, rv, tmp
=======
	.macro	addruart, rp, rv
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ldr	\rp, =DOVE_SB_REGS_PHYS_BASE
	ldr	\rv, =DOVE_SB_REGS_VIRT_BASE
	orr	\rp, \rp, #0x00012000
	orr	\rv, \rv, #0x00012000
	.endm

#define UART_SHIFT	2
#include <asm/hardware/debug-8250.S>
