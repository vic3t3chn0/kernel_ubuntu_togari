/*
 * Contiguous Memory Allocator for DMA mapping framework
 * Copyright (c) 2010-2011 by Samsung Electronics.
 * Written by:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *	Michal Nazarewicz <mina86@mina86.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License or (at your optional) any later version of the license.
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * The Linux Foundation chooses to take subject only to the GPLv2 license
 * terms, and distributes only under these terms.
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */

#define pr_fmt(fmt) "cma: " fmt

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_CMA_DEBUG
=======
#ifdef CONFIG_DMA_CMA_DEBUG
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#ifdef CONFIG_DMA_CMA_DEBUG
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifndef DEBUG
#  define DEBUG
#endif
#endif

#include <asm/page.h>
#include <asm/dma-contiguous.h>

#include <linux/memblock.h>
#include <linux/err.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/of_platform.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/mm.h>
#include <linux/mutex.h>
#include <linux/page-isolation.h>
#include <linux/slab.h>
#include <linux/swap.h>
#include <linux/mm_types.h>
#include <linux/dma-contiguous.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <trace/events/kmem.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifndef SZ_1M
#define SZ_1M (1 << 20)
#endif

struct cma {
	unsigned long	base_pfn;
	unsigned long	count;
	unsigned long	*bitmap;
};

<<<<<<< HEAD
<<<<<<< HEAD
static DEFINE_MUTEX(cma_mutex);

struct cma *dma_contiguous_def_area;
phys_addr_t dma_contiguous_def_base;

static struct cma_area {
	phys_addr_t base;
	unsigned long size;
	struct cma *cma;
	const char *name;
} cma_areas[MAX_CMA_AREAS];
static unsigned cma_area_count;


static struct cma_map {
	phys_addr_t base;
	struct device *dev;
} cma_maps[MAX_CMA_AREAS] __initdata;
static unsigned cma_map_count __initdata;

static struct cma *cma_get_area(phys_addr_t base)
{
	int i;
	for (i = 0; i < cma_area_count; i++)
		if (cma_areas[i].base == base)
			return cma_areas[i].cma;
	return NULL;
}

static struct cma *cma_get_area_by_name(const char *name)
{
	int i;
	if (!name)
		return NULL;

	for (i = 0; i < cma_area_count; i++)
		if (cma_areas[i].name && strcmp(cma_areas[i].name, name) == 0)
			return cma_areas[i].cma;
	return NULL;
}


=======
struct cma *dma_contiguous_default_area;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
struct cma *dma_contiguous_default_area;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifdef CONFIG_CMA_SIZE_MBYTES
#define CMA_SIZE_MBYTES CONFIG_CMA_SIZE_MBYTES
#else
#define CMA_SIZE_MBYTES 0
#endif

/*
 * Default global CMA area size can be defined in kernel's .config.
 * This is usefull mainly for distro maintainers to create a kernel
 * that works correctly for most supported systems.
 * The size can be set in bytes or as a percentage of the total memory
 * in the system.
 *
 * Users, who want to set the size of global CMA area for their system
 * should use cma= kernel parameter.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static const phys_addr_t size_bytes = CMA_SIZE_MBYTES * SZ_1M;
static phys_addr_t size_cmdline = -1;
=======
static const unsigned long size_bytes = CMA_SIZE_MBYTES * SZ_1M;
static long size_cmdline = -1;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static const unsigned long size_bytes = CMA_SIZE_MBYTES * SZ_1M;
static long size_cmdline = -1;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static int __init early_cma(char *p)
{
	pr_debug("%s(%s)\n", __func__, p);
	size_cmdline = memparse(p, &p);
	return 0;
}
early_param("cma", early_cma);

#ifdef CONFIG_CMA_SIZE_PERCENTAGE

<<<<<<< HEAD
<<<<<<< HEAD
static phys_addr_t __init __maybe_unused cma_early_percent_memory(void)
=======
static unsigned long __init __maybe_unused cma_early_percent_memory(void)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static unsigned long __init __maybe_unused cma_early_percent_memory(void)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct memblock_region *reg;
	unsigned long total_pages = 0;

	/*
	 * We cannot use memblock_phys_mem_size() here, because
	 * memblock_analyze() has not been called yet.
	 */
	for_each_memblock(memory, reg)
		total_pages += memblock_region_memory_end_pfn(reg) -
			       memblock_region_memory_base_pfn(reg);

	return (total_pages * CONFIG_CMA_SIZE_PERCENTAGE / 100) << PAGE_SHIFT;
}

#else

<<<<<<< HEAD
<<<<<<< HEAD
static inline __maybe_unused phys_addr_t cma_early_percent_memory(void)
=======
static inline __maybe_unused unsigned long cma_early_percent_memory(void)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static inline __maybe_unused unsigned long cma_early_percent_memory(void)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return 0;
}

#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/**
 * dma_contiguous_reserve() - reserve area for contiguous memory handling
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specific code once the early allocator (memblock or bootmem)
 * has been activated and all other subsystems have already allocated/reserved
 * memory.
 */
void __init dma_contiguous_reserve(phys_addr_t limit)
{
	unsigned long selected_size = 0;

	pr_debug("%s(limit %08lx)\n", __func__, (unsigned long)limit);

	if (size_cmdline != -1) {
		selected_size = size_cmdline;
	} else {
#ifdef CONFIG_CMA_SIZE_SEL_MBYTES
		selected_size = size_bytes;
#elif defined(CONFIG_CMA_SIZE_SEL_PERCENTAGE)
		selected_size = cma_early_percent_memory();
#elif defined(CONFIG_CMA_SIZE_SEL_MIN)
		selected_size = min(size_bytes, cma_early_percent_memory());
#elif defined(CONFIG_CMA_SIZE_SEL_MAX)
		selected_size = max(size_bytes, cma_early_percent_memory());
#endif
	}

	if (selected_size) {
		pr_debug("%s: reserving %ld MiB for global area\n", __func__,
			 selected_size / SZ_1M);

		dma_declare_contiguous(NULL, selected_size, 0, limit);
	}
};

static DEFINE_MUTEX(cma_mutex);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static __init int cma_activate_area(unsigned long base_pfn, unsigned long count)
{
	unsigned long pfn = base_pfn;
	unsigned i = count >> pageblock_order;
	struct zone *zone;

	WARN_ON_ONCE(!pfn_valid(pfn));
	zone = page_zone(pfn_to_page(pfn));

	do {
		unsigned j;
		base_pfn = pfn;
		for (j = pageblock_nr_pages; j; --j, pfn++) {
			WARN_ON_ONCE(!pfn_valid(pfn));
			if (page_zone(pfn_to_page(pfn)) != zone)
				return -EINVAL;
		}
		init_cma_reserved_pageblock(pfn_to_page(base_pfn));
	} while (--i);
	return 0;
}

static __init struct cma *cma_create_area(unsigned long base_pfn,
				     unsigned long count)
{
	int bitmap_size = BITS_TO_LONGS(count) * sizeof(long);
	struct cma *cma;
	int ret = -ENOMEM;

	pr_debug("%s(base %08lx, count %lx)\n", __func__, base_pfn, count);

	cma = kmalloc(sizeof *cma, GFP_KERNEL);
	if (!cma)
		return ERR_PTR(-ENOMEM);

	cma->base_pfn = base_pfn;
	cma->count = count;
	cma->bitmap = kzalloc(bitmap_size, GFP_KERNEL);

	if (!cma->bitmap)
		goto no_mem;

	ret = cma_activate_area(base_pfn, count);
	if (ret)
		goto error;

	pr_debug("%s: returned %p\n", __func__, (void *)cma);
	return cma;

error:
	kfree(cma->bitmap);
no_mem:
	kfree(cma);
	return ERR_PTR(ret);
}

<<<<<<< HEAD
<<<<<<< HEAD
/*****************************************************************************/

#ifdef CONFIG_OF
int __init cma_fdt_scan(unsigned long node, const char *uname,
				int depth, void *data)
{
	phys_addr_t base, size;
	unsigned long len;
	__be32 *prop;
	char *name;

	if (!of_get_flat_dt_prop(node, "linux,contiguous-region", NULL))
		return 0;

	prop = of_get_flat_dt_prop(node, "reg", &len);
	if (!prop || (len != 2 * sizeof(unsigned long)))
		return 0;

	base = be32_to_cpu(prop[0]);
	size = be32_to_cpu(prop[1]);

	name = of_get_flat_dt_prop(node, "label", NULL);

	pr_info("Found %s, memory base %lx, size %ld MiB\n", uname,
		(unsigned long)base, (unsigned long)size / SZ_1M);
	dma_contiguous_reserve_area(size, &base, MEMBLOCK_ALLOC_ANYWHERE, name);

	return 0;
}
#endif

/**
 * dma_contiguous_reserve() - reserve area for contiguous memory handling
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specific code once the early allocator (memblock or bootmem)
 * has been activated and all other subsystems have already allocated/reserved
 * memory. It reserves contiguous areas for global, device independent
 * allocations and (optionally) all areas defined in device tree structures.
 */
void __init dma_contiguous_reserve(phys_addr_t limit)
{
	phys_addr_t sel_size = 0;

	pr_debug("%s(limit %08lx)\n", __func__, (unsigned long)limit);

	if (size_cmdline != -1) {
		sel_size = size_cmdline;
	} else {
#ifdef CONFIG_CMA_SIZE_SEL_MBYTES
		sel_size = size_bytes;
#elif defined(CONFIG_CMA_SIZE_SEL_PERCENTAGE)
		sel_size = cma_early_percent_memory();
#elif defined(CONFIG_CMA_SIZE_SEL_MIN)
		sel_size = min(size_bytes, cma_early_percent_memory());
#elif defined(CONFIG_CMA_SIZE_SEL_MAX)
		sel_size = max(size_bytes, cma_early_percent_memory());
#endif
	}

	if (sel_size) {
		phys_addr_t base = 0;
		pr_debug("%s: reserving %ld MiB for global area\n", __func__,
			 (unsigned long)sel_size / SZ_1M);

		if (dma_contiguous_reserve_area(sel_size, &base, limit, NULL)
		    == 0)
			dma_contiguous_def_base = base;
	}
#ifdef CONFIG_OF
	of_scan_flat_dt(cma_fdt_scan, NULL);
#endif
};

/**
 * dma_contiguous_reserve_area() - reserve custom contiguous area
 * @size: Size of the reserved area (in bytes),
 * @base: Pointer to the base address of the reserved area, also used to return
 * 	  base address of the actually reserved area, optional, use pointer to
 *	  0 for any
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specific code once the early allocator (memblock or bootmem)
 * has been activated and all other subsystems have already allocated/reserved
 * memory. This function allows to create custom reserved areas for specific
 * devices.
 */
int __init dma_contiguous_reserve_area(phys_addr_t size, phys_addr_t *res_base,
				       phys_addr_t limit, const char *name)
{
	phys_addr_t base = *res_base;
	phys_addr_t alignment;
	int ret = 0;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct cma_reserved {
	phys_addr_t start;
	unsigned long size;
	struct device *dev;
} cma_reserved[MAX_CMA_AREAS] __initdata;
static unsigned cma_reserved_count __initdata;

static int __init cma_init_reserved_areas(void)
{
	struct cma_reserved *r = cma_reserved;
	unsigned i = cma_reserved_count;

	pr_debug("%s()\n", __func__);

	for (; i; --i, ++r) {
		struct cma *cma;
		cma = cma_create_area(PFN_DOWN(r->start),
					r->size >> PAGE_SHIFT);
		if (!IS_ERR(cma))
			dev_set_cma_area(r->dev, cma);
		else
			printk(KERN_ERR "%s() cma_create_area error for %ud\n",
					__func__, i);
	}
	return 0;
}
core_initcall(cma_init_reserved_areas);

/**
 * dma_declare_contiguous() - reserve area for contiguous memory handling
 *			      for particular device
 * @dev:   Pointer to device structure.
 * @size:  Size of the reserved memory.
 * @base:  Start address of the reserved memory (optional, 0 for any).
 * @limit: End address of the reserved memory (optional, 0 for any).
 *
 * This function reserves memory for specified device. It should be
 * called by board specific code when early allocator (memblock or bootmem)
 * is still activate.
 */
int __init dma_declare_contiguous(struct device *dev, unsigned long size,
				  phys_addr_t base, phys_addr_t limit)
{
	struct cma_reserved *r = &cma_reserved[cma_reserved_count];
	unsigned long alignment;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	pr_debug("%s(size %lx, base %08lx, limit %08lx)\n", __func__,
		 (unsigned long)size, (unsigned long)base,
		 (unsigned long)limit);

	/* Sanity checks */
<<<<<<< HEAD
<<<<<<< HEAD
	if (cma_area_count == ARRAY_SIZE(cma_areas)) {
=======
	if (cma_reserved_count == ARRAY_SIZE(cma_reserved)) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (cma_reserved_count == ARRAY_SIZE(cma_reserved)) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		pr_err("Not enough slots for CMA reserved regions!\n");
		return -ENOSPC;
	}

	if (!size)
		return -EINVAL;

	/* Sanitise input arguments */
<<<<<<< HEAD
<<<<<<< HEAD
	alignment = PAGE_SIZE << max(MAX_ORDER - 1, pageblock_order);
=======
	alignment = PAGE_SIZE << max(MAX_ORDER-1, pageblock_order);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	alignment = PAGE_SIZE << max(MAX_ORDER-1, pageblock_order);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	base = ALIGN(base, alignment);
	size = ALIGN(size, alignment);
	limit &= ~(alignment - 1);

	/* Reserve memory */
	if (base) {
		if (memblock_is_region_reserved(base, size) ||
		    memblock_reserve(base, size) < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
			ret = -EBUSY;
=======
			base = -EBUSY;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			base = -EBUSY;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			goto err;
		}
	} else {
		/*
		 * Use __memblock_alloc_base() since
		 * memblock_alloc_base() panic()s.
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		phys_addr_t addr = __memblock_alloc_base(size, alignment, limit);
		if (!addr) {
			ret = -ENOMEM;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		phys_addr_t addr = __memblock_alloc_base(size, alignment,
									limit);
		if (!addr) {
			base = -ENOMEM;
			goto err;
		} else if (addr + size > ~(unsigned long)0) {
			memblock_free(addr, size);
			base = -EINVAL;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			goto err;
		} else {
			base = addr;
		}
	}

	/*
	 * Each reserved area must be initialised later, when more kernel
	 * subsystems (like slab allocator) are available.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	cma_areas[cma_area_count].base = base;
	cma_areas[cma_area_count].size = size;
	cma_areas[cma_area_count].name = name;
	cma_area_count++;
	*res_base = base;

	pr_info("CMA: reserved %ld MiB at %08lx\n", (unsigned long)size / SZ_1M,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	r->start = base;
	r->size = size;
	r->dev = dev;
	cma_reserved_count++;
	pr_info("CMA: reserved %ld MiB at %08lx\n", size / SZ_1M,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		(unsigned long)base);

	/* Architecture specific contiguous memory fixup. */
	dma_contiguous_early_fixup(base, size);
	return 0;
err:
<<<<<<< HEAD
<<<<<<< HEAD
	pr_err("CMA: failed to reserve %ld MiB\n", (unsigned long)size / SZ_1M);
	return ret;
}

/**
 * dma_contiguous_add_device() - add device to custom contiguous reserved area
 * @dev:   Pointer to device structure.
 * @base: Pointer to the base address of the reserved area returned by
 *        dma_contiguous_reserve_area() function, also used to return
 *
 * This function assigns the given device to the contiguous memory area
 * reserved earlier by dma_contiguous_reserve_area() function.
 */
int __init dma_contiguous_add_device(struct device *dev, phys_addr_t base)
{
	if (cma_map_count == ARRAY_SIZE(cma_maps)) {
		pr_err("Not enough slots for CMA reserved regions!\n");
		return -ENOSPC;
	}
	cma_maps[cma_map_count].dev = dev;
	cma_maps[cma_map_count].base = base;
	cma_map_count++;
	return 0;
}

#ifdef CONFIG_OF
static void cma_assign_device_from_dt(struct device *dev)
{
	struct device_node *node;
	struct cma *cma;
	const char *name;
	u32 value;

	node = of_parse_phandle(dev->of_node, "linux,contiguous-region", 0);
	if (!node)
		return;
	if (of_property_read_u32(node, "reg", &value) && !value)
		return;

	if (of_property_read_string(node, "label", &name))
		return;

	cma = cma_get_area_by_name(name);
	if (!cma)
		return;

	dev_set_cma_area(dev, cma);
	pr_info("Assigned CMA region at %lx to %s device\n", (unsigned long)value, dev_name(dev));
}

static int cma_device_init_notifier_call(struct notifier_block *nb,
					 unsigned long event, void *data)
{
	struct device *dev = data;
	if (event == BUS_NOTIFY_ADD_DEVICE && dev->of_node)
		cma_assign_device_from_dt(dev);
	return NOTIFY_DONE;
}

static struct notifier_block cma_dev_init_nb = {
	.notifier_call = cma_device_init_notifier_call,
};
#endif

static int __init cma_init_reserved_areas(void)
{
	struct cma *cma;
	int i;

	for (i = 0; i < cma_area_count; i++) {
		phys_addr_t base = PFN_DOWN(cma_areas[i].base);
		unsigned int count = cma_areas[i].size >> PAGE_SHIFT;

		cma = cma_create_area(base, count);
		if (!IS_ERR(cma))
			cma_areas[i].cma = cma;
	}

	dma_contiguous_def_area = cma_get_area(dma_contiguous_def_base);

	for (i = 0; i < cma_map_count; i++) {
		cma = cma_get_area(cma_maps[i].base);
		dev_set_cma_area(cma_maps[i].dev, cma);
	}

#ifdef CONFIG_OF
	bus_register_notifier(&platform_bus_type, &cma_dev_init_nb);
#endif
	return 0;
}
core_initcall(cma_init_reserved_areas);

phys_addr_t cma_get_base(struct device *dev)
{
	struct cma *cma = dev_get_cma_area(dev);

	return cma->base_pfn << PAGE_SHIFT;
}

/**
 * dma_alloc_from_contiguous() - allocate pages from contiguous area
 * @dev:   Pointer to device for which the allocation is performed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 *
 * This function allocates memory buffer for specified device. It uses
 * device specific contiguous memory area if available or the default
 * global one. Requires architecture specific get_dev_cma_area() helper
 * function.
 */
struct page *dma_alloc_from_contiguous(struct device *dev, int count,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	pr_err("CMA: failed to reserve %ld MiB\n", size / SZ_1M);
	return base;
}

static struct page *__dma_alloc_from_contiguous(struct device *dev, int count,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				       unsigned int align)
{
	unsigned long mask, pfn, pageno, start = 0;
	struct cma *cma = dev_get_cma_area(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct page *page = NULL;
	int ret;
	int tries = 0;
=======
	int ret;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	int ret;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!cma || !cma->count)
		return NULL;

	if (align > CONFIG_CMA_ALIGNMENT)
		align = CONFIG_CMA_ALIGNMENT;

	pr_debug("%s(cma %p, count %d, align %d)\n", __func__, (void *)cma,
		 count, align);

	if (!count)
		return NULL;

	mask = (1 << align) - 1;

	mutex_lock(&cma_mutex);

	for (;;) {
		pageno = bitmap_find_next_zero_area(cma->bitmap, cma->count,
						    start, count, mask);
<<<<<<< HEAD
<<<<<<< HEAD
		if (pageno >= cma->count)
			break;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (pageno >= cma->count) {
			printk(KERN_ERR "%s : cma->count is %lu, "
					"pageno is %lu\n", __func__,
					cma->count, pageno);
			ret = -ENOMEM;
			goto error;
		}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		pfn = cma->base_pfn + pageno;
		ret = alloc_contig_range(pfn, pfn + count, MIGRATE_CMA);
		if (ret == 0) {
			bitmap_set(cma->bitmap, pageno, count);
<<<<<<< HEAD
<<<<<<< HEAD
			page = pfn_to_page(pfn);
			break;
		} else if (ret != -EBUSY) {
			break;
		}
		tries++;
		trace_dma_alloc_contiguous_retry(tries);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		} else if (ret != -EBUSY && ret != -EAGAIN) {
			goto error;
		}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		pr_debug("%s(): memory range at %p is busy, retrying\n",
			 __func__, pfn_to_page(pfn));
		/* try again with a bit different memory target */
		start = pageno + mask + 1;
	}

	mutex_unlock(&cma_mutex);
<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s(): returned %p\n", __func__, page);
	return page;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	pr_debug("%s(): returned %p\n", __func__, pfn_to_page(pfn));
	return pfn_to_page(pfn);
error:
	pr_err("%s(): returned error (%d)\n", __func__, ret);
	mutex_unlock(&cma_mutex);
	return NULL;
}

struct dma_prepare_alloc_ctx {
	struct device *dev;
	int count;
	unsigned int align;
	struct work_struct work;
	struct list_head node;
	struct page *result;
};

/* list of asynchronous allocations */
static LIST_HEAD(dma_prepare_alloc_head);
/* protects dma_prepare_alloc_head */
static DEFINE_SPINLOCK(dma_prepare_alloc_lock);

static void do_dma_prepare_alloc(struct work_struct *work)
{
	struct dma_prepare_alloc_ctx *ctx = container_of(
			work, struct dma_prepare_alloc_ctx, work);

	ctx->result = __dma_alloc_from_contiguous(ctx->dev, ctx->count,
			ctx->align);
	printk(KERN_INFO "%s[%d]: alloc %d pages for dev %s %s\n",
		__func__, __LINE__, ctx->count, dev_name(ctx->dev),
		ctx->result ? "succeeded" : "failed");
}

/**
 * dma_prepare_alloc_from_contiguous() - prepare allocation of pages in
 * an asynchronous thread
 * @dev:   Pointer to device for which the allocation is performed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 *
 * This function prepares an allocation by scheduling it in a separate work
 * thread. Once dma_alloc_from_contiguous is called then it searches
 * the dma_prepare_alloc_head list in the first place.
 */
int dma_prepare_alloc_from_contiguous(struct device *dev, int count,
				unsigned int align)
{
	struct dma_prepare_alloc_ctx *ctx;
	unsigned long flags;

	ctx = kzalloc(sizeof *ctx, GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = dev;
	ctx->count = count;
	ctx->align = align;
	INIT_WORK(&ctx->work, do_dma_prepare_alloc);

	spin_lock_irqsave(&dma_prepare_alloc_lock, flags);
	list_add_tail(&ctx->node, &dma_prepare_alloc_head);
	spin_unlock_irqrestore(&dma_prepare_alloc_lock, flags);

	queue_work(system_long_wq, &ctx->work);
	return 0;
}

/**
 * dma_alloc_from_contiguous() - allocate pages from contiguous area
 * @dev:   Pointer to device for which the allocation is performed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 *
 * This function allocates memory buffer for specified device. It uses
 * device specific contiguous memory area if available or the default
 * global one. Requires architecture specific get_dev_cma_area() helper
 * function.
 */
struct page *dma_alloc_from_contiguous(struct device *dev, int count,
				unsigned int align)
{
	unsigned long flags;
	struct list_head *i, *n;
	struct dma_prepare_alloc_ctx *ctx = NULL;
	struct page *result = NULL;

	/* search for a cached allocation */
	spin_lock_irqsave(&dma_prepare_alloc_lock, flags);
	list_for_each_safe(i, n, &dma_prepare_alloc_head) {
		ctx = list_entry(i, struct dma_prepare_alloc_ctx, node);
		if (ctx->dev == dev && ctx->count == count &&
		    ctx->align == align) {
			list_del(i);
			break;
		}
		ctx = NULL;
	}
	spin_unlock_irqrestore(&dma_prepare_alloc_lock, flags);

	/* If a cached allocation is found then use its result */
	if (ctx) {
		flush_work(&ctx->work);
		result = ctx->result;
		kfree(ctx);
	}
	/* fallback to sync allocation */
	if (!result)
		result = __dma_alloc_from_contiguous(dev, count, align);
	return result;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**
 * dma_release_from_contiguous() - release allocated pages
 * @dev:   Pointer to device for which the pages were allocated.
 * @pages: Allocated pages.
 * @count: Number of allocated pages.
 *
 * This function releases memory allocated by dma_alloc_from_contiguous().
 * It returns false when provided pages do not belong to contiguous area and
 * true otherwise.
 */
bool dma_release_from_contiguous(struct device *dev, struct page *pages,
				 int count)
{
	struct cma *cma = dev_get_cma_area(dev);
	unsigned long pfn;

	if (!cma || !pages)
		return false;

	pr_debug("%s(page %p)\n", __func__, (void *)pages);

	pfn = page_to_pfn(pages);

<<<<<<< HEAD
<<<<<<< HEAD
	if (pfn < cma->base_pfn || pfn >= cma->base_pfn + cma->count)
		return false;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (pfn < cma->base_pfn || pfn >= cma->base_pfn + cma->count) {
		pr_info("%s : return false\n", __func__);
		return false;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	VM_BUG_ON(pfn + count > cma->base_pfn + cma->count);

	mutex_lock(&cma_mutex);
	bitmap_clear(cma->bitmap, pfn - cma->base_pfn, count);
	free_contig_range(pfn, count);
	mutex_unlock(&cma_mutex);

	return true;
}
