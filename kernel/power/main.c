/*
 * kernel/power/main.c - PM subsystem core functionality.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
<<<<<<< HEAD
<<<<<<< HEAD
 *
=======
 * 
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * 
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * This file is released under the GPLv2
 *
 */

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/resume-trace.h>
#include <linux/workqueue.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/hrtimer.h>

#include "power.h"

#define MAX_BUF 100
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#if defined(CONFIG_CPU_FREQ) && defined(CONFIG_ARCH_EXYNOS4)
#define CONFIG_DVFS_LIMIT
#endif

#if defined(CONFIG_CPU_EXYNOS4210)
#define CONFIG_GPU_LOCK
#define CONFIG_ROTATION_BOOSTER_SUPPORT
#endif

#ifdef CONFIG_DVFS_LIMIT
#include <linux/cpufreq.h>
#include <mach/cpufreq.h>
#endif

#ifdef CONFIG_GPU_LOCK
#include <mach/gpufreq.h>
#endif

#if defined(CONFIG_CPU_EXYNOS4412) && defined(CONFIG_VIDEO_MALI400MP) \
		&& defined(CONFIG_VIDEO_MALI400MP_DVFS)
#define CONFIG_PEGASUS_GPU_LOCK
extern int mali_dvfs_bottom_lock_push(int lock_step);
extern int mali_dvfs_bottom_lock_pop(void);
#endif

#include "power.h"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

DEFINE_MUTEX(pm_mutex);

#ifdef CONFIG_PM_SLEEP

/* Routines for PM-transition notifications */

static BLOCKING_NOTIFIER_HEAD(pm_chain_head);

<<<<<<< HEAD
<<<<<<< HEAD
static void touch_event_fn(struct work_struct *work);
static DECLARE_WORK(touch_event_struct, touch_event_fn);

static struct hrtimer tc_ev_timer;
static int tc_ev_processed;
static ktime_t touch_evt_timer_val;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int register_pm_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&pm_chain_head, nb);
}
EXPORT_SYMBOL_GPL(register_pm_notifier);

int unregister_pm_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&pm_chain_head, nb);
}
EXPORT_SYMBOL_GPL(unregister_pm_notifier);

int pm_notifier_call_chain(unsigned long val)
{
<<<<<<< HEAD
<<<<<<< HEAD
	int ret = blocking_notifier_call_chain(&pm_chain_head, val, NULL);

	return notifier_to_errno(ret);
=======
	return (blocking_notifier_call_chain(&pm_chain_head, val, NULL)
			== NOTIFY_BAD) ? -EINVAL : 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return (blocking_notifier_call_chain(&pm_chain_head, val, NULL)
			== NOTIFY_BAD) ? -EINVAL : 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/* If set, devices may be suspended and resumed asynchronously. */
int pm_async_enabled = 1;

static ssize_t pm_async_show(struct kobject *kobj, struct kobj_attribute *attr,
			     char *buf)
{
	return sprintf(buf, "%d\n", pm_async_enabled);
}

static ssize_t pm_async_store(struct kobject *kobj, struct kobj_attribute *attr,
			      const char *buf, size_t n)
{
	unsigned long val;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (val > 1)
		return -EINVAL;

	pm_async_enabled = val;
	return n;
}

power_attr(pm_async);

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t
touch_event_show(struct kobject *kobj,
		 struct kobj_attribute *attr, char *buf)
{
	if (tc_ev_processed == 0)
		return snprintf(buf, strnlen("touch_event", MAX_BUF) + 1,
				"touch_event");
	else
		return snprintf(buf, strnlen("null", MAX_BUF) + 1,
				"null");
}

static ssize_t
touch_event_store(struct kobject *kobj,
		  struct kobj_attribute *attr,
		  const char *buf, size_t n)
{

	hrtimer_cancel(&tc_ev_timer);
	tc_ev_processed = 0;

	/* set a timer to notify the userspace to stop processing
	 * touch event
	 */
	hrtimer_start(&tc_ev_timer, touch_evt_timer_val, HRTIMER_MODE_REL);

	/* wakeup the userspace poll */
	sysfs_notify(kobj, NULL, "touch_event");

	return n;
}

power_attr(touch_event);

static ssize_t
touch_event_timer_show(struct kobject *kobj,
		 struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_BUF, "%lld", touch_evt_timer_val.tv64);
}

static ssize_t
touch_event_timer_store(struct kobject *kobj,
			struct kobj_attribute *attr,
			const char *buf, size_t n)
{
	unsigned long val;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	touch_evt_timer_val = ktime_set(0, val*1000);

	return n;
}

power_attr(touch_event_timer);

static void touch_event_fn(struct work_struct *work)
{
	/* wakeup the userspace poll */
	tc_ev_processed = 1;
	sysfs_notify(power_kobj, NULL, "touch_event");

	return;
}

static enum hrtimer_restart tc_ev_stop(struct hrtimer *hrtimer)
{

	schedule_work(&touch_event_struct);

	return HRTIMER_NORESTART;
}

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_PM_DEBUG
int pm_test_level = TEST_NONE;

static const char * const pm_tests[__TEST_AFTER_LAST] = {
	[TEST_NONE] = "none",
	[TEST_CORE] = "core",
	[TEST_CPUS] = "processors",
	[TEST_PLATFORM] = "platform",
	[TEST_DEVICES] = "devices",
	[TEST_FREEZER] = "freezer",
};

static ssize_t pm_test_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf)
{
	char *s = buf;
	int level;

	for (level = TEST_FIRST; level <= TEST_MAX; level++)
		if (pm_tests[level]) {
			if (level == pm_test_level)
				s += sprintf(s, "[%s] ", pm_tests[level]);
			else
				s += sprintf(s, "%s ", pm_tests[level]);
		}

	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	return (s - buf);
}

static ssize_t pm_test_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t n)
{
	const char * const *s;
	int level;
	char *p;
	int len;
	int error = -EINVAL;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

<<<<<<< HEAD
<<<<<<< HEAD
	lock_system_sleep();
=======
	mutex_lock(&pm_mutex);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	mutex_lock(&pm_mutex);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	level = TEST_FIRST;
	for (s = &pm_tests[level]; level <= TEST_MAX; s++, level++)
		if (*s && len == strlen(*s) && !strncmp(buf, *s, len)) {
			pm_test_level = level;
			error = 0;
			break;
		}

<<<<<<< HEAD
<<<<<<< HEAD
	unlock_system_sleep();
=======
	mutex_unlock(&pm_mutex);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	mutex_unlock(&pm_mutex);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return error ? error : n;
}

power_attr(pm_test);
#endif /* CONFIG_PM_DEBUG */

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_DEBUG_FS
static char *suspend_step_name(enum suspend_stat_step step)
{
	switch (step) {
	case SUSPEND_FREEZE:
		return "freeze";
	case SUSPEND_PREPARE:
		return "prepare";
	case SUSPEND_SUSPEND:
		return "suspend";
	case SUSPEND_SUSPEND_NOIRQ:
		return "suspend_noirq";
	case SUSPEND_RESUME_NOIRQ:
		return "resume_noirq";
	case SUSPEND_RESUME:
		return "resume";
	default:
		return "";
	}
}

static int suspend_stats_show(struct seq_file *s, void *unused)
{
	int i, index, last_dev, last_errno, last_step;

	last_dev = suspend_stats.last_failed_dev + REC_FAILED_NUM - 1;
	last_dev %= REC_FAILED_NUM;
	last_errno = suspend_stats.last_failed_errno + REC_FAILED_NUM - 1;
	last_errno %= REC_FAILED_NUM;
	last_step = suspend_stats.last_failed_step + REC_FAILED_NUM - 1;
	last_step %= REC_FAILED_NUM;
	seq_printf(s, "%s: %d\n%s: %d\n%s: %d\n%s: %d\n%s: %d\n"
			"%s: %d\n%s: %d\n%s: %d\n%s: %d\n%s: %d\n",
			"success", suspend_stats.success,
			"fail", suspend_stats.fail,
			"failed_freeze", suspend_stats.failed_freeze,
			"failed_prepare", suspend_stats.failed_prepare,
			"failed_suspend", suspend_stats.failed_suspend,
			"failed_suspend_late",
				suspend_stats.failed_suspend_late,
			"failed_suspend_noirq",
				suspend_stats.failed_suspend_noirq,
			"failed_resume", suspend_stats.failed_resume,
			"failed_resume_early",
				suspend_stats.failed_resume_early,
			"failed_resume_noirq",
				suspend_stats.failed_resume_noirq);
	seq_printf(s,	"failures:\n  last_failed_dev:\t%-s\n",
			suspend_stats.failed_devs[last_dev]);
	for (i = 1; i < REC_FAILED_NUM; i++) {
		index = last_dev + REC_FAILED_NUM - i;
		index %= REC_FAILED_NUM;
		seq_printf(s, "\t\t\t%-s\n",
			suspend_stats.failed_devs[index]);
	}
	seq_printf(s,	"  last_failed_errno:\t%-d\n",
			suspend_stats.errno[last_errno]);
	for (i = 1; i < REC_FAILED_NUM; i++) {
		index = last_errno + REC_FAILED_NUM - i;
		index %= REC_FAILED_NUM;
		seq_printf(s, "\t\t\t%-d\n",
			suspend_stats.errno[index]);
	}
	seq_printf(s,	"  last_failed_step:\t%-s\n",
			suspend_step_name(
				suspend_stats.failed_steps[last_step]));
	for (i = 1; i < REC_FAILED_NUM; i++) {
		index = last_step + REC_FAILED_NUM - i;
		index %= REC_FAILED_NUM;
		seq_printf(s, "\t\t\t%-s\n",
			suspend_step_name(
				suspend_stats.failed_steps[index]));
	}

	return 0;
}

static int suspend_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, suspend_stats_show, NULL);
}

static const struct file_operations suspend_stats_operations = {
	.open           = suspend_stats_open,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};

static int __init pm_debugfs_init(void)
{
	debugfs_create_file("suspend_stats", S_IFREG | S_IRUGO,
			NULL, NULL, &suspend_stats_operations);
	return 0;
}

late_initcall(pm_debugfs_init);
#endif /* CONFIG_DEBUG_FS */

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* CONFIG_PM_SLEEP */

struct kobject *power_kobj;

/**
 *	state - control system power state.
 *
 *	show() returns what states are supported, which is hard-coded to
 *	'standby' (Power-On Suspend), 'mem' (Suspend-to-RAM), and
 *	'disk' (Suspend-to-Disk).
 *
<<<<<<< HEAD
<<<<<<< HEAD
 *	store() accepts one of those strings, translates it into the
=======
 *	store() accepts one of those strings, translates it into the 
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *	store() accepts one of those strings, translates it into the 
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *	proper enumerated value, and initiates a suspend transition.
 */
static ssize_t state_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	char *s = buf;
#ifdef CONFIG_SUSPEND
	int i;

	for (i = 0; i < PM_SUSPEND_MAX; i++) {
		if (pm_states[i] && valid_state(i))
			s += sprintf(s,"%s ", pm_states[i]);
	}
#endif
#ifdef CONFIG_HIBERNATION
	s += sprintf(s, "%s\n", "disk");
#else
	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';
#endif
	return (s - buf);
}
<<<<<<< HEAD
<<<<<<< HEAD

static suspend_state_t decode_state(const char *buf, size_t n)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_FAST_BOOT
bool fake_shut_down = false;
EXPORT_SYMBOL(fake_shut_down);

extern void wakelock_force_suspend(void);
#endif

static ssize_t state_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
#ifdef CONFIG_SUSPEND
#ifdef CONFIG_EARLYSUSPEND
	suspend_state_t state = PM_SUSPEND_ON;
#else
	suspend_state_t state = PM_SUSPEND_STANDBY;
#endif
	const char * const *s;
#endif
	char *p;
	int len;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	int error = -EINVAL;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	int error = -EINVAL;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Check hibernation first. */
	if (len == 4 && !strncmp(buf, "disk", len))
		return PM_SUSPEND_MAX;

#ifdef CONFIG_SUSPEND
	for (s = &pm_states[state]; state < PM_SUSPEND_MAX; s++, state++)
		if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
			return state;
#endif

	return PM_SUSPEND_ON;
}

static ssize_t state_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
	suspend_state_t state;
	int error;

	error = pm_autosleep_lock();
	if (error)
		return error;

	if (pm_autosleep_state() > PM_SUSPEND_ON) {
		error = -EBUSY;
		goto out;
	}

	state = decode_state(buf, n);
	if (state < PM_SUSPEND_MAX)
		error = pm_suspend(state);
	else if (state == PM_SUSPEND_MAX)
		error = hibernate();
	else
		error = -EINVAL;

 out:
	pm_autosleep_unlock();
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* First, check if we are requested to hibernate */
	if (len == 4 && !strncmp(buf, "disk", len)) {
		error = hibernate();
  goto Exit;
	}

#ifdef CONFIG_SUSPEND
	for (s = &pm_states[state]; state < PM_SUSPEND_MAX; s++, state++) {
		if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
			break;
	}

#ifdef CONFIG_FAST_BOOT
	if (len == 4 && !strncmp(buf, "dmem", len)) {
		pr_info("%s: fake shut down!!!\n", __func__);
		fake_shut_down = true;
		state = PM_SUSPEND_MEM;
	}
#endif

	if (state < PM_SUSPEND_MAX && *s) {
#ifdef CONFIG_EARLYSUSPEND
		if (state == PM_SUSPEND_ON || valid_state(state)) {
			error = 0;
			request_suspend_state(state);
		}
#ifdef CONFIG_FAST_BOOT
		if (fake_shut_down)
			wakelock_force_suspend();
#endif
#else
		error = enter_state(state);
#endif
	}
#endif

 Exit:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return error ? error : n;
}

power_attr(state);

#ifdef CONFIG_PM_SLEEP
/*
 * The 'wakeup_count' attribute, along with the functions defined in
 * drivers/base/power/wakeup.c, provides a means by which wakeup events can be
 * handled in a non-racy way.
 *
 * If a wakeup event occurs when the system is in a sleep state, it simply is
 * woken up.  In turn, if an event that would wake the system up from a sleep
 * state occurs when it is undergoing a transition to that sleep state, the
 * transition should be aborted.  Moreover, if such an event occurs when the
 * system is in the working state, an attempt to start a transition to the
 * given sleep state should fail during certain period after the detection of
 * the event.  Using the 'state' attribute alone is not sufficient to satisfy
 * these requirements, because a wakeup event may occur exactly when 'state'
 * is being written to and may be delivered to user space right before it is
 * frozen, so the event will remain only partially processed until the system is
 * woken up by another event.  In particular, it won't cause the transition to
 * a sleep state to be aborted.
 *
 * This difficulty may be overcome if user space uses 'wakeup_count' before
 * writing to 'state'.  It first should read from 'wakeup_count' and store
 * the read value.  Then, after carrying out its own preparations for the system
 * transition to a sleep state, it should write the stored value to
 * 'wakeup_count'.  If that fails, at least one wakeup event has occurred since
 * 'wakeup_count' was read and 'state' should not be written to.  Otherwise, it
 * is allowed to write to 'state', but the transition will be aborted if there
 * are any wakeup events detected after 'wakeup_count' was written to.
 */

static ssize_t wakeup_count_show(struct kobject *kobj,
				struct kobj_attribute *attr,
				char *buf)
{
	unsigned int val;

<<<<<<< HEAD
<<<<<<< HEAD
	return pm_get_wakeup_count(&val, true) ?
		sprintf(buf, "%u\n", val) : -EINTR;
=======
	return pm_get_wakeup_count(&val) ? sprintf(buf, "%u\n", val) : -EINTR;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return pm_get_wakeup_count(&val) ? sprintf(buf, "%u\n", val) : -EINTR;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static ssize_t wakeup_count_store(struct kobject *kobj,
				struct kobj_attribute *attr,
				const char *buf, size_t n)
{
	unsigned int val;
<<<<<<< HEAD
<<<<<<< HEAD
	int error;

	error = pm_autosleep_lock();
	if (error)
		return error;

	if (pm_autosleep_state() > PM_SUSPEND_ON) {
		error = -EBUSY;
		goto out;
	}

	error = -EINVAL;
	if (sscanf(buf, "%u", &val) == 1) {
		if (pm_save_wakeup_count(val))
			error = n;
	}

 out:
	pm_autosleep_unlock();
	return error;
}

power_attr(wakeup_count);

#ifdef CONFIG_PM_AUTOSLEEP
static ssize_t autosleep_show(struct kobject *kobj,
			      struct kobj_attribute *attr,
			      char *buf)
{
	suspend_state_t state = pm_autosleep_state();

	if (state == PM_SUSPEND_ON)
		return sprintf(buf, "off\n");

#ifdef CONFIG_SUSPEND
	if (state < PM_SUSPEND_MAX)
		return sprintf(buf, "%s\n", valid_state(state) ?
						pm_states[state] : "error");
#endif
#ifdef CONFIG_HIBERNATION
	return sprintf(buf, "disk\n");
#else
	return sprintf(buf, "error");
#endif
}

static ssize_t autosleep_store(struct kobject *kobj,
			       struct kobj_attribute *attr,
			       const char *buf, size_t n)
{
	suspend_state_t state = decode_state(buf, n);
	int error;

	if (state == PM_SUSPEND_ON
	    && strcmp(buf, "off") && strcmp(buf, "off\n"))
		return -EINVAL;

	error = pm_autosleep_set_state(state);
	return error ? error : n;
}

power_attr(autosleep);
#endif /* CONFIG_PM_AUTOSLEEP */

#ifdef CONFIG_PM_WAKELOCKS
static ssize_t wake_lock_show(struct kobject *kobj,
			      struct kobj_attribute *attr,
			      char *buf)
{
	return pm_show_wakelocks(buf, true);
}

static ssize_t wake_lock_store(struct kobject *kobj,
			       struct kobj_attribute *attr,
			       const char *buf, size_t n)
{
	int error = pm_wake_lock(buf);
	return error ? error : n;
}

power_attr(wake_lock);

static ssize_t wake_unlock_show(struct kobject *kobj,
				struct kobj_attribute *attr,
				char *buf)
{
	return pm_show_wakelocks(buf, false);
}

static ssize_t wake_unlock_store(struct kobject *kobj,
				 struct kobj_attribute *attr,
				 const char *buf, size_t n)
{
	int error = pm_wake_unlock(buf);
	return error ? error : n;
}

power_attr(wake_unlock);

#endif /* CONFIG_PM_WAKELOCKS */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (sscanf(buf, "%u", &val) == 1) {
		if (pm_save_wakeup_count(val))
			return n;
	}
	return -EINVAL;
}

power_attr(wakeup_count);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* CONFIG_PM_SLEEP */

#ifdef CONFIG_PM_TRACE
int pm_trace_enabled;

static ssize_t pm_trace_show(struct kobject *kobj, struct kobj_attribute *attr,
			     char *buf)
{
	return sprintf(buf, "%d\n", pm_trace_enabled);
}

static ssize_t
pm_trace_store(struct kobject *kobj, struct kobj_attribute *attr,
	       const char *buf, size_t n)
{
	int val;

	if (sscanf(buf, "%d", &val) == 1) {
		pm_trace_enabled = !!val;
		return n;
	}
	return -EINVAL;
}

power_attr(pm_trace);

static ssize_t pm_trace_dev_match_show(struct kobject *kobj,
				       struct kobj_attribute *attr,
				       char *buf)
{
	return show_trace_dev_match(buf, PAGE_SIZE);
}

static ssize_t
pm_trace_dev_match_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t n)
{
	return -EINVAL;
}

power_attr(pm_trace_dev_match);

#endif /* CONFIG_PM_TRACE */

#ifdef CONFIG_USER_WAKELOCK
power_attr(wake_lock);
power_attr(wake_unlock);
#endif

<<<<<<< HEAD
<<<<<<< HEAD
static struct attribute *g[] = {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_DVFS_LIMIT
static int cpufreq_max_limit_val = -1;
static int cpufreq_min_limit_val = -1;
DEFINE_MUTEX(cpufreq_limit_mutex);

static ssize_t cpufreq_table_show(struct kobject *kobj,
				struct kobj_attribute *attr,
				char *buf)
{
	ssize_t count = 0;
	struct cpufreq_frequency_table *table;
	struct cpufreq_policy *policy;
	unsigned int min_freq = ~0;
	unsigned int max_freq = 0;
	unsigned int i = 0;

	table = cpufreq_frequency_get_table(0);
	if (!table) {
		printk(KERN_ERR "%s: Failed to get the cpufreq table\n",
			__func__);
		return sprintf(buf, "Failed to get the cpufreq table\n");
	}

	policy = cpufreq_cpu_get(0);
	if (policy) {
	/* /sys/devices/system/cpu/cpu0/cpufreq/scaling_min&max_freq */
		min_freq = policy->min;
		max_freq = policy->max;
        #if 0  /* /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min&max_freq */
		min_freq = policy->cpuinfo.min_freq;
		max_freq = policy->cpuinfo.max_freq;
	#endif
	}

	for (i = 0; (table[i].frequency != CPUFREQ_TABLE_END); i++) {
		if ((table[i].frequency == CPUFREQ_ENTRY_INVALID) ||
		    (table[i].frequency > max_freq) ||
		    (table[i].frequency < min_freq))
			continue;
		count += sprintf(&buf[count], "%d ", table[i].frequency);
	}
	count += sprintf(&buf[count], "\n");

	return count;
}

static ssize_t cpufreq_table_store(struct kobject *kobj,
				struct kobj_attribute *attr,
				const char *buf, size_t n)
{
	printk(KERN_ERR "%s: cpufreq_table is read-only\n", __func__);
	return -EINVAL;
}

#define VALID_LEVEL 1
static int get_cpufreq_level(unsigned int freq, unsigned int *level)
{
	struct cpufreq_frequency_table *table;
	unsigned int i = 0;

	table = cpufreq_frequency_get_table(0);
	if (!table) {
		printk(KERN_ERR "%s: Failed to get the cpufreq table\n",
			__func__);
		return -EINVAL;
	}

	for (i = 0; (table[i].frequency != CPUFREQ_TABLE_END); i++)
		if (table[i].frequency == freq) {
			*level = i;
			return VALID_LEVEL;
		}

	printk(KERN_ERR "%s: %u KHz is an unsupported cpufreq\n",
		__func__, freq);
	return -EINVAL;
}

static ssize_t cpufreq_max_limit_show(struct kobject *kobj,
					struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%d\n", cpufreq_max_limit_val);
}

static ssize_t cpufreq_max_limit_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t n)
{
	int val;
	unsigned int cpufreq_level;
	int lock_ret;
	ssize_t ret = -EINVAL;

	mutex_lock(&cpufreq_limit_mutex);

	if (sscanf(buf, "%d", &val) != 1) {
		printk(KERN_ERR "%s: Invalid cpufreq format\n", __func__);
		goto out;
	}

	if (val == -1) { /* Unlock request */
		if (cpufreq_max_limit_val != -1) {
			exynos_cpufreq_upper_limit_free(DVFS_LOCK_ID_USER);
			cpufreq_max_limit_val = -1;
		} else /* Already unlocked */
			printk(KERN_ERR "%s: Unlock request is ignored\n",
				__func__);
	} else { /* Lock request */
		if (get_cpufreq_level((unsigned int)val, &cpufreq_level)
		    == VALID_LEVEL) {
			if (cpufreq_max_limit_val != -1)
				/* Unlock the previous lock */
				exynos_cpufreq_upper_limit_free(
					DVFS_LOCK_ID_USER);
			lock_ret = exynos_cpufreq_upper_limit(
					DVFS_LOCK_ID_USER, cpufreq_level);
			/* ret of exynos_cpufreq_upper_limit is meaningless.
			   0 is fail? success? */
			cpufreq_max_limit_val = val;
		} else /* Invalid lock request --> No action */
			printk(KERN_ERR "%s: Lock request is invalid\n",
				__func__);
	}

	ret = n;
out:
	mutex_unlock(&cpufreq_limit_mutex);
	return ret;
}

static ssize_t cpufreq_min_limit_show(struct kobject *kobj,
					struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%d\n", cpufreq_min_limit_val);
}

static ssize_t cpufreq_min_limit_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t n)
{
	int val;
	unsigned int cpufreq_level;
	int lock_ret;
	ssize_t ret = -EINVAL;

	mutex_lock(&cpufreq_limit_mutex);

	if (sscanf(buf, "%d", &val) != 1) {
		printk(KERN_ERR "%s: Invalid cpufreq format\n", __func__);
		goto out;
	}

	if (val == -1) { /* Unlock request */
		if (cpufreq_min_limit_val != -1) {
			exynos_cpufreq_lock_free(DVFS_LOCK_ID_USER);
			cpufreq_min_limit_val = -1;
		} else /* Already unlocked */
			printk(KERN_ERR "%s: Unlock request is ignored\n",
				__func__);
	} else { /* Lock request */
		if (get_cpufreq_level((unsigned int)val, &cpufreq_level)
			== VALID_LEVEL) {
			if (cpufreq_min_limit_val != -1)
				/* Unlock the previous lock */
				exynos_cpufreq_lock_free(DVFS_LOCK_ID_USER);
			lock_ret = exynos_cpufreq_lock(
					DVFS_LOCK_ID_USER, cpufreq_level);
			/* ret of exynos_cpufreq_lock is meaningless.
			   0 is fail? success? */
			cpufreq_min_limit_val = val;
		if ((cpufreq_max_limit_val != -1) &&
			    (cpufreq_min_limit_val > cpufreq_max_limit_val))
				printk(KERN_ERR "%s: Min lock may not work well"
					" because of Max lock\n", __func__);
		} else /* Invalid lock request --> No action */
			printk(KERN_ERR "%s: Lock request is invalid\n",
				__func__);
	}

	ret = n;
out:
	mutex_unlock(&cpufreq_limit_mutex);
	return ret;
}

power_attr(cpufreq_table);
power_attr(cpufreq_max_limit);
power_attr(cpufreq_min_limit);
#endif /* CONFIG_DVFS_LIMIT */

#ifdef CONFIG_GPU_LOCK
static int gpu_lock_val;
DEFINE_MUTEX(gpu_lock_mutex);

static ssize_t gpu_lock_show(struct kobject *kobj,
					struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%d\n", gpu_lock_val);
}

static ssize_t gpu_lock_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t n)
{
	int val;
	ssize_t ret = -EINVAL;

	mutex_lock(&gpu_lock_mutex);

	if (sscanf(buf, "%d", &val) != 1) {
		pr_info("%s: Invalid mali lock format\n", __func__);
		goto out;
	}

	if (val == 0) {
		if (gpu_lock_val != 0) {
			exynos_gpufreq_unlock();
			gpu_lock_val = 0;
		} else {
			pr_info("%s: Unlock request is ignored\n", __func__);
		}
	} else if (val == 1) {
		if (gpu_lock_val == 0) {
			exynos_gpufreq_lock();
			gpu_lock_val = val;
		} else {
			pr_info("%s: Lock request is ignored\n", __func__);
		}
	} else {
		pr_info("%s: Lock request is invalid\n", __func__);
	}

	ret = n;
out:
	mutex_unlock(&gpu_lock_mutex);
	return ret;
}
power_attr(gpu_lock);
#endif

#ifdef CONFIG_ROTATION_BOOSTER_SUPPORT
static inline void rotation_booster_on(void)
{
	exynos_cpufreq_lock(DVFS_LOCK_ID_ROTATION_BOOSTER, L0);
	exynos4_busfreq_lock(DVFS_LOCK_ID_ROTATION_BOOSTER, BUS_L0);
	exynos_gpufreq_lock();
}

static inline void rotation_booster_off(void)
{
	exynos_gpufreq_unlock();
	exynos4_busfreq_lock_free(DVFS_LOCK_ID_ROTATION_BOOSTER);
	exynos_cpufreq_lock_free(DVFS_LOCK_ID_ROTATION_BOOSTER);
}

static int rotation_booster_val;
DEFINE_MUTEX(rotation_booster_mutex);

static ssize_t rotation_booster_show(struct kobject *kobj,
					struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "%d\n", rotation_booster_val);
}

static ssize_t rotation_booster_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t n)
{
	int val;
	ssize_t ret = -EINVAL;

	mutex_lock(&rotation_booster_mutex);

	if (sscanf(buf, "%d", &val) != 1) {
		pr_info("%s: Invalid rotation_booster on, off format\n", \
			__func__);
		goto out;
	}

	if (val == 0) {
		if (rotation_booster_val != 0) {
			rotation_booster_off();
			rotation_booster_val = 0;
		} else {
			pr_info("%s: rotation_booster off request"
				" is ignored\n", __func__);
		}
	} else if (val == 1) {
		if (rotation_booster_val == 0) {
			rotation_booster_on();
			rotation_booster_val = val;
		} else {
			pr_info("%s: rotation_booster on request"
				" is ignored\n", __func__);
		}
	} else {
		pr_info("%s: rotation_booster request is invalid\n", __func__);
	}

	ret = n;
out:
	mutex_unlock(&rotation_booster_mutex);
	return ret;
}
power_attr(rotation_booster);
#else /* CONFIG_ROTATION_BOOSTER_SUPPORT */
static inline void rotation_booster_on(void){}
static inline void rotation_booster_off(void){}
#endif /* CONFIG_ROTATION_BOOSTER_SUPPORT */

#ifdef CONFIG_PEGASUS_GPU_LOCK
static int mali_lock_val;
static int mali_lock_cnt;
DEFINE_MUTEX(mali_lock_mutex);

static ssize_t mali_lock_show(struct kobject *kobj,
					struct kobj_attribute *attr,
					char *buf)
{
	return sprintf(buf, "level = %d, count = %d\n",
			mali_lock_val, mali_lock_cnt);
}

static ssize_t mali_lock_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t n)
{
	int val;
	ssize_t ret = -EINVAL;

	mutex_lock(&mali_lock_mutex);

	if (sscanf(buf, "%d", &val) != 1) {
		pr_info("%s: Invalid mali lock format\n", __func__);
		goto out;
	}

	if (val == 0) {	/* unlock */
		mali_lock_cnt = mali_dvfs_bottom_lock_pop();
		if (mali_lock_cnt == 0)
			mali_lock_val = 0;
	} else if (val > 0 && val < 5) { /* lock with level */
		mali_lock_cnt = mali_dvfs_bottom_lock_push(val);
		if (mali_lock_val < val)
			mali_lock_val = val;
	} else {
		pr_info("%s: Lock request is invalid\n", __func__);
	}

	ret = n;
out:
	mutex_unlock(&mali_lock_mutex);
	return ret;
}
power_attr(mali_lock);
#endif

static struct attribute * g[] = {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&state_attr.attr,
#ifdef CONFIG_PM_TRACE
	&pm_trace_attr.attr,
	&pm_trace_dev_match_attr.attr,
#endif
#ifdef CONFIG_PM_SLEEP
	&pm_async_attr.attr,
	&wakeup_count_attr.attr,
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_PM_AUTOSLEEP
	&autosleep_attr.attr,
#endif
#ifdef CONFIG_PM_WAKELOCKS
	&wake_lock_attr.attr,
	&wake_unlock_attr.attr,
#endif
	&touch_event_attr.attr,
	&touch_event_timer_attr.attr,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_PM_DEBUG
	&pm_test_attr.attr,
#endif
#ifdef CONFIG_USER_WAKELOCK
	&wake_lock_attr.attr,
	&wake_unlock_attr.attr,
#endif
#endif
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_DVFS_LIMIT
	&cpufreq_table_attr.attr,
	&cpufreq_max_limit_attr.attr,
	&cpufreq_min_limit_attr.attr,
#endif
#ifdef CONFIG_GPU_LOCK
	&gpu_lock_attr.attr,
#endif
#ifdef CONFIG_PEGASUS_GPU_LOCK
	&mali_lock_attr.attr,
#endif
#ifdef CONFIG_ROTATION_BOOSTER_SUPPORT
	&rotation_booster_attr.attr,
#endif
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = g,
};

#ifdef CONFIG_PM_RUNTIME
struct workqueue_struct *pm_wq;
EXPORT_SYMBOL_GPL(pm_wq);

static int __init pm_start_workqueue(void)
{
	pm_wq = alloc_workqueue("pm", WQ_FREEZABLE, 0);

	return pm_wq ? 0 : -ENOMEM;
}
#else
static inline int pm_start_workqueue(void) { return 0; }
#endif

static int __init pm_init(void)
{
	int error = pm_start_workqueue();
	if (error)
		return error;
	hibernate_image_size_init();
	hibernate_reserved_size_init();
<<<<<<< HEAD
<<<<<<< HEAD

	touch_evt_timer_val = ktime_set(2, 0);
	hrtimer_init(&tc_ev_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	tc_ev_timer.function = &tc_ev_stop;
	tc_ev_processed = 1;

	power_kobj = kobject_create_and_add("power", NULL);
	if (!power_kobj)
		return -ENOMEM;
	error = sysfs_create_group(power_kobj, &attr_group);
	if (error)
		return error;
	return pm_autosleep_init();
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	power_kobj = kobject_create_and_add("power", NULL);
	if (!power_kobj)
		return -ENOMEM;
	return sysfs_create_group(power_kobj, &attr_group);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

core_initcall(pm_init);
