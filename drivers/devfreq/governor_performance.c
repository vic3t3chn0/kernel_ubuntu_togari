/*
 *  linux/drivers/devfreq/governor_performance.c
 *
 *  Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/devfreq.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>
#include "governor.h"

static int devfreq_performance_func(struct devfreq *df,
				    unsigned long *freq,
				u32 *flag)
=======

static int devfreq_performance_func(struct devfreq *df,
				    unsigned long *freq)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

static int devfreq_performance_func(struct devfreq *df,
				    unsigned long *freq)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	/*
	 * target callback should be able to get floor value as
	 * said in devfreq.h
	 */
	if (!df->max_freq)
		*freq = UINT_MAX;
	else
		*freq = df->max_freq;
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int devfreq_performance_handler(struct devfreq *devfreq,
				unsigned int event, void *data)
{
	int ret = 0;
	unsigned long freq;

	mutex_lock(&devfreq->lock);
	freq = devfreq->previous_freq;
	switch (event) {
	case DEVFREQ_GOV_START:
		devfreq->profile->target(devfreq->dev.parent,
				&freq,
				DEVFREQ_FLAG_WAKEUP_MAXFREQ);
		/* fall through */
	case DEVFREQ_GOV_RESUME:
		ret = update_devfreq(devfreq);
		break;
	case DEVFREQ_GOV_SUSPEND:
		devfreq->profile->target(devfreq->dev.parent,
				&freq,
				DEVFREQ_FLAG_WAKEUP_MAXFREQ);
		break;
	}
	mutex_unlock(&devfreq->lock);
	return ret;
}

static struct devfreq_governor devfreq_performance = {
	.name = "performance",
	.get_target_freq = devfreq_performance_func,
	.event_handler = devfreq_performance_handler,
};

static int __init devfreq_performance_init(void)
{
	return devfreq_add_governor(&devfreq_performance);
}
subsys_initcall(devfreq_performance_init);

static void __exit devfreq_performance_exit(void)
{
	int ret;

	ret = devfreq_remove_governor(&devfreq_performance);
	if (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	return;
}
module_exit(devfreq_performance_exit);
MODULE_LICENSE("GPL");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
const struct devfreq_governor devfreq_performance = {
	.name = "performance",
	.get_target_freq = devfreq_performance_func,
	.no_central_polling = true,
};
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
