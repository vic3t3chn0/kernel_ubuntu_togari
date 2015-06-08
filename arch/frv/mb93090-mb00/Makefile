#
# Makefile for the MB93090-MB00 motherboard stuff
#

ifeq "$(CONFIG_PCI)" "y"
<<<<<<< HEAD
obj-y := pci-frv.o pci-irq.o pci-vdk.o
=======
<<<<<<< HEAD
obj-y := pci-frv.o pci-irq.o pci-vdk.o
=======
obj-y := pci-frv.o pci-irq.o pci-vdk.o pci-iomap.o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

ifeq "$(CONFIG_MMU)" "y"
obj-y += pci-dma.o
else
obj-y += pci-dma-nommu.o
endif
endif

obj-$(CONFIG_MTD) += flash.o
