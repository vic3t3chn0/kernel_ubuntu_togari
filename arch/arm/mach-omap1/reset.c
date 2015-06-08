/*
 * OMAP1 reset support
 */
#include <linux/kernel.h>
#include <linux/io.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <plat/prcm.h>

#include <mach/hardware.h>

void omap1_restart(char mode, const char *cmd)
<<<<<<< HEAD
=======
=======
#include <mach/hardware.h>
#include <mach/system.h>
#include <plat/prcm.h>

void omap1_arch_reset(char mode, const char *cmd)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	/*
	 * Workaround for 5912/1611b bug mentioned in sprz209d.pdf p. 28
	 * "Global Software Reset Affects Traffic Controller Frequency".
	 */
	if (cpu_is_omap5912()) {
		omap_writew(omap_readw(DPLL_CTL) & ~(1 << 4), DPLL_CTL);
		omap_writew(0x8, ARM_RSTCT1);
	}

	omap_writew(1, ARM_RSTCT1);
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

void (*arch_reset)(char, const char *) = omap1_arch_reset;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
