/*
 * MX35 CPU type detection
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/module.h>
#include <linux/io.h>
#include <mach/hardware.h>
#include <mach/iim.h>

<<<<<<< HEAD
static int mx35_cpu_rev = -1;

static int mx35_read_cpu_rev(void)
{
	u32 rev;
=======
unsigned int mx35_cpu_rev;
EXPORT_SYMBOL(mx35_cpu_rev);

void __init mx35_read_cpu_rev(void)
{
	u32 rev;
	char *srev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	rev = __raw_readl(MX35_IO_ADDRESS(MX35_IIM_BASE_ADDR + MXC_IIMSREV));
	switch (rev) {
	case 0x00:
<<<<<<< HEAD
		return IMX_CHIP_REVISION_1_0;
	case 0x10:
		return IMX_CHIP_REVISION_2_0;
	case 0x11:
		return IMX_CHIP_REVISION_2_1;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}

int mx35_revision(void)
{
	if (mx35_cpu_rev == -1)
		mx35_cpu_rev = mx35_read_cpu_rev();

	return mx35_cpu_rev;
}
EXPORT_SYMBOL(mx35_revision);
=======
		mx35_cpu_rev = IMX_CHIP_REVISION_1_0;
		srev = "1.0";
		break;
	case 0x10:
		mx35_cpu_rev = IMX_CHIP_REVISION_2_0;
		srev = "2.0";
		break;
	case 0x11:
		mx35_cpu_rev = IMX_CHIP_REVISION_2_1;
		srev = "2.1";
		break;
	default:
		mx35_cpu_rev = IMX_CHIP_REVISION_UNKNOWN;
		srev = "unknown";
	}

	printk(KERN_INFO "CPU identified as i.MX35, silicon rev %s\n", srev);
}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
