
saa7134-y :=	saa7134-cards.o saa7134-core.o saa7134-i2c.o
saa7134-y +=	saa7134-ts.o saa7134-tvaudio.o saa7134-vbi.o
saa7134-y +=	saa7134-video.o
saa7134-$(CONFIG_VIDEO_SAA7134_RC) += saa7134-input.o

obj-$(CONFIG_VIDEO_SAA7134) +=  saa6752hs.o saa7134.o saa7134-empress.o

obj-$(CONFIG_VIDEO_SAA7134_ALSA) += saa7134-alsa.o

obj-$(CONFIG_VIDEO_SAA7134_DVB) += saa7134-dvb.o

<<<<<<< HEAD
<<<<<<< HEAD
ccflags-y += -I$(srctree)/drivers/media/video
ccflags-y += -I$(srctree)/drivers/media/common/tuners
ccflags-y += -I$(srctree)/drivers/media/dvb/dvb-core
ccflags-y += -I$(srctree)/drivers/media/dvb/frontends
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
EXTRA_CFLAGS += -Idrivers/media/video
EXTRA_CFLAGS += -Idrivers/media/common/tuners
EXTRA_CFLAGS += -Idrivers/media/dvb/dvb-core
EXTRA_CFLAGS += -Idrivers/media/dvb/frontends
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
