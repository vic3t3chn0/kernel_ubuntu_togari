/*
 *  linux/arch/arm/lib/testchangebit.S
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
testop	_test_and_change_bit, eor, str
=======
<<<<<<< HEAD
testop	_test_and_change_bit, eor, str
=======
ENTRY(_test_and_change_bit)
	testop	eor, str
ENDPROC(_test_and_change_bit)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
