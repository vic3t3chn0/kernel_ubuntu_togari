/*
 * Support for hardware-assisted userspace interrupt masking.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#define pr_fmt(fmt) "intc: " fmt

#include <linux/errno.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/device.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/stat.h>
=======
#include <linux/sysdev.h>
#include <linux/init.h>
#include <linux/io.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/sysdev.h>
#include <linux/init.h>
#include <linux/io.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/sizes.h>
#include "internals.h"

static void __iomem *uimask;

static ssize_t
<<<<<<< HEAD
<<<<<<< HEAD
show_intc_userimask(struct device *dev,
		    struct device_attribute *attr, char *buf)
=======
show_intc_userimask(struct sysdev_class *cls,
		    struct sysdev_class_attribute *attr, char *buf)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
show_intc_userimask(struct sysdev_class *cls,
		    struct sysdev_class_attribute *attr, char *buf)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return sprintf(buf, "%d\n", (__raw_readl(uimask) >> 4) & 0xf);
}

static ssize_t
<<<<<<< HEAD
<<<<<<< HEAD
store_intc_userimask(struct device *dev,
		     struct device_attribute *attr,
=======
store_intc_userimask(struct sysdev_class *cls,
		     struct sysdev_class_attribute *attr,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
store_intc_userimask(struct sysdev_class *cls,
		     struct sysdev_class_attribute *attr,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		     const char *buf, size_t count)
{
	unsigned long level;

	level = simple_strtoul(buf, NULL, 10);

	/*
	 * Minimal acceptable IRQ levels are in the 2 - 16 range, but
	 * these are chomped so as to not interfere with normal IRQs.
	 *
	 * Level 1 is a special case on some CPUs in that it's not
	 * directly settable, but given that USERIMASK cuts off below a
	 * certain level, we don't care about this limitation here.
	 * Level 0 on the other hand equates to user masking disabled.
	 *
	 * We use the default priority level as a cut off so that only
	 * special case opt-in IRQs can be mangled.
	 */
	if (level >= intc_get_dfl_prio_level())
		return -EINVAL;

	__raw_writel(0xa5 << 24 | level << 4, uimask);

	return count;
}

<<<<<<< HEAD
<<<<<<< HEAD
static DEVICE_ATTR(userimask, S_IRUSR | S_IWUSR,
		   show_intc_userimask, store_intc_userimask);
=======
static SYSDEV_CLASS_ATTR(userimask, S_IRUSR | S_IWUSR,
			 show_intc_userimask, store_intc_userimask);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static SYSDEV_CLASS_ATTR(userimask, S_IRUSR | S_IWUSR,
			 show_intc_userimask, store_intc_userimask);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2


static int __init userimask_sysdev_init(void)
{
	if (unlikely(!uimask))
		return -ENXIO;

<<<<<<< HEAD
<<<<<<< HEAD
	return device_create_file(intc_subsys.dev_root, &dev_attr_userimask);
=======
	return sysdev_class_create_file(&intc_sysdev_class, &attr_userimask);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return sysdev_class_create_file(&intc_sysdev_class, &attr_userimask);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
late_initcall(userimask_sysdev_init);

int register_intc_userimask(unsigned long addr)
{
	if (unlikely(uimask))
		return -EBUSY;

	uimask = ioremap_nocache(addr, SZ_4K);
	if (unlikely(!uimask))
		return -ENOMEM;

	pr_info("userimask support registered for levels 0 -> %d\n",
		intc_get_dfl_prio_level() - 1);

	return 0;
}
