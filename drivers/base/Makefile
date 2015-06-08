# Makefile for the Linux device tree

<<<<<<< HEAD
<<<<<<< HEAD
obj-y			:= core.o bus.o dd.o syscore.o \
			   driver.o class.o platform.o \
			   cpu.o firmware.o init.o map.o devres.o \
			   attribute_container.o transport_class.o \
			   topology.o sys.o
obj-$(CONFIG_DEVTMPFS)	+= devtmpfs.o
obj-$(CONFIG_CMA) += dma-contiguous.o
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-y			:= core.o sys.o bus.o dd.o syscore.o \
			   driver.o class.o platform.o \
			   cpu.o firmware.o init.o map.o devres.o \
			   attribute_container.o transport_class.o
obj-$(CONFIG_DEVTMPFS)	+= devtmpfs.o
obj-$(CONFIG_DMA_CMA)	+= dma-contiguous.o
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-y			+= power/
obj-$(CONFIG_HAS_DMA)	+= dma-mapping.o
obj-$(CONFIG_HAVE_GENERIC_DMA_COHERENT) += dma-coherent.o
obj-$(CONFIG_DMA_SHARED_BUFFER) += dma-buf.o
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_GENLOCK) += genlock.o
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_ISA)	+= isa.o
obj-$(CONFIG_FW_LOADER)	+= firmware_class.o
obj-$(CONFIG_NUMA)	+= node.o
obj-$(CONFIG_MEMORY_HOTPLUG_SPARSE) += memory.o
<<<<<<< HEAD
<<<<<<< HEAD
=======
obj-$(CONFIG_SMP)	+= topology.o
obj-$(CONFIG_IOMMU_EXYNOS4_API) += s5p-iommu.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
obj-$(CONFIG_SMP)	+= topology.o
obj-$(CONFIG_IOMMU_EXYNOS4_API) += s5p-iommu.o
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
ifeq ($(CONFIG_SYSFS),y)
obj-$(CONFIG_MODULES)	+= module.o
endif
obj-$(CONFIG_SYS_HYPERVISOR) += hypervisor.o
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_REGMAP)	+= regmap/
obj-$(CONFIG_SOC_BUS) += soc.o
obj-$(CONFIG_PINCTRL) += pinctrl.o
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

obj-$(CONFIG_SYNC)	+= sync.o
obj-$(CONFIG_SW_SYNC)	+= sw_sync.o

ccflags-$(CONFIG_DEBUG_DRIVER) := -DDEBUG

