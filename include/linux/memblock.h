#ifndef _LINUX_MEMBLOCK_H
#define _LINUX_MEMBLOCK_H
#ifdef __KERNEL__

<<<<<<< HEAD
=======
#define MEMBLOCK_ERROR	0

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#ifdef CONFIG_HAVE_MEMBLOCK
/*
 * Logical memory blocks.
 *
 * Copyright (C) 2001 Peter Bergner, IBM Corp.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <linux/init.h>
#include <linux/mm.h>

<<<<<<< HEAD
=======
#include <asm/memblock.h>

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define INIT_MEMBLOCK_REGIONS	128

struct memblock_region {
	phys_addr_t base;
	phys_addr_t size;
<<<<<<< HEAD
#ifdef CONFIG_HAVE_MEMBLOCK_NODE_MAP
	int nid;
#endif
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

struct memblock_type {
	unsigned long cnt;	/* number of regions */
	unsigned long max;	/* size of the allocated array */
<<<<<<< HEAD
	phys_addr_t total_size;	/* size of all regions */
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct memblock_region *regions;
};

struct memblock {
	phys_addr_t current_limit;
<<<<<<< HEAD
=======
	phys_addr_t memory_size;	/* Updated by memblock_analyze() */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct memblock_type memory;
	struct memblock_type reserved;
};

extern struct memblock memblock;
extern int memblock_debug;
<<<<<<< HEAD
=======
extern int memblock_can_resize;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#define memblock_dbg(fmt, ...) \
	if (memblock_debug) printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)

<<<<<<< HEAD
phys_addr_t memblock_find_in_range_node(phys_addr_t start, phys_addr_t end,
				phys_addr_t size, phys_addr_t align, int nid);
phys_addr_t memblock_find_in_range(phys_addr_t start, phys_addr_t end,
				   phys_addr_t size, phys_addr_t align);
int memblock_free_reserved_regions(void);
int memblock_reserve_reserved_regions(void);

void memblock_allow_resize(void);
int memblock_add_node(phys_addr_t base, phys_addr_t size, int nid);
int memblock_add(phys_addr_t base, phys_addr_t size);
int memblock_remove(phys_addr_t base, phys_addr_t size);
int memblock_free(phys_addr_t base, phys_addr_t size);
int memblock_reserve(phys_addr_t base, phys_addr_t size);

#ifdef CONFIG_HAVE_MEMBLOCK_NODE_MAP
void __next_mem_pfn_range(int *idx, int nid, unsigned long *out_start_pfn,
			  unsigned long *out_end_pfn, int *out_nid);

/**
 * for_each_mem_pfn_range - early memory pfn range iterator
 * @i: an integer used as loop variable
 * @nid: node selector, %MAX_NUMNODES for all nodes
 * @p_start: ptr to ulong for start pfn of the range, can be %NULL
 * @p_end: ptr to ulong for end pfn of the range, can be %NULL
 * @p_nid: ptr to int for nid of the range, can be %NULL
 *
 * Walks over configured memory ranges.  Available after early_node_map is
 * populated.
 */
#define for_each_mem_pfn_range(i, nid, p_start, p_end, p_nid)		\
	for (i = -1, __next_mem_pfn_range(&i, nid, p_start, p_end, p_nid); \
	     i >= 0; __next_mem_pfn_range(&i, nid, p_start, p_end, p_nid))
#endif /* CONFIG_HAVE_MEMBLOCK_NODE_MAP */

void __next_free_mem_range(u64 *idx, int nid, phys_addr_t *out_start,
			   phys_addr_t *out_end, int *out_nid);

/**
 * for_each_free_mem_range - iterate through free memblock areas
 * @i: u64 used as loop variable
 * @nid: node selector, %MAX_NUMNODES for all nodes
 * @p_start: ptr to phys_addr_t for start address of the range, can be %NULL
 * @p_end: ptr to phys_addr_t for end address of the range, can be %NULL
 * @p_nid: ptr to int for nid of the range, can be %NULL
 *
 * Walks over free (memory && !reserved) areas of memblock.  Available as
 * soon as memblock is initialized.
 */
#define for_each_free_mem_range(i, nid, p_start, p_end, p_nid)		\
	for (i = 0,							\
	     __next_free_mem_range(&i, nid, p_start, p_end, p_nid);	\
	     i != (u64)ULLONG_MAX;					\
	     __next_free_mem_range(&i, nid, p_start, p_end, p_nid))

void __next_free_mem_range_rev(u64 *idx, int nid, phys_addr_t *out_start,
			       phys_addr_t *out_end, int *out_nid);

/**
 * for_each_free_mem_range_reverse - rev-iterate through free memblock areas
 * @i: u64 used as loop variable
 * @nid: node selector, %MAX_NUMNODES for all nodes
 * @p_start: ptr to phys_addr_t for start address of the range, can be %NULL
 * @p_end: ptr to phys_addr_t for end address of the range, can be %NULL
 * @p_nid: ptr to int for nid of the range, can be %NULL
 *
 * Walks over free (memory && !reserved) areas of memblock in reverse
 * order.  Available as soon as memblock is initialized.
 */
#define for_each_free_mem_range_reverse(i, nid, p_start, p_end, p_nid)	\
	for (i = (u64)ULLONG_MAX,					\
	     __next_free_mem_range_rev(&i, nid, p_start, p_end, p_nid);	\
	     i != (u64)ULLONG_MAX;					\
	     __next_free_mem_range_rev(&i, nid, p_start, p_end, p_nid))

#ifdef CONFIG_HAVE_MEMBLOCK_NODE_MAP
int memblock_set_node(phys_addr_t base, phys_addr_t size, int nid);

static inline void memblock_set_region_node(struct memblock_region *r, int nid)
{
	r->nid = nid;
}

static inline int memblock_get_region_node(const struct memblock_region *r)
{
	return r->nid;
}
#else
static inline void memblock_set_region_node(struct memblock_region *r, int nid)
{
}

static inline int memblock_get_region_node(const struct memblock_region *r)
{
	return 0;
}
#endif /* CONFIG_HAVE_MEMBLOCK_NODE_MAP */

phys_addr_t memblock_alloc_nid(phys_addr_t size, phys_addr_t align, int nid);
phys_addr_t memblock_alloc_try_nid(phys_addr_t size, phys_addr_t align, int nid);

phys_addr_t memblock_alloc(phys_addr_t size, phys_addr_t align);
=======
u64 memblock_find_in_range(u64 start, u64 end, u64 size, u64 align);
int memblock_free_reserved_regions(void);
int memblock_reserve_reserved_regions(void);

extern void memblock_init(void);
extern void memblock_analyze(void);
extern long memblock_add(phys_addr_t base, phys_addr_t size);
extern long memblock_remove(phys_addr_t base, phys_addr_t size);
extern long memblock_free(phys_addr_t base, phys_addr_t size);
extern long memblock_reserve(phys_addr_t base, phys_addr_t size);

/* The numa aware allocator is only available if
 * CONFIG_ARCH_POPULATES_NODE_MAP is set
 */
extern phys_addr_t memblock_alloc_nid(phys_addr_t size, phys_addr_t align,
					int nid);
extern phys_addr_t memblock_alloc_try_nid(phys_addr_t size, phys_addr_t align,
					    int nid);

extern phys_addr_t memblock_alloc(phys_addr_t size, phys_addr_t align);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/* Flags for memblock_alloc_base() amd __memblock_alloc_base() */
#define MEMBLOCK_ALLOC_ANYWHERE	(~(phys_addr_t)0)
#define MEMBLOCK_ALLOC_ACCESSIBLE	0

<<<<<<< HEAD
phys_addr_t memblock_alloc_base(phys_addr_t size, phys_addr_t align,
				phys_addr_t max_addr);
phys_addr_t __memblock_alloc_base(phys_addr_t size, phys_addr_t align,
				  phys_addr_t max_addr);
phys_addr_t memblock_phys_mem_size(void);
phys_addr_t memblock_start_of_DRAM(void);
phys_addr_t memblock_end_of_DRAM(void);
void memblock_enforce_memory_limit(phys_addr_t memory_limit);
int memblock_is_memory(phys_addr_t addr);
int memblock_is_region_memory(phys_addr_t base, phys_addr_t size);
int memblock_overlaps_memory(phys_addr_t base, phys_addr_t size);
int memblock_is_reserved(phys_addr_t addr);
int memblock_is_region_reserved(phys_addr_t base, phys_addr_t size);

extern void __memblock_dump_all(void);

static inline void memblock_dump_all(void)
{
	if (memblock_debug)
		__memblock_dump_all();
}
=======
extern phys_addr_t memblock_alloc_base(phys_addr_t size,
					 phys_addr_t align,
					 phys_addr_t max_addr);
extern phys_addr_t __memblock_alloc_base(phys_addr_t size,
					   phys_addr_t align,
					   phys_addr_t max_addr);
extern phys_addr_t memblock_phys_mem_size(void);
extern phys_addr_t memblock_end_of_DRAM(void);
extern void memblock_enforce_memory_limit(phys_addr_t memory_limit);
extern int memblock_is_memory(phys_addr_t addr);
extern int memblock_is_region_memory(phys_addr_t base, phys_addr_t size);
extern int memblock_is_reserved(phys_addr_t addr);
extern int memblock_is_region_reserved(phys_addr_t base, phys_addr_t size);

extern void memblock_dump_all(void);

/* Provided by the architecture */
extern phys_addr_t memblock_nid_range(phys_addr_t start, phys_addr_t end, int *nid);
extern int memblock_memory_can_coalesce(phys_addr_t addr1, phys_addr_t size1,
				   phys_addr_t addr2, phys_addr_t size2);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/**
 * memblock_set_current_limit - Set the current allocation limit to allow
 *                         limiting allocations to what is currently
 *                         accessible during boot
 * @limit: New limit value (physical address)
 */
<<<<<<< HEAD
void memblock_set_current_limit(phys_addr_t limit);
=======
extern void memblock_set_current_limit(phys_addr_t limit);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9


/*
 * pfn conversion functions
 *
 * While the memory MEMBLOCKs should always be page aligned, the reserved
 * MEMBLOCKs may not be. This accessor attempt to provide a very clear
 * idea of what they return for such non aligned MEMBLOCKs.
 */

/**
 * memblock_region_memory_base_pfn - Return the lowest pfn intersecting with the memory region
 * @reg: memblock_region structure
 */
static inline unsigned long memblock_region_memory_base_pfn(const struct memblock_region *reg)
{
	return PFN_UP(reg->base);
}

/**
 * memblock_region_memory_end_pfn - Return the end_pfn this region
 * @reg: memblock_region structure
 */
static inline unsigned long memblock_region_memory_end_pfn(const struct memblock_region *reg)
{
	return PFN_DOWN(reg->base + reg->size);
}

/**
 * memblock_region_reserved_base_pfn - Return the lowest pfn intersecting with the reserved region
 * @reg: memblock_region structure
 */
static inline unsigned long memblock_region_reserved_base_pfn(const struct memblock_region *reg)
{
	return PFN_DOWN(reg->base);
}

/**
 * memblock_region_reserved_end_pfn - Return the end_pfn this region
 * @reg: memblock_region structure
 */
static inline unsigned long memblock_region_reserved_end_pfn(const struct memblock_region *reg)
{
	return PFN_UP(reg->base + reg->size);
}

#define for_each_memblock(memblock_type, region)					\
	for (region = memblock.memblock_type.regions;				\
	     region < (memblock.memblock_type.regions + memblock.memblock_type.cnt);	\
	     region++)


<<<<<<< HEAD
#ifdef CONFIG_ARCH_DISCARD_MEMBLOCK
#define __init_memblock __meminit
#define __initdata_memblock __meminitdata
=======
#ifdef ARCH_DISCARD_MEMBLOCK
#define __init_memblock __init
#define __initdata_memblock __initdata
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#else
#define __init_memblock
#define __initdata_memblock
#endif

#else
static inline phys_addr_t memblock_alloc(phys_addr_t size, phys_addr_t align)
{
<<<<<<< HEAD
	return 0;
=======
	return MEMBLOCK_ERROR;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

#endif /* CONFIG_HAVE_MEMBLOCK */

#endif /* __KERNEL__ */

#endif /* _LINUX_MEMBLOCK_H */
