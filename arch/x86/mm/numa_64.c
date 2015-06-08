/*
 * Generic VM initialization for x86-64 NUMA setups.
 * Copyright 2002,2003 Andi Kleen, SuSE Labs.
 */
#include <linux/bootmem.h>

#include "numa_internal.h"

void __init initmem_init(void)
{
	x86_numa_init();
}

unsigned long __init numa_free_all_bootmem(void)
{
	unsigned long pages = 0;
	int i;

	for_each_online_node(i)
		pages += free_all_bootmem_node(NODE_DATA(i));

<<<<<<< HEAD
	pages += free_low_memory_core_early(MAX_NUMNODES);
=======
<<<<<<< HEAD
	pages += free_low_memory_core_early(MAX_NUMNODES);
=======
	pages += free_all_memory_core_early(MAX_NUMNODES);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return pages;
}
