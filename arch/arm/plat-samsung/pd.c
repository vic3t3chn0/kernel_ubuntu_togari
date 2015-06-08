/* linux/arch/arm/plat-samsung/pd.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung Power domain support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/pm_runtime.h>

#include <plat/pd.h>

static int samsung_pd_probe(struct platform_device *pdev)
{
	struct samsung_pd_info *pdata = pdev->dev.platform_data;
	struct device *dev = &pdev->dev;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	int ret = 0;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!pdata) {
		dev_err(dev, "no device data specified\n");
		return -ENOENT;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	pdata->id = pdev->id;
	if (pdata->init) {
		ret = pdata->init(dev);
		if (ret) {
			dev_err(dev, "init fails");
			return ret;
		}
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	dev_info(dev, "power domain registered\n");
	return 0;
}

static int __devexit samsung_pd_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	pm_runtime_disable(dev);
	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
static int samsung_pd_suspend(struct device *dev)
{
	struct samsung_pd_info *pdata = dev->platform_data;
	int ret = 0;

	if (pdata->save)
		ret = pdata->save(dev);

	dev_dbg(dev, "suspended\n");

	return ret;
}

static int samsung_pd_resume(struct device *dev)
{
	struct samsung_pd_info *pdata = dev->platform_data;
	int ret = 0;

	if (pdata->restore)
		ret = pdata->restore(dev);

	dev_dbg(dev, "resumed\n");

	return ret;
}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int samsung_pd_runtime_suspend(struct device *dev)
{
	struct samsung_pd_info *pdata = dev->platform_data;
	int ret = 0;

	if (pdata->disable)
		ret = pdata->disable(dev);

<<<<<<< HEAD
	dev_dbg(dev, "suspended\n");
=======
<<<<<<< HEAD
	dev_dbg(dev, "suspended\n");
=======
	dev_dbg(dev, "runtime suspended\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int samsung_pd_runtime_resume(struct device *dev)
{
	struct samsung_pd_info *pdata = dev->platform_data;
	int ret = 0;

	if (pdata->enable)
		ret = pdata->enable(dev);

<<<<<<< HEAD
	dev_dbg(dev, "resumed\n");
=======
<<<<<<< HEAD
	dev_dbg(dev, "resumed\n");
=======
	dev_dbg(dev, "runtime resumed\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static const struct dev_pm_ops samsung_pd_pm_ops = {
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	.suspend		= samsung_pd_suspend,
	.resume			= samsung_pd_resume,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.runtime_suspend	= samsung_pd_runtime_suspend,
	.runtime_resume		= samsung_pd_runtime_resume,
};

static struct platform_driver samsung_pd_driver = {
	.driver		= {
		.name		= "samsung-pd",
		.owner		= THIS_MODULE,
		.pm		= &samsung_pd_pm_ops,
	},
	.probe		= samsung_pd_probe,
	.remove		= __devexit_p(samsung_pd_remove),
};

static int __init samsung_pd_init(void)
{
	int ret;

	ret = platform_driver_register(&samsung_pd_driver);
	if (ret)
		printk(KERN_ERR "%s: failed to add PD driver\n", __func__);

	return ret;
}
arch_initcall(samsung_pd_init);
