#
# Makefile for the kernel mmc core.
#

obj-$(CONFIG_MMC)		+= mmc_core.o
mmc_core-y			:= core.o bus.o host.o \
				   mmc.o mmc_ops.o sd.o sd_ops.o \
				   sdio.o sdio_ops.o sdio_bus.o \
				   sdio_cis.o sdio_io.o sdio_irq.o \
<<<<<<< HEAD
<<<<<<< HEAD
				   quirks.o cd-gpio.o
=======
				   quirks.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				   quirks.o
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

mmc_core-$(CONFIG_DEBUG_FS)	+= debugfs.o
