<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
   zreladdr-y	+= 0x48008000
params_phys-y	:= 0x48000100
# This isn't used.
#initrd_phys-y	:= 0x48800000
<<<<<<< HEAD
=======
=======
# Note: the following conditions must always be true:
#   ZRELADDR == virt_to_phys(TEXTADDR)
#   PARAMS_PHYS must be within 4MB of ZRELADDR
#   INITRD_PHYS must be in RAM

ifdef CONFIG_MACH_U300_SINGLE_RAM
     zreladdr-y	:= 0x28E08000
  params_phys-y	:= 0x28E00100
else
     zreladdr-y	:= 0x48008000
  params_phys-y	:= 0x48000100
endif

# This isn't used.
#initrd_phys-y	:= 0x29800000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
