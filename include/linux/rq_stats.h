<<<<<<< HEAD
/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
=======
<<<<<<< HEAD
/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

struct rq_data {
	unsigned int rq_avg;
	unsigned long rq_poll_jiffies;
	unsigned long def_timer_jiffies;
	unsigned long rq_poll_last_jiffy;
	unsigned long rq_poll_total_jiffies;
	unsigned long def_timer_last_jiffy;
	unsigned int def_interval;
<<<<<<< HEAD
	unsigned int hotplug_disabled;
=======
<<<<<<< HEAD
	unsigned int hotplug_disabled;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int64_t def_start_time;
	struct attribute_group *attr_group;
	struct kobject *kobj;
	struct work_struct def_timer_work;
	int init;
};

extern spinlock_t rq_lock;
extern struct rq_data rq_info;
extern struct workqueue_struct *rq_wq;
