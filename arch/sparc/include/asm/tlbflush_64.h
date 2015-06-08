#ifndef _SPARC64_TLBFLUSH_H
#define _SPARC64_TLBFLUSH_H

#include <linux/mm.h>
#include <asm/mmu_context.h>

/* TSB flush operations. */

#define TLB_BATCH_NR	192

struct tlb_batch {
	struct mm_struct *mm;
	unsigned long tlb_nr;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	unsigned long active;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long vaddrs[TLB_BATCH_NR];
};

extern void flush_tsb_kernel_range(unsigned long start, unsigned long end);
extern void flush_tsb_user(struct tlb_batch *tb);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* TLB flush operations. */

extern void flush_tlb_pending(void);

#define flush_tlb_range(vma,start,end)	\
	do { (void)(start); flush_tlb_pending(); } while (0)
#define flush_tlb_page(vma,addr)	flush_tlb_pending()
#define flush_tlb_mm(mm)		flush_tlb_pending()

/* Local cpu only.  */
extern void __flush_tlb_all(void);

<<<<<<< HEAD
=======
=======
extern void flush_tsb_user_page(struct mm_struct *mm, unsigned long vaddr);

/* TLB flush operations. */

static inline void flush_tlb_mm(struct mm_struct *mm)
{
}

static inline void flush_tlb_page(struct vm_area_struct *vma,
				  unsigned long vmaddr)
{
}

static inline void flush_tlb_range(struct vm_area_struct *vma,
				   unsigned long start, unsigned long end)
{
}

#define __HAVE_ARCH_ENTER_LAZY_MMU_MODE

extern void flush_tlb_pending(void);
extern void arch_enter_lazy_mmu_mode(void);
extern void arch_leave_lazy_mmu_mode(void);
#define arch_flush_lazy_mmu_mode()      do {} while (0)

/* Local cpu only.  */
extern void __flush_tlb_all(void);
extern void __flush_tlb_page(unsigned long context, unsigned long vaddr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern void __flush_tlb_kernel_range(unsigned long start, unsigned long end);

#ifndef CONFIG_SMP

#define flush_tlb_kernel_range(start,end) \
do {	flush_tsb_kernel_range(start,end); \
	__flush_tlb_kernel_range(start,end); \
} while (0)

<<<<<<< HEAD
#else /* CONFIG_SMP */

extern void smp_flush_tlb_kernel_range(unsigned long start, unsigned long end);
=======
<<<<<<< HEAD
#else /* CONFIG_SMP */

extern void smp_flush_tlb_kernel_range(unsigned long start, unsigned long end);
=======
static inline void global_flush_tlb_page(struct mm_struct *mm, unsigned long vaddr)
{
	__flush_tlb_page(CTX_HWBITS(mm->context), vaddr);
}

#else /* CONFIG_SMP */

extern void smp_flush_tlb_kernel_range(unsigned long start, unsigned long end);
extern void smp_flush_tlb_page(struct mm_struct *mm, unsigned long vaddr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define flush_tlb_kernel_range(start, end) \
do {	flush_tsb_kernel_range(start,end); \
	smp_flush_tlb_kernel_range(start, end); \
} while (0)

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define global_flush_tlb_page(mm, vaddr) \
	smp_flush_tlb_page(mm, vaddr)

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* ! CONFIG_SMP */

#endif /* _SPARC64_TLBFLUSH_H */
