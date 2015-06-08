ifeq ($(CONFIG_REALVIEW_HIGH_PHYS_OFFSET),y)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
   zreladdr-y	+= 0x70008000
params_phys-y	:= 0x70000100
initrd_phys-y	:= 0x70800000
else
   zreladdr-y	+= 0x00008000
<<<<<<< HEAD
=======
=======
   zreladdr-y	:= 0x70008000
params_phys-y	:= 0x70000100
initrd_phys-y	:= 0x70800000
else
   zreladdr-y	:= 0x00008000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
params_phys-y	:= 0x00000100
initrd_phys-y	:= 0x00800000
endif
