/*
 * linux/arch/arm/mach-mmp/time.c
 *
 *   Support for clocksource and clockevents
 *
 * Copyright (C) 2008 Marvell International Ltd.
 * All rights reserved.
 *
 *   2008-04-11: Jason Chagas <Jason.chagas@marvell.com>
 *   2008-10-08: Bin Yang <bin.yang@marvell.com>
 *
 * The timers module actually includes three timers, each timer with up to
 * three match comparators. Timer #0 is used here in free-running mode as
 * the clock source, and match comparator #1 used as clock event device.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/clockchips.h>

#include <linux/io.h>
#include <linux/irq.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <linux/sched.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <asm/sched_clock.h>
#include <mach/addr-map.h>
#include <mach/regs-timers.h>
#include <mach/regs-apbc.h>
#include <mach/irqs.h>
#include <mach/cputype.h>
#include <asm/mach/time.h>

#include "clock.h"

#define TIMERS_VIRT_BASE	TIMERS1_VIRT_BASE

#define MAX_DELTA		(0xfffffffe)
#define MIN_DELTA		(16)

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
static DEFINE_CLOCK_DATA(cd);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * FIXME: the timer needs some delay to stablize the counter capture
 */
static inline uint32_t timer_read(void)
{
	int delay = 100;

<<<<<<< HEAD
	__raw_writel(1, TIMERS_VIRT_BASE + TMR_CVWR(1));
=======
<<<<<<< HEAD
	__raw_writel(1, TIMERS_VIRT_BASE + TMR_CVWR(1));
=======
	__raw_writel(1, TIMERS_VIRT_BASE + TMR_CVWR(0));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	while (delay--)
		cpu_relax();

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return __raw_readl(TIMERS_VIRT_BASE + TMR_CVWR(1));
}

static u32 notrace mmp_read_sched_clock(void)
{
	return timer_read();
<<<<<<< HEAD
=======
=======
	return __raw_readl(TIMERS_VIRT_BASE + TMR_CVWR(0));
}

unsigned long long notrace sched_clock(void)
{
	u32 cyc = timer_read();
	return cyc_to_sched_clock(&cd, cyc, (u32)~0);
}

static void notrace mmp_update_sched_clock(void)
{
	u32 cyc = timer_read();
	update_sched_clock(&cd, cyc, (u32)~0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * Clear pending interrupt status.
	 */
	__raw_writel(0x01, TIMERS_VIRT_BASE + TMR_ICR(0));

	/*
	 * Disable timer 0.
	 */
	__raw_writel(0x02, TIMERS_VIRT_BASE + TMR_CER);

	c->event_handler(c);

<<<<<<< HEAD
=======
=======
	/* disable and clear pending interrupt status */
	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_IER(0));
	__raw_writel(0x1, TIMERS_VIRT_BASE + TMR_ICR(0));
	c->event_handler(c);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return IRQ_HANDLED;
}

static int timer_set_next_event(unsigned long delta,
				struct clock_event_device *dev)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long flags;

	local_irq_save(flags);

	/*
	 * Disable timer 0.
	 */
	__raw_writel(0x02, TIMERS_VIRT_BASE + TMR_CER);

	/*
	 * Clear and enable timer match 0 interrupt.
	 */
	__raw_writel(0x01, TIMERS_VIRT_BASE + TMR_ICR(0));
	__raw_writel(0x01, TIMERS_VIRT_BASE + TMR_IER(0));

	/*
	 * Setup new clockevent timer value.
	 */
	__raw_writel(delta - 1, TIMERS_VIRT_BASE + TMR_TN_MM(0, 0));

	/*
	 * Enable timer 0.
	 */
	__raw_writel(0x03, TIMERS_VIRT_BASE + TMR_CER);

	local_irq_restore(flags);

<<<<<<< HEAD
=======
=======
	unsigned long flags, next;

	local_irq_save(flags);

	/* clear pending interrupt status and enable */
	__raw_writel(0x01, TIMERS_VIRT_BASE + TMR_ICR(0));
	__raw_writel(0x01, TIMERS_VIRT_BASE + TMR_IER(0));

	next = timer_read() + delta;
	__raw_writel(next, TIMERS_VIRT_BASE + TMR_TN_MM(0, 0));

	local_irq_restore(flags);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static void timer_set_mode(enum clock_event_mode mode,
			   struct clock_event_device *dev)
{
	unsigned long flags;

	local_irq_save(flags);
	switch (mode) {
	case CLOCK_EVT_MODE_ONESHOT:
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		/* disable the matching interrupt */
		__raw_writel(0x00, TIMERS_VIRT_BASE + TMR_IER(0));
		break;
	case CLOCK_EVT_MODE_RESUME:
	case CLOCK_EVT_MODE_PERIODIC:
		break;
	}
	local_irq_restore(flags);
}

static struct clock_event_device ckevt = {
	.name		= "clockevent",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.shift		= 32,
	.rating		= 200,
	.set_next_event	= timer_set_next_event,
	.set_mode	= timer_set_mode,
};

static cycle_t clksrc_read(struct clocksource *cs)
{
	return timer_read();
}

static struct clocksource cksrc = {
	.name		= "clocksource",
	.rating		= 200,
	.read		= clksrc_read,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};

static void __init timer_config(void)
{
	uint32_t ccr = __raw_readl(TIMERS_VIRT_BASE + TMR_CCR);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_CER); /* disable */

	ccr &= (cpu_is_mmp2()) ? (TMR_CCR_CS_0(0) | TMR_CCR_CS_1(0)) :
		(TMR_CCR_CS_0(3) | TMR_CCR_CS_1(3));
	__raw_writel(ccr, TIMERS_VIRT_BASE + TMR_CCR);

	/* set timer 0 to periodic mode, and timer 1 to free-running mode */
	__raw_writel(0x2, TIMERS_VIRT_BASE + TMR_CMR);

	__raw_writel(0x1, TIMERS_VIRT_BASE + TMR_PLCR(0)); /* periodic */
	__raw_writel(0x7, TIMERS_VIRT_BASE + TMR_ICR(0));  /* clear status */
	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_IER(0));

	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_PLCR(1)); /* free-running */
	__raw_writel(0x7, TIMERS_VIRT_BASE + TMR_ICR(1));  /* clear status */
	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_IER(1));

	/* enable timer 1 counter */
	__raw_writel(0x2, TIMERS_VIRT_BASE + TMR_CER);
<<<<<<< HEAD
=======
=======
	uint32_t cer = __raw_readl(TIMERS_VIRT_BASE + TMR_CER);
	uint32_t cmr = __raw_readl(TIMERS_VIRT_BASE + TMR_CMR);

	__raw_writel(cer & ~0x1, TIMERS_VIRT_BASE + TMR_CER); /* disable */

	ccr &= (cpu_is_mmp2()) ? TMR_CCR_CS_0(0) : TMR_CCR_CS_0(3);
	__raw_writel(ccr, TIMERS_VIRT_BASE + TMR_CCR);

	/* free-running mode */
	__raw_writel(cmr | 0x01, TIMERS_VIRT_BASE + TMR_CMR);

	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_PLCR(0)); /* free-running */
	__raw_writel(0x7, TIMERS_VIRT_BASE + TMR_ICR(0));  /* clear status */
	__raw_writel(0x0, TIMERS_VIRT_BASE + TMR_IER(0));

	/* enable timer counter */
	__raw_writel(cer | 0x01, TIMERS_VIRT_BASE + TMR_CER);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct irqaction timer_irq = {
	.name		= "timer",
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= timer_interrupt,
	.dev_id		= &ckevt,
};

void __init timer_init(int irq)
{
	timer_config();

<<<<<<< HEAD
	setup_sched_clock(mmp_read_sched_clock, 32, CLOCK_TICK_RATE);
=======
<<<<<<< HEAD
	setup_sched_clock(mmp_read_sched_clock, 32, CLOCK_TICK_RATE);
=======
	init_sched_clock(&cd, mmp_update_sched_clock, 32, CLOCK_TICK_RATE);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	ckevt.mult = div_sc(CLOCK_TICK_RATE, NSEC_PER_SEC, ckevt.shift);
	ckevt.max_delta_ns = clockevent_delta2ns(MAX_DELTA, &ckevt);
	ckevt.min_delta_ns = clockevent_delta2ns(MIN_DELTA, &ckevt);
	ckevt.cpumask = cpumask_of(0);

	setup_irq(irq, &timer_irq);

	clocksource_register_hz(&cksrc, CLOCK_TICK_RATE);
	clockevents_register_device(&ckevt);
}
