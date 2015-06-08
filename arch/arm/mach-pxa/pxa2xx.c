/*
 * linux/arch/arm/mach-pxa/pxa2xx.c
 *
 * code specific to pxa2xx
 *
 * Copyright (C) 2008 Dmitry Baryshkov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
<<<<<<< HEAD
#include <linux/io.h>
=======
<<<<<<< HEAD
#include <linux/io.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <mach/hardware.h>
#include <mach/pxa2xx-regs.h>
#include <mach/mfp-pxa25x.h>
#include <mach/reset.h>
#include <mach/irda.h>

void pxa2xx_clear_reset_status(unsigned int mask)
{
	/* RESET_STATUS_* has a 1:1 mapping with RCSR */
	RCSR = mask;
}

static unsigned long pxa2xx_mfp_fir[] = {
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,
};

static unsigned long pxa2xx_mfp_sir[] = {
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,
};

static unsigned long pxa2xx_mfp_off[] = {
	GPIO46_GPIO | MFP_LPM_DRIVE_LOW,
	GPIO47_GPIO | MFP_LPM_DRIVE_LOW,
};

void pxa2xx_transceiver_mode(struct device *dev, int mode)
{
	if (mode & IR_OFF) {
		pxa2xx_mfp_config(pxa2xx_mfp_off, ARRAY_SIZE(pxa2xx_mfp_off));
	} else if (mode & IR_SIRMODE) {
		pxa2xx_mfp_config(pxa2xx_mfp_sir, ARRAY_SIZE(pxa2xx_mfp_sir));
	} else if (mode & IR_FIRMODE) {
		pxa2xx_mfp_config(pxa2xx_mfp_fir, ARRAY_SIZE(pxa2xx_mfp_fir));
	} else
		BUG();
}
EXPORT_SYMBOL_GPL(pxa2xx_transceiver_mode);
