/*
 * PowerPC 64-bit swsusp implementation
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 *
 * GPLv2
 */

<<<<<<< HEAD
#include <asm/iommu.h>
#include <linux/irq.h>
#include <linux/sched.h>
=======
<<<<<<< HEAD
#include <asm/iommu.h>
#include <linux/irq.h>
#include <linux/sched.h>
=======
#include <asm/system.h>
#include <asm/iommu.h>
#include <linux/irq.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/interrupt.h>

void do_after_copyback(void)
{
	iommu_restore();
	touch_softlockup_watchdog();
	mb();
}

void _iommu_save(void)
{
	iommu_save();
}
