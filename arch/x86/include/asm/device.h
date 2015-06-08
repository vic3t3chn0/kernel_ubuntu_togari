#ifndef _ASM_X86_DEVICE_H
#define _ASM_X86_DEVICE_H

struct dev_archdata {
#ifdef CONFIG_ACPI
	void	*acpi_handle;
#endif
#ifdef CONFIG_X86_64
struct dma_map_ops *dma_ops;
#endif
<<<<<<< HEAD
#if defined(CONFIG_INTEL_IOMMU) || defined(CONFIG_AMD_IOMMU)
=======
<<<<<<< HEAD
#if defined(CONFIG_INTEL_IOMMU) || defined(CONFIG_AMD_IOMMU)
=======
#if defined(CONFIG_DMAR) || defined(CONFIG_AMD_IOMMU)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	void *iommu; /* hook for IOMMU specific extension */
#endif
};

struct pdev_archdata {
};

#endif /* _ASM_X86_DEVICE_H */
