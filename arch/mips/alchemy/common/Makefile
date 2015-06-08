#
#  Copyright 2000, 2008 MontaVista Software Inc.
#  Author: MontaVista Software, Inc. <source@mvista.com>
#
# Makefile for the Alchemy Au1xx0 CPUs, generic files.
#

obj-y += prom.o time.o clocks.o platform.o power.o setup.o \
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	sleeper.o dma.o dbdma.o vss.o irq.o

# optional gpiolib support
ifeq ($(CONFIG_ALCHEMY_GPIO_INDIRECT),)
 obj-$(CONFIG_GPIOLIB) += gpiolib.o
endif
<<<<<<< HEAD
=======
=======
	sleeper.o dma.o dbdma.o

obj-$(CONFIG_ALCHEMY_GPIOINT_AU1000) += irq.o

# optional gpiolib support
ifeq ($(CONFIG_ALCHEMY_GPIO_INDIRECT),)
 ifeq ($(CONFIG_GPIOLIB),y)
  obj-$(CONFIG_ALCHEMY_GPIOINT_AU1000) += gpiolib-au1000.o
 endif
endif

obj-$(CONFIG_PCI)		+= pci.o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
