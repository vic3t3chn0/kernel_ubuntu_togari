#
# Makefile for arch/m68knommu/platform/68328.
#

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
model-y			  := ram
model-$(CONFIG_ROMKERNEL) := rom

head-y			= head-$(model-y).o
<<<<<<< HEAD
=======
=======
head-y			= head-$(MODEL).o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
head-$(CONFIG_PILOT)	= head-pilot.o
head-$(CONFIG_DRAGEN2)	= head-de2.o

obj-y			+= entry.o ints.o timers.o
obj-$(CONFIG_M68328)	+= config.o
obj-$(CONFIG_ROM)	+= romvec.o

extra-y			:= head.o
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
extra-$(CONFIG_M68328)	+= bootlogo.rh head.o

$(obj)/bootlogo.rh: $(src)/bootlogo.h
	perl $(src)/bootlogo.pl < $(src)/bootlogo.h > $(obj)/bootlogo.rh
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

$(obj)/head.o: $(obj)/$(head-y)
	ln -sf $(head-y) $(obj)/head.o

<<<<<<< HEAD
clean-files := $(obj)/head.o $(head-y)
=======
<<<<<<< HEAD
clean-files := $(obj)/head.o $(head-y)
=======
clean-files := $(obj)/bootlogo.rh $(obj)/head.o $(head-y)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
