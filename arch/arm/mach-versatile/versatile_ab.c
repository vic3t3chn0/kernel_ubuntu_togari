/*
 *  linux/arch/arm/mach-versatile/versatile_ab.c
 *
 *  Copyright (C) 2004 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/init.h>
#include <linux/device.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <linux/sysdev.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/amba/bus.h>
#include <linux/io.h>

#include <mach/hardware.h>
#include <asm/irq.h>
<<<<<<< HEAD
#include <asm/hardware/vic.h>
=======
<<<<<<< HEAD
#include <asm/hardware/vic.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/mach-types.h>

#include <asm/mach/arch.h>

#include "core.h"

MACHINE_START(VERSATILE_AB, "ARM-Versatile AB")
	/* Maintainer: ARM Ltd/Deep Blue Solutions Ltd */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.atag_offset	= 0x100,
	.map_io		= versatile_map_io,
	.init_early	= versatile_init_early,
	.init_irq	= versatile_init_irq,
	.handle_irq	= vic_handle_irq,
	.timer		= &versatile_timer,
	.init_machine	= versatile_init,
	.restart	= versatile_restart,
<<<<<<< HEAD
=======
=======
	.boot_params	= 0x00000100,
	.map_io		= versatile_map_io,
	.init_early	= versatile_init_early,
	.init_irq	= versatile_init_irq,
	.timer		= &versatile_timer,
	.init_machine	= versatile_init,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MACHINE_END
