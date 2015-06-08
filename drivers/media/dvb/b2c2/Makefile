b2c2-flexcop-objs = flexcop.o flexcop-fe-tuner.o flexcop-i2c.o \
	flexcop-sram.o flexcop-eeprom.o flexcop-misc.o flexcop-hw-filter.o
obj-$(CONFIG_DVB_B2C2_FLEXCOP) += b2c2-flexcop.o

ifneq ($(CONFIG_DVB_B2C2_FLEXCOP_PCI),)
b2c2-flexcop-objs += flexcop-dma.o
endif

b2c2-flexcop-pci-objs = flexcop-pci.o
obj-$(CONFIG_DVB_B2C2_FLEXCOP_PCI) += b2c2-flexcop-pci.o

b2c2-flexcop-usb-objs = flexcop-usb.o
obj-$(CONFIG_DVB_B2C2_FLEXCOP_USB) += b2c2-flexcop-usb.o

<<<<<<< HEAD
<<<<<<< HEAD
ccflags-y += -Idrivers/media/dvb/dvb-core/ -Idrivers/media/dvb/frontends/
ccflags-y += -Idrivers/media/common/tuners/
=======
EXTRA_CFLAGS += -Idrivers/media/dvb/dvb-core/ -Idrivers/media/dvb/frontends/
EXTRA_CFLAGS += -Idrivers/media/common/tuners/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
EXTRA_CFLAGS += -Idrivers/media/dvb/dvb-core/ -Idrivers/media/dvb/frontends/
EXTRA_CFLAGS += -Idrivers/media/common/tuners/
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
