# The standard locations for stuff on CLPS711x type processors
<<<<<<< HEAD
   zreladdr-y				+= 0xc0028000
=======
<<<<<<< HEAD
   zreladdr-y				+= 0xc0028000
=======
   zreladdr-y				:= 0xc0028000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
params_phys-y				:= 0xc0000100
# Should probably have some agreement on these...
initrd_phys-$(CONFIG_ARCH_P720T)	:= 0xc0400000
initrd_phys-$(CONFIG_ARCH_CDB89712)	:= 0x00700000
