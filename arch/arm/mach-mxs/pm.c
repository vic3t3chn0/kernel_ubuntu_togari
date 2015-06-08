/*
 * Copyright (C) 2010 Freescale Semiconductor, Inc.
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
 */

#include <linux/kernel.h>
#include <linux/suspend.h>
#include <linux/io.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <mach/system.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static int mxs_suspend_enter(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
<<<<<<< HEAD
		cpu_do_idle();
=======
<<<<<<< HEAD
		cpu_do_idle();
=======
		arch_idle();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	default:
		return -EINVAL;
	}
	return 0;
}

static struct platform_suspend_ops mxs_suspend_ops = {
	.enter = mxs_suspend_enter,
	.valid = suspend_valid_only_mem,
};

static int __init mxs_pm_init(void)
{
	suspend_set_ops(&mxs_suspend_ops);
	return 0;
}
device_initcall(mxs_pm_init);
