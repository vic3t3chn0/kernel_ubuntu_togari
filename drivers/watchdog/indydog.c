/*
 *	IndyDog	0.3	A Hardware Watchdog Device for SGI IP22
 *
 *	(c) Copyright 2002 Guido Guenther <agx@sigxcpu.org>,
 *						All Rights Reserved.
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 *	based on softdog.c by Alan Cox <alan@lxorguk.ukuu.org.uk>
 */

<<<<<<< HEAD
<<<<<<< HEAD
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/watchdog.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <asm/sgi/mc.h>

<<<<<<< HEAD
<<<<<<< HEAD
static unsigned long indydog_alive;
static DEFINE_SPINLOCK(indydog_lock);

#define WATCHDOG_TIMEOUT 30		/* 30 sec default timeout */

static bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define PFX "indydog: "
static unsigned long indydog_alive;
static spinlock_t indydog_lock;

#define WATCHDOG_TIMEOUT 30		/* 30 sec default timeout */

static int nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, int, 0);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

static void indydog_start(void)
{
	u32 mc_ctrl0;

	spin_lock(&indydog_lock);
	mc_ctrl0 = sgimc->cpuctrl0;
	mc_ctrl0 = sgimc->cpuctrl0 | SGIMC_CCTRL0_WDOG;
	sgimc->cpuctrl0 = mc_ctrl0;
	spin_unlock(&indydog_lock);
}

static void indydog_stop(void)
{
	u32 mc_ctrl0;

	spin_lock(&indydog_lock);

	mc_ctrl0 = sgimc->cpuctrl0;
	mc_ctrl0 &= ~SGIMC_CCTRL0_WDOG;
	sgimc->cpuctrl0 = mc_ctrl0;
	spin_unlock(&indydog_lock);

<<<<<<< HEAD
<<<<<<< HEAD
	pr_info("Stopped watchdog timer\n");
=======
	printk(KERN_INFO PFX "Stopped watchdog timer.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO PFX "Stopped watchdog timer.\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void indydog_ping(void)
{
	sgimc->watchdogt = 0;
}

/*
 *	Allow only one person to hold it open
 */
static int indydog_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &indydog_alive))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	/* Activate timer */
	indydog_start();
	indydog_ping();

<<<<<<< HEAD
<<<<<<< HEAD
	pr_info("Started watchdog timer\n");
=======
	printk(KERN_INFO "Started watchdog timer.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO "Started watchdog timer.\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return nonseekable_open(inode, file);
}

static int indydog_release(struct inode *inode, struct file *file)
{
	/* Shut off the timer.
	 * Lock it in if it's a module and we defined ...NOWAYOUT */
	if (!nowayout)
		indydog_stop();		/* Turn the WDT off */
	clear_bit(0, &indydog_alive);
	return 0;
}

static ssize_t indydog_write(struct file *file, const char *data,
						size_t len, loff_t *ppos)
{
	/* Refresh the timer. */
	if (len)
		indydog_ping();
	return len;
}

static long indydog_ioctl(struct file *file, unsigned int cmd,
							unsigned long arg)
{
	int options, retval = -EINVAL;
	static const struct watchdog_info ident = {
		.options		= WDIOF_KEEPALIVEPING,
		.firmware_version	= 0,
		.identity		= "Hardware Watchdog for SGI IP22",
	};

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		if (copy_to_user((struct watchdog_info *)arg,
				 &ident, sizeof(ident)))
			return -EFAULT;
		return 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		return put_user(0, (int *)arg);
	case WDIOC_SETOPTIONS:
	{
		if (get_user(options, (int *)arg))
			return -EFAULT;
		if (options & WDIOS_DISABLECARD) {
			indydog_stop();
			retval = 0;
		}
		if (options & WDIOS_ENABLECARD) {
			indydog_start();
			retval = 0;
		}
		return retval;
	}
	case WDIOC_KEEPALIVE:
		indydog_ping();
		return 0;
	case WDIOC_GETTIMEOUT:
		return put_user(WATCHDOG_TIMEOUT, (int *)arg);
	default:
		return -ENOTTY;
	}
}

static int indydog_notify_sys(struct notifier_block *this,
					unsigned long code, void *unused)
{
	if (code == SYS_DOWN || code == SYS_HALT)
		indydog_stop();		/* Turn the WDT off */

	return NOTIFY_DONE;
}

static const struct file_operations indydog_fops = {
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.write		= indydog_write,
	.unlocked_ioctl	= indydog_ioctl,
	.open		= indydog_open,
	.release	= indydog_release,
};

static struct miscdevice indydog_miscdev = {
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &indydog_fops,
};

static struct notifier_block indydog_notifier = {
	.notifier_call = indydog_notify_sys,
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
static char banner[] __initdata =
	KERN_INFO PFX "Hardware Watchdog Timer for SGI IP22: 0.3\n";

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static char banner[] __initdata =
	KERN_INFO PFX "Hardware Watchdog Timer for SGI IP22: 0.3\n";

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init watchdog_init(void)
{
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = register_reboot_notifier(&indydog_notifier);
	if (ret) {
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_init(&indydog_lock);

	ret = register_reboot_notifier(&indydog_notifier);
	if (ret) {
		printk(KERN_ERR PFX
			"cannot register reboot notifier (err=%d)\n", ret);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ret;
	}

	ret = misc_register(&indydog_miscdev);
	if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
=======
		printk(KERN_ERR PFX
			"cannot register miscdev on minor=%d (err=%d)\n",
							WATCHDOG_MINOR, ret);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR PFX
			"cannot register miscdev on minor=%d (err=%d)\n",
							WATCHDOG_MINOR, ret);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		unregister_reboot_notifier(&indydog_notifier);
		return ret;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	pr_info("Hardware Watchdog Timer for SGI IP22: 0.3\n");
=======
	printk(banner);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(banner);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static void __exit watchdog_exit(void)
{
	misc_deregister(&indydog_miscdev);
	unregister_reboot_notifier(&indydog_notifier);
}

module_init(watchdog_init);
module_exit(watchdog_exit);

MODULE_AUTHOR("Guido Guenther <agx@sigxcpu.org>");
MODULE_DESCRIPTION("Hardware Watchdog Device for SGI IP22");
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(WATCHDOG_MINOR);
