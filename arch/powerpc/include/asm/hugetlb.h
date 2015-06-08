#ifndef _ASM_POWERPC_HUGETLB_H
#define _ASM_POWERPC_HUGETLB_H

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_HUGETLB_PAGE
#include <asm/page.h>

extern struct kmem_cache *hugepte_cache;

static inline pte_t *hugepd_page(hugepd_t hpd)
{
	BUG_ON(!hugepd_ok(hpd));
	return (pte_t *)((hpd.pd & ~HUGEPD_SHIFT_MASK) | PD_HUGE);
}

static inline unsigned int hugepd_shift(hugepd_t hpd)
{
	return hpd.pd & HUGEPD_SHIFT_MASK;
}

static inline pte_t *hugepte_offset(hugepd_t *hpdp, unsigned long addr,
				    unsigned pdshift)
{
	/*
	 * On FSL BookE, we have multiple higher-level table entries that
	 * point to the same hugepte.  Just use the first one since they're all
	 * identical.  So for that case, idx=0.
	 */
	unsigned long idx = 0;

	pte_t *dir = hugepd_page(*hpdp);
#ifndef CONFIG_PPC_FSL_BOOK3E
	idx = (addr & ((1UL << pdshift) - 1)) >> hugepd_shift(*hpdp);
#endif

	return dir + idx;
}

<<<<<<< HEAD
=======
=======
#include <asm/page.h>

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
pte_t *huge_pte_offset_and_shift(struct mm_struct *mm,
				 unsigned long addr, unsigned *shift);

void flush_dcache_icache_hugepage(struct page *page);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#if defined(CONFIG_PPC_MM_SLICES) || defined(CONFIG_PPC_SUBPAGE_PROT)
int is_hugepage_only_range(struct mm_struct *mm, unsigned long addr,
			   unsigned long len);
#else
static inline int is_hugepage_only_range(struct mm_struct *mm,
					 unsigned long addr,
					 unsigned long len)
{
	return 0;
}
#endif

void book3e_hugetlb_preload(struct vm_area_struct *vma, unsigned long ea,
			    pte_t pte);
void flush_hugetlb_page(struct vm_area_struct *vma, unsigned long vmaddr);
<<<<<<< HEAD
=======
=======
int is_hugepage_only_range(struct mm_struct *mm, unsigned long addr,
			   unsigned long len);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void hugetlb_free_pgd_range(struct mmu_gather *tlb, unsigned long addr,
			    unsigned long end, unsigned long floor,
			    unsigned long ceiling);

/*
 * The version of vma_mmu_pagesize() in arch/powerpc/mm/hugetlbpage.c needs
 * to override the version in mm/hugetlb.c
 */
#define vma_mmu_pagesize vma_mmu_pagesize

/*
 * If the arch doesn't supply something else, assume that hugepage
 * size aligned regions are ok without further preparation.
 */
static inline int prepare_hugepage_range(struct file *file,
			unsigned long addr, unsigned long len)
{
	struct hstate *h = hstate_file(file);
	if (len & ~huge_page_mask(h))
		return -EINVAL;
	if (addr & ~huge_page_mask(h))
		return -EINVAL;
	return 0;
}

static inline void hugetlb_prefault_arch_hook(struct mm_struct *mm)
{
}


static inline void set_huge_pte_at(struct mm_struct *mm, unsigned long addr,
				   pte_t *ptep, pte_t pte)
{
	set_pte_at(mm, addr, ptep, pte);
}

static inline pte_t huge_ptep_get_and_clear(struct mm_struct *mm,
					    unsigned long addr, pte_t *ptep)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_PPC64
	return __pte(pte_update(mm, addr, ptep, ~0UL, 1));
#else
	return __pte(pte_update(ptep, ~0UL, 0));
#endif
<<<<<<< HEAD
=======
=======
	unsigned long old = pte_update(mm, addr, ptep, ~0UL, 1);
	return __pte(old);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static inline void huge_ptep_clear_flush(struct vm_area_struct *vma,
					 unsigned long addr, pte_t *ptep)
{
	pte_t pte;
	pte = huge_ptep_get_and_clear(vma->vm_mm, addr, ptep);
	flush_tlb_page(vma, addr);
}

static inline int huge_pte_none(pte_t pte)
{
	return pte_none(pte);
}

static inline pte_t huge_pte_wrprotect(pte_t pte)
{
	return pte_wrprotect(pte);
}

static inline int huge_ptep_set_access_flags(struct vm_area_struct *vma,
					     unsigned long addr, pte_t *ptep,
					     pte_t pte, int dirty)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef HUGETLB_NEED_PRELOAD
	/*
	 * The "return 1" forces a call of update_mmu_cache, which will write a
	 * TLB entry.  Without this, platforms that don't do a write of the TLB
	 * entry in the TLB miss handler asm will fault ad infinitum.
	 */
	ptep_set_access_flags(vma, addr, ptep, pte, dirty);
	return 1;
#else
	return ptep_set_access_flags(vma, addr, ptep, pte, dirty);
#endif
<<<<<<< HEAD
=======
=======
	return ptep_set_access_flags(vma, addr, ptep, pte, dirty);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static inline pte_t huge_ptep_get(pte_t *ptep)
{
	return *ptep;
}

static inline int arch_prepare_hugepage(struct page *page)
{
	return 0;
}

static inline void arch_release_hugepage(struct page *page)
{
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#else /* ! CONFIG_HUGETLB_PAGE */
static inline void flush_hugetlb_page(struct vm_area_struct *vma,
				      unsigned long vmaddr)
{
}
#endif /* CONFIG_HUGETLB_PAGE */


/*
 * FSL Book3E platforms require special gpage handling - the gpages
 * are reserved early in the boot process by memblock instead of via
 * the .dts as on IBM platforms.
 */
#if defined(CONFIG_HUGETLB_PAGE) && defined(CONFIG_PPC_FSL_BOOK3E)
extern void __init reserve_hugetlb_gpages(void);
#else
static inline void reserve_hugetlb_gpages(void)
{
}
#endif

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* _ASM_POWERPC_HUGETLB_H */
