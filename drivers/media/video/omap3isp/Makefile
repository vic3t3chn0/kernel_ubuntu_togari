# Makefile for OMAP3 ISP driver

<<<<<<< HEAD
<<<<<<< HEAD
ccflags-$(CONFIG_VIDEO_OMAP3_DEBUG) += -DDEBUG
=======
ifdef CONFIG_VIDEO_OMAP3_DEBUG
EXTRA_CFLAGS += -DDEBUG
endif
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
ifdef CONFIG_VIDEO_OMAP3_DEBUG
EXTRA_CFLAGS += -DDEBUG
endif
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

omap3-isp-objs += \
	isp.o ispqueue.o ispvideo.o \
	ispcsiphy.o ispccp2.o ispcsi2.o \
	ispccdc.o isppreview.o ispresizer.o \
	ispstat.o isph3a_aewb.o isph3a_af.o isphist.o

obj-$(CONFIG_VIDEO_OMAP3) += omap3-isp.o
