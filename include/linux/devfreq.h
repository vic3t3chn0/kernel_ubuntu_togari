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

#ifndef __LINUX_DEVFREQ_H__
#define __LINUX_DEVFREQ_H__

#include <linux/device.h>
#include <linux/notifier.h>
#include <linux/opp.h>

#define DEVFREQ_NAME_LEN 16

struct devfreq;

/**
 * struct devfreq_dev_status - Data given from devfreq user device to
 *			     governors. Represents the performance
 *			     statistics.
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @total_time:		The total time represented by this instance of
 *			devfreq_dev_status
 * @busy_time:		The time that the device was working among the
 *			total_time.
 * @current_frequency:	The operating frequency.
 * @private_data:	An entry not specified by the devfreq framework.
<<<<<<< HEAD
=======
=======
 * @total_time		The total time represented by this instance of
 *			devfreq_dev_status
 * @busy_time		The time that the device was working among the
 *			total_time.
 * @current_frequency	The operating frequency.
 * @private_data	An entry not specified by the devfreq framework.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *			A device and a specific governor may have their
 *			own protocol with private_data. However, because
 *			this is governor-specific, a governor using this
 *			will be only compatible with devices aware of it.
 */
struct devfreq_dev_status {
	/* both since the last measure */
	unsigned long total_time;
	unsigned long busy_time;
	unsigned long current_frequency;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	void *private_data;
};

/*
 * The resulting frequency should be at most this. (this bound is the
 * least upper bound; thus, the resulting freq should be lower or same)
 * If the flag is not set, the resulting frequency should be at most the
 * bound (greatest lower bound)
 */
#define DEVFREQ_FLAG_LEAST_UPPER_BOUND		0x1
#define DEVFREQ_FLAG_WAKEUP_MAXFREQ		0x2

#define DEVFREQ_FLAG_FAST_HINT	0x2
#define DEVFREQ_FLAG_SLOW_HINT	0x4

/**
 * struct devfreq_governor_data - mapping to per device governor data
 * @name:		The name of the governor.
 * @data:		Private data for the governor.
 *
 * Devices may pass in an array of this structure to allow governors
 * to get the correct data pointer when they are enabled after
 * the devfreq_add_device() call.
 */
struct devfreq_governor_data {
	const char *name;
	void *data;
};

/**
 * struct devfreq_dev_profile - Devfreq's user device profile
 * @initial_freq:	The operating frequency when devfreq_add_device() is
 *			called.
 * @polling_ms:		The polling interval in ms. 0 disables polling.
 * @target:		The device should set its operating frequency at
<<<<<<< HEAD
=======
=======
	void *private_date;
};

/**
 * struct devfreq_pm_qos_table - An PM QoS requiement entry for devfreq dev.
 * @freq		Lowest frequency to meet the QoS requirement
 *			represented by qos_value. If freq=0, it means that
 *			this element is the last in the array.
 * @qos_value		The qos value defined in pm_qos_params.h
 *
 * Note that the array of devfreq_pm_qos_table should be sorted by freq
 * in the ascending order except for the last element, which should be 0.
 */
struct devfreq_pm_qos_table {
	unsigned long freq; /* 0 if this is the last element */
	s32 qos_value;
};

/*
 * target callback, which is to provide additional information to the
 * devfreq driver.
 */

/* The resulting frequency should be at least this. (least upper bound) */
#define DEVFREQ_OPTION_FREQ_LUB	0x0
/* The resulting frequency should be at most this. (greatest lower bound) */
#define DEVFREQ_OPTION_FREQ_GLB 0x1

/**
 * struct devfreq_dev_profile - Devfreq's user device profile
 * @initial_freq	The operating frequency when devfreq_add_device() is
 *			called.
 * @polling_ms		The polling interval in ms. 0 disables polling.
 * @qos_type		QoS Type (defined in pm_qos_params.h)
 *			0 (PM_QOS_RESERVED) if not used.
 * @qos_use_max		true: throughput (larger is faster)
 *			false: latency (smaller is faster)
 * @qos_list		Array of QoS requirements ending with .freq = 0
 *			NULL if not used. It should be either NULL or
 *			have a length > 1 with a first element effective.
 * @target		The device should set its operating frequency at
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *			freq or lowest-upper-than-freq value. If freq is
 *			higher than any operable frequency, set maximum.
 *			Before returning, target function should set
 *			freq at the current frequency.
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *			The "flags" parameter's possible values are
 *			explained above with "DEVFREQ_FLAG_*" macros.
 * @get_dev_status:	The device should provide the current performance
 *			status to devfreq, which is used by governors.
 * @get_cur_freq:	The device should provide the current frequency
 *			at which it is operating.
 * @exit:		An optional callback that is called when devfreq
<<<<<<< HEAD
=======
=======
 *			The "option" parameter's possible values are
 *			explained above with "DEVFREQ_OPTION_*" macros.
 * @get_dev_status	The device should provide the current performance
 *			status to devfreq, which is used by governors.
 * @exit		An optional callback that is called when devfreq
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *			is removing the devfreq object due to error or
 *			from devfreq_remove_device() call. If the user
 *			has registered devfreq->nb at a notifier-head,
 *			this is the time to unregister it.
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @freq_table:	Optional list of frequencies to support statistics.
 * @max_state:	The size of freq_table.
 * @governor_data:	Optional array of private data for governors.
 *			This is used to set devfreq->data correctly
 *			when a governor is enabled via sysfs or other
 *			mechanisms after the devfreq_add_device() call.
 * @num_governor_data:  Number of elements in governor_data.
<<<<<<< HEAD
=======
=======
 *
 * Note that the array of qos_list should be sorted by freq
 * in the ascending order.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct devfreq_dev_profile {
	unsigned long initial_freq;
	unsigned int polling_ms;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int (*target)(struct device *dev, unsigned long *freq, u32 flags);
	int (*get_dev_status)(struct device *dev,
			      struct devfreq_dev_status *stat);
	int (*get_cur_freq)(struct device *dev, unsigned long *freq);
	void (*exit)(struct device *dev);

	unsigned int *freq_table;
	unsigned int max_state;
	const struct devfreq_governor_data *governor_data;
	unsigned int num_governor_data;
<<<<<<< HEAD
=======
=======
	int qos_type;
	bool qos_use_max;
	struct devfreq_pm_qos_table *qos_list;

	int (*target)(struct device *dev, unsigned long *freq, u32 options);
	int (*get_dev_status)(struct device *dev,
			      struct devfreq_dev_status *stat);
	void (*exit)(struct device *dev);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * struct devfreq_governor - Devfreq policy governor
<<<<<<< HEAD
 * @node:		list node - contains registered devfreq governors
 * @name:		Governor's name
 * @get_target_freq:	Returns desired operating frequency for the device.
=======
<<<<<<< HEAD
 * @node:		list node - contains registered devfreq governors
 * @name:		Governor's name
 * @get_target_freq:	Returns desired operating frequency for the device.
=======
 * @name		Governor's name
 * @get_target_freq	Returns desired operating frequency for the device.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *			Basically, get_target_freq will run
 *			devfreq_dev_profile.get_dev_status() to get the
 *			status of the device (load = busy_time / total_time).
 *			If no_central_polling is set, this callback is called
 *			only with update_devfreq() notified by OPP.
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @event_handler:      Callback for devfreq core framework to notify events
 *                      to governors. Events include per device governor
 *                      init and exit, opp changes out of devfreq, suspend
 *                      and resume of per device devfreq during device idle.
<<<<<<< HEAD
=======
=======
 * @init		Called when the devfreq is being attached to a device
 * @exit		Called when the devfreq is being removed from a
 *			device. Governor should stop any internal routines
 *			before return because related data may be
 *			freed after exit().
 * @no_central_polling	Do not use devfreq's central polling mechanism.
 *			When this is set, devfreq will not call
 *			get_target_freq with devfreq_monitor(). However,
 *			devfreq will call get_target_freq with
 *			devfreq_update() notified by OPP framework.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Note that the callbacks are called with devfreq->lock locked by devfreq.
 */
struct devfreq_governor {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct list_head node;

	const char name[DEVFREQ_NAME_LEN];
	int (*get_target_freq)(struct devfreq *this, unsigned long *freq,
				u32 *flag);
	int (*event_handler)(struct devfreq *devfreq,
				unsigned int event, void *data);
<<<<<<< HEAD
=======
=======
	const char name[DEVFREQ_NAME_LEN];
	int (*get_target_freq)(struct devfreq *this, unsigned long *freq);
	int (*init)(struct devfreq *this);
	void (*exit)(struct devfreq *this);
	const bool no_central_polling;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * struct devfreq - Device devfreq structure
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @node:	list node - contains the devices with devfreq that have been
 *		registered.
 * @lock:	a mutex to protect accessing devfreq.
 * @dev:	device registered by devfreq class. dev.parent is the device
 *		using devfreq.
 * @profile:	device-specific devfreq profile
 * @governor:	method how to choose frequency based on the usage.
 * @governor_name:	devfreq governor name for use with this devfreq
 * @nb:		notifier block used to notify devfreq object that it should
 *		reevaluate operable frequencies. Devfreq users may use
 *		devfreq.nb to the corresponding register notifier call chain.
 * @work:	delayed work for load monitoring.
 * @previous_freq:	previously configured frequency value.
 * @data:	Private data of the governor. The devfreq framework does not
 *		touch this.
 * @min_freq:	Limit minimum frequency requested by user (0: none)
 * @max_freq:	Limit maximum frequency requested by user (0: none)
 * @stop_polling:	 devfreq polling status of a device.
 * @total_trans:	Number of devfreq transitions
 * @trans_table:	Statistics of devfreq transitions
 * @time_in_state:	Statistics of devfreq states
 * @last_stat_updated:	The last time stat updated
<<<<<<< HEAD
=======
=======
 * @node	list node - contains the devices with devfreq that have been
 *		registered.
 * @lock	a mutex to protect accessing devfreq.
 * @dev		device registered by devfreq class. dev.parent is the device
 *		using devfreq.
 * @profile	device-specific devfreq profile
 * @governor	method how to choose frequency based on the usage.
 * @nb		notifier block used to notify devfreq object that it should
 *		reevaluate operable frequencies. Devfreq users may use
 *		devfreq.nb to the corresponding register notifier call chain.
 * @polling_jiffies	interval in jiffies.
 * @previous_freq	previously configured frequency value.
 * @next_polling	the number of remaining jiffies to poll with
 *			"devfreq_monitor" executions to reevaluate
 *			frequency/voltage of the device. Set by
 *			profile's polling_ms interval.
 * @data	Private data of the governor. The devfreq framework does not
 *		touch this.
 * @being_removed	a flag to mark that this object is being removed in
 *			order to prevent trying to remove the object multiple times.
 * @min_freq	Limit minimum frequency requested by user (0: none)
 * @max_freq	Limit maximum frequency requested by user (0: none)
 * @qos_nb	notifier block used to notify pm qos requests
 * @qos_min_freq	Limit minimum frequency requested by QoS
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This structure stores the devfreq information for a give device.
 *
 * Note that when a governor accesses entries in struct devfreq in its
 * functions except for the context of callbacks defined in struct
 * devfreq_governor, the governor should protect its access with the
 * struct mutex lock in struct devfreq. A governor may use this mutex
 * to protect its own private data in void *data as well.
 */
struct devfreq {
	struct list_head node;

	struct mutex lock;
	struct device dev;
	struct devfreq_dev_profile *profile;
	const struct devfreq_governor *governor;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	char governor_name[DEVFREQ_NAME_LEN];
	struct notifier_block nb;
	struct delayed_work work;

	unsigned long previous_freq;

	void *data; /* private data for governors */

	unsigned long min_freq;
	unsigned long max_freq;
	bool stop_polling;

	/* information for device freqeuncy transition */
	unsigned int total_trans;
	unsigned int *trans_table;
	unsigned long *time_in_state;
	unsigned long last_stat_updated;
<<<<<<< HEAD
=======
=======
	struct notifier_block nb;

	unsigned long polling_jiffies;
	unsigned long previous_freq;
	unsigned int next_polling;

	void *data; /* private data for governors */

	bool being_removed;

	unsigned long min_freq;
	unsigned long max_freq;
	struct notifier_block qos_nb;
	unsigned long qos_min_freq;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

#if defined(CONFIG_PM_DEVFREQ)
extern struct devfreq *devfreq_add_device(struct device *dev,
				  struct devfreq_dev_profile *profile,
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				  const char *governor_name,
				  void *data);
extern int devfreq_remove_device(struct devfreq *devfreq);
extern int devfreq_suspend_device(struct devfreq *devfreq);
extern int devfreq_resume_device(struct devfreq *devfreq);

/* Helper functions for devfreq user device driver with OPP. */
extern struct opp *devfreq_recommended_opp(struct device *dev,
					   unsigned long *freq, u32 flags);
<<<<<<< HEAD
=======
=======
				  const struct devfreq_governor *governor,
				  void *data);
extern int devfreq_remove_device(struct devfreq *devfreq);

/* Helper functions for devfreq user device driver with OPP. */
extern struct opp *devfreq_recommended_opp(struct device *dev,
					   unsigned long *freq, bool floor);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int devfreq_register_opp_notifier(struct device *dev,
					 struct devfreq *devfreq);
extern int devfreq_unregister_opp_notifier(struct device *dev,
					   struct devfreq *devfreq);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_DEVFREQ_GOV_SIMPLE_ONDEMAND
/**
 * struct devfreq_simple_ondemand_data - void *data fed to struct devfreq
 *	and devfreq_add_device
 * @upthreshold:	If the load is over this value, the frequency jumps.
 *			Specify 0 to use the default. Valid value = 0 to 100.
 * @downdifferential:	If the load is under upthreshold - downdifferential,
 *			the governor may consider slowing the frequency down.
 *			Specify 0 to use the default. Valid value = 0 to 100.
 *			downdifferential < upthreshold must hold.
 * @simple_scaling:	Setting this flag will scale the clocks up only if the
 *			load is above @upthreshold and will scale the clocks
 *			down only if the load is below @downdifferential.
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_DEVFREQ_GOV_POWERSAVE
extern const struct devfreq_governor devfreq_powersave;
#endif
#ifdef CONFIG_DEVFREQ_GOV_PERFORMANCE
extern const struct devfreq_governor devfreq_performance;
#endif
#ifdef CONFIG_DEVFREQ_GOV_USERSPACE
extern const struct devfreq_governor devfreq_userspace;
#endif
#ifdef CONFIG_DEVFREQ_GOV_SIMPLE_ONDEMAND
extern const struct devfreq_governor devfreq_simple_ondemand;
/**
 * struct devfreq_simple_ondemand_data - void *data fed to struct devfreq
 *	and devfreq_add_device
 * @ upthreshold	If the load is over this value, the frequency jumps.
 *			Specify 0 to use the default. Valid value = 0 to 100.
 * @ downdifferential	If the load is under upthreshold - downdifferential,
 *			the governor may consider slowing the frequency down.
 *			Specify 0 to use the default. Valid value = 0 to 100.
 *			downdifferential < upthreshold must hold.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * If the fed devfreq_simple_ondemand_data pointer is NULL to the governor,
 * the governor uses the default values.
 */
struct devfreq_simple_ondemand_data {
	unsigned int upthreshold;
	unsigned int downdifferential;
<<<<<<< HEAD
	unsigned int simple_scaling;
};
=======
<<<<<<< HEAD
	unsigned int simple_scaling;
};
=======
};

int devfreq_simple_ondemand_flexrate_do(struct devfreq *devfreq,
					unsigned long interval,
					unsigned long number);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif

#else /* !CONFIG_PM_DEVFREQ */
static struct devfreq *devfreq_add_device(struct device *dev,
					  struct devfreq_dev_profile *profile,
<<<<<<< HEAD
					  const char *governor_name,
=======
<<<<<<< HEAD
					  const char *governor_name,
=======
					  struct devfreq_governor *governor,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					  void *data)
{
	return NULL;
}

static int devfreq_remove_device(struct devfreq *devfreq)
{
	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int devfreq_suspend_device(struct devfreq *devfreq)
{
	return 0;
}

static int devfreq_resume_device(struct devfreq *devfreq)
{
	return 0;
}

static struct opp *devfreq_recommended_opp(struct device *dev,
					   unsigned long *freq, u32 flags)
<<<<<<< HEAD
=======
=======
static struct opp *devfreq_recommended_opp(struct device *dev,
					   unsigned long *freq, bool floor)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return -EINVAL;
}

static int devfreq_register_opp_notifier(struct device *dev,
					 struct devfreq *devfreq)
{
	return -EINVAL;
}

static int devfreq_unregister_opp_notifier(struct device *dev,
					   struct devfreq *devfreq)
{
	return -EINVAL;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define devfreq_powersave	NULL
#define devfreq_performance	NULL
#define devfreq_userspace	NULL
#define devfreq_simple_ondemand	NULL

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* CONFIG_PM_DEVFREQ */

#endif /* __LINUX_DEVFREQ_H__ */
