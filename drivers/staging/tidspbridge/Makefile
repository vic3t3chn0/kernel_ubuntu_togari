<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_TIDSPBRIDGE)	+= tidspbridge.o
=======
obj-$(CONFIG_TIDSPBRIDGE)	+= bridgedriver.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
obj-$(CONFIG_TIDSPBRIDGE)	+= bridgedriver.o
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

libgen = gen/gh.o gen/uuidutil.o
libcore = core/chnl_sm.o core/msg_sm.o core/io_sm.o core/tiomap3430.o \
		core/tiomap3430_pwr.o core/tiomap_io.o \
		core/ue_deh.o core/wdt.o core/dsp-clock.o core/sync.o
libpmgr = pmgr/chnl.o pmgr/io.o pmgr/msg.o pmgr/cod.o pmgr/dev.o pmgr/dspapi.o \
		pmgr/dmm.o pmgr/cmm.o pmgr/dbll.o
librmgr = rmgr/dbdcd.o rmgr/disp.o rmgr/drv.o rmgr/mgr.o rmgr/node.o \
		rmgr/proc.o rmgr/pwr.o rmgr/rmm.o rmgr/strm.o rmgr/dspdrv.o \
		rmgr/nldr.o rmgr/drv_interface.o
libdload = dynload/cload.o dynload/getsection.o dynload/reloc.o \
		 dynload/tramp.o
libhw = hw/hw_mmu.o

<<<<<<< HEAD
<<<<<<< HEAD
tidspbridge-y := $(libgen) $(libservices) $(libcore) $(libpmgr) $(librmgr) \
=======
bridgedriver-y := $(libgen) $(libservices) $(libcore) $(libpmgr) $(librmgr) \
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
bridgedriver-y := $(libgen) $(libservices) $(libcore) $(libpmgr) $(librmgr) \
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			$(libdload) $(libhw)

#Machine dependent
ccflags-y += -D_TI_ -D_DB_TIOMAP -DTMS32060 \
		-DTICFG_PROC_VER -DTICFG_EVM_TYPE -DCHNL_SMCLASS \
		-DCHNL_MESSAGES -DUSE_LEVEL_1_MACROS

ccflags-y += -Idrivers/staging/tidspbridge/include
ccflags-y += -Idrivers/staging/tidspbridge/services
ccflags-y += -Idrivers/staging/tidspbridge/core
ccflags-y += -Idrivers/staging/tidspbridge/pmgr
ccflags-y += -Idrivers/staging/tidspbridge/rmgr
ccflags-y += -Idrivers/staging/tidspbridge/dynload
ccflags-y += -Idrivers/staging/tidspbridge/hw
ccflags-y += -Iarch/arm

