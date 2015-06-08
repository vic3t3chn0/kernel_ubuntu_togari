/*
 * OMAP hardware spinlock device initialization
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com
 *
 * Contact: Simon Que <sque@ti.com>
 *          Hari Kanigeri <h-kanigeri2@ti.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
<<<<<<< HEAD
#include <linux/hwspinlock.h>
=======
<<<<<<< HEAD
#include <linux/hwspinlock.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <plat/omap_hwmod.h>
#include <plat/omap_device.h>

<<<<<<< HEAD
static struct hwspinlock_pdata omap_hwspinlock_pdata __initdata = {
	.base_id = 0,
=======
<<<<<<< HEAD
static struct hwspinlock_pdata omap_hwspinlock_pdata __initdata = {
	.base_id = 0,
=======
struct omap_device_pm_latency omap_spinlock_latency[] = {
	{
		.deactivate_func = omap_device_idle_hwmods,
		.activate_func   = omap_device_enable_hwmods,
		.flags = OMAP_DEVICE_LATENCY_AUTO_ADJUST,
	}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

int __init hwspinlocks_init(void)
{
	int retval = 0;
	struct omap_hwmod *oh;
<<<<<<< HEAD
	struct platform_device *pdev;
=======
<<<<<<< HEAD
	struct platform_device *pdev;
=======
	struct omap_device *od;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	const char *oh_name = "spinlock";
	const char *dev_name = "omap_hwspinlock";

	/*
	 * Hwmod lookup will fail in case our platform doesn't support the
	 * hardware spinlock module, so it is safe to run this initcall
	 * on all omaps
	 */
	oh = omap_hwmod_lookup(oh_name);
	if (oh == NULL)
		return -EINVAL;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	pdev = omap_device_build(dev_name, 0, oh, &omap_hwspinlock_pdata,
				sizeof(struct hwspinlock_pdata),
				NULL, 0, false);
	if (IS_ERR(pdev)) {
		pr_err("Can't build omap_device for %s:%s\n", dev_name,
								oh_name);
		retval = PTR_ERR(pdev);
<<<<<<< HEAD
=======
=======
	od = omap_device_build(dev_name, 0, oh, NULL, 0,
				omap_spinlock_latency,
				ARRAY_SIZE(omap_spinlock_latency), false);
	if (IS_ERR(od)) {
		pr_err("Can't build omap_device for %s:%s\n", dev_name,
								oh_name);
		retval = PTR_ERR(od);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return retval;
}
/* early board code might need to reserve specific hwspinlock instances */
postcore_initcall(hwspinlocks_init);
