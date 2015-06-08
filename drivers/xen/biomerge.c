#include <linux/bio.h>
#include <linux/io.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <xen/page.h>

bool xen_biovec_phys_mergeable(const struct bio_vec *vec1,
			       const struct bio_vec *vec2)
{
	unsigned long mfn1 = pfn_to_mfn(page_to_pfn(vec1->bv_page));
	unsigned long mfn2 = pfn_to_mfn(page_to_pfn(vec2->bv_page));

	return __BIOVEC_PHYS_MERGEABLE(vec1, vec2) &&
		((mfn1 == mfn2) || ((mfn1+1) == mfn2));
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL(xen_biovec_phys_mergeable);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
