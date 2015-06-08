/*
 * Debugging macro include header
 *
 *  Copyright (C) 1994-1999 Russell King
 *  Copyright (C) 2001-2006 Storlink, Corp.
 *  Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <mach/hardware.h>

<<<<<<< HEAD
	.macro	addruart, rp, rv, tmp
=======
<<<<<<< HEAD
	.macro	addruart, rp, rv, tmp
=======
	.macro	addruart, rp, rv
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ldr	\rp, =GEMINI_UART_BASE			@ physical
	ldr	\rv, =IO_ADDRESS(GEMINI_UART_BASE)	@ virtual
	.endm

#define UART_SHIFT	2
#define FLOW_CONTROL
#include <asm/hardware/debug-8250.S>
