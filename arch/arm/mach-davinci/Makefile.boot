ifeq ($(CONFIG_ARCH_DAVINCI_DA8XX),y)
ifeq ($(CONFIG_ARCH_DAVINCI_DMx),y)
$(error Cannot enable DaVinci and DA8XX platforms concurrently)
else
<<<<<<< HEAD
   zreladdr-y	+= 0xc0008000
=======
   zreladdr-y	:= 0xc0008000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
params_phys-y	:= 0xc0000100
initrd_phys-y	:= 0xc0800000
endif
else
<<<<<<< HEAD
   zreladdr-y	+= 0x80008000
=======
   zreladdr-y	:= 0x80008000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
params_phys-y	:= 0x80000100
initrd_phys-y	:= 0x80800000
endif
