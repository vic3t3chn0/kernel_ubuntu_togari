#ifndef __ASM_SH_DMA_MAPPING_H
#define __ASM_SH_DMA_MAPPING_H

extern struct dma_map_ops *dma_ops;
extern void no_iommu_init(void);

static inline struct dma_map_ops *get_dma_ops(struct device *dev)
{
	return dma_ops;
}

#include <asm-generic/dma-coherent.h>
#include <asm-generic/dma-mapping-common.h>

static inline int dma_supported(struct device *dev, u64 mask)
{
	struct dma_map_ops *ops = get_dma_ops(dev);

	if (ops->dma_supported)
		return ops->dma_supported(dev, mask);

	return 1;
}

static inline int dma_set_mask(struct device *dev, u64 mask)
{
	struct dma_map_ops *ops = get_dma_ops(dev);

	if (!dev->dma_mask || !dma_supported(dev, mask))
		return -EIO;
	if (ops->set_dma_mask)
		return ops->set_dma_mask(dev, mask);

	*dev->dma_mask = mask;

	return 0;
}

void dma_cache_sync(struct device *dev, void *vaddr, size_t size,
		    enum dma_data_direction dir);

#define dma_alloc_noncoherent(d, s, h, f) dma_alloc_coherent(d, s, h, f)
#define dma_free_noncoherent(d, s, v, h) dma_free_coherent(d, s, v, h)

static inline int dma_mapping_error(struct device *dev, dma_addr_t dma_addr)
{
	struct dma_map_ops *ops = get_dma_ops(dev);

	if (ops->mapping_error)
		return ops->mapping_error(dev, dma_addr);

	return dma_addr == 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define dma_alloc_coherent(d,s,h,f)	dma_alloc_attrs(d,s,h,f,NULL)

static inline void *dma_alloc_attrs(struct device *dev, size_t size,
				    dma_addr_t *dma_handle, gfp_t gfp,
				    struct dma_attrs *attrs)
<<<<<<< HEAD
=======
=======
static inline void *dma_alloc_coherent(struct device *dev, size_t size,
				       dma_addr_t *dma_handle, gfp_t gfp)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct dma_map_ops *ops = get_dma_ops(dev);
	void *memory;

	if (dma_alloc_from_coherent(dev, size, dma_handle, &memory))
		return memory;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!ops->alloc)
		return NULL;

	memory = ops->alloc(dev, size, dma_handle, gfp, attrs);
<<<<<<< HEAD
=======
=======
	if (!ops->alloc_coherent)
		return NULL;

	memory = ops->alloc_coherent(dev, size, dma_handle, gfp);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	debug_dma_alloc_coherent(dev, size, *dma_handle, memory);

	return memory;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define dma_free_coherent(d,s,c,h) dma_free_attrs(d,s,c,h,NULL)

static inline void dma_free_attrs(struct device *dev, size_t size,
				  void *vaddr, dma_addr_t dma_handle,
				  struct dma_attrs *attrs)
<<<<<<< HEAD
=======
=======
static inline void dma_free_coherent(struct device *dev, size_t size,
				     void *vaddr, dma_addr_t dma_handle)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_release_from_coherent(dev, get_order(size), vaddr))
		return;

	debug_dma_free_coherent(dev, size, vaddr, dma_handle);
<<<<<<< HEAD
	if (ops->free)
		ops->free(dev, size, vaddr, dma_handle, attrs);
=======
<<<<<<< HEAD
	if (ops->free)
		ops->free(dev, size, vaddr, dma_handle, attrs);
=======
	if (ops->free_coherent)
		ops->free_coherent(dev, size, vaddr, dma_handle);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/* arch/sh/mm/consistent.c */
extern void *dma_generic_alloc_coherent(struct device *dev, size_t size,
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					dma_addr_t *dma_addr, gfp_t flag,
					struct dma_attrs *attrs);
extern void dma_generic_free_coherent(struct device *dev, size_t size,
				      void *vaddr, dma_addr_t dma_handle,
				      struct dma_attrs *attrs);
<<<<<<< HEAD
=======
=======
					dma_addr_t *dma_addr, gfp_t flag);
extern void dma_generic_free_coherent(struct device *dev, size_t size,
				      void *vaddr, dma_addr_t dma_handle);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __ASM_SH_DMA_MAPPING_H */
