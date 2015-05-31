/* sysfs.c: Toplogy sysfs support code for sparc64.
 *
 * Copyright (C) 2007 David S. Miller <davem@davemloft.net>
 */
#include <linux/sched.h>
<<<<<<< HEAD
#include <linux/device.h>
=======
#include <linux/sysdev.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#include <linux/cpu.h>
#include <linux/smp.h>
#include <linux/percpu.h>
#include <linux/init.h>

#include <asm/cpudata.h>
#include <asm/hypervisor.h>
#include <asm/spitfire.h>

static DEFINE_PER_CPU(struct hv_mmu_statistics, mmu_stats) __attribute__((aligned(64)));

#define SHOW_MMUSTAT_ULONG(NAME) \
<<<<<<< HEAD
static ssize_t show_##NAME(struct device *dev, \
			struct device_attribute *attr, char *buf) \
=======
static ssize_t show_##NAME(struct sys_device *dev, \
			struct sysdev_attribute *attr, char *buf) \
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{ \
	struct hv_mmu_statistics *p = &per_cpu(mmu_stats, dev->id); \
	return sprintf(buf, "%lu\n", p->NAME); \
} \
<<<<<<< HEAD
static DEVICE_ATTR(NAME, 0444, show_##NAME, NULL)
=======
static SYSDEV_ATTR(NAME, 0444, show_##NAME, NULL)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_256mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_256mb_tte);

static struct attribute *mmu_stat_attrs[] = {
<<<<<<< HEAD
	&dev_attr_immu_tsb_hits_ctx0_8k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_8k_tte.attr,
	&dev_attr_immu_tsb_hits_ctx0_64k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_64k_tte.attr,
	&dev_attr_immu_tsb_hits_ctx0_4mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_4mb_tte.attr,
	&dev_attr_immu_tsb_hits_ctx0_256mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_256mb_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_8k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_8k_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_64k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_64k_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_4mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_4mb_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_256mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_8k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_8k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_64k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_64k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_8k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_8k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_64k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_64k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_256mb_tte.attr,
=======
	&attr_immu_tsb_hits_ctx0_8k_tte.attr,
	&attr_immu_tsb_ticks_ctx0_8k_tte.attr,
	&attr_immu_tsb_hits_ctx0_64k_tte.attr,
	&attr_immu_tsb_ticks_ctx0_64k_tte.attr,
	&attr_immu_tsb_hits_ctx0_4mb_tte.attr,
	&attr_immu_tsb_ticks_ctx0_4mb_tte.attr,
	&attr_immu_tsb_hits_ctx0_256mb_tte.attr,
	&attr_immu_tsb_ticks_ctx0_256mb_tte.attr,
	&attr_immu_tsb_hits_ctxnon0_8k_tte.attr,
	&attr_immu_tsb_ticks_ctxnon0_8k_tte.attr,
	&attr_immu_tsb_hits_ctxnon0_64k_tte.attr,
	&attr_immu_tsb_ticks_ctxnon0_64k_tte.attr,
	&attr_immu_tsb_hits_ctxnon0_4mb_tte.attr,
	&attr_immu_tsb_ticks_ctxnon0_4mb_tte.attr,
	&attr_immu_tsb_hits_ctxnon0_256mb_tte.attr,
	&attr_immu_tsb_ticks_ctxnon0_256mb_tte.attr,
	&attr_dmmu_tsb_hits_ctx0_8k_tte.attr,
	&attr_dmmu_tsb_ticks_ctx0_8k_tte.attr,
	&attr_dmmu_tsb_hits_ctx0_64k_tte.attr,
	&attr_dmmu_tsb_ticks_ctx0_64k_tte.attr,
	&attr_dmmu_tsb_hits_ctx0_4mb_tte.attr,
	&attr_dmmu_tsb_ticks_ctx0_4mb_tte.attr,
	&attr_dmmu_tsb_hits_ctx0_256mb_tte.attr,
	&attr_dmmu_tsb_ticks_ctx0_256mb_tte.attr,
	&attr_dmmu_tsb_hits_ctxnon0_8k_tte.attr,
	&attr_dmmu_tsb_ticks_ctxnon0_8k_tte.attr,
	&attr_dmmu_tsb_hits_ctxnon0_64k_tte.attr,
	&attr_dmmu_tsb_ticks_ctxnon0_64k_tte.attr,
	&attr_dmmu_tsb_hits_ctxnon0_4mb_tte.attr,
	&attr_dmmu_tsb_ticks_ctxnon0_4mb_tte.attr,
	&attr_dmmu_tsb_hits_ctxnon0_256mb_tte.attr,
	&attr_dmmu_tsb_ticks_ctxnon0_256mb_tte.attr,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	NULL,
};

static struct attribute_group mmu_stat_group = {
	.attrs = mmu_stat_attrs,
	.name = "mmu_stats",
};

/* XXX convert to rusty's on_one_cpu */
static unsigned long run_on_cpu(unsigned long cpu,
			        unsigned long (*func)(unsigned long),
				unsigned long arg)
{
	cpumask_t old_affinity;
	unsigned long ret;

	cpumask_copy(&old_affinity, tsk_cpus_allowed(current));
	/* should return -EINVAL to userspace */
	if (set_cpus_allowed_ptr(current, cpumask_of(cpu)))
		return 0;

	ret = func(arg);

	set_cpus_allowed_ptr(current, &old_affinity);

	return ret;
}

static unsigned long read_mmustat_enable(unsigned long junk)
{
	unsigned long ra = 0;

	sun4v_mmustat_info(&ra);

	return ra != 0;
}

static unsigned long write_mmustat_enable(unsigned long val)
{
	unsigned long ra, orig_ra;

	if (val)
		ra = __pa(&per_cpu(mmu_stats, smp_processor_id()));
	else
		ra = 0UL;

	return sun4v_mmustat_conf(ra, &orig_ra);
}

<<<<<<< HEAD
static ssize_t show_mmustat_enable(struct device *s,
				struct device_attribute *attr, char *buf)
=======
static ssize_t show_mmustat_enable(struct sys_device *s,
				struct sysdev_attribute *attr, char *buf)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	unsigned long val = run_on_cpu(s->id, read_mmustat_enable, 0);
	return sprintf(buf, "%lx\n", val);
}

<<<<<<< HEAD
static ssize_t store_mmustat_enable(struct device *s,
			struct device_attribute *attr, const char *buf,
=======
static ssize_t store_mmustat_enable(struct sys_device *s,
			struct sysdev_attribute *attr, const char *buf,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			size_t count)
{
	unsigned long val, err;
	int ret = sscanf(buf, "%ld", &val);

	if (ret != 1)
		return -EINVAL;

	err = run_on_cpu(s->id, write_mmustat_enable, val);
	if (err)
		return -EIO;

	return count;
}

<<<<<<< HEAD
static DEVICE_ATTR(mmustat_enable, 0644, show_mmustat_enable, store_mmustat_enable);

static int mmu_stats_supported;

static int register_mmu_stats(struct device *s)
{
	if (!mmu_stats_supported)
		return 0;
	device_create_file(s, &dev_attr_mmustat_enable);
=======
static SYSDEV_ATTR(mmustat_enable, 0644, show_mmustat_enable, store_mmustat_enable);

static int mmu_stats_supported;

static int register_mmu_stats(struct sys_device *s)
{
	if (!mmu_stats_supported)
		return 0;
	sysdev_create_file(s, &attr_mmustat_enable);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	return sysfs_create_group(&s->kobj, &mmu_stat_group);
}

#ifdef CONFIG_HOTPLUG_CPU
<<<<<<< HEAD
static void unregister_mmu_stats(struct device *s)
=======
static void unregister_mmu_stats(struct sys_device *s)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	if (!mmu_stats_supported)
		return;
	sysfs_remove_group(&s->kobj, &mmu_stat_group);
<<<<<<< HEAD
	device_remove_file(s, &dev_attr_mmustat_enable);
=======
	sysdev_remove_file(s, &attr_mmustat_enable);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}
#endif

#define SHOW_CPUDATA_ULONG_NAME(NAME, MEMBER) \
<<<<<<< HEAD
static ssize_t show_##NAME(struct device *dev, \
		struct device_attribute *attr, char *buf) \
=======
static ssize_t show_##NAME(struct sys_device *dev, \
		struct sysdev_attribute *attr, char *buf) \
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{ \
	cpuinfo_sparc *c = &cpu_data(dev->id); \
	return sprintf(buf, "%lu\n", c->MEMBER); \
}

#define SHOW_CPUDATA_UINT_NAME(NAME, MEMBER) \
<<<<<<< HEAD
static ssize_t show_##NAME(struct device *dev, \
		struct device_attribute *attr, char *buf) \
=======
static ssize_t show_##NAME(struct sys_device *dev, \
		struct sysdev_attribute *attr, char *buf) \
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{ \
	cpuinfo_sparc *c = &cpu_data(dev->id); \
	return sprintf(buf, "%u\n", c->MEMBER); \
}

SHOW_CPUDATA_ULONG_NAME(clock_tick, clock_tick);
SHOW_CPUDATA_UINT_NAME(l1_dcache_size, dcache_size);
SHOW_CPUDATA_UINT_NAME(l1_dcache_line_size, dcache_line_size);
SHOW_CPUDATA_UINT_NAME(l1_icache_size, icache_size);
SHOW_CPUDATA_UINT_NAME(l1_icache_line_size, icache_line_size);
SHOW_CPUDATA_UINT_NAME(l2_cache_size, ecache_size);
SHOW_CPUDATA_UINT_NAME(l2_cache_line_size, ecache_line_size);

<<<<<<< HEAD
static struct device_attribute cpu_core_attrs[] = {
	__ATTR(clock_tick,          0444, show_clock_tick, NULL),
	__ATTR(l1_dcache_size,      0444, show_l1_dcache_size, NULL),
	__ATTR(l1_dcache_line_size, 0444, show_l1_dcache_line_size, NULL),
	__ATTR(l1_icache_size,      0444, show_l1_icache_size, NULL),
	__ATTR(l1_icache_line_size, 0444, show_l1_icache_line_size, NULL),
	__ATTR(l2_cache_size,       0444, show_l2_cache_size, NULL),
	__ATTR(l2_cache_line_size,  0444, show_l2_cache_line_size, NULL),
=======
static struct sysdev_attribute cpu_core_attrs[] = {
	_SYSDEV_ATTR(clock_tick,          0444, show_clock_tick, NULL),
	_SYSDEV_ATTR(l1_dcache_size,      0444, show_l1_dcache_size, NULL),
	_SYSDEV_ATTR(l1_dcache_line_size, 0444, show_l1_dcache_line_size, NULL),
	_SYSDEV_ATTR(l1_icache_size,      0444, show_l1_icache_size, NULL),
	_SYSDEV_ATTR(l1_icache_line_size, 0444, show_l1_icache_line_size, NULL),
	_SYSDEV_ATTR(l2_cache_size,       0444, show_l2_cache_size, NULL),
	_SYSDEV_ATTR(l2_cache_line_size,  0444, show_l2_cache_line_size, NULL),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

static DEFINE_PER_CPU(struct cpu, cpu_devices);

static void register_cpu_online(unsigned int cpu)
{
	struct cpu *c = &per_cpu(cpu_devices, cpu);
<<<<<<< HEAD
	struct device *s = &c->dev;
	int i;

	for (i = 0; i < ARRAY_SIZE(cpu_core_attrs); i++)
		device_create_file(s, &cpu_core_attrs[i]);
=======
	struct sys_device *s = &c->sysdev;
	int i;

	for (i = 0; i < ARRAY_SIZE(cpu_core_attrs); i++)
		sysdev_create_file(s, &cpu_core_attrs[i]);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	register_mmu_stats(s);
}

#ifdef CONFIG_HOTPLUG_CPU
static void unregister_cpu_online(unsigned int cpu)
{
	struct cpu *c = &per_cpu(cpu_devices, cpu);
<<<<<<< HEAD
	struct device *s = &c->dev;
=======
	struct sys_device *s = &c->sysdev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	int i;

	unregister_mmu_stats(s);
	for (i = 0; i < ARRAY_SIZE(cpu_core_attrs); i++)
<<<<<<< HEAD
		device_remove_file(s, &cpu_core_attrs[i]);
=======
		sysdev_remove_file(s, &cpu_core_attrs[i]);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}
#endif

static int __cpuinit sysfs_cpu_notify(struct notifier_block *self,
				      unsigned long action, void *hcpu)
{
	unsigned int cpu = (unsigned int)(long)hcpu;

	switch (action) {
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		register_cpu_online(cpu);
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		unregister_cpu_online(cpu);
		break;
#endif
	}
	return NOTIFY_OK;
}

static struct notifier_block __cpuinitdata sysfs_cpu_nb = {
	.notifier_call	= sysfs_cpu_notify,
};

static void __init check_mmu_stats(void)
{
	unsigned long dummy1, err;

	if (tlb_type != hypervisor)
		return;

	err = sun4v_mmustat_info(&dummy1);
	if (!err)
		mmu_stats_supported = 1;
}

static void register_nodes(void)
{
#ifdef CONFIG_NUMA
	int i;

	for (i = 0; i < MAX_NUMNODES; i++)
		register_one_node(i);
#endif
}

static int __init topology_init(void)
{
	int cpu;

	register_nodes();

	check_mmu_stats();

	register_cpu_notifier(&sysfs_cpu_nb);

	for_each_possible_cpu(cpu) {
		struct cpu *c = &per_cpu(cpu_devices, cpu);

		register_cpu(c, cpu);
		if (cpu_online(cpu))
			register_cpu_online(cpu);
	}

	return 0;
}

subsys_initcall(topology_init);
