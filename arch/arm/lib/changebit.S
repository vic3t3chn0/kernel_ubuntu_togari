/*
 *  linux/arch/arm/lib/changebit.S
 *
 *  Copyright (C) 1995-1996 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>
#include <asm/assembler.h>
#include "bitops.h"
                .text

<<<<<<< HEAD
bitop	_change_bit, eor
=======
<<<<<<< HEAD
bitop	_change_bit, eor
=======
ENTRY(_change_bit)
	bitop	eor
ENDPROC(_change_bit)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
