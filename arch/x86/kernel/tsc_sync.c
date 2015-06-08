/*
 * check TSC synchronization.
 *
 * Copyright (C) 2006, Red Hat, Inc., Ingo Molnar
 *
 * We check whether all boot CPUs have their TSC's synchronized,
 * print a warning if not and turn off the TSC clock-source.
 *
 * The warp-check is point-to-point between two CPUs, the CPU
 * initiating the bootup is the 'source CPU', the freshly booting
 * CPU is the 'target CPU'.
 *
 * Only two CPUs may participate - they can enter in any order.
 * ( The serial nature of the boot logic and the CPU hotplug lock
 *   protects against more than 2 CPUs entering this code. )
 */
#include <linux/spinlock.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/nmi.h>
#include <asm/tsc.h>

/*
 * Entry/exit counters that make sure that both CPUs
 * run the measurement code at once:
 */
static __cpuinitdata atomic_t start_count;
static __cpuinitdata atomic_t stop_count;

/*
 * We use a raw spinlock in this exceptional case, because
 * we want to have the fastest, inlined, non-debug version
 * of a critical section, to be able to prove TSC time-warps:
 */
static __cpuinitdata arch_spinlock_t sync_lock = __ARCH_SPIN_LOCK_UNLOCKED;

static __cpuinitdata cycles_t last_tsc;
static __cpuinitdata cycles_t max_warp;
static __cpuinitdata int nr_warps;

/*
 * TSC-warp measurement loop running on both CPUs:
 */
<<<<<<< HEAD
static __cpuinit void check_tsc_warp(unsigned int timeout)
=======
<<<<<<< HEAD
static __cpuinit void check_tsc_warp(unsigned int timeout)
=======
static __cpuinit void check_tsc_warp(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	cycles_t start, now, prev, end;
	int i;

	rdtsc_barrier();
	start = get_cycles();
	rdtsc_barrier();
	/*
<<<<<<< HEAD
	 * The measurement runs for 'timeout' msecs:
	 */
	end = start + (cycles_t) tsc_khz * timeout;
=======
<<<<<<< HEAD
	 * The measurement runs for 'timeout' msecs:
	 */
	end = start + (cycles_t) tsc_khz * timeout;
=======
	 * The measurement runs for 20 msecs:
	 */
	end = start + tsc_khz * 20ULL;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	now = start;

	for (i = 0; ; i++) {
		/*
		 * We take the global lock, measure TSC, save the
		 * previous TSC that was measured (possibly on
		 * another CPU) and update the previous TSC timestamp.
		 */
		arch_spin_lock(&sync_lock);
		prev = last_tsc;
		rdtsc_barrier();
		now = get_cycles();
		rdtsc_barrier();
		last_tsc = now;
		arch_spin_unlock(&sync_lock);

		/*
		 * Be nice every now and then (and also check whether
		 * measurement is done [we also insert a 10 million
		 * loops safety exit, so we dont lock up in case the
		 * TSC readout is totally broken]):
		 */
		if (unlikely(!(i & 7))) {
			if (now > end || i > 10000000)
				break;
			cpu_relax();
			touch_nmi_watchdog();
		}
		/*
		 * Outside the critical section we can now see whether
		 * we saw a time-warp of the TSC going backwards:
		 */
		if (unlikely(prev > now)) {
			arch_spin_lock(&sync_lock);
			max_warp = max(max_warp, prev - now);
			nr_warps++;
			arch_spin_unlock(&sync_lock);
		}
	}
	WARN(!(now-start),
		"Warning: zero tsc calibration delta: %Ld [max: %Ld]\n",
			now-start, end-start);
}

/*
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * If the target CPU coming online doesn't have any of its core-siblings
 * online, a timeout of 20msec will be used for the TSC-warp measurement
 * loop. Otherwise a smaller timeout of 2msec will be used, as we have some
 * information about this socket already (and this information grows as we
 * have more and more logical-siblings in that socket).
 *
 * Ideally we should be able to skip the TSC sync check on the other
 * core-siblings, if the first logical CPU in a socket passed the sync test.
 * But as the TSC is per-logical CPU and can potentially be modified wrongly
 * by the bios, TSC sync test for smaller duration should be able
 * to catch such errors. Also this will catch the condition where all the
 * cores in the socket doesn't get reset at the same time.
 */
static inline unsigned int loop_timeout(int cpu)
{
	return (cpumask_weight(cpu_core_mask(cpu)) > 1) ? 2 : 20;
}

/*
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Source CPU calls into this - it waits for the freshly booted
 * target CPU to arrive and then starts the measurement:
 */
void __cpuinit check_tsc_sync_source(int cpu)
{
	int cpus = 2;

	/*
	 * No need to check if we already know that the TSC is not
	 * synchronized:
	 */
	if (unsynchronized_tsc())
		return;

<<<<<<< HEAD
	if (tsc_clocksource_reliable) {
=======
<<<<<<< HEAD
	if (tsc_clocksource_reliable) {
=======
	if (boot_cpu_has(X86_FEATURE_TSC_RELIABLE)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (cpu == (nr_cpu_ids-1) || system_state != SYSTEM_BOOTING)
			pr_info(
			"Skipped synchronization checks as TSC is reliable.\n");
		return;
	}

	/*
	 * Reset it - in case this is a second bootup:
	 */
	atomic_set(&stop_count, 0);

	/*
	 * Wait for the target to arrive:
	 */
	while (atomic_read(&start_count) != cpus-1)
		cpu_relax();
	/*
	 * Trigger the target to continue into the measurement too:
	 */
	atomic_inc(&start_count);

<<<<<<< HEAD
	check_tsc_warp(loop_timeout(cpu));
=======
<<<<<<< HEAD
	check_tsc_warp(loop_timeout(cpu));
=======
	check_tsc_warp();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	while (atomic_read(&stop_count) != cpus-1)
		cpu_relax();

	if (nr_warps) {
		pr_warning("TSC synchronization [CPU#%d -> CPU#%d]:\n",
			smp_processor_id(), cpu);
		pr_warning("Measured %Ld cycles TSC warp between CPUs, "
			   "turning off TSC clock.\n", max_warp);
		mark_tsc_unstable("check_tsc_sync_source failed");
	} else {
		pr_debug("TSC synchronization [CPU#%d -> CPU#%d]: passed\n",
			smp_processor_id(), cpu);
	}

	/*
	 * Reset it - just in case we boot another CPU later:
	 */
	atomic_set(&start_count, 0);
	nr_warps = 0;
	max_warp = 0;
	last_tsc = 0;

	/*
	 * Let the target continue with the bootup:
	 */
	atomic_inc(&stop_count);
}

/*
 * Freshly booted CPUs call into this:
 */
void __cpuinit check_tsc_sync_target(void)
{
	int cpus = 2;

<<<<<<< HEAD
	if (unsynchronized_tsc() || tsc_clocksource_reliable)
=======
<<<<<<< HEAD
	if (unsynchronized_tsc() || tsc_clocksource_reliable)
=======
	if (unsynchronized_tsc() || boot_cpu_has(X86_FEATURE_TSC_RELIABLE))
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return;

	/*
	 * Register this CPU's participation and wait for the
	 * source CPU to start the measurement:
	 */
	atomic_inc(&start_count);
	while (atomic_read(&start_count) != cpus)
		cpu_relax();

<<<<<<< HEAD
	check_tsc_warp(loop_timeout(smp_processor_id()));
=======
<<<<<<< HEAD
	check_tsc_warp(loop_timeout(smp_processor_id()));
=======
	check_tsc_warp();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * Ok, we are done:
	 */
	atomic_inc(&stop_count);

	/*
	 * Wait for the source CPU to print stuff:
	 */
	while (atomic_read(&stop_count) != cpus)
		cpu_relax();
}
