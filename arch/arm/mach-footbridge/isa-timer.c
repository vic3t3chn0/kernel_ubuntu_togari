/*
 *  linux/arch/arm/mach-footbridge/isa-timer.c
 *
 *  Copyright (C) 1998 Russell King.
 *  Copyright (C) 1998 Phil Blundell
 */
#include <linux/clockchips.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/i8253.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
<<<<<<< HEAD
=======
=======
#include <linux/clocksource.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/spinlock.h>
#include <linux/timex.h>

#include <asm/irq.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <asm/i8253.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/mach/time.h>

#include "common.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
DEFINE_RAW_SPINLOCK(i8253_lock);

static void pit_set_mode(enum clock_event_mode mode,
	struct clock_event_device *evt)
{
	unsigned long flags;

	raw_local_irq_save(flags);

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		outb_p(0x34, PIT_MODE);
		outb_p(PIT_LATCH & 0xff, PIT_CH0);
		outb_p(PIT_LATCH >> 8, PIT_CH0);
		break;

	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:
		outb_p(0x30, PIT_MODE);
		outb_p(0, PIT_CH0);
		outb_p(0, PIT_CH0);
		break;

	case CLOCK_EVT_MODE_ONESHOT:
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
	local_irq_restore(flags);
}

static int pit_set_next_event(unsigned long delta,
	struct clock_event_device *evt)
{
	return 0;
}

static struct clock_event_device pit_ce = {
	.name		= "pit",
	.features	= CLOCK_EVT_FEAT_PERIODIC,
	.set_mode	= pit_set_mode,
	.set_next_event	= pit_set_next_event,
	.shift		= 32,
};

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static irqreturn_t pit_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *ce = dev_id;
	ce->event_handler(ce);
	return IRQ_HANDLED;
}

static struct irqaction pit_timer_irq = {
	.name		= "pit",
	.handler	= pit_timer_interrupt,
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
<<<<<<< HEAD
	.dev_id		= &i8253_clockevent,
=======
<<<<<<< HEAD
	.dev_id		= &i8253_clockevent,
=======
	.dev_id		= &pit_ce,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static void __init isa_timer_init(void)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	clocksource_i8253_init();

	setup_irq(i8253_clockevent.irq, &pit_timer_irq);
	clockevent_i8253_init(false);
<<<<<<< HEAD
=======
=======
	pit_ce.cpumask = cpumask_of(smp_processor_id());
	pit_ce.mult = div_sc(PIT_TICK_RATE, NSEC_PER_SEC, pit_ce.shift);
	pit_ce.max_delta_ns = clockevent_delta2ns(0x7fff, &pit_ce);
	pit_ce.min_delta_ns = clockevent_delta2ns(0x000f, &pit_ce);

	clocksource_i8253_init();

	setup_irq(pit_ce.irq, &pit_timer_irq);
	clockevents_register_device(&pit_ce);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

struct sys_timer isa_timer = {
	.init		= isa_timer_init,
};
