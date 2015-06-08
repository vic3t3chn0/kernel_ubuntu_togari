/*
 * Watchdog driver for the wm8350
 *
 * Copyright (C) 2007, 2008 Wolfson Microelectronics <linux@wolfsonmicro.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation
 */

<<<<<<< HEAD
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/kernel.h>
<<<<<<< HEAD
=======
#include <linux/fs.h>
#include <linux/miscdevice.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
#include <linux/platform_device.h>
#include <linux/watchdog.h>
#include <linux/uaccess.h>
#include <linux/mfd/wm8350/core.h>

<<<<<<< HEAD
static bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
=======
static int nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, int, 0);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

<<<<<<< HEAD
static DEFINE_MUTEX(wdt_mutex);

static struct {
	unsigned int time;  /* Seconds */
	u16 val;	    /* To be set in WM8350_SYSTEM_CONTROL_2 */
=======
static unsigned long wm8350_wdt_users;
static struct miscdevice wm8350_wdt_miscdev;
static int wm8350_wdt_expect_close;
static DEFINE_MUTEX(wdt_mutex);

static struct {
	int time;  /* Seconds */
	u16 val;   /* To be set in WM8350_SYSTEM_CONTROL_2 */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
} wm8350_wdt_cfgs[] = {
	{ 1, 0x02 },
	{ 2, 0x04 },
	{ 4, 0x05 },
};

<<<<<<< HEAD
static int wm8350_wdt_set_timeout(struct watchdog_device *wdt_dev,
				  unsigned int timeout)
{
	struct wm8350 *wm8350 = watchdog_get_drvdata(wdt_dev);
	int ret, i;
	u16 reg;

	for (i = 0; i < ARRAY_SIZE(wm8350_wdt_cfgs); i++)
		if (wm8350_wdt_cfgs[i].time == timeout)
			break;
	if (i == ARRAY_SIZE(wm8350_wdt_cfgs))
		return -EINVAL;
=======
static struct wm8350 *get_wm8350(void)
{
	return dev_get_drvdata(wm8350_wdt_miscdev.parent);
}

static int wm8350_wdt_set_timeout(struct wm8350 *wm8350, u16 value)
{
	int ret;
	u16 reg;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_read(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_TO_MASK;
<<<<<<< HEAD
	reg |= wm8350_wdt_cfgs[i].val;
=======
	reg |= value;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	ret = wm8350_reg_write(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

<<<<<<< HEAD
	wdt_dev->timeout = timeout;
	return ret;
}

static int wm8350_wdt_start(struct watchdog_device *wdt_dev)
{
	struct wm8350 *wm8350 = watchdog_get_drvdata(wdt_dev);
=======
	return ret;
}

static int wm8350_wdt_start(struct wm8350 *wm8350)
{
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	int ret;
	u16 reg;

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_read(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_MODE_MASK;
	reg |= 0x20;
	ret = wm8350_reg_write(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

	return ret;
}

<<<<<<< HEAD
static int wm8350_wdt_stop(struct watchdog_device *wdt_dev)
{
	struct wm8350 *wm8350 = watchdog_get_drvdata(wdt_dev);
=======
static int wm8350_wdt_stop(struct wm8350 *wm8350)
{
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	int ret;
	u16 reg;

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_read(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_MODE_MASK;
	ret = wm8350_reg_write(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

	return ret;
}

<<<<<<< HEAD
static int wm8350_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct wm8350 *wm8350 = watchdog_get_drvdata(wdt_dev);
=======
static int wm8350_wdt_kick(struct wm8350 *wm8350)
{
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	int ret;
	u16 reg;

	mutex_lock(&wdt_mutex);

	reg = wm8350_reg_read(wm8350, WM8350_SYSTEM_CONTROL_2);
	ret = wm8350_reg_write(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	mutex_unlock(&wdt_mutex);

	return ret;
}

<<<<<<< HEAD
static const struct watchdog_info wm8350_wdt_info = {
=======
static int wm8350_wdt_open(struct inode *inode, struct file *file)
{
	struct wm8350 *wm8350 = get_wm8350();
	int ret;

	if (!wm8350)
		return -ENODEV;

	if (test_and_set_bit(0, &wm8350_wdt_users))
		return -EBUSY;

	ret = wm8350_wdt_start(wm8350);
	if (ret != 0)
		return ret;

	return nonseekable_open(inode, file);
}

static int wm8350_wdt_release(struct inode *inode, struct file *file)
{
	struct wm8350 *wm8350 = get_wm8350();

	if (wm8350_wdt_expect_close)
		wm8350_wdt_stop(wm8350);
	else {
		dev_warn(wm8350->dev, "Watchdog device closed uncleanly\n");
		wm8350_wdt_kick(wm8350);
	}

	clear_bit(0, &wm8350_wdt_users);

	return 0;
}

static ssize_t wm8350_wdt_write(struct file *file,
				const char __user *data, size_t count,
				loff_t *ppos)
{
	struct wm8350 *wm8350 = get_wm8350();
	size_t i;

	if (count) {
		wm8350_wdt_kick(wm8350);

		if (!nowayout) {
			/* In case it was set long ago */
			wm8350_wdt_expect_close = 0;

			/* scan to see whether or not we got the magic
			   character */
			for (i = 0; i != count; i++) {
				char c;
				if (get_user(c, data + i))
					return -EFAULT;
				if (c == 'V')
					wm8350_wdt_expect_close = 42;
			}
		}
	}
	return count;
}

static const struct watchdog_info ident = {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "WM8350 Watchdog",
};

<<<<<<< HEAD
static const struct watchdog_ops wm8350_wdt_ops = {
	.owner = THIS_MODULE,
	.start = wm8350_wdt_start,
	.stop = wm8350_wdt_stop,
	.ping = wm8350_wdt_ping,
	.set_timeout = wm8350_wdt_set_timeout,
};

static struct watchdog_device wm8350_wdt = {
	.info = &wm8350_wdt_info,
	.ops = &wm8350_wdt_ops,
	.timeout = 4,
	.min_timeout = 1,
	.max_timeout = 4,
=======
static long wm8350_wdt_ioctl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	struct wm8350 *wm8350 = get_wm8350();
	int ret = -ENOTTY, time, i;
	void __user *argp = (void __user *)arg;
	int __user *p = argp;
	u16 reg;

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		ret = copy_to_user(argp, &ident, sizeof(ident)) ? -EFAULT : 0;
		break;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		ret = put_user(0, p);
		break;

	case WDIOC_SETOPTIONS:
	{
		int options;

		if (get_user(options, p))
			return -EFAULT;

		ret = -EINVAL;

		/* Setting both simultaneously means at least one must fail */
		if (options == WDIOS_DISABLECARD)
			ret = wm8350_wdt_start(wm8350);

		if (options == WDIOS_ENABLECARD)
			ret = wm8350_wdt_stop(wm8350);
		break;
	}

	case WDIOC_KEEPALIVE:
		ret = wm8350_wdt_kick(wm8350);
		break;

	case WDIOC_SETTIMEOUT:
		ret = get_user(time, p);
		if (ret)
			break;

		if (time == 0) {
			if (nowayout)
				ret = -EINVAL;
			else
				wm8350_wdt_stop(wm8350);
			break;
		}

		for (i = 0; i < ARRAY_SIZE(wm8350_wdt_cfgs); i++)
			if (wm8350_wdt_cfgs[i].time == time)
				break;
		if (i == ARRAY_SIZE(wm8350_wdt_cfgs))
			ret = -EINVAL;
		else
			ret = wm8350_wdt_set_timeout(wm8350,
						     wm8350_wdt_cfgs[i].val);
		break;

	case WDIOC_GETTIMEOUT:
		reg = wm8350_reg_read(wm8350, WM8350_SYSTEM_CONTROL_2);
		reg &= WM8350_WDOG_TO_MASK;
		for (i = 0; i < ARRAY_SIZE(wm8350_wdt_cfgs); i++)
			if (wm8350_wdt_cfgs[i].val == reg)
				break;
		if (i == ARRAY_SIZE(wm8350_wdt_cfgs)) {
			dev_warn(wm8350->dev,
				 "Unknown watchdog configuration: %x\n", reg);
			ret = -EINVAL;
		} else
			ret = put_user(wm8350_wdt_cfgs[i].time, p);

	}

	return ret;
}

static const struct file_operations wm8350_wdt_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.write = wm8350_wdt_write,
	.unlocked_ioctl = wm8350_wdt_ioctl,
	.open = wm8350_wdt_open,
	.release = wm8350_wdt_release,
};

static struct miscdevice wm8350_wdt_miscdev = {
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &wm8350_wdt_fops,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
};

static int __devinit wm8350_wdt_probe(struct platform_device *pdev)
{
	struct wm8350 *wm8350 = platform_get_drvdata(pdev);

	if (!wm8350) {
		pr_err("No driver data supplied\n");
		return -ENODEV;
	}

<<<<<<< HEAD
	watchdog_set_nowayout(&wm8350_wdt, nowayout);
	watchdog_set_drvdata(&wm8350_wdt, wm8350);

	/* Default to 4s timeout */
	wm8350_wdt_set_timeout(&wm8350_wdt, 4);

	return watchdog_register_device(&wm8350_wdt);
=======
	/* Default to 4s timeout */
	wm8350_wdt_set_timeout(wm8350, 0x05);

	wm8350_wdt_miscdev.parent = &pdev->dev;

	return misc_register(&wm8350_wdt_miscdev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static int __devexit wm8350_wdt_remove(struct platform_device *pdev)
{
<<<<<<< HEAD
	watchdog_unregister_device(&wm8350_wdt);
=======
	misc_deregister(&wm8350_wdt_miscdev);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

static struct platform_driver wm8350_wdt_driver = {
	.probe = wm8350_wdt_probe,
	.remove = __devexit_p(wm8350_wdt_remove),
	.driver = {
		.name = "wm8350-wdt",
	},
};

<<<<<<< HEAD
module_platform_driver(wm8350_wdt_driver);
=======
static int __init wm8350_wdt_init(void)
{
	return platform_driver_register(&wm8350_wdt_driver);
}
module_init(wm8350_wdt_init);

static void __exit wm8350_wdt_exit(void)
{
	platform_driver_unregister(&wm8350_wdt_driver);
}
module_exit(wm8350_wdt_exit);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("WM8350 Watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-wdt");
