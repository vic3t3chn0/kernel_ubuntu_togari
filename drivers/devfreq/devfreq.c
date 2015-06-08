/*
 * devfreq: Generic Dynamic Voltage and Frequency Scaling (DVFS) Framework
 *	    for Non-CPU Devices.
 *
 * Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/opp.h>
#include <linux/devfreq.h>
#include <linux/workqueue.h>
#include <linux/platform_device.h>
#include <linux/list.h>
#include <linux/printk.h>
#include <linux/hrtimer.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include "governor.h"

static struct class *devfreq_class;

/*
 * devfreq core provides delayed work based load monitoring helper
 * functions. Governors can use these or can implement their own
 * monitoring mechanism.
 */
static struct workqueue_struct *devfreq_wq;

/* The list of all device-devfreq governors */
static LIST_HEAD(devfreq_governor_list);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/pm_qos_params.h>
#include "governor.h"

struct class *devfreq_class;

/*
 * devfreq_work periodically monitors every registered device.
 * The minimum polling interval is one jiffy. The polling interval is
 * determined by the minimum polling period among all polling devfreq
 * devices. The resolution of polling interval is one jiffy.
 */
static bool polling;
static struct workqueue_struct *devfreq_wq;
static struct delayed_work devfreq_work;

/* wait removing if this is to be removed */
static struct devfreq *wait_remove_device;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* The list of all device-devfreq */
static LIST_HEAD(devfreq_list);
static DEFINE_MUTEX(devfreq_list_lock);

/**
 * find_device_devfreq() - find devfreq struct using device pointer
 * @dev:	device pointer used to lookup device devfreq.
 *
 * Search the list of device devfreqs and return the matched device's
 * devfreq info. devfreq_list_lock should be held by the caller.
 */
static struct devfreq *find_device_devfreq(struct device *dev)
{
	struct devfreq *tmp_devfreq;

	if (unlikely(IS_ERR_OR_NULL(dev))) {
		pr_err("DEVFREQ: %s: Invalid parameters\n", __func__);
		return ERR_PTR(-EINVAL);
	}
	WARN(!mutex_is_locked(&devfreq_list_lock),
	     "devfreq_list_lock must be locked.");

	list_for_each_entry(tmp_devfreq, &devfreq_list, node) {
		if (tmp_devfreq->dev.parent == dev)
			return tmp_devfreq;
	}

	return ERR_PTR(-ENODEV);
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * devfreq_set_freq_limits() - Set min and max frequency from freq_table
 * @devfreq:	the devfreq instance
 */
static void devfreq_set_freq_limits(struct devfreq *devfreq)
{
	int idx;
	unsigned long min = ~0, max = 0;

	if (!devfreq->profile->freq_table)
		return;

	for (idx = 0; idx < devfreq->profile->max_state; idx++) {
		if (min > devfreq->profile->freq_table[idx])
			min = devfreq->profile->freq_table[idx];
		if (max < devfreq->profile->freq_table[idx])
			max = devfreq->profile->freq_table[idx];
	}

	devfreq->min_freq = min;
	devfreq->max_freq = max;
}

/**
 * devfreq_get_freq_level() - Lookup freq_table for the frequency
 * @devfreq:	the devfreq instance
 * @freq:	the target frequency
 */
int devfreq_get_freq_level(struct devfreq *devfreq, unsigned long freq)
{
	int lev;

	for (lev = 0; lev < devfreq->profile->max_state; lev++)
		if (freq == devfreq->profile->freq_table[lev])
			return lev;

	return -EINVAL;
}
EXPORT_SYMBOL(devfreq_get_freq_level);

/**
 * devfreq_update_status() - Update statistics of devfreq behavior
 * @devfreq:	the devfreq instance
 * @freq:	the update target frequency
 */
static int devfreq_update_status(struct devfreq *devfreq, unsigned long freq)
{
	int lev, prev_lev;
	unsigned long cur_time;

	lev = devfreq_get_freq_level(devfreq, freq);
	if (lev < 0)
		return lev;

	cur_time = jiffies;
	devfreq->time_in_state[lev] +=
			 cur_time - devfreq->last_stat_updated;
	devfreq->last_stat_updated = cur_time;

	if (freq == devfreq->previous_freq)
		return 0;

	prev_lev = devfreq_get_freq_level(devfreq, devfreq->previous_freq);
	if (prev_lev < 0)
		return 0;

	if (lev != prev_lev) {
		devfreq->trans_table[(prev_lev *
				devfreq->profile->max_state) + lev]++;
		devfreq->total_trans++;
	}

	return 0;
}

/**
 * find_devfreq_governor() - find devfreq governor from name
 * @name:	name of the governor
 *
 * Search the list of devfreq governors and return the matched
 * governor's pointer. devfreq_list_lock should be held by the caller.
 */
static struct devfreq_governor *find_devfreq_governor(const char *name)
{
	struct devfreq_governor *tmp_governor;

	if (unlikely(IS_ERR_OR_NULL(name))) {
		pr_err("DEVFREQ: %s: Invalid parameters\n", __func__);
		return ERR_PTR(-EINVAL);
	}
	WARN(!mutex_is_locked(&devfreq_list_lock),
	     "devfreq_list_lock must be locked.");

	list_for_each_entry(tmp_governor, &devfreq_governor_list, node) {
		if (!strncmp(tmp_governor->name, name, DEVFREQ_NAME_LEN))
			return tmp_governor;
	}

	return ERR_PTR(-ENODEV);
}

/* Load monitoring helper functions for governors use */

/**
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * update_devfreq() - Reevaluate the device and configure frequency.
 * @devfreq:	the devfreq instance.
 *
 * Note: Lock devfreq->lock before calling update_devfreq
 *	 This function is exported for governors.
 */
int update_devfreq(struct devfreq *devfreq)
{
	unsigned long freq;
	int err = 0;
<<<<<<< HEAD
<<<<<<< HEAD
	u32 flags = 0;
=======
	u32 options = 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	u32 options = 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!mutex_is_locked(&devfreq->lock)) {
		WARN(true, "devfreq->lock must be locked by the caller.\n");
		return -EINVAL;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	if (!devfreq->governor)
		return -EINVAL;

	/* Reevaluate the proper frequency */
	err = devfreq->governor->get_target_freq(devfreq, &freq, &flags);
=======
	/* Reevaluate the proper frequency */
	err = devfreq->governor->get_target_freq(devfreq, &freq);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Reevaluate the proper frequency */
	err = devfreq->governor->get_target_freq(devfreq, &freq);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (err)
		return err;

	/*
	 * Adjust the freuqency with user freq and QoS.
	 *
	 * List from the highest proiority
<<<<<<< HEAD
<<<<<<< HEAD
	 * max_freq (probably called by thermal when it's too hot)
	 * min_freq
	 */

	if (devfreq->min_freq && freq < devfreq->min_freq) {
		freq = devfreq->min_freq;
		flags &= ~DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use GLB */
	}
	if (devfreq->max_freq && freq > devfreq->max_freq) {
		freq = devfreq->max_freq;
		flags |= DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use LUB */
	}

	err = devfreq->profile->target(devfreq->dev.parent, &freq, flags);
	if (err)
		return err;

	if (devfreq->profile->freq_table)
		if (devfreq_update_status(devfreq, freq))
			dev_err(&devfreq->dev,
				"Couldn't update frequency transition information.\n");

	devfreq->previous_freq = freq;
	return err;
}
EXPORT_SYMBOL(update_devfreq);

/**
 * devfreq_monitor() - Periodically poll devfreq objects.
 * @work:	the work struct used to run devfreq_monitor periodically.
 *
 */
static void devfreq_monitor(struct work_struct *work)
{
	int err;
	struct devfreq *devfreq = container_of(work,
					struct devfreq, work.work);

	mutex_lock(&devfreq->lock);
	err = update_devfreq(devfreq);
	if (err)
		dev_err(&devfreq->dev, "dvfs failed with (%d) error\n", err);

	queue_delayed_work(devfreq_wq, &devfreq->work,
				msecs_to_jiffies(devfreq->profile->polling_ms));
	mutex_unlock(&devfreq->lock);
}

/**
 * devfreq_monitor_start() - Start load monitoring of devfreq instance
 * @devfreq:	the devfreq instance.
 *
 * Helper function for starting devfreq device load monitoing. By
 * default delayed work based monitoring is supported. Function
 * to be called from governor in response to DEVFREQ_GOV_START
 * event when device is added to devfreq framework.
 */
void devfreq_monitor_start(struct devfreq *devfreq)
{
	INIT_DELAYED_WORK_DEFERRABLE(&devfreq->work, devfreq_monitor);
	if (devfreq->profile->polling_ms)
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jiffies(devfreq->profile->polling_ms));
}
EXPORT_SYMBOL(devfreq_monitor_start);

/**
 * devfreq_monitor_stop() - Stop load monitoring of a devfreq instance
 * @devfreq:	the devfreq instance.
 *
 * Helper function to stop devfreq device load monitoing. Function
 * to be called from governor in response to DEVFREQ_GOV_STOP
 * event when device is removed from devfreq framework.
 */
void devfreq_monitor_stop(struct devfreq *devfreq)
{
	cancel_delayed_work_sync(&devfreq->work);
}
EXPORT_SYMBOL(devfreq_monitor_stop);

/**
 * devfreq_monitor_suspend() - Suspend load monitoring of a devfreq instance
 * @devfreq:	the devfreq instance.
 *
 * Helper function to suspend devfreq device load monitoing. Function
 * to be called from governor in response to DEVFREQ_GOV_SUSPEND
 * event or when polling interval is set to zero.
 *
 * Note: Though this function is same as devfreq_monitor_stop(),
 * intentionally kept separate to provide hooks for collecting
 * transition statistics.
 */
void devfreq_monitor_suspend(struct devfreq *devfreq)
{
	mutex_lock(&devfreq->lock);
	if (devfreq->stop_polling) {
		mutex_unlock(&devfreq->lock);
		return;
	}

	devfreq->stop_polling = true;
	mutex_unlock(&devfreq->lock);
	cancel_delayed_work_sync(&devfreq->work);
}
EXPORT_SYMBOL(devfreq_monitor_suspend);

/**
 * devfreq_monitor_resume() - Resume load monitoring of a devfreq instance
 * @devfreq:    the devfreq instance.
 *
 * Helper function to resume devfreq device load monitoing. Function
 * to be called from governor in response to DEVFREQ_GOV_RESUME
 * event or when polling interval is set to non-zero.
 */
void devfreq_monitor_resume(struct devfreq *devfreq)
{
	mutex_lock(&devfreq->lock);
	if (!devfreq->stop_polling)
		goto out;

	if (!delayed_work_pending(&devfreq->work) &&
			devfreq->profile->polling_ms)
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jiffies(devfreq->profile->polling_ms));
	devfreq->stop_polling = false;

out:
	mutex_unlock(&devfreq->lock);
}
EXPORT_SYMBOL(devfreq_monitor_resume);

/**
 * devfreq_interval_update() - Update device devfreq monitoring interval
 * @devfreq:    the devfreq instance.
 * @delay:      new polling interval to be set.
 *
 * Helper function to set new load monitoring polling interval. Function
 * to be called from governor in response to DEVFREQ_GOV_INTERVAL event.
 */
void devfreq_interval_update(struct devfreq *devfreq, unsigned int *delay)
{
	unsigned int cur_delay = devfreq->profile->polling_ms;
	unsigned int new_delay = *delay;

	mutex_lock(&devfreq->lock);
	devfreq->profile->polling_ms = new_delay;

	if (devfreq->stop_polling)
		goto out;

	/* if new delay is zero, stop polling */
	if (!new_delay) {
		mutex_unlock(&devfreq->lock);
		cancel_delayed_work_sync(&devfreq->work);
		return;
	}

	/* if current delay is zero, start polling with new delay */
	if (!cur_delay) {
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jiffies(devfreq->profile->polling_ms));
		goto out;
	}

	/* if current delay is greater than new delay, restart polling */
	if (cur_delay > new_delay) {
		mutex_unlock(&devfreq->lock);
		cancel_delayed_work_sync(&devfreq->work);
		mutex_lock(&devfreq->lock);
		if (!devfreq->stop_polling)
			queue_delayed_work(devfreq_wq, &devfreq->work,
			      msecs_to_jiffies(devfreq->profile->polling_ms));
	}
out:
	mutex_unlock(&devfreq->lock);
}
EXPORT_SYMBOL(devfreq_interval_update);

/**
 * devfreq_notifier_call() - Notify that the device frequency requirements
 *			   has been changed out of devfreq framework.
 * @nb:		the notifier_block (supposed to be devfreq->nb)
 * @type:	not used
 * @devp:	not used
 *
 * Called by a notifier that uses devfreq->nb.
 */
static int devfreq_notifier_call(struct notifier_block *nb, unsigned long type,
				 void *devp)
{
	struct devfreq *devfreq = container_of(nb, struct devfreq, nb);
	int ret;

	mutex_lock(&devfreq->lock);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * min_freq
	 * max_freq
	 * qos_min_freq
	 */

	if (devfreq->qos_min_freq && freq < devfreq->qos_min_freq) {
		freq = devfreq->qos_min_freq;
		options &= ~(1 << 0);
		options |= DEVFREQ_OPTION_FREQ_LUB;
	}
	if (devfreq->max_freq && freq > devfreq->max_freq) {
		freq = devfreq->max_freq;
		options &= ~(1 << 0);
		options |= DEVFREQ_OPTION_FREQ_GLB;
	}
	if (devfreq->min_freq && freq < devfreq->min_freq) {
		freq = devfreq->min_freq;
		options &= ~(1 << 0);
		options |= DEVFREQ_OPTION_FREQ_LUB;
	}

	err = devfreq->profile->target(devfreq->dev.parent, &freq, options);
	if (err)
		return err;

	devfreq->previous_freq = freq;
	return err;
}

/**
 * devfreq_notifier_call() - Notify that the device frequency requirements
 *			   has been changed out of devfreq framework.
 * @nb		the notifier_block (supposed to be devfreq->nb)
 * @val		not used.
 * @devp	not used
 *
 * Called by a notifier that uses devfreq->nb.
 */
static int devfreq_notifier_call(struct notifier_block *nb, unsigned long val,
				 void *devp)
{
	struct devfreq *devfreq = container_of(nb, struct devfreq, nb);
	int ret;

	mutex_lock(&devfreq->lock);
	ret = update_devfreq(devfreq);
	mutex_unlock(&devfreq->lock);

	return ret;
}

/**
 * devfreq_qos_notifier_call() -
 */
static int devfreq_qos_notifier_call(struct notifier_block *nb,
				     unsigned long value, void *devp)
{
	struct devfreq *devfreq = container_of(nb, struct devfreq, qos_nb);
	int ret;
	int i;
	unsigned long default_value = 0;
	struct devfreq_pm_qos_table *qos_list = devfreq->profile->qos_list;
	bool qos_use_max = devfreq->profile->qos_use_max;

	if (!qos_list)
		return NOTIFY_DONE;

	mutex_lock(&devfreq->lock);

	switch (devfreq->profile->qos_type) {
	case PM_QOS_CPU_DMA_LATENCY:
		default_value = PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE;
		break;
	case PM_QOS_NETWORK_LATENCY:
		default_value = PM_QOS_NETWORK_LAT_DEFAULT_VALUE;
		break;
	case PM_QOS_NETWORK_THROUGHPUT:
		default_value = PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE;
		break;
	case PM_QOS_BUS_DMA_THROUGHPUT:
		default_value = PM_QOS_BUS_DMA_THROUGHPUT_DEFAULT_VALUE;
		break;
	case PM_QOS_DISPLAY_FREQUENCY:
		default_value = PM_QOS_DISPLAY_FREQUENCY_DEFAULT_VALUE;
		break;
	default:
		/* Won't do any check to detect "default" state */
		break;
	}

	if (value == default_value) {
		devfreq->qos_min_freq = 0;
		goto update;
	}

	for (i = 0; qos_list[i].freq; i++) {
		/* QoS Met */
		if ((qos_use_max && qos_list[i].qos_value >= value) ||
		    (!qos_use_max && qos_list[i].qos_value <= value)) {
			devfreq->qos_min_freq = qos_list[i].freq;
			goto update;
		}
	}

	/* Use the highest QoS freq */
	if (i > 0)
		devfreq->qos_min_freq = qos_list[i - 1].freq;

update:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = update_devfreq(devfreq);
	mutex_unlock(&devfreq->lock);

	return ret;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * _remove_devfreq() - Remove devfreq from the list and release its resources.
 * @devfreq:	the devfreq struct
 * @skip:	skip calling device_unregister().
 */
static void _remove_devfreq(struct devfreq *devfreq, bool skip)
{
	mutex_lock(&devfreq_list_lock);
	if (IS_ERR(find_device_devfreq(devfreq->dev.parent))) {
		mutex_unlock(&devfreq_list_lock);
		dev_warn(&devfreq->dev, "releasing devfreq which doesn't exist\n");
		return;
	}
	list_del(&devfreq->node);
	mutex_unlock(&devfreq_list_lock);

	if (devfreq->governor)
		devfreq->governor->event_handler(devfreq,
						 DEVFREQ_GOV_STOP, NULL);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * _remove_devfreq() - Remove devfreq from the device.
 * @devfreq:	the devfreq struct
 * @skip:	skip calling device_unregister().
 *
 * Note that the caller should lock devfreq->lock before calling
 * this. _remove_devfreq() will unlock it and free devfreq
 * internally. devfreq_list_lock should be locked by the caller
 * as well (not relased at return)
 *
 * Lock usage:
 * devfreq->lock: locked before call.
 *		  unlocked at return (and freed)
 * devfreq_list_lock: locked before call.
 *		      kept locked at return.
 *		      if devfreq is centrally polled.
 *
 * Freed memory:
 * devfreq
 */
static void _remove_devfreq(struct devfreq *devfreq, bool skip)
{
	if (!mutex_is_locked(&devfreq->lock)) {
		WARN(true, "devfreq->lock must be locked by the caller.\n");
		return;
	}
	if (!devfreq->governor->no_central_polling &&
	    !mutex_is_locked(&devfreq_list_lock)) {
		WARN(true, "devfreq_list_lock must be locked by the caller.\n");
		return;
	}

	if (devfreq->being_removed)
		return;

	devfreq->being_removed = true;

	if (devfreq->profile->qos_type)
		pm_qos_remove_notifier(devfreq->profile->qos_type,
				       &devfreq->qos_nb);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (devfreq->profile->exit)
		devfreq->profile->exit(devfreq->dev.parent);

<<<<<<< HEAD
<<<<<<< HEAD
=======
	if (devfreq->governor->exit)
		devfreq->governor->exit(devfreq);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (devfreq->governor->exit)
		devfreq->governor->exit(devfreq);

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!skip && get_device(&devfreq->dev)) {
		device_unregister(&devfreq->dev);
		put_device(&devfreq->dev);
	}

<<<<<<< HEAD
<<<<<<< HEAD
	mutex_destroy(&devfreq->lock);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!devfreq->governor->no_central_polling)
		list_del(&devfreq->node);

	mutex_unlock(&devfreq->lock);
	mutex_destroy(&devfreq->lock);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	kfree(devfreq);
}

/**
 * devfreq_dev_release() - Callback for struct device to release the device.
 * @dev:	the devfreq device
 *
 * This calls _remove_devfreq() if _remove_devfreq() is not called.
 * Note that devfreq_dev_release() could be called by _remove_devfreq() as
 * well as by others unregistering the device.
 */
static void devfreq_dev_release(struct device *dev)
{
	struct devfreq *devfreq = to_devfreq(dev);
<<<<<<< HEAD
<<<<<<< HEAD

	_remove_devfreq(devfreq, true);
}

/**
 * find_governor_data - Find device specific private data for a governor.
 * @profile: The profile to search.
 * @governor_name: The governor to search for.
 *
 * Look up the device specific data for a governor.
 */
static void *find_governor_data(struct devfreq_dev_profile *profile,
				const char *governor_name)
{
	void *data = NULL;
	int i;

	if (profile->governor_data == NULL)
		return NULL;

	for (i = 0; i < profile->num_governor_data; i++) {
		if (strncmp(governor_name, profile->governor_data[i].name,
			     DEVFREQ_NAME_LEN) == 0) {
			data = profile->governor_data[i].data;
			break;
		}
	}
	return data;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	bool central_polling = !devfreq->governor->no_central_polling;

	/*
	 * If devfreq_dev_release() was called by device_unregister() of
	 * _remove_devfreq(), we cannot mutex_lock(&devfreq->lock) and
	 * being_removed is already set. This also partially checks the case
	 * where devfreq_dev_release() is called from a thread other than
	 * the one called _remove_devfreq(); however, this case is
	 * dealt completely with another following being_removed check.
	 *
	 * Because being_removed is never being
	 * unset, we do not need to worry about race conditions on
	 * being_removed.
	 */
	if (devfreq->being_removed)
		return;

	if (central_polling)
		mutex_lock(&devfreq_list_lock);

	mutex_lock(&devfreq->lock);

	/*
	 * Check being_removed flag again for the case where
	 * devfreq_dev_release() was called in a thread other than the one
	 * possibly called _remove_devfreq().
	 */
	if (devfreq->being_removed) {
		mutex_unlock(&devfreq->lock);
		goto out;
	}

	/* devfreq->lock is unlocked and removed in _removed_devfreq() */
	_remove_devfreq(devfreq, true);

out:
	if (central_polling)
		mutex_unlock(&devfreq_list_lock);
}

/**
 * devfreq_monitor() - Periodically poll devfreq objects.
 * @work: the work struct used to run devfreq_monitor periodically.
 *
 */
static void devfreq_monitor(struct work_struct *work)
{
	static unsigned long last_polled_at;
	struct devfreq *devfreq, *tmp;
	int error;
	unsigned long jiffies_passed;
	unsigned long next_jiffies = ULONG_MAX, now = jiffies;
	struct device *dev;

	/* Initially last_polled_at = 0, polling every device at bootup */
	jiffies_passed = now - last_polled_at;
	last_polled_at = now;
	if (jiffies_passed == 0)
		jiffies_passed = 1;

	mutex_lock(&devfreq_list_lock);
	list_for_each_entry_safe(devfreq, tmp, &devfreq_list, node) {
		mutex_lock(&devfreq->lock);
		dev = devfreq->dev.parent;

		/* Do not remove tmp for a while */
		wait_remove_device = tmp;

		if (devfreq->governor->no_central_polling ||
		    devfreq->next_polling == 0) {
			mutex_unlock(&devfreq->lock);
			continue;
		}
		mutex_unlock(&devfreq_list_lock);

		/*
		 * Reduce more next_polling if devfreq_wq took an extra
		 * delay. (i.e., CPU has been idled.)
		 */
		if (devfreq->next_polling <= jiffies_passed) {
			error = update_devfreq(devfreq);

			/* Remove a devfreq with an error. */
			if (error && error != -EAGAIN) {

				dev_err(dev, "Due to update_devfreq error(%d), devfreq(%s) is removed from the device\n",
					error, devfreq->governor->name);

				/*
				 * Unlock devfreq before locking the list
				 * in order to avoid deadlock with
				 * find_device_devfreq or others
				 */
				mutex_unlock(&devfreq->lock);
				mutex_lock(&devfreq_list_lock);
				/* Check if devfreq is already removed */
				if (IS_ERR(find_device_devfreq(dev)))
					continue;
				mutex_lock(&devfreq->lock);
				/* This unlocks devfreq->lock and free it */
				_remove_devfreq(devfreq, false);
				continue;
			}
			devfreq->next_polling = devfreq->polling_jiffies;
		} else {
			devfreq->next_polling -= jiffies_passed;
		}

		if (devfreq->next_polling)
			next_jiffies = (next_jiffies > devfreq->next_polling) ?
					devfreq->next_polling : next_jiffies;

		mutex_unlock(&devfreq->lock);
		mutex_lock(&devfreq_list_lock);
	}
	wait_remove_device = NULL;
	mutex_unlock(&devfreq_list_lock);

	if (next_jiffies > 0 && next_jiffies < ULONG_MAX) {
		polling = true;
		queue_delayed_work(devfreq_wq, &devfreq_work, next_jiffies);
	} else {
		polling = false;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**
 * devfreq_add_device() - Add devfreq feature to the device
 * @dev:	the device to add devfreq feature.
 * @profile:	device-specific profile to run devfreq.
<<<<<<< HEAD
<<<<<<< HEAD
 * @governor_name:	name of the policy to choose frequency.
=======
 * @governor:	the policy to choose frequency.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @governor:	the policy to choose frequency.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @data:	private data for the governor. The devfreq framework does not
 *		touch this value.
 */
struct devfreq *devfreq_add_device(struct device *dev,
				   struct devfreq_dev_profile *profile,
<<<<<<< HEAD
<<<<<<< HEAD
				   const char *governor_name,
				   void *data)
{
	struct devfreq *devfreq;
	struct devfreq_governor *governor;
	int err = 0;

	if (!dev || !profile || !governor_name) {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				   const struct devfreq_governor *governor,
				   void *data)
{
	struct devfreq *devfreq;
	int err = 0;

	if (!dev || !profile || !governor) {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_err(dev, "%s: Invalid parameters.\n", __func__);
		return ERR_PTR(-EINVAL);
	}

<<<<<<< HEAD
<<<<<<< HEAD
	mutex_lock(&devfreq_list_lock);
	devfreq = find_device_devfreq(dev);
	mutex_unlock(&devfreq_list_lock);
	if (!IS_ERR(devfreq)) {
		dev_err(dev, "%s: Unable to create devfreq for the device. It already has one.\n", __func__);
		err = -EINVAL;
		goto err_out;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!governor->no_central_polling) {
		mutex_lock(&devfreq_list_lock);
		devfreq = find_device_devfreq(dev);
		mutex_unlock(&devfreq_list_lock);
		if (!IS_ERR(devfreq)) {
			dev_err(dev, "%s: Unable to create devfreq for the device. It already has one.\n", __func__);
			err = -EINVAL;
			goto out;
		}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	devfreq = kzalloc(sizeof(struct devfreq), GFP_KERNEL);
	if (!devfreq) {
		dev_err(dev, "%s: Unable to create devfreq for the device\n",
			__func__);
		err = -ENOMEM;
<<<<<<< HEAD
<<<<<<< HEAD
		goto err_out;
=======
		goto out;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto out;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	mutex_init(&devfreq->lock);
	mutex_lock(&devfreq->lock);
	devfreq->dev.parent = dev;
	devfreq->dev.class = devfreq_class;
	devfreq->dev.release = devfreq_dev_release;
	devfreq->profile = profile;
<<<<<<< HEAD
<<<<<<< HEAD
	strncpy(devfreq->governor_name, governor_name, DEVFREQ_NAME_LEN);
	devfreq->previous_freq = profile->initial_freq;

	devfreq->data = data ? data : find_governor_data(devfreq->profile,
							 governor_name);

	devfreq->nb.notifier_call = devfreq_notifier_call;

	devfreq->trans_table =	devm_kzalloc(dev, sizeof(unsigned int) *
						devfreq->profile->max_state *
						devfreq->profile->max_state,
						GFP_KERNEL);
	devfreq->time_in_state = devm_kzalloc(dev, sizeof(unsigned int) *
						devfreq->profile->max_state,
						GFP_KERNEL);
	devfreq->last_stat_updated = jiffies;
	devfreq_set_freq_limits(devfreq);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	devfreq->governor = governor;
	devfreq->previous_freq = profile->initial_freq;
	devfreq->data = data;
	devfreq->next_polling = devfreq->polling_jiffies
			      = msecs_to_jiffies(devfreq->profile->polling_ms);
	devfreq->nb.notifier_call = devfreq_notifier_call;
	devfreq->qos_nb.notifier_call = devfreq_qos_notifier_call;

	/* Check the sanity of qos_list/qos_type */
	if (profile->qos_type || profile->qos_list) {
		int i;
		bool positive_corelation = false;

		if (profile->qos_type == PM_QOS_CPU_DMA_LATENCY ||
		    profile->qos_type == PM_QOS_NETWORK_LATENCY) {
			if (profile->qos_use_max) {
				dev_err(dev, "qos_use_max value inconsistent\n");
				err = -EINVAL;
			}
		} else {
			if (!profile->qos_use_max) {
				dev_err(dev, "qos_use_max value inconsistent\n");
				err = -EINVAL;
			}
		}
		if (err)
			goto err_dev;

		if (!profile->qos_type || !profile->qos_list) {
			dev_err(dev, "QoS requirement partially omitted.\n");
			err = -EINVAL;
			goto err_dev;
		}

		if (!profile->qos_list[0].freq) {
			dev_err(dev, "The first QoS requirement is the end of list.\n");
			err = -EINVAL;
			goto err_dev;
		}

		for (i = 1; profile->qos_list[i].freq; i++) {
			if (profile->qos_list[i].freq <=
			    profile->qos_list[i - 1].freq) {
				dev_err(dev, "qos_list[].freq not sorted in the ascending order. ([%d]=%lu, [%d]=%lu)\n",
					i - 1, profile->qos_list[i - 1].freq,
					i, profile->qos_list[i].freq);
				err = -EINVAL;
				goto err_dev;
			}

			if (i == 1) {
				if (profile->qos_list[0].qos_value <
				    profile->qos_list[1].qos_value)
					positive_corelation = true;
				continue;
			}

			if (((profile->qos_list[i - 1].qos_value <=
			      profile->qos_list[i].qos_value) &&
			     !positive_corelation)
			    ||
			    ((profile->qos_list[i - 1].qos_value >=
			      profile->qos_list[i].qos_value) &&
			     positive_corelation)) {
				dev_err(dev, "qos_list[].qos_value not sorted.\n");
				err = -EINVAL;
				goto err_dev;
			}
		}

		pm_qos_add_notifier(profile->qos_type, &devfreq->qos_nb);
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	dev_set_name(&devfreq->dev, dev_name(dev));
	err = device_register(&devfreq->dev);
	if (err) {
		put_device(&devfreq->dev);
<<<<<<< HEAD
<<<<<<< HEAD
		mutex_unlock(&devfreq->lock);
		goto err_dev;
	}

	mutex_unlock(&devfreq->lock);

	mutex_lock(&devfreq_list_lock);
	list_add(&devfreq->node, &devfreq_list);

	governor = find_devfreq_governor(devfreq->governor_name);
	if (!IS_ERR(governor))
		devfreq->governor = governor;
	if (devfreq->governor)
		err = devfreq->governor->event_handler(devfreq,
					DEVFREQ_GOV_START, NULL);
	mutex_unlock(&devfreq_list_lock);
	if (err) {
		dev_err(dev, "%s: Unable to start governor for the device\n",
			__func__);
		goto err_init;
	}

	return devfreq;

err_init:
	list_del(&devfreq->node);
	device_unregister(&devfreq->dev);
err_dev:
	kfree(devfreq);
err_out:
	return ERR_PTR(err);
}
EXPORT_SYMBOL(devfreq_add_device);

/**
 * devfreq_remove_device() - Remove devfreq feature from a device.
 * @devfreq:	the devfreq instance to be removed
 */
int devfreq_remove_device(struct devfreq *devfreq)
{
	if (!devfreq)
		return -EINVAL;

	_remove_devfreq(devfreq, false);

	return 0;
}
EXPORT_SYMBOL(devfreq_remove_device);

/**
 * devfreq_suspend_device() - Suspend devfreq of a device.
 * @devfreq: the devfreq instance to be suspended
 */
int devfreq_suspend_device(struct devfreq *devfreq)
{
	if (!devfreq)
		return -EINVAL;

	if (!devfreq->governor)
		return 0;

	return devfreq->governor->event_handler(devfreq,
				DEVFREQ_GOV_SUSPEND, NULL);
}
EXPORT_SYMBOL(devfreq_suspend_device);

/**
 * devfreq_resume_device() - Resume devfreq of a device.
 * @devfreq: the devfreq instance to be resumed
 */
int devfreq_resume_device(struct devfreq *devfreq)
{
	if (!devfreq)
		return -EINVAL;

	if (!devfreq->governor)
		return 0;

	return devfreq->governor->event_handler(devfreq,
				DEVFREQ_GOV_RESUME, NULL);
}
EXPORT_SYMBOL(devfreq_resume_device);

/**
 * devfreq_add_governor() - Add devfreq governor
 * @governor:	the devfreq governor to be added
 */
int devfreq_add_governor(struct devfreq_governor *governor)
{
	struct devfreq_governor *g;
	struct devfreq *devfreq;
	int err = 0;

	if (!governor) {
		pr_err("%s: Invalid parameters.\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&devfreq_list_lock);
	g = find_devfreq_governor(governor->name);
	if (!IS_ERR(g)) {
		pr_err("%s: governor %s already registered\n", __func__,
		       g->name);
		err = -EINVAL;
		goto err_out;
	}

	list_add(&governor->node, &devfreq_governor_list);

	list_for_each_entry(devfreq, &devfreq_list, node) {
		int ret = 0;
		struct device *dev = devfreq->dev.parent;

		if (!strncmp(devfreq->governor_name, governor->name,
			     DEVFREQ_NAME_LEN)) {
			/* The following should never occur */
			if (devfreq->governor) {
				dev_warn(dev,
					 "%s: Governor %s already present\n",
					 __func__, devfreq->governor->name);
				ret = devfreq->governor->event_handler(devfreq,
							DEVFREQ_GOV_STOP, NULL);
				if (ret) {
					dev_warn(dev,
						 "%s: Governor %s stop = %d\n",
						 __func__,
						 devfreq->governor->name, ret);
				}
				/* Fall through */
			}
			devfreq->governor = governor;
			ret = devfreq->governor->event_handler(devfreq,
						DEVFREQ_GOV_START, NULL);
			if (ret) {
				dev_warn(dev, "%s: Governor %s start=%d\n",
					 __func__, devfreq->governor->name,
					 ret);
			}
		}
	}

err_out:
	mutex_unlock(&devfreq_list_lock);

	return err;
}
EXPORT_SYMBOL(devfreq_add_governor);

/**
 * devfreq_remove_device() - Remove devfreq feature from a device.
 * @governor:	the devfreq governor to be removed
 */
int devfreq_remove_governor(struct devfreq_governor *governor)
{
	struct devfreq_governor *g;
	struct devfreq *devfreq;
	int err = 0;

	if (!governor) {
		pr_err("%s: Invalid parameters.\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&devfreq_list_lock);
	g = find_devfreq_governor(governor->name);
	if (IS_ERR(g)) {
		pr_err("%s: governor %s not registered\n", __func__,
		       governor->name);
		err = PTR_ERR(g);
		goto err_out;
	}
	list_for_each_entry(devfreq, &devfreq_list, node) {
		int ret;
		struct device *dev = devfreq->dev.parent;

		if (!strncmp(devfreq->governor_name, governor->name,
			     DEVFREQ_NAME_LEN)) {
			/* we should have a devfreq governor! */
			if (!devfreq->governor) {
				dev_warn(dev, "%s: Governor %s NOT present\n",
					 __func__, governor->name);
				continue;
				/* Fall through */
			}
			ret = devfreq->governor->event_handler(devfreq,
						DEVFREQ_GOV_STOP, NULL);
			if (ret) {
				dev_warn(dev, "%s: Governor %s stop=%d\n",
					 __func__, devfreq->governor->name,
					 ret);
			}
			devfreq->governor = NULL;
		}
	}

	list_del(&governor->node);
err_out:
	mutex_unlock(&devfreq_list_lock);

	return err;
}
EXPORT_SYMBOL(devfreq_remove_governor);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto err_qos_add;
	}

	if (governor->init)
		err = governor->init(devfreq);
	if (err)
		goto err_init;

	mutex_unlock(&devfreq->lock);

	if (governor->no_central_polling)
		goto out;

	mutex_lock(&devfreq_list_lock);

	list_add(&devfreq->node, &devfreq_list);

	if (devfreq_wq && devfreq->next_polling && !polling) {
		polling = true;
		queue_delayed_work(devfreq_wq, &devfreq_work,
				   devfreq->next_polling);
	}
	mutex_unlock(&devfreq_list_lock);
	goto out;
err_init:
	device_unregister(&devfreq->dev);
err_qos_add:
	if (profile->qos_type || profile->qos_list)
		pm_qos_remove_notifier(profile->qos_type, &devfreq->qos_nb);
err_dev:
	mutex_unlock(&devfreq->lock);
	kfree(devfreq);
out:
	if (err)
		return ERR_PTR(err);
	else
		return devfreq;
}

/**
 * devfreq_remove_device() - Remove devfreq feature from a device.
 * @devfreq	the devfreq instance to be removed
 */
int devfreq_remove_device(struct devfreq *devfreq)
{
	bool central_polling;

	if (!devfreq)
		return -EINVAL;

	central_polling = !devfreq->governor->no_central_polling;

	if (central_polling) {
		mutex_lock(&devfreq_list_lock);
		while (wait_remove_device == devfreq) {
			mutex_unlock(&devfreq_list_lock);
			schedule();
			mutex_lock(&devfreq_list_lock);
		}
	}

	mutex_lock(&devfreq->lock);

	_remove_devfreq(devfreq, false); /* it unlocks devfreq->lock */

	if (central_polling)
		mutex_unlock(&devfreq_list_lock);

	return 0;
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static ssize_t show_governor(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
<<<<<<< HEAD
<<<<<<< HEAD
	if (!to_devfreq(dev)->governor)
		return -EINVAL;

	return sprintf(buf, "%s\n", to_devfreq(dev)->governor->name);
}

static ssize_t store_governor(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct devfreq *df = to_devfreq(dev);
	int ret;
	char str_governor[DEVFREQ_NAME_LEN + 1];
	struct devfreq_governor *governor;

	ret = sscanf(buf, "%" __stringify(DEVFREQ_NAME_LEN) "s", str_governor);
	if (ret != 1)
		return -EINVAL;

	mutex_lock(&devfreq_list_lock);
	governor = find_devfreq_governor(str_governor);
	if (IS_ERR(governor)) {
		ret = PTR_ERR(governor);
		goto out;
	}
	if (df->governor == governor)
		goto out;

	if (df->governor) {
		ret = df->governor->event_handler(df, DEVFREQ_GOV_STOP, NULL);
		if (ret) {
			dev_warn(dev, "%s: Governor %s not stopped(%d)\n",
				 __func__, df->governor->name, ret);
			goto out;
		}
	}
	df->data = find_governor_data(df->profile, str_governor);
	df->governor = governor;
	strncpy(df->governor_name, governor->name, DEVFREQ_NAME_LEN);
	ret = df->governor->event_handler(df, DEVFREQ_GOV_START, NULL);
	if (ret)
		dev_warn(dev, "%s: Governor %s not started(%d)\n",
			 __func__, df->governor->name, ret);
out:
	mutex_unlock(&devfreq_list_lock);

	if (!ret)
		ret = count;
	return ret;
}
static ssize_t show_available_governors(struct device *d,
				    struct device_attribute *attr,
				    char *buf)
{
	struct devfreq_governor *tmp_governor;
	ssize_t count = 0;

	mutex_lock(&devfreq_list_lock);
	list_for_each_entry(tmp_governor, &devfreq_governor_list, node)
		count += scnprintf(&buf[count], (PAGE_SIZE - count - 2),
				   "%s ", tmp_governor->name);
	mutex_unlock(&devfreq_list_lock);

	/* Truncate the trailing space */
	if (count)
		count--;

	count += sprintf(&buf[count], "\n");

	return count;
}

static ssize_t show_freq(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	unsigned long freq;
	struct devfreq *devfreq = to_devfreq(dev);

	if (devfreq->profile->get_cur_freq &&
		!devfreq->profile->get_cur_freq(devfreq->dev.parent, &freq))
			return sprintf(buf, "%lu\n", freq);

	return sprintf(buf, "%lu\n", devfreq->previous_freq);
}

static ssize_t show_target_freq(struct device *dev,
			struct device_attribute *attr, char *buf)
{
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sprintf(buf, "%s\n", to_devfreq(dev)->governor->name);
}

static ssize_t show_freq(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sprintf(buf, "%lu\n", to_devfreq(dev)->previous_freq);
}

static ssize_t show_polling_interval(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", to_devfreq(dev)->profile->polling_ms);
}

static ssize_t store_polling_interval(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct devfreq *df = to_devfreq(dev);
	unsigned int value;
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!df->governor)
		return -EINVAL;

	ret = sscanf(buf, "%u", &value);
	if (ret != 1)
		return -EINVAL;

	df->governor->event_handler(df, DEVFREQ_GOV_INTERVAL, &value);
	ret = count;

	return ret;
}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = sscanf(buf, "%u", &value);
	if (ret != 1)
		goto out;

	mutex_lock(&df->lock);
	df->profile->polling_ms = value;
	df->next_polling = df->polling_jiffies
			 = msecs_to_jiffies(value);
	mutex_unlock(&df->lock);

	ret = count;

	if (df->governor->no_central_polling)
		goto out;

	mutex_lock(&devfreq_list_lock);
	if (df->next_polling > 0 && !polling) {
		polling = true;
		queue_delayed_work(devfreq_wq, &devfreq_work,
				   df->next_polling);
	}
	mutex_unlock(&devfreq_list_lock);
out:
	return ret;
}

static ssize_t show_central_polling(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n",
		       !to_devfreq(dev)->governor->no_central_polling);
}

static ssize_t show_qos_min_freq(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	return sprintf(buf, "%lu\n", to_devfreq(dev)->qos_min_freq);
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t store_min_freq(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct devfreq *df = to_devfreq(dev);
	unsigned long value;
	int ret;
	unsigned long max;

	ret = sscanf(buf, "%lu", &value);
	if (ret != 1)
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;
=======
		goto out;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto out;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&df->lock);
	max = df->max_freq;
	if (value && max && value > max) {
		ret = -EINVAL;
		goto unlock;
	}

	df->min_freq = value;
	update_devfreq(df);
	ret = count;
unlock:
	mutex_unlock(&df->lock);
<<<<<<< HEAD
<<<<<<< HEAD
=======
out:
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
out:
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static ssize_t show_min_freq(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	return sprintf(buf, "%lu\n", to_devfreq(dev)->min_freq);
}

static ssize_t store_max_freq(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct devfreq *df = to_devfreq(dev);
	unsigned long value;
	int ret;
	unsigned long min;

	ret = sscanf(buf, "%lu", &value);
	if (ret != 1)
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;
=======
		goto out;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto out;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&df->lock);
	min = df->min_freq;
	if (value && min && value < min) {
		ret = -EINVAL;
		goto unlock;
	}

	df->max_freq = value;
	update_devfreq(df);
	ret = count;
unlock:
	mutex_unlock(&df->lock);
<<<<<<< HEAD
<<<<<<< HEAD
=======
out:
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
out:
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static ssize_t show_max_freq(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	return sprintf(buf, "%lu\n", to_devfreq(dev)->max_freq);
}

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t show_available_freqs(struct device *d,
				    struct device_attribute *attr,
				    char *buf)
{
	struct devfreq *df = to_devfreq(d);
	struct device *dev = df->dev.parent;
	struct opp *opp;
	ssize_t count = 0;
	unsigned long freq = 0;

	rcu_read_lock();
	do {
		opp = opp_find_freq_ceil(dev, &freq);
		if (IS_ERR(opp))
			break;

		count += scnprintf(&buf[count], (PAGE_SIZE - count - 2),
				   "%lu ", freq);
		freq++;
	} while (1);
	rcu_read_unlock();

	/* Truncate the trailing space */
	if (count)
		count--;

	count += sprintf(&buf[count], "\n");

	return count;
}

static ssize_t show_trans_table(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct devfreq *devfreq = to_devfreq(dev);
	ssize_t len;
	int i, j, err;
	unsigned int max_state = devfreq->profile->max_state;

	err = devfreq_update_status(devfreq, devfreq->previous_freq);
	if (err)
		return 0;

	len = sprintf(buf, "   From  :   To\n");
	len += sprintf(buf + len, "         :");
	for (i = 0; i < max_state; i++)
		len += sprintf(buf + len, "%8u",
				devfreq->profile->freq_table[i]);

	len += sprintf(buf + len, "   time(ms)\n");

	for (i = 0; i < max_state; i++) {
		if (devfreq->profile->freq_table[i]
					== devfreq->previous_freq) {
			len += sprintf(buf + len, "*");
		} else {
			len += sprintf(buf + len, " ");
		}
		len += sprintf(buf + len, "%8u:",
				devfreq->profile->freq_table[i]);
		for (j = 0; j < max_state; j++)
			len += sprintf(buf + len, "%8u",
				devfreq->trans_table[(i * max_state) + j]);
		len += sprintf(buf + len, "%10u\n",
			jiffies_to_msecs(devfreq->time_in_state[i]));
	}

	len += sprintf(buf + len, "Total transition : %u\n",
					devfreq->total_trans);
	return len;
}

static struct device_attribute devfreq_attrs[] = {
	__ATTR(governor, S_IRUGO | S_IWUSR, show_governor, store_governor),
	__ATTR(available_governors, S_IRUGO, show_available_governors, NULL),
	__ATTR(cur_freq, S_IRUGO, show_freq, NULL),
	__ATTR(available_frequencies, S_IRUGO, show_available_freqs, NULL),
	__ATTR(target_freq, S_IRUGO, show_target_freq, NULL),
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct device_attribute devfreq_attrs[] = {
	__ATTR(governor, S_IRUGO, show_governor, NULL),
	__ATTR(cur_freq, S_IRUGO, show_freq, NULL),
	__ATTR(central_polling, S_IRUGO, show_central_polling, NULL),
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	__ATTR(polling_interval, S_IRUGO | S_IWUSR, show_polling_interval,
	       store_polling_interval),
	__ATTR(min_freq, S_IRUGO | S_IWUSR, show_min_freq, store_min_freq),
	__ATTR(max_freq, S_IRUGO | S_IWUSR, show_max_freq, store_max_freq),
<<<<<<< HEAD
<<<<<<< HEAD
	__ATTR(trans_stat, S_IRUGO, show_trans_table, NULL),
	{ },
};

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	__ATTR(qos_min_freq, S_IRUGO, show_qos_min_freq, NULL),
	{ },
};

/**
 * devfreq_start_polling() - Initialize data structure for devfreq framework and
 *			   start polling registered devfreq devices.
 */
static int __init devfreq_start_polling(void)
{
	mutex_lock(&devfreq_list_lock);
	polling = false;
	devfreq_wq = create_freezable_workqueue("devfreq_wq");
	INIT_DELAYED_WORK_DEFERRABLE(&devfreq_work, devfreq_monitor);
	mutex_unlock(&devfreq_list_lock);

	devfreq_monitor(&devfreq_work.work);
	return 0;
}
late_initcall(devfreq_start_polling);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init devfreq_init(void)
{
	devfreq_class = class_create(THIS_MODULE, "devfreq");
	if (IS_ERR(devfreq_class)) {
		pr_err("%s: couldn't create class\n", __FILE__);
		return PTR_ERR(devfreq_class);
	}
<<<<<<< HEAD
<<<<<<< HEAD

	devfreq_wq = create_freezable_workqueue("devfreq_wq");
	if (IS_ERR(devfreq_wq)) {
		class_destroy(devfreq_class);
		pr_err("%s: couldn't create workqueue\n", __FILE__);
		return PTR_ERR(devfreq_wq);
	}
	devfreq_class->dev_attrs = devfreq_attrs;

=======
	devfreq_class->dev_attrs = devfreq_attrs;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	devfreq_class->dev_attrs = devfreq_attrs;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}
subsys_initcall(devfreq_init);

static void __exit devfreq_exit(void)
{
	class_destroy(devfreq_class);
<<<<<<< HEAD
<<<<<<< HEAD
	destroy_workqueue(devfreq_wq);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
module_exit(devfreq_exit);

/*
 * The followings are helper functions for devfreq user device drivers with
 * OPP framework.
 */

/**
 * devfreq_recommended_opp() - Helper function to get proper OPP for the
 *			     freq value given to target callback.
<<<<<<< HEAD
<<<<<<< HEAD
 * @dev:	The devfreq user device. (parent of devfreq)
 * @freq:	The frequency given to target function
 * @flags:	Flags handed from devfreq framework.
 *
 * Locking: This function must be called under rcu_read_lock(). opp is a rcu
 * protected pointer. The reason for the same is that the opp pointer which is
 * returned will remain valid for use with opp_get_{voltage, freq} only while
 * under the locked area. The pointer returned must be used prior to unlocking
 * with rcu_read_unlock() to maintain the integrity of the pointer.
 */
struct opp *devfreq_recommended_opp(struct device *dev, unsigned long *freq,
				    u32 flags)
{
	struct opp *opp;

	if (flags & DEVFREQ_FLAG_LEAST_UPPER_BOUND) {
		/* The freq is an upper bound. opp should be lower */
		opp = opp_find_freq_floor(dev, freq);

		/* If not available, use the closest opp */
		if (opp == ERR_PTR(-ERANGE))
			opp = opp_find_freq_ceil(dev, freq);
	} else {
		/* The freq is an lower bound. opp should be higher */
		opp = opp_find_freq_ceil(dev, freq);

		/* If not available, use the closest opp */
		if (opp == ERR_PTR(-ERANGE))
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @dev		The devfreq user device. (parent of devfreq)
 * @freq	The frequency given to target function
 * @floor	false: find LUB first and use GLB if LUB not available.
 *		true:  find GLB first and use LUB if GLB not available.
 *
 * LUB: least upper bound (at least this freq or above, but the least)
 * GLB: greatest lower bound (at most this freq or below, but the most)
 *
 */
struct opp *devfreq_recommended_opp(struct device *dev, unsigned long *freq,
				    bool floor)
{
	struct opp *opp;

	if (floor) {
		opp = opp_find_freq_floor(dev, freq);

		if (opp == ERR_PTR(-ENODEV))
			opp = opp_find_freq_ceil(dev, freq);
	} else {
		opp = opp_find_freq_ceil(dev, freq);

		if (opp == ERR_PTR(-ENODEV))
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			opp = opp_find_freq_floor(dev, freq);
	}

	return opp;
}

/**
 * devfreq_register_opp_notifier() - Helper function to get devfreq notified
 *				   for any changes in the OPP availability
 *				   changes
<<<<<<< HEAD
<<<<<<< HEAD
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 */
int devfreq_register_opp_notifier(struct device *dev, struct devfreq *devfreq)
{
	struct srcu_notifier_head *nh;
	int ret = 0;

	rcu_read_lock();
	nh = opp_get_notifier(dev);
	if (IS_ERR(nh))
		ret = PTR_ERR(nh);
	rcu_read_unlock();
	if (!ret)
		ret = srcu_notifier_chain_register(nh, &devfreq->nb);

	return ret;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @dev		The devfreq user device. (parent of devfreq)
 * @devfreq	The devfreq object.
 */
int devfreq_register_opp_notifier(struct device *dev, struct devfreq *devfreq)
{
	struct srcu_notifier_head *nh = opp_get_notifier(dev);

	if (IS_ERR(nh))
		return PTR_ERR(nh);
	return srcu_notifier_chain_register(nh, &devfreq->nb);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**
 * devfreq_unregister_opp_notifier() - Helper function to stop getting devfreq
 *				     notified for any changes in the OPP
 *				     availability changes anymore.
<<<<<<< HEAD
<<<<<<< HEAD
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
=======
 * @dev		The devfreq user device. (parent of devfreq)
 * @devfreq	The devfreq object.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @dev		The devfreq user device. (parent of devfreq)
 * @devfreq	The devfreq object.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * At exit() callback of devfreq_dev_profile, this must be included if
 * devfreq_recommended_opp is used.
 */
int devfreq_unregister_opp_notifier(struct device *dev, struct devfreq *devfreq)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct srcu_notifier_head *nh;
	int ret = 0;

	rcu_read_lock();
	nh = opp_get_notifier(dev);
	if (IS_ERR(nh))
		ret = PTR_ERR(nh);
	rcu_read_unlock();
	if (!ret)
		ret = srcu_notifier_chain_unregister(nh, &devfreq->nb);

	return ret;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct srcu_notifier_head *nh = opp_get_notifier(dev);

	if (IS_ERR(nh))
		return PTR_ERR(nh);
	return srcu_notifier_chain_unregister(nh, &devfreq->nb);
}

/**
 * In progress (prototyping)
 */
int devfreq_simple_ondemand_flexrate_do(struct devfreq *devfreq,
					unsigned long interval,
					unsigned long number)
{
	return 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_DESCRIPTION("devfreq class support");
MODULE_LICENSE("GPL");
