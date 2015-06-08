/*
 * linux/arch/arm/mach-footbridge/personal.c
 *
 * Personal server (Skiff) machine fixup
 */
#include <linux/init.h>
#include <linux/spinlock.h>

#include <asm/hardware/dec21285.h>
#include <asm/mach-types.h>

#include <asm/mach/arch.h>

#include "common.h"

MACHINE_START(PERSONAL_SERVER, "Compaq-PersonalServer")
	/* Maintainer: Jamey Hicks / George France */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.atag_offset	= 0x100,
	.map_io		= footbridge_map_io,
	.init_irq	= footbridge_init_irq,
	.timer		= &footbridge_timer,
	.restart	= footbridge_restart,
<<<<<<< HEAD
=======
=======
	.boot_params	= 0x00000100,
	.map_io		= footbridge_map_io,
	.init_irq	= footbridge_init_irq,
	.timer		= &footbridge_timer,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MACHINE_END

