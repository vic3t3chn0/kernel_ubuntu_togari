#
# S/390 crypto devices
#

<<<<<<< HEAD
ap-objs := ap_bus.o
obj-$(CONFIG_ZCRYPT) += ap.o zcrypt_api.o zcrypt_pcicc.o zcrypt_pcixcc.o
obj-$(CONFIG_ZCRYPT) += zcrypt_pcica.o zcrypt_cex2a.o
=======
ifdef CONFIG_ZCRYPT_MONOLITHIC

z90crypt-objs := zcrypt_mono.o ap_bus.o zcrypt_api.o \
		zcrypt_pcica.o zcrypt_pcicc.o zcrypt_pcixcc.o zcrypt_cex2a.o
obj-$(CONFIG_ZCRYPT) += z90crypt.o

else

ap-objs := ap_bus.o
obj-$(CONFIG_ZCRYPT) += ap.o zcrypt_api.o zcrypt_pcicc.o zcrypt_pcixcc.o
obj-$(CONFIG_ZCRYPT) += zcrypt_pcica.o zcrypt_cex2a.o

endif
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
