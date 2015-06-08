<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
# Those numbers are used only by the non-DT V2P-CA9 platform
# The DT-enabled ones require CONFIG_AUTO_ZRELADDR=y
   zreladdr-y	+= 0x60008000
params_phys-y	:= 0x60000100
initrd_phys-y	:= 0x60800000

dtb-$(CONFIG_ARCH_VEXPRESS_DT)	+= vexpress-v2p-ca5s.dtb \
				   vexpress-v2p-ca9.dtb \
				   vexpress-v2p-ca15-tc1.dtb
<<<<<<< HEAD
=======
=======
   zreladdr-y	:= 0x60008000
params_phys-y	:= 0x60000100
initrd_phys-y	:= 0x60800000
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
