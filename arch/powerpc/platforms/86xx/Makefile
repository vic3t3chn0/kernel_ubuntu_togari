#
# Makefile for the PowerPC 86xx linux kernel.
#

obj-y				:= pic.o
obj-$(CONFIG_SMP)		+= mpc86xx_smp.o
obj-$(CONFIG_MPC8641_HPCN)	+= mpc86xx_hpcn.o
obj-$(CONFIG_SBC8641D)		+= sbc8641d.o
obj-$(CONFIG_MPC8610_HPCD)	+= mpc8610_hpcd.o
<<<<<<< HEAD
obj-$(CONFIG_GEF_SBC610)	+= gef_sbc610.o
obj-$(CONFIG_GEF_SBC310)	+= gef_sbc310.o
obj-$(CONFIG_GEF_PPC9A)		+= gef_ppc9a.o
=======
<<<<<<< HEAD
obj-$(CONFIG_GEF_SBC610)	+= gef_sbc610.o
obj-$(CONFIG_GEF_SBC310)	+= gef_sbc310.o
obj-$(CONFIG_GEF_PPC9A)		+= gef_ppc9a.o
=======
gef-gpio-$(CONFIG_GPIOLIB)	+= gef_gpio.o
obj-$(CONFIG_GEF_SBC610)	+= gef_sbc610.o gef_pic.o $(gef-gpio-y)
obj-$(CONFIG_GEF_SBC310)	+= gef_sbc310.o gef_pic.o $(gef-gpio-y)
obj-$(CONFIG_GEF_PPC9A)		+= gef_ppc9a.o gef_pic.o $(gef-gpio-y)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
