__ZRELADDR	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_MEMORY_START) + 0x8000]')

<<<<<<< HEAD
   zreladdr-y   += $(__ZRELADDR)
=======
   zreladdr-y   := $(__ZRELADDR)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

# Unsupported legacy stuff
#
#params_phys-y (Instead: Pass atags pointer in r2)
#initrd_phys-y (Instead: Use compiled-in initramfs)
