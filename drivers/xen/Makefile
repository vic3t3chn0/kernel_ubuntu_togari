obj-y	+= grant-table.o features.o events.o manage.o balloon.o
obj-y	+= xenbus/
<<<<<<< HEAD
<<<<<<< HEAD
=======
obj-y	+= tmem.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
obj-y	+= tmem.o
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

nostackp := $(call cc-option, -fno-stack-protector)
CFLAGS_features.o			:= $(nostackp)

obj-$(CONFIG_BLOCK)			+= biomerge.o
obj-$(CONFIG_HOTPLUG_CPU)		+= cpu_hotplug.o
obj-$(CONFIG_XEN_XENCOMM)		+= xencomm.o
obj-$(CONFIG_XEN_BALLOON)		+= xen-balloon.o
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_XEN_SELFBALLOONING)	+= xen-selfballoon.o
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_XEN_DEV_EVTCHN)		+= xen-evtchn.o
obj-$(CONFIG_XEN_GNTDEV)		+= xen-gntdev.o
obj-$(CONFIG_XEN_GRANT_DEV_ALLOC)	+= xen-gntalloc.o
obj-$(CONFIG_XENFS)			+= xenfs/
obj-$(CONFIG_XEN_SYS_HYPERVISOR)	+= sys-hypervisor.o
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_XEN_PVHVM)			+= platform-pci.o
obj-$(CONFIG_XEN_TMEM)			+= tmem.o
obj-$(CONFIG_SWIOTLB_XEN)		+= swiotlb-xen.o
obj-$(CONFIG_XEN_DOM0)			+= pci.o
obj-$(CONFIG_XEN_PCIDEV_BACKEND)	+= xen-pciback/
obj-$(CONFIG_XEN_PRIVCMD)		+= xen-privcmd.o
obj-$(CONFIG_XEN_ACPI_PROCESSOR)	+= xen-acpi-processor.o
xen-evtchn-y				:= evtchn.o
xen-gntdev-y				:= gntdev.o
xen-gntalloc-y				:= gntalloc.o
xen-privcmd-y				:= privcmd.o
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_XEN_PLATFORM_PCI)		+= xen-platform-pci.o
obj-$(CONFIG_SWIOTLB_XEN)		+= swiotlb-xen.o
obj-$(CONFIG_XEN_DOM0)			+= pci.o

xen-evtchn-y				:= evtchn.o
xen-gntdev-y				:= gntdev.o
xen-gntalloc-y				:= gntalloc.o

xen-platform-pci-y			:= platform-pci.o
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
