# Address where decompressor will be written and eventually executed.
#
# default to SDRAM
<<<<<<< HEAD
zreladdr-y      += $(CONFIG_BCM_ZRELADDR)
=======
zreladdr-y      := $(CONFIG_BCM_ZRELADDR)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
params_phys-y   := 0x00000800

