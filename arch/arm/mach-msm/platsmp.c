/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
<<<<<<< HEAD
 *  Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
=======
<<<<<<< HEAD
 *  Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
=======
 *  Copyright (c) 2010, Code Aurora Forum. All rights reserved.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cpumask.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/regulator/krait-regulator.h>

#include <asm/hardware/gic.h>
#include <asm/cacheflush.h>
#include <asm/cputype.h>
#include <asm/mach-types.h>
#include <asm/smp_plat.h>

#include <mach/socinfo.h>
#include <mach/hardware.h>
#include <mach/msm_iomap.h>

#include "pm.h"
#include "platsmp.h"
#include "scm-boot.h"
#include "spm.h"
<<<<<<< HEAD
=======
=======
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/jiffies.h>
#include <linux/smp.h>
#include <linux/io.h>

#include <asm/hardware/gic.h>
#include <asm/cacheflush.h>
#include <asm/mach-types.h>

#include <mach/msm_iomap.h>

#include "scm-boot.h"
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define VDD_SC1_ARRAY_CLAMP_GFS_CTL 0x15A0
#define SCSS_CPU1CORE_RESET 0xD80
#define SCSS_DBG_STATUS_CORE_PWRDUP 0xE64

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
/* Mask for edge trigger PPIs except AVS_SVICINT and AVS_SVICINTSWDONE */
#define GIC_PPI_EDGE_MASK 0xFFFFD7FF

extern void msm_secondary_startup(void);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * control for which core is the next to come out of the secondary
 * boot "holding pen".
 */
volatile int pen_release = -1;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Write pen_release in a way that is guaranteed to be visible to all
 * observers, irrespective of whether they're taking part in coherency
 * or not.  This is necessary for the hotplug code to work reliably.
 */
void __cpuinit write_pen_release(int val)
{
	pen_release = val;
	smp_wmb();
	__cpuc_flush_dcache_area((void *)&pen_release, sizeof(pen_release));
	outer_clean_range(__pa(&pen_release), __pa(&pen_release + 1));
}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static DEFINE_SPINLOCK(boot_lock);

void __cpuinit platform_secondary_init(unsigned int cpu)
{
<<<<<<< HEAD
	WARN_ON(msm_platform_secondary_init(cpu));
=======
<<<<<<< HEAD
	WARN_ON(msm_platform_secondary_init(cpu));
=======
	/* Configure edge-triggered PPIs */
	writel(GIC_PPI_EDGE_MASK, MSM_QGIC_DIST_BASE + GIC_DIST_CONFIG + 4);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * if any interrupts are already enabled for the primary
	 * core (e.g. timer irq), then they will not have been enabled
	 * for us: do so
	 */
	gic_secondary_init(0);

	/*
	 * let the primary processor know we're out of the
	 * pen, then head off into the C entry point
	 */
<<<<<<< HEAD
	write_pen_release(-1);
=======
<<<<<<< HEAD
	write_pen_release(-1);
=======
	pen_release = -1;
	smp_wmb();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * Synchronise with the boot thread.
	 */
	spin_lock(&boot_lock);
	spin_unlock(&boot_lock);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __cpuinit release_secondary_sim(unsigned long base, unsigned int cpu)
{
	void *base_ptr = ioremap_nocache(base + (cpu * 0x10000), SZ_4K);
	if (!base_ptr)
		return -ENODEV;

	writel_relaxed(0x800, base_ptr+0x04);
	writel_relaxed(0x3FFF, base_ptr+0x14);

	mb();
	iounmap(base_ptr);
	return 0;
}

static int __cpuinit scorpion_release_secondary(void)
{
	void *base_ptr = ioremap_nocache(0x00902000, SZ_4K*2);
	if (!base_ptr)
		return -EINVAL;

	writel_relaxed(0, base_ptr + VDD_SC1_ARRAY_CLAMP_GFS_CTL);
	dmb();
	writel_relaxed(0, base_ptr + SCSS_CPU1CORE_RESET);
	writel_relaxed(3, base_ptr + SCSS_DBG_STATUS_CORE_PWRDUP);
	mb();
	iounmap(base_ptr);

	return 0;
}

static int __cpuinit msm8960_release_secondary(unsigned long base,
						unsigned int cpu)
{
	void *base_ptr = ioremap_nocache(base + (cpu * 0x10000), SZ_4K);
	if (!base_ptr)
		return -ENODEV;

	msm_spm_turn_on_cpu_rail(cpu);

	writel_relaxed(0x109, base_ptr+0x04);
	writel_relaxed(0x101, base_ptr+0x04);
	mb();
	ndelay(300);

	writel_relaxed(0x121, base_ptr+0x04);
	mb();
	udelay(2);

	writel_relaxed(0x120, base_ptr+0x04);
	mb();
	udelay(2);

	writel_relaxed(0x100, base_ptr+0x04);
	mb();
	udelay(100);

	writel_relaxed(0x180, base_ptr+0x04);
	mb();
	iounmap(base_ptr);
	return 0;
}

static int __cpuinit msm8974_release_secondary(unsigned long base,
						unsigned int cpu)
{
	void *base_ptr = ioremap_nocache(base + (cpu * 0x10000), SZ_4K);

	if (!base_ptr)
		return -ENODEV;

	secondary_cpu_hs_init(base_ptr, cpu);

	writel_relaxed(0x021, base_ptr+0x04);
	mb();
	udelay(2);

	writel_relaxed(0x020, base_ptr+0x04);
	mb();
	udelay(2);

	writel_relaxed(0x000, base_ptr+0x04);
	mb();

	writel_relaxed(0x080, base_ptr+0x04);
	mb();
	iounmap(base_ptr);
	return 0;
}

static int __cpuinit arm_release_secondary(unsigned long base, unsigned int cpu)
{
	void *base_ptr = ioremap_nocache(base + (cpu * 0x10000), SZ_4K);
	if (!base_ptr)
		return -ENODEV;

	writel_relaxed(0x00000033, base_ptr+0x04);
	mb();

	writel_relaxed(0x10000001, base_ptr+0x14);
	mb();
	udelay(2);

	writel_relaxed(0x00000031, base_ptr+0x04);
	mb();

	writel_relaxed(0x00000039, base_ptr+0x04);
	mb();
	udelay(2);

	writel_relaxed(0x00020038, base_ptr+0x04);
	mb();
	udelay(2);


	writel_relaxed(0x00020008, base_ptr+0x04);
	mb();

	writel_relaxed(0x00020088, base_ptr+0x04);
	mb();

	iounmap(base_ptr);
	return 0;
}

static int __cpuinit release_from_pen(unsigned int cpu)
{
	unsigned long timeout;

	/* Set preset_lpj to avoid subsequent lpj recalculations */
	preset_lpj = loops_per_jiffy;
<<<<<<< HEAD
=======
=======
static __cpuinit void prepare_cold_cpu(unsigned int cpu)
{
	int ret;
	ret = scm_set_boot_addr(virt_to_phys(msm_secondary_startup),
				SCM_FLAG_COLDBOOT_CPU1);
	if (ret == 0) {
		void *sc1_base_ptr;
		sc1_base_ptr = ioremap_nocache(0x00902000, SZ_4K*2);
		if (sc1_base_ptr) {
			writel(0, sc1_base_ptr + VDD_SC1_ARRAY_CLAMP_GFS_CTL);
			writel(0, sc1_base_ptr + SCSS_CPU1CORE_RESET);
			writel(3, sc1_base_ptr + SCSS_DBG_STATUS_CORE_PWRDUP);
			iounmap(sc1_base_ptr);
		}
	} else
		printk(KERN_DEBUG "Failed to set secondary core boot "
				  "address\n");
}

int __cpuinit boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;
	static int cold_boot_done;

	/* Only need to bring cpu out of reset this way once */
	if (cold_boot_done == false) {
		prepare_cold_cpu(cpu);
		cold_boot_done = true;
	}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * set synchronisation state between this boot processor
	 * and the secondary one
	 */
	spin_lock(&boot_lock);

	/*
	 * The secondary processor is waiting to be released from
	 * the holding pen - release it, then wait for it to flag
	 * that it has been released by resetting pen_release.
	 *
	 * Note that "pen_release" is the hardware CPU ID, whereas
	 * "cpu" is Linux's internal ID.
	 */
<<<<<<< HEAD
	write_pen_release(cpu_logical_map(cpu));
=======
<<<<<<< HEAD
	write_pen_release(cpu_logical_map(cpu));
=======
	pen_release = cpu;
	__cpuc_flush_dcache_area((void *)&pen_release, sizeof(pen_release));
	outer_clean_range(__pa(&pen_release), __pa(&pen_release + 1));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * Send the secondary CPU a soft interrupt, thereby causing
	 * the boot monitor to read the system wide flags register,
	 * and branch to the address found there.
	 */
	gic_raise_softirq(cpumask_of(cpu), 1);

	timeout = jiffies + (1 * HZ);
	while (time_before(jiffies, timeout)) {
		smp_rmb();
		if (pen_release == -1)
			break;

		udelay(10);
	}

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then wait for it to finish
	 */
	spin_unlock(&boot_lock);

	return pen_release != -1 ? -ENOSYS : 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
DEFINE_PER_CPU(int, cold_boot_done);

int __cpuinit scorpion_boot_secondary(unsigned int cpu,
				      struct task_struct *idle)
{
	pr_debug("Starting secondary CPU %d\n", cpu);

	if (per_cpu(cold_boot_done, cpu) == false) {
		scorpion_release_secondary();
		per_cpu(cold_boot_done, cpu) = true;
	}
	return release_from_pen(cpu);
}

int __cpuinit msm8960_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	pr_debug("Starting secondary CPU %d\n", cpu);

	if (per_cpu(cold_boot_done, cpu) == false) {
		msm8960_release_secondary(0x02088000, cpu);
		per_cpu(cold_boot_done, cpu) = true;
	}
	return release_from_pen(cpu);
}

int __cpuinit msm8974_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	pr_debug("Starting secondary CPU %d\n", cpu);

	if (per_cpu(cold_boot_done, cpu) == false) {
		if (of_board_is_sim())
			release_secondary_sim(0xf9088000, cpu);
		else if (!of_board_is_rumi())
			msm8974_release_secondary(0xf9088000, cpu);

		per_cpu(cold_boot_done, cpu) = true;
	}
	return release_from_pen(cpu);
}

int __cpuinit arm_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	pr_debug("Starting secondary CPU %d\n", cpu);

	if (per_cpu(cold_boot_done, cpu) == false) {
		if (of_board_is_sim())
			release_secondary_sim(0xf9088000, cpu);
		else if (!of_board_is_rumi())
			arm_release_secondary(0xf9088000, cpu);

		per_cpu(cold_boot_done, cpu) = true;
	}
	return release_from_pen(cpu);
}

/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the system.
 */
static void __init msm_smp_init_cpus(void)
{
	unsigned int i, ncores = get_core_count();

	if (ncores > nr_cpu_ids) {
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
			ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
	}

	for (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);

	set_smp_cross_call(gic_raise_softirq);
}

static void __init arm_smp_init_cpus(void)
{
	unsigned int i, ncores;

	ncores = (__raw_readl(MSM_APCS_GCC_BASE + 0x30)) & 0xF;

	if (ncores > nr_cpu_ids) {
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
			ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
	}

	for (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);

	set_smp_cross_call(gic_raise_softirq);
}

static int cold_boot_flags[] __initdata = {
	0,
	SCM_FLAG_COLDBOOT_CPU1,
	SCM_FLAG_COLDBOOT_CPU2,
	SCM_FLAG_COLDBOOT_CPU3,
};

static void __init msm_platform_smp_prepare_cpus(unsigned int max_cpus)
{
	int cpu, map;
	unsigned int flags = 0;

	for_each_present_cpu(cpu) {
		map = cpu_logical_map(cpu);
		if (map > ARRAY_SIZE(cold_boot_flags)) {
			set_cpu_present(cpu, false);
			__WARN();
			continue;
		}
		flags |= cold_boot_flags[map];
	}

	if (scm_set_boot_addr(virt_to_phys(msm_secondary_startup), flags))
		pr_warn("Failed to set CPU boot address\n");
}

struct smp_operations arm_smp_ops __initdata = {
	.smp_init_cpus = arm_smp_init_cpus,
	.smp_prepare_cpus = msm_platform_smp_prepare_cpus,
	.smp_secondary_init = platform_secondary_init,
	.smp_boot_secondary = arm_boot_secondary,
	.cpu_kill = platform_cpu_kill,
	.cpu_die = platform_cpu_die,
	.cpu_disable = platform_cpu_disable
};

struct smp_operations msm8974_smp_ops __initdata = {
	.smp_init_cpus = msm_smp_init_cpus,
	.smp_prepare_cpus = msm_platform_smp_prepare_cpus,
	.smp_secondary_init = platform_secondary_init,
	.smp_boot_secondary = msm8974_boot_secondary,
	.cpu_kill = platform_cpu_kill,
	.cpu_die = platform_cpu_die,
	.cpu_disable = platform_cpu_disable
};

struct smp_operations msm8960_smp_ops __initdata = {
	.smp_init_cpus = msm_smp_init_cpus,
	.smp_prepare_cpus = msm_platform_smp_prepare_cpus,
	.smp_secondary_init = platform_secondary_init,
	.smp_boot_secondary = msm8960_boot_secondary,
	.cpu_kill = platform_cpu_kill,
	.cpu_die = platform_cpu_die,
	.cpu_disable = platform_cpu_disable
};

struct smp_operations scorpion_smp_ops __initdata = {
	.smp_init_cpus = msm_smp_init_cpus,
	.smp_prepare_cpus = msm_platform_smp_prepare_cpus,
	.smp_secondary_init = platform_secondary_init,
	.smp_boot_secondary = scorpion_boot_secondary,
	.cpu_kill = platform_cpu_kill,
	.cpu_die = platform_cpu_die,
	.cpu_disable = platform_cpu_disable
};
<<<<<<< HEAD
=======
=======
/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the system. The msm8x60
 * does not support the ARM SCU, so just set the possible cpu mask to
 * NR_CPUS.
 */
void __init smp_init_cpus(void)
{
	unsigned int i;

	for (i = 0; i < NR_CPUS; i++)
		set_cpu_possible(i, true);

        set_smp_cross_call(gic_raise_softirq);
}

void __init platform_smp_prepare_cpus(unsigned int max_cpus)
{
	int i;

	/*
	 * Initialise the present map, which describes the set of CPUs
	 * actually populated at the present time.
	 */
	for (i = 0; i < max_cpus; i++)
		set_cpu_present(i, true);
}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
