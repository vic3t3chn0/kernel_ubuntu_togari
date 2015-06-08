#
# Makefile for the Linux/SuperH CPU-specifc backends.
#

obj-$(CONFIG_CPU_SH2)		= sh2/
obj-$(CONFIG_CPU_SH2A)		= sh2a/
obj-$(CONFIG_CPU_SH3)		= sh3/
obj-$(CONFIG_CPU_SH4)		= sh4/
obj-$(CONFIG_CPU_SH5)		= sh5/

# Special cases for family ancestry.

obj-$(CONFIG_CPU_SH4A)		+= sh4a/
obj-$(CONFIG_ARCH_SHMOBILE)	+= shmobile/

# Common interfaces.

obj-$(CONFIG_SH_ADC)		+= adc.o
obj-$(CONFIG_SH_CLK_CPG_LEGACY)	+= clock-cpg.o

<<<<<<< HEAD
obj-y	+= irq/ init.o clock.o fpu.o proc.o
=======
<<<<<<< HEAD
obj-y	+= irq/ init.o clock.o fpu.o proc.o
=======
obj-y	+= irq/ init.o clock.o fpu.o hwblk.o proc.o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
