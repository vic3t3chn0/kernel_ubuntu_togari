obj-$(CONFIG_RTLWIFI) 		+= rtlwifi.o
rtlwifi-objs	:=		\
		base.o		\
		cam.o		\
		core.o		\
		debug.o		\
		efuse.o		\
		ps.o		\
		rc.o		\
		regd.o

rtl8192c_common-objs +=		\

ifneq ($(CONFIG_PCI),)
rtlwifi-objs	+= pci.o
endif

ifneq ($(CONFIG_USB),)
rtlwifi-objs	+= usb.o
endif

obj-$(CONFIG_RTL8192C_COMMON)	+= rtl8192c/
obj-$(CONFIG_RTL8192CE)		+= rtl8192ce/
obj-$(CONFIG_RTL8192CU)		+= rtl8192cu/
obj-$(CONFIG_RTL8192SE)		+= rtl8192se/
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_RTL8192DE)		+= rtl8192de/
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

ccflags-y += -D__CHECK_ENDIAN__
