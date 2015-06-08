#ifndef _ASM_ARM_MEMBLOCK_H
#define _ASM_ARM_MEMBLOCK_H

struct meminfo;
struct machine_desc;

extern void arm_memblock_init(struct meminfo *, struct machine_desc *);

<<<<<<< HEAD
phys_addr_t arm_memblock_steal(phys_addr_t size, phys_addr_t align);

=======
<<<<<<< HEAD
phys_addr_t arm_memblock_steal(phys_addr_t size, phys_addr_t align);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
