<<<<<<< HEAD
<<<<<<< HEAD
tcm_fc-y +=		tfc_cmd.o \
			tfc_conf.o \
			tfc_io.o \
			tfc_sess.o

obj-$(CONFIG_TCM_FC)	+= tcm_fc.o
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
EXTRA_CFLAGS += -I$(srctree)/drivers/target/ \
		-I$(srctree)/drivers/scsi/ \
		-I$(srctree)/include/scsi/ \
		-I$(srctree)/drivers/target/tcm_fc/

tcm_fc-y +=	tfc_cmd.o \
		tfc_conf.o \
		tfc_io.o \
		tfc_sess.o

obj-$(CONFIG_TCM_FC)	+= tcm_fc.o

ifdef CONFIGFS_TCM_FC_DEBUG
EXTRA_CFLAGS	+= -DTCM_FC_DEBUG
endif
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
