<<<<<<< HEAD
<<<<<<< HEAD
ccflags-y := -Idrivers/net/ethernet/chelsio/cxgb3
=======
ccflags-y := -Idrivers/net/cxgb3
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
ccflags-y := -Idrivers/net/cxgb3
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

obj-$(CONFIG_INFINIBAND_CXGB3) += iw_cxgb3.o

iw_cxgb3-y :=  iwch_cm.o iwch_ev.o iwch_cq.o iwch_qp.o iwch_mem.o \
	       iwch_provider.o iwch.o cxio_hal.o cxio_resource.o

ccflags-$(CONFIG_INFINIBAND_CXGB3_DEBUG) += -DDEBUG
