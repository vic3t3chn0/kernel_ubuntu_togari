<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
ifeq ($(CONFIG_SA1111),y)
   zreladdr-y	+= 0xc0208000
else
   zreladdr-y	+= 0xc0008000
<<<<<<< HEAD
=======
=======
   zreladdr-y	:= 0xc0008000
ifeq ($(CONFIG_ARCH_SA1100),y)
   zreladdr-$(CONFIG_SA1111)		:= 0xc0208000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
endif
params_phys-y	:= 0xc0000100
initrd_phys-y	:= 0xc0800000

