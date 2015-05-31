#
# Makefile for arch/m68knommu/platform/68VZ328.
#

obj-y		:= config.o
<<<<<<< HEAD
extra-$(DRAGEN2):= screen.h
=======
logo-$(UCDIMM)	:= bootlogo.rh
logo-$(DRAGEN2)	:= screen.h
extra-y		:= $(logo-y)

$(obj)/bootlogo.rh: $(src)/../68EZ328/bootlogo.h
	perl $(src)/bootlogo.pl < $(src)/../68328/bootlogo.h > $(obj)/bootlogo.rh
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

$(obj)/screen.h: $(src)/screen.xbm $(src)/xbm2lcd.pl
	perl $(src)/xbm2lcd.pl < $(src)/screen.xbm > $(obj)/screen.h

<<<<<<< HEAD
clean-files := $(obj)/screen.h
=======
clean-files := $(obj)/screen.h $(obj)/bootlogo.rh
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
