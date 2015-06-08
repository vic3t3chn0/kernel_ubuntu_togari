/*
 * kernel/power/suspend.c - Suspend to RAM and standby functionality.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 *
 * This file is released under the GPLv2.
 */

#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/cpu.h>
#include <linux/syscalls.h>
#include <linux/gfp.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/slab.h>
<<<<<<< HEAD
#include <linux/export.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/rtc.h>
=======
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/ftrace.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
#include <trace/events/power.h>

#include "power.h"

const char *const pm_states[PM_SUSPEND_MAX] = {
#ifdef CONFIG_EARLYSUSPEND
	[PM_SUSPEND_ON]		= "on",
#endif
	[PM_SUSPEND_STANDBY]	= "standby",
	[PM_SUSPEND_MEM]	= "mem",
};

static const struct platform_suspend_ops *suspend_ops;

/**
<<<<<<< HEAD
 * suspend_set_ops - Set the global suspend method table.
 * @ops: Suspend operations to use.
 */
void suspend_set_ops(const struct platform_suspend_ops *ops)
{
	lock_system_sleep();
	suspend_ops = ops;
	unlock_system_sleep();
}
EXPORT_SYMBOL_GPL(suspend_set_ops);
=======
 *	suspend_set_ops - Set the global suspend method table.
 *	@ops:	Pointer to ops structure.
 */
void suspend_set_ops(const struct platform_suspend_ops *ops)
{
	mutex_lock(&pm_mutex);
	suspend_ops = ops;
	mutex_unlock(&pm_mutex);
}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

bool valid_state(suspend_state_t state)
{
	/*
	 * All states need lowlevel support and need to be valid to the lowlevel
	 * implementation, no valid callback implies that none are valid.
	 */
	return suspend_ops && suspend_ops->valid && suspend_ops->valid(state);
}

/**
<<<<<<< HEAD
 * suspend_valid_only_mem - Generic memory-only valid callback.
 *
 * Platform drivers that implement mem suspend only and only need to check for
 * that in their .valid() callback can use this instead of rolling their own
 * .valid() callback.
=======
 * suspend_valid_only_mem - generic memory-only valid callback
 *
 * Platform drivers that implement mem suspend only and only need
 * to check for that in their .valid callback can use this instead
 * of rolling their own .valid callback.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 */
int suspend_valid_only_mem(suspend_state_t state)
{
	return state == PM_SUSPEND_MEM;
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(suspend_valid_only_mem);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

static int suspend_test(int level)
{
#ifdef CONFIG_PM_DEBUG
	if (pm_test_level == level) {
		printk(KERN_INFO "suspend debug: Waiting for 5 seconds.\n");
		mdelay(5000);
		return 1;
	}
#endif /* !CONFIG_PM_DEBUG */
	return 0;
}

/**
<<<<<<< HEAD
 * suspend_prepare - Prepare for entering system sleep state.
 *
 * Common code run for every system sleep state that can be entered (except for
 * hibernation).  Run suspend notifiers, allocate the "suspend" console and
 * freeze processes.
=======
 *	suspend_prepare - Do prep work before entering low-power state.
 *
 *	This is common code that is called for each state that we're entering.
 *	Run suspend notifiers, allocate a console and stop all processes.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 */
static int suspend_prepare(void)
{
	int error;

	if (!suspend_ops || !suspend_ops->enter)
		return -EPERM;

	pm_prepare_console();

	error = pm_notifier_call_chain(PM_SUSPEND_PREPARE);
	if (error)
		goto Finish;

<<<<<<< HEAD
=======
	error = usermodehelper_disable();
	if (error)
		goto Finish;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	error = suspend_freeze_processes();
	if (!error)
		return 0;

<<<<<<< HEAD
	suspend_stats.failed_freeze++;
	dpm_save_failed_step(SUSPEND_FREEZE);
=======
	suspend_thaw_processes();
	usermodehelper_enable();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 Finish:
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
	return error;
}

/* default implementation */
void __attribute__ ((weak)) arch_suspend_disable_irqs(void)
{
	local_irq_disable();
}

/* default implementation */
void __attribute__ ((weak)) arch_suspend_enable_irqs(void)
{
	local_irq_enable();
}

<<<<<<< HEAD
/**
 * suspend_enter - Make the system enter the given sleep state.
 * @state: System sleep state to enter.
 * @wakeup: Returns information that the sleep state should not be re-entered.
=======
#if !defined(CONFIG_CPU_EXYNOS4210)
#define CHECK_POINT printk(KERN_DEBUG "%s:%d\n", __func__, __LINE__)
#else
#define CHECK_POINT
#endif

/**
 * suspend_enter - enter the desired system sleep state.
 * @state: State to enter
 * @wakeup: Returns information that suspend should not be entered again.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 *
 * This function should be called after devices have been suspended.
 */
static int suspend_enter(suspend_state_t state, bool *wakeup)
{
	int error;

<<<<<<< HEAD
=======
	CHECK_POINT;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (suspend_ops->prepare) {
		error = suspend_ops->prepare();
		if (error)
			goto Platform_finish;
	}

<<<<<<< HEAD
	error = dpm_suspend_end(PMSG_SUSPEND);
=======
	CHECK_POINT;

	error = dpm_suspend_noirq(PMSG_SUSPEND);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to power down\n");
		goto Platform_finish;
	}

<<<<<<< HEAD
=======
	CHECK_POINT;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (suspend_ops->prepare_late) {
		error = suspend_ops->prepare_late();
		if (error)
			goto Platform_wake;
	}

	if (suspend_test(TEST_PLATFORM))
		goto Platform_wake;

	error = disable_nonboot_cpus();
	if (error || suspend_test(TEST_CPUS))
		goto Enable_cpus;

<<<<<<< HEAD
=======
	CHECK_POINT;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	arch_suspend_disable_irqs();
	BUG_ON(!irqs_disabled());

	error = syscore_suspend();
<<<<<<< HEAD
=======

	CHECK_POINT;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (!error) {
		*wakeup = pm_wakeup_pending();
		if (!(suspend_test(TEST_CORE) || *wakeup)) {
			error = suspend_ops->enter(state);
			events_check_enabled = false;
		}
		syscore_resume();
	}

	arch_suspend_enable_irqs();
	BUG_ON(irqs_disabled());

 Enable_cpus:
	enable_nonboot_cpus();

 Platform_wake:
	if (suspend_ops->wake)
		suspend_ops->wake();

<<<<<<< HEAD
	dpm_resume_start(PMSG_RESUME);
=======
	dpm_resume_noirq(PMSG_RESUME);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

 Platform_finish:
	if (suspend_ops->finish)
		suspend_ops->finish();

	return error;
}

/**
<<<<<<< HEAD
 * suspend_devices_and_enter - Suspend devices and enter system sleep state.
 * @state: System sleep state to enter.
=======
 *	suspend_devices_and_enter - suspend devices and enter the desired system
 *				    sleep state.
 *	@state:		  state to enter
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 */
int suspend_devices_and_enter(suspend_state_t state)
{
	int error;
	bool wakeup = false;

	if (!suspend_ops)
		return -ENOSYS;

	trace_machine_suspend(state);
	if (suspend_ops->begin) {
		error = suspend_ops->begin(state);
		if (error)
			goto Close;
	}
	suspend_console();
<<<<<<< HEAD
=======
	ftrace_stop();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	suspend_test_start();
	error = dpm_suspend_start(PMSG_SUSPEND);
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to suspend\n");
		goto Recover_platform;
	}
	suspend_test_finish("suspend devices");
	if (suspend_test(TEST_DEVICES))
		goto Recover_platform;

	do {
		error = suspend_enter(state, &wakeup);
	} while (!error && !wakeup
		&& suspend_ops->suspend_again && suspend_ops->suspend_again());

 Resume_devices:
	suspend_test_start();
	dpm_resume_end(PMSG_RESUME);
	suspend_test_finish("resume devices");
<<<<<<< HEAD
=======
	ftrace_start();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	resume_console();
 Close:
	if (suspend_ops->end)
		suspend_ops->end();
	trace_machine_suspend(PWR_EVENT_EXIT);
	return error;

 Recover_platform:
	if (suspend_ops->recover)
		suspend_ops->recover();
	goto Resume_devices;
}

/**
<<<<<<< HEAD
 * suspend_finish - Clean up before finishing the suspend sequence.
 *
 * Call platform code to clean up, restart processes, and free the console that
 * we've allocated. This routine is not called for hibernation.
=======
 *	suspend_finish - Do final work before exiting suspend sequence.
 *
 *	Call platform code to clean up, restart processes, and free the
 *	console that we've allocated. This is not called for suspend-to-disk.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 */
static void suspend_finish(void)
{
	suspend_thaw_processes();
<<<<<<< HEAD
=======
	usermodehelper_enable();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
}

<<<<<<< HEAD
/**
 * enter_state - Do common work needed to enter system sleep state.
 * @state: System sleep state to enter.
 *
 * Make sure that no one else is trying to put the system into a sleep state.
 * Fail if that's not the case.  Otherwise, prepare for system suspend, make the
 * system enter the given sleep state and clean up after wakeup.
 */
static int enter_state(suspend_state_t state)
{
	int error;
=======
#ifdef CONFIG_PM_WATCHDOG_TIMEOUT
void pm_wd_timeout(unsigned long data)
{
	struct pm_wd_data *wd_data = (void *)data;
	struct task_struct *tsk = wd_data->tsk;

	pr_emerg("%s: PM watchdog timeout: %d seconds\n",  __func__,
			wd_data->timeout);

	pr_emerg("stack:\n");
	show_stack(tsk, NULL);

	BUG();
}

void pm_wd_add_timer(struct timer_list *timer, struct pm_wd_data *data,
			int timeout)
{
	data->timeout = timeout;
	data->tsk = get_current();
	init_timer_on_stack(timer);
	timer->expires = jiffies + HZ * data->timeout;
	timer->function = pm_wd_timeout;
	timer->data = (unsigned long)data;
	add_timer(timer);
}

void pm_wd_del_timer(struct timer_list *timer)
{
	del_timer_sync(timer);
	destroy_timer_on_stack(timer);
}
#endif

/**
 *	enter_state - Do common work of entering low-power state.
 *	@state:		pm_state structure for state we're entering.
 *
 *	Make sure we're the only ones trying to enter a sleep state. Fail
 *	if someone has beat us to it, since we don't want anything weird to
 *	happen when we wake up.
 *	Then, do the setup for suspend, enter the state, and cleaup (after
 *	we've woken up).
 */
int enter_state(suspend_state_t state)
{
	int error;
	struct timer_list timer;
	struct pm_wd_data data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	if (!valid_state(state))
		return -ENODEV;

	if (!mutex_trylock(&pm_mutex))
		return -EBUSY;

	printk(KERN_INFO "PM: Syncing filesystems ... ");
	sys_sync();
	printk("done.\n");

	pr_debug("PM: Preparing system for %s sleep\n", pm_states[state]);
	error = suspend_prepare();
	if (error)
		goto Unlock;

	if (suspend_test(TEST_FREEZER))
		goto Finish;

	pr_debug("PM: Entering %s sleep\n", pm_states[state]);
	pm_restrict_gfp_mask();
	error = suspend_devices_and_enter(state);
	pm_restore_gfp_mask();

 Finish:
<<<<<<< HEAD
	pr_debug("PM: Finishing wakeup.\n");
	suspend_finish();
=======
	pm_wd_add_timer(&timer, &data, 15);

	pr_debug("PM: Finishing wakeup.\n");
	suspend_finish();

	pm_wd_del_timer(&timer);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 Unlock:
	mutex_unlock(&pm_mutex);
	return error;
}

<<<<<<< HEAD
static void pm_suspend_marker(char *annotation)
{
	struct timespec ts;
	struct rtc_time tm;

	getnstimeofday(&ts);
	rtc_time_to_tm(ts.tv_sec, &tm);
	pr_info("PM: suspend %s %d-%02d-%02d %02d:%02d:%02d.%09lu UTC\n",
		annotation, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec);
}

/**
 * pm_suspend - Externally visible function for suspending the system.
 * @state: System sleep state to enter.
 *
 * Check if the value of @state represents one of the supported states,
 * execute enter_state() and update system suspend statistics.
 */
int pm_suspend(suspend_state_t state)
{
	int error;

	if (state <= PM_SUSPEND_ON || state >= PM_SUSPEND_MAX)
		return -EINVAL;

	pm_suspend_marker("entry");
	error = enter_state(state);
	if (error) {
		suspend_stats.fail++;
		dpm_save_failed_errno(error);
	} else {
		suspend_stats.success++;
	}
	pm_suspend_marker("exit");
	return error;
=======
/**
 *	pm_suspend - Externally visible function for suspending system.
 *	@state:		Enumerated value of state to enter.
 *
 *	Determine whether or not value is within range, get state
 *	structure, and enter (above).
 */
int pm_suspend(suspend_state_t state)
{
	if (state > PM_SUSPEND_ON && state < PM_SUSPEND_MAX)
		return enter_state(state);
	return -EINVAL;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}
EXPORT_SYMBOL(pm_suspend);
