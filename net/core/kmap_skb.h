#include <linux/highmem.h>

static inline void *kmap_skb_frag(const skb_frag_t *frag)
{
#ifdef CONFIG_HIGHMEM
	BUG_ON(in_irq());

	local_bh_disable();
#endif
<<<<<<< HEAD
	return kmap_atomic(skb_frag_page(frag));
=======
<<<<<<< HEAD
	return kmap_atomic(skb_frag_page(frag));
=======
	return kmap_atomic(frag->page, KM_SKB_DATA_SOFTIRQ);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static inline void kunmap_skb_frag(void *vaddr)
{
<<<<<<< HEAD
	kunmap_atomic(vaddr);
=======
<<<<<<< HEAD
	kunmap_atomic(vaddr);
=======
	kunmap_atomic(vaddr, KM_SKB_DATA_SOFTIRQ);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_HIGHMEM
	local_bh_enable();
#endif
}
