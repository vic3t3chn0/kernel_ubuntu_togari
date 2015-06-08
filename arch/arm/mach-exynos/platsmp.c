<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/platsmp.c
=======
<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/platsmp.c
=======
/* linux/arch/arm/mach-exynos/platsmp.c
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Cloned from linux/arch/arm/mach-vexpress/platsmp.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/jiffies.h>
#include <linux/smp.h>
#include <linux/io.h>

#include <asm/cacheflush.h>
#include <asm/hardware/gic.h>
<<<<<<< HEAD
#include <asm/smp_plat.h>
#include <asm/smp_scu.h>
=======
<<<<<<< HEAD
#include <asm/smp_plat.h>
#include <asm/smp_scu.h>
=======
#include <asm/smp_scu.h>
#include <asm/unified.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <mach/hardware.h>
#include <mach/regs-clock.h>
#include <mach/regs-pmu.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <plat/cpu.h>

extern void exynos4_secondary_startup(void);

#define CPU1_BOOT_REG		(samsung_rev() == EXYNOS4210_REV_1_1 ? \
				S5P_INFORM5 : S5P_VA_SYSRAM)
<<<<<<< HEAD
=======
=======
#include <mach/smc.h>

#include <plat/cpu.h>
#include <plat/exynos4.h>
#ifdef CONFIG_SEC_WATCHDOG_RESET
#include <plat/regs-watchdog.h>
#endif

extern void exynos_secondary_startup(void);
extern unsigned int gic_bank_offset;

struct _cpu_boot_info {
	void __iomem *power_base;
	void __iomem *boot_base;
};

struct _cpu_boot_info cpu_boot_info[NR_CPUS];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * control for which core is the next to come out of the secondary
 * boot "holding pen"
 */
<<<<<<< HEAD

volatile int __cpuinitdata pen_release = -1;
=======
<<<<<<< HEAD

volatile int __cpuinitdata pen_release = -1;
=======
volatile int pen_release = -1;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * Write pen_release in a way that is guaranteed to be visible to all
 * observers, irrespective of whether they're taking part in coherency
 * or not.  This is necessary for the hotplug code to work reliably.
 */
static void write_pen_release(int val)
{
	pen_release = val;
	smp_wmb();
	__cpuc_flush_dcache_area((void *)&pen_release, sizeof(pen_release));
	outer_clean_range(__pa(&pen_release), __pa(&pen_release + 1));
}

static void __iomem *scu_base_addr(void)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	if (soc_is_exynos5210() || soc_is_exynos5250())
		return 0;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return (void __iomem *)(S5P_VA_SCU);
}

static DEFINE_SPINLOCK(boot_lock);

void __cpuinit platform_secondary_init(unsigned int cpu)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	void __iomem *dist_base = S5P_VA_GIC_DIST +
				 (gic_bank_offset * cpu);
	void __iomem *cpu_base = S5P_VA_GIC_CPU +
				(gic_bank_offset * cpu);

	/* Enable the full line of zero */
	if (soc_is_exynos4210() || soc_is_exynos4212() || soc_is_exynos4412())
		enable_cache_foz();

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * if any interrupts are already enabled for the primary
	 * core (e.g. timer irq), then they will not have been enabled
	 * for us: do so
	 */
<<<<<<< HEAD
	gic_secondary_init(0);
=======
<<<<<<< HEAD
	gic_secondary_init(0);
=======
	gic_secondary_init_base(0, dist_base, cpu_base);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * let the primary processor know we're out of the
	 * pen, then head off into the C entry point
	 */
	write_pen_release(-1);

	/*
	 * Synchronise with the boot thread.
	 */
	spin_lock(&boot_lock);
	spin_unlock(&boot_lock);
}

<<<<<<< HEAD
int __cpuinit boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;
=======
<<<<<<< HEAD
int __cpuinit boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;
=======
static int exynos_power_up_cpu(unsigned int cpu)
{
	unsigned int timeout;
	unsigned int val;
	void __iomem *power_base = cpu_boot_info[cpu].power_base;

	val = __raw_readl(power_base);
	if (!(val & S5P_CORE_LOCAL_PWR_EN)) {
		__raw_writel(S5P_CORE_LOCAL_PWR_EN, power_base);

		/* wait max 10 ms until cpu is on */
		timeout = 10;
		while (timeout) {
			val = __raw_readl(power_base + 0x4);

			if ((val & S5P_CORE_LOCAL_PWR_EN) == S5P_CORE_LOCAL_PWR_EN)
				break;

			mdelay(1);
			timeout--;
		}

		if (timeout == 0) {
			printk(KERN_ERR "cpu%d power up failed", cpu);
			return -ETIMEDOUT;
		}
	}

	return 0;
}

int __cpuinit boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned long timeout;
	int ret;
#ifdef CONFIG_SEC_WATCHDOG_RESET
	unsigned int tmp_wtcon;
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * Set synchronisation state between this boot processor
	 * and the secondary one
	 */
	spin_lock(&boot_lock);

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#ifdef CONFIG_SEC_WATCHDOG_RESET
	tmp_wtcon = __raw_readl(S3C2410_WTCON);
#endif

	ret = exynos_power_up_cpu(cpu);
	if (ret) {
		spin_unlock(&boot_lock);
		return ret;
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * The secondary processor is waiting to be released from
	 * the holding pen - release it, then wait for it to flag
	 * that it has been released by resetting pen_release.
	 *
	 * Note that "pen_release" is the hardware CPU ID, whereas
	 * "cpu" is Linux's internal ID.
	 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	write_pen_release(cpu_logical_map(cpu));

	if (!(__raw_readl(S5P_ARM_CORE1_STATUS) & S5P_CORE_LOCAL_PWR_EN)) {
		__raw_writel(S5P_CORE_LOCAL_PWR_EN,
			     S5P_ARM_CORE1_CONFIGURATION);

		timeout = 10;

		/* wait max 10 ms until cpu1 is on */
		while ((__raw_readl(S5P_ARM_CORE1_STATUS)
			& S5P_CORE_LOCAL_PWR_EN) != S5P_CORE_LOCAL_PWR_EN) {
			if (timeout-- == 0)
				break;

			mdelay(1);
		}

		if (timeout == 0) {
			printk(KERN_ERR "cpu1 power enable failed");
			spin_unlock(&boot_lock);
			return -ETIMEDOUT;
		}
	}
<<<<<<< HEAD
=======
=======
	write_pen_release(cpu);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * Send the secondary CPU a soft interrupt, thereby causing
	 * the boot monitor to read the system wide flags register,
	 * and branch to the address found there.
	 */
<<<<<<< HEAD

=======
<<<<<<< HEAD

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	timeout = jiffies + (1 * HZ);
	while (time_before(jiffies, timeout)) {
		smp_rmb();

<<<<<<< HEAD
		__raw_writel(virt_to_phys(exynos4_secondary_startup),
			CPU1_BOOT_REG);
		gic_raise_softirq(cpumask_of(cpu), 1);
=======
<<<<<<< HEAD
		__raw_writel(virt_to_phys(exynos4_secondary_startup),
			CPU1_BOOT_REG);
		gic_raise_softirq(cpumask_of(cpu), 1);
=======
		__raw_writel(BSYM(virt_to_phys(exynos_secondary_startup)),
			cpu_boot_info[cpu].boot_base);

#ifdef CONFIG_ARM_TRUSTZONE
		if (soc_is_exynos4412())
			exynos_smc(SMC_CMD_CPU1BOOT, cpu, 0, 0);
		else
			exynos_smc(SMC_CMD_CPU1BOOT, 0, 0, 0);
#endif
		smp_send_reschedule(cpu);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (pen_release == -1)
			break;

		udelay(10);
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#ifdef CONFIG_SEC_WATCHDOG_RESET
	__raw_writel(tmp_wtcon, S3C2410_WTCON);
#endif

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
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
=======
static inline unsigned long exynos5_get_core_count(void)
{
	u32 val;

	/* Read L2 control register */
	asm volatile("mrc p15, 1, %0, c9, c0, 2" : "=r"(val));

	/* core count : [25:24] of L2 control register + 1 */
	val = ((val >> 24) & 3) + 1;

	return val;
}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the system.
 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void __init smp_init_cpus(void)
{
	void __iomem *scu_base = scu_base_addr();
	unsigned int i, ncores;

	if (soc_is_exynos5250())
		ncores = 2;
	else
		ncores = scu_base ? scu_get_core_count(scu_base) : 1;

	/* sanity check */
	if (ncores > nr_cpu_ids) {
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
			ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
<<<<<<< HEAD
=======
=======
void __init smp_init_cpus(void)
{
	unsigned int i, ncores;

	void __iomem *scu_base = scu_base_addr();

	ncores = scu_base ? scu_get_core_count(scu_base) :
			    exynos5_get_core_count();

	/* sanity check */
	if (ncores > NR_CPUS) {
		printk(KERN_WARNING
		       "EXYNOS: no. of cores (%d) greater than configured "
		       "maximum of %d - clipping\n",
		       ncores, NR_CPUS);
		ncores = NR_CPUS;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	for (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);

	set_smp_cross_call(gic_raise_softirq);
}

void __init platform_smp_prepare_cpus(unsigned int max_cpus)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!soc_is_exynos5250())
		scu_enable(scu_base_addr());

	/*
	 * Write the address of secondary startup into the
	 * system-wide flags register. The boot monitor waits
	 * until it receives a soft interrupt, and then the
	 * secondary CPU branches to this address.
	 */
	__raw_writel(virt_to_phys(exynos4_secondary_startup),
			CPU1_BOOT_REG);
<<<<<<< HEAD
=======
=======
	int i;

	/*
	 * Initialise the present map, which describes the set of CPUs
	 * actually populated at the present time.
	 */
	for (i = 0; i < max_cpus; i++)
		set_cpu_present(i, true);

	if (scu_base_addr())
		scu_enable(scu_base_addr());
	else
		flush_cache_all();

	/* Set up secondary boot base and core power cofiguration base address */
	for (i = 1; i < max_cpus; i++) {
#ifdef CONFIG_ARM_TRUSTZONE
		cpu_boot_info[i].boot_base = S5P_VA_SYSRAM_NS + 0x1C;
#else
		if (soc_is_exynos4210() && (samsung_rev() >= EXYNOS4210_REV_1_1))
			cpu_boot_info[i].boot_base = S5P_INFORM5;
		else
			cpu_boot_info[i].boot_base = S5P_VA_SYSRAM;
#endif
		if (soc_is_exynos4412())
			cpu_boot_info[i].boot_base += (0x4 * i);
		cpu_boot_info[i].power_base = S5P_ARM_CORE_CONFIGURATION(i);
	}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
