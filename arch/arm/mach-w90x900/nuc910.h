/*
 * arch/arm/mach-w90x900/nuc910.h
 *
 * Copyright (c) 2008 Nuvoton corporation
 *
 * Header file for NUC900 CPU support
 *
 * Wan ZongShun <mcuos.com@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
<<<<<<< HEAD
#include "nuc9xx.h"
=======
<<<<<<< HEAD
#include "nuc9xx.h"
=======

struct map_desc;
struct sys_timer;

/* core initialisation functions */

extern void nuc900_init_irq(void);
extern struct sys_timer nuc900_timer;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* extern file from nuc910.c */

extern void nuc910_board_init(void);
extern void nuc910_init_clocks(void);
extern void nuc910_map_io(void);
