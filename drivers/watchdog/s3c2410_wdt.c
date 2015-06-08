/* linux/drivers/char/watchdog/s3c2410_wdt.c
 *
 * Copyright (c) 2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 Watchdog Timer Support
 *
 * Based on, softdog.c by Alan Cox,
 *     (c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>
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
#include <linux/timer.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/miscdevice.h> /* for MODULE_ALIAS_MISCDEV */
#include <linux/watchdog.h>
=======
#include <linux/miscdevice.h>
#include <linux/watchdog.h>
#include <linux/fs.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/miscdevice.h>
#include <linux/watchdog.h>
#include <linux/fs.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/cpufreq.h>
#include <linux/slab.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/err.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <mach/map.h>

#undef S3C_VA_WATCHDOG
#define S3C_VA_WATCHDOG (0)

#include <plat/regs-watchdog.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define CONFIG_S3C2410_WATCHDOG_ATBOOT		(0)
#define CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME	(15)

static bool nowayout	= WATCHDOG_NOWAYOUT;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define PFX "s3c2410-wdt: "

#define CONFIG_S3C2410_WATCHDOG_ATBOOT		(0)
#define CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME	(15)

static int nowayout	= WATCHDOG_NOWAYOUT;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int tmr_margin	= CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME;
static int tmr_atboot	= CONFIG_S3C2410_WATCHDOG_ATBOOT;
static int soft_noboot;
static int debug;

module_param(tmr_margin,  int, 0);
module_param(tmr_atboot,  int, 0);
<<<<<<< HEAD
<<<<<<< HEAD
module_param(nowayout,   bool, 0);
=======
module_param(nowayout,    int, 0);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
module_param(nowayout,    int, 0);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
module_param(soft_noboot, int, 0);
module_param(debug,	  int, 0);

MODULE_PARM_DESC(tmr_margin, "Watchdog tmr_margin in seconds. (default="
		__MODULE_STRING(CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME) ")");
MODULE_PARM_DESC(tmr_atboot,
		"Watchdog is started at boot time if set to 1, default="
			__MODULE_STRING(CONFIG_S3C2410_WATCHDOG_ATBOOT));
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
MODULE_PARM_DESC(soft_noboot, "Watchdog action, set to 1 to ignore reboots, "
			"0 to reboot (default 0)");
MODULE_PARM_DESC(debug, "Watchdog debug, set to >1 for debug (default 0)");

<<<<<<< HEAD
<<<<<<< HEAD
=======
static unsigned long open_lock;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static unsigned long open_lock;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct device    *wdt_dev;	/* platform device attached to */
static struct resource	*wdt_mem;
static struct resource	*wdt_irq;
static struct clk	*wdt_clock;
static void __iomem	*wdt_base;
static unsigned int	 wdt_count;
<<<<<<< HEAD
<<<<<<< HEAD
=======
static char		 expect_close;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static char		 expect_close;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static DEFINE_SPINLOCK(wdt_lock);

/* watchdog control routines */

<<<<<<< HEAD
<<<<<<< HEAD
#define DBG(fmt, ...)					\
do {							\
	if (debug)					\
		pr_info(fmt, ##__VA_ARGS__);		\
} while (0)

/* functions */

static int s3c2410wdt_keepalive(struct watchdog_device *wdd)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define DBG(msg...) do { \
	if (debug) \
		printk(KERN_INFO msg); \
	} while (0)

/* functions */

static void s3c2410wdt_keepalive(void)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	spin_lock(&wdt_lock);
	writel(wdt_count, wdt_base + S3C2410_WTCNT);
	spin_unlock(&wdt_lock);
<<<<<<< HEAD
<<<<<<< HEAD

	return 0;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void __s3c2410wdt_stop(void)
{
	unsigned long wtcon;

	wtcon = readl(wdt_base + S3C2410_WTCON);
	wtcon &= ~(S3C2410_WTCON_ENABLE | S3C2410_WTCON_RSTEN);
	writel(wtcon, wdt_base + S3C2410_WTCON);
}

<<<<<<< HEAD
<<<<<<< HEAD
static int s3c2410wdt_stop(struct watchdog_device *wdd)
=======
static void s3c2410wdt_stop(void)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static void s3c2410wdt_stop(void)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	spin_lock(&wdt_lock);
	__s3c2410wdt_stop();
	spin_unlock(&wdt_lock);
<<<<<<< HEAD
<<<<<<< HEAD

	return 0;
}

static int s3c2410wdt_start(struct watchdog_device *wdd)
=======
}

static void s3c2410wdt_start(void)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
}

static void s3c2410wdt_start(void)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	unsigned long wtcon;

	spin_lock(&wdt_lock);

	__s3c2410wdt_stop();

	wtcon = readl(wdt_base + S3C2410_WTCON);
	wtcon |= S3C2410_WTCON_ENABLE | S3C2410_WTCON_DIV128;

	if (soft_noboot) {
		wtcon |= S3C2410_WTCON_INTEN;
		wtcon &= ~S3C2410_WTCON_RSTEN;
	} else {
		wtcon &= ~S3C2410_WTCON_INTEN;
		wtcon |= S3C2410_WTCON_RSTEN;
	}

	DBG("%s: wdt_count=0x%08x, wtcon=%08lx\n",
	    __func__, wdt_count, wtcon);

	writel(wdt_count, wdt_base + S3C2410_WTDAT);
	writel(wdt_count, wdt_base + S3C2410_WTCNT);
	writel(wtcon, wdt_base + S3C2410_WTCON);
	spin_unlock(&wdt_lock);
<<<<<<< HEAD
<<<<<<< HEAD

	return 0;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static inline int s3c2410wdt_is_running(void)
{
	return readl(wdt_base + S3C2410_WTCON) & S3C2410_WTCON_ENABLE;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int s3c2410wdt_set_heartbeat(struct watchdog_device *wdd, unsigned timeout)
=======
static int s3c2410wdt_set_heartbeat(int timeout)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int s3c2410wdt_set_heartbeat(int timeout)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	unsigned long freq = clk_get_rate(wdt_clock);
	unsigned int count;
	unsigned int divisor = 1;
	unsigned long wtcon;

	if (timeout < 1)
		return -EINVAL;

	freq /= 128;
	count = timeout * freq;

	DBG("%s: count=%d, timeout=%d, freq=%lu\n",
	    __func__, count, timeout, freq);

	/* if the count is bigger than the watchdog register,
	   then work out what we need to do (and if) we can
	   actually make this value
	*/

	if (count >= 0x10000) {
		for (divisor = 1; divisor <= 0x100; divisor++) {
			if ((count / divisor) < 0x10000)
				break;
		}

		if ((count / divisor) >= 0x10000) {
			dev_err(wdt_dev, "timeout %d too big\n", timeout);
			return -EINVAL;
		}
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======
	tmr_margin = timeout;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	tmr_margin = timeout;

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	DBG("%s: timeout=%d, divisor=%d, count=%d (%08x)\n",
	    __func__, timeout, divisor, count, count/divisor);

	count /= divisor;
	wdt_count = count;

	/* update the pre-scaler */
	wtcon = readl(wdt_base + S3C2410_WTCON);
	wtcon &= ~S3C2410_WTCON_PRESCALE_MASK;
	wtcon |= S3C2410_WTCON_PRESCALE(divisor-1);

	writel(count, wdt_base + S3C2410_WTDAT);
	writel(wtcon, wdt_base + S3C2410_WTCON);

<<<<<<< HEAD
<<<<<<< HEAD
	wdd->timeout = timeout;

	return 0;
}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

/*
 *	/dev/watchdog handling
 */

static int s3c2410wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &open_lock))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	expect_close = 0;

	/* start the timer */
	s3c2410wdt_start();
	return nonseekable_open(inode, file);
}

static int s3c2410wdt_release(struct inode *inode, struct file *file)
{
	/*
	 *	Shut off the timer.
	 *	Lock it in if it's a module and we set nowayout
	 */

	if (expect_close == 42)
		s3c2410wdt_stop();
	else {
		dev_err(wdt_dev, "Unexpected close, not stopping watchdog\n");
		s3c2410wdt_keepalive();
	}
	expect_close = 0;
	clear_bit(0, &open_lock);
	return 0;
}

static ssize_t s3c2410wdt_write(struct file *file, const char __user *data,
				size_t len, loff_t *ppos)
{
	/*
	 *	Refresh the timer.
	 */
	if (len) {
		if (!nowayout) {
			size_t i;

			/* In case it was set long ago */
			expect_close = 0;

			for (i = 0; i != len; i++) {
				char c;

				if (get_user(c, data + i))
					return -EFAULT;
				if (c == 'V')
					expect_close = 42;
			}
		}
		s3c2410wdt_keepalive();
	}
	return len;
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define OPTIONS (WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE)

static const struct watchdog_info s3c2410_wdt_ident = {
	.options          =     OPTIONS,
	.firmware_version =	0,
	.identity         =	"S3C2410 Watchdog",
};

<<<<<<< HEAD
<<<<<<< HEAD
static struct watchdog_ops s3c2410wdt_ops = {
	.owner = THIS_MODULE,
	.start = s3c2410wdt_start,
	.stop = s3c2410wdt_stop,
	.ping = s3c2410wdt_keepalive,
	.set_timeout = s3c2410wdt_set_heartbeat,
};

static struct watchdog_device s3c2410_wdd = {
	.info = &s3c2410_wdt_ident,
	.ops = &s3c2410wdt_ops,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static long s3c2410wdt_ioctl(struct file *file,	unsigned int cmd,
							unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int __user *p = argp;
	int new_margin;

	switch (cmd) {
	case WDIOC_GETSUPPORT:
		return copy_to_user(argp, &s3c2410_wdt_ident,
			sizeof(s3c2410_wdt_ident)) ? -EFAULT : 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		return put_user(0, p);
	case WDIOC_KEEPALIVE:
		s3c2410wdt_keepalive();
		return 0;
	case WDIOC_SETTIMEOUT:
		if (get_user(new_margin, p))
			return -EFAULT;
		if (s3c2410wdt_set_heartbeat(new_margin))
			return -EINVAL;
		s3c2410wdt_keepalive();
		return put_user(tmr_margin, p);
	case WDIOC_GETTIMEOUT:
		return put_user(tmr_margin, p);
	default:
		return -ENOTTY;
	}
}

/* kernel interface */

static const struct file_operations s3c2410wdt_fops = {
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.write		= s3c2410wdt_write,
	.unlocked_ioctl	= s3c2410wdt_ioctl,
	.open		= s3c2410wdt_open,
	.release	= s3c2410wdt_release,
};

static struct miscdevice s3c2410wdt_miscdev = {
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &s3c2410wdt_fops,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/* interrupt handler code */

static irqreturn_t s3c2410wdt_irq(int irqno, void *param)
{
	dev_info(wdt_dev, "watchdog timer expired (irq)\n");

<<<<<<< HEAD
<<<<<<< HEAD
	s3c2410wdt_keepalive(&s3c2410_wdd);
=======
	s3c2410wdt_keepalive();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	s3c2410wdt_keepalive();
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return IRQ_HANDLED;
}


#ifdef CONFIG_CPU_FREQ

static int s3c2410wdt_cpufreq_transition(struct notifier_block *nb,
					  unsigned long val, void *data)
{
	int ret;

	if (!s3c2410wdt_is_running())
		goto done;

	if (val == CPUFREQ_PRECHANGE) {
		/* To ensure that over the change we don't cause the
		 * watchdog to trigger, we perform an keep-alive if
		 * the watchdog is running.
		 */

<<<<<<< HEAD
<<<<<<< HEAD
		s3c2410wdt_keepalive(&s3c2410_wdd);
	} else if (val == CPUFREQ_POSTCHANGE) {
		s3c2410wdt_stop(&s3c2410_wdd);

		ret = s3c2410wdt_set_heartbeat(&s3c2410_wdd, s3c2410_wdd.timeout);

		if (ret >= 0)
			s3c2410wdt_start(&s3c2410_wdd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		s3c2410wdt_keepalive();
	} else if (val == CPUFREQ_POSTCHANGE) {
		s3c2410wdt_stop();

		ret = s3c2410wdt_set_heartbeat(tmr_margin);

		if (ret >= 0)
			s3c2410wdt_start();
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		else
			goto err;
	}

done:
	return 0;

 err:
<<<<<<< HEAD
<<<<<<< HEAD
	dev_err(wdt_dev, "cannot set new value for timeout %d\n",
				s3c2410_wdd.timeout);
=======
	dev_err(wdt_dev, "cannot set new value for timeout %d\n", tmr_margin);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	dev_err(wdt_dev, "cannot set new value for timeout %d\n", tmr_margin);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static struct notifier_block s3c2410wdt_cpufreq_transition_nb = {
	.notifier_call	= s3c2410wdt_cpufreq_transition,
};

static inline int s3c2410wdt_cpufreq_register(void)
{
	return cpufreq_register_notifier(&s3c2410wdt_cpufreq_transition_nb,
					 CPUFREQ_TRANSITION_NOTIFIER);
}

static inline void s3c2410wdt_cpufreq_deregister(void)
{
	cpufreq_unregister_notifier(&s3c2410wdt_cpufreq_transition_nb,
				    CPUFREQ_TRANSITION_NOTIFIER);
}

#else
static inline int s3c2410wdt_cpufreq_register(void)
{
	return 0;
}

static inline void s3c2410wdt_cpufreq_deregister(void)
{
}
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2


/* device interface */

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __devinit s3c2410wdt_probe(struct platform_device *pdev)
{
	struct device *dev;
	unsigned int wtcon;
	int started = 0;
	int ret;
	int size;

	DBG("%s: probe=%p\n", __func__, pdev);

	dev = &pdev->dev;
	wdt_dev = &pdev->dev;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	/* get the memory region for the watchdog timer */

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* get the memory region for the watchdog timer */

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	wdt_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (wdt_mem == NULL) {
		dev_err(dev, "no memory resource specified\n");
		return -ENOENT;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	wdt_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (wdt_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err;
	}

	/* get the memory region for the watchdog timer */

	size = resource_size(wdt_mem);
	if (!request_mem_region(wdt_mem->start, size, pdev->name)) {
		dev_err(dev, "failed to get memory region\n");
		ret = -EBUSY;
		goto err;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	size = resource_size(wdt_mem);
	if (!request_mem_region(wdt_mem->start, size, pdev->name)) {
		dev_err(dev, "failed to get memory region\n");
		return -EBUSY;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	wdt_base = ioremap(wdt_mem->start, size);
	if (wdt_base == NULL) {
		dev_err(dev, "failed to ioremap() region\n");
		ret = -EINVAL;
		goto err_req;
	}

	DBG("probe: mapped wdt_base=%p\n", wdt_base);

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	wdt_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (wdt_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err_map;
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	wdt_clock = clk_get(&pdev->dev, "watchdog");
	if (IS_ERR(wdt_clock)) {
		dev_err(dev, "failed to find watchdog clock source\n");
		ret = PTR_ERR(wdt_clock);
		goto err_map;
	}

	clk_enable(wdt_clock);

<<<<<<< HEAD
<<<<<<< HEAD
	ret = s3c2410wdt_cpufreq_register();
	if (ret < 0) {
		pr_err("failed to register cpufreq\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	* Watchdog timer should be stopped
	* before set prescaler to prevent unexpected expired watchdog timer
	*/
	if (!tmr_atboot)
		s3c2410wdt_stop();

	ret = s3c2410wdt_cpufreq_register();
	if (ret) {
		printk(KERN_ERR PFX "failed to register cpufreq\n");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto err_clk;
	}

	/* see if we can actually set the requested timer margin, and if
	 * not, try the default value */

<<<<<<< HEAD
<<<<<<< HEAD
	if (s3c2410wdt_set_heartbeat(&s3c2410_wdd, tmr_margin)) {
		started = s3c2410wdt_set_heartbeat(&s3c2410_wdd,
=======
	if (s3c2410wdt_set_heartbeat(tmr_margin)) {
		started = s3c2410wdt_set_heartbeat(
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (s3c2410wdt_set_heartbeat(tmr_margin)) {
		started = s3c2410wdt_set_heartbeat(
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME);

		if (started == 0)
			dev_info(dev,
			   "tmr_margin value out of range, default %d used\n",
			       CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME);
		else
			dev_info(dev, "default timer value is out of range, "
							"cannot start\n");
	}

<<<<<<< HEAD
<<<<<<< HEAD
	ret = request_irq(wdt_irq->start, s3c2410wdt_irq, 0, pdev->name, pdev);
	if (ret != 0) {
		dev_err(dev, "failed to install irq (%d)\n", ret);
		goto err_cpufreq;
	}

	watchdog_set_nowayout(&s3c2410_wdd, nowayout);

	ret = watchdog_register_device(&s3c2410_wdd);
	if (ret) {
		dev_err(dev, "cannot register watchdog (%d)\n", ret);
		goto err_irq;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = misc_register(&s3c2410wdt_miscdev);
	if (ret) {
		dev_err(dev, "cannot register miscdev on minor=%d (%d)\n",
			WATCHDOG_MINOR, ret);
		goto err_cpufreq;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if (tmr_atboot && started == 0) {
		dev_info(dev, "starting watchdog timer\n");
<<<<<<< HEAD
<<<<<<< HEAD
		s3c2410wdt_start(&s3c2410_wdd);
=======
		s3c2410wdt_start();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		s3c2410wdt_start();
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	} else if (!tmr_atboot) {
		/* if we're not enabling the watchdog, then ensure it is
		 * disabled if it has been left running from the bootloader
		 * or other source */

<<<<<<< HEAD
<<<<<<< HEAD
		s3c2410wdt_stop(&s3c2410_wdd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		s3c2410wdt_stop();
	}

	ret = request_irq(wdt_irq->start, s3c2410wdt_irq, 0, pdev->name, pdev);
	if (ret != 0) {
		dev_err(dev, "failed to install irq (%d)\n", ret);
		goto err_misc_reg;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	/* print out a statement of readiness */

	wtcon = readl(wdt_base + S3C2410_WTCON);

	dev_info(dev, "watchdog %sactive, reset %sabled, irq %sabled\n",
		 (wtcon & S3C2410_WTCON_ENABLE) ?  "" : "in",
<<<<<<< HEAD
<<<<<<< HEAD
		 (wtcon & S3C2410_WTCON_RSTEN) ? "en" : "dis",
		 (wtcon & S3C2410_WTCON_INTEN) ? "en" : "dis");

	return 0;

 err_irq:
	free_irq(wdt_irq->start, pdev);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 (wtcon & S3C2410_WTCON_RSTEN) ? "" : "dis",
		 (wtcon & S3C2410_WTCON_INTEN) ? "" : "en");

	return 0;

 err_misc_reg:
	misc_deregister(&s3c2410wdt_miscdev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 err_cpufreq:
	s3c2410wdt_cpufreq_deregister();

 err_clk:
	clk_disable(wdt_clock);
	clk_put(wdt_clock);
<<<<<<< HEAD
<<<<<<< HEAD
	wdt_clock = NULL;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

 err_map:
	iounmap(wdt_base);

 err_req:
	release_mem_region(wdt_mem->start, size);
<<<<<<< HEAD
<<<<<<< HEAD

 err:
	wdt_irq = NULL;
	wdt_mem = NULL;
=======
	wdt_mem = NULL;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	wdt_mem = NULL;

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int __devexit s3c2410wdt_remove(struct platform_device *dev)
{
<<<<<<< HEAD
<<<<<<< HEAD
	watchdog_unregister_device(&s3c2410_wdd);

	free_irq(wdt_irq->start, dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	free_irq(wdt_irq->start, dev);
	wdt_irq = NULL;

	misc_deregister(&s3c2410wdt_miscdev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	s3c2410wdt_cpufreq_deregister();

	clk_disable(wdt_clock);
	clk_put(wdt_clock);
	wdt_clock = NULL;

	iounmap(wdt_base);

	release_mem_region(wdt_mem->start, resource_size(wdt_mem));
<<<<<<< HEAD
<<<<<<< HEAD
	wdt_irq = NULL;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	wdt_mem = NULL;
	return 0;
}

static void s3c2410wdt_shutdown(struct platform_device *dev)
{
<<<<<<< HEAD
<<<<<<< HEAD
	s3c2410wdt_stop(&s3c2410_wdd);
=======
	s3c2410wdt_stop();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	s3c2410wdt_stop();
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

#ifdef CONFIG_PM

static unsigned long wtcon_save;
static unsigned long wtdat_save;

static int s3c2410wdt_suspend(struct platform_device *dev, pm_message_t state)
{
	/* Save watchdog state, and turn it off. */
	wtcon_save = readl(wdt_base + S3C2410_WTCON);
	wtdat_save = readl(wdt_base + S3C2410_WTDAT);

	/* Note that WTCNT doesn't need to be saved. */
<<<<<<< HEAD
<<<<<<< HEAD
	s3c2410wdt_stop(&s3c2410_wdd);
=======
	s3c2410wdt_stop();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	s3c2410wdt_stop();
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static int s3c2410wdt_resume(struct platform_device *dev)
{
	/* Restore watchdog state. */

	writel(wtdat_save, wdt_base + S3C2410_WTDAT);
	writel(wtdat_save, wdt_base + S3C2410_WTCNT); /* Reset count */
	writel(wtcon_save, wdt_base + S3C2410_WTCON);

<<<<<<< HEAD
<<<<<<< HEAD
	pr_info("watchdog %sabled\n",
		(wtcon_save & S3C2410_WTCON_ENABLE) ? "en" : "dis");
=======
	printk(KERN_INFO PFX "watchdog %sabled\n",
	       (wtcon_save & S3C2410_WTCON_ENABLE) ? "en" : "dis");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO PFX "watchdog %sabled\n",
	       (wtcon_save & S3C2410_WTCON_ENABLE) ? "en" : "dis");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

#else
#define s3c2410wdt_suspend NULL
#define s3c2410wdt_resume  NULL
#endif /* CONFIG_PM */

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_OF
static const struct of_device_id s3c2410_wdt_match[] = {
	{ .compatible = "samsung,s3c2410-wdt" },
	{},
};
MODULE_DEVICE_TABLE(of, s3c2410_wdt_match);
#else
#define s3c2410_wdt_match NULL
#endif
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static struct platform_driver s3c2410wdt_driver = {
	.probe		= s3c2410wdt_probe,
	.remove		= __devexit_p(s3c2410wdt_remove),
	.shutdown	= s3c2410wdt_shutdown,
	.suspend	= s3c2410wdt_suspend,
	.resume		= s3c2410wdt_resume,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "s3c2410-wdt",
<<<<<<< HEAD
<<<<<<< HEAD
		.of_match_table	= s3c2410_wdt_match,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	},
};


<<<<<<< HEAD
<<<<<<< HEAD
static int __init watchdog_init(void)
{
	pr_info("S3C2410 Watchdog Timer, (c) 2004 Simtec Electronics\n");

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static char banner[] __initdata =
	KERN_INFO "S3C2410 Watchdog Timer, (c) 2004 Simtec Electronics\n";

static int __init watchdog_init(void)
{
	printk(banner);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return platform_driver_register(&s3c2410wdt_driver);
}

static void __exit watchdog_exit(void)
{
	platform_driver_unregister(&s3c2410wdt_driver);
}

module_init(watchdog_init);
module_exit(watchdog_exit);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>, "
	      "Dimitry Andric <dimitry.andric@tomtom.com>");
MODULE_DESCRIPTION("S3C2410 Watchdog Device Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(WATCHDOG_MINOR);
MODULE_ALIAS("platform:s3c2410-wdt");
