ifeq ($(CONFIG_GEMINI_MEM_SWAP),y)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
   zreladdr-y	+= 0x00008000
params_phys-y	:= 0x00000100
initrd_phys-y	:= 0x00800000
else
   zreladdr-y	+= 0x10008000
<<<<<<< HEAD
=======
=======
   zreladdr-y	:= 0x00008000
params_phys-y	:= 0x00000100
initrd_phys-y	:= 0x00800000
else
   zreladdr-y	:= 0x10008000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
params_phys-y	:= 0x10000100
initrd_phys-y	:= 0x10800000
endif
