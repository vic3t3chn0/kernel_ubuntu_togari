#
# Makefile for the drm device driver.  This driver provides support for the
# Direct Rendering Infrastructure (DRI) in XFree86 4.1.0 and higher.

ccflags-y := -Iinclude/drm

drm-y       :=	drm_auth.o drm_buffer.o drm_bufs.o drm_cache.o \
		drm_context.o drm_dma.o \
		drm_drv.o drm_fops.o drm_gem.o drm_ioctl.o drm_irq.o \
		drm_lock.o drm_memory.o drm_proc.o drm_stub.o drm_vm.o \
		drm_agpsupport.o drm_scatter.o ati_pcigart.o drm_pci.o \
		drm_platform.o drm_sysfs.o drm_hashtab.o drm_mm.o \
		drm_crtc.o drm_modes.o drm_edid.o \
		drm_info.o drm_debugfs.o drm_encoder_slave.o \
<<<<<<< HEAD
<<<<<<< HEAD
		drm_trace_points.o drm_global.o drm_prime.o
=======
		drm_trace_points.o drm_global.o drm_prime.o drm_backlight.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		drm_trace_points.o drm_global.o drm_prime.o drm_backlight.o
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

drm-$(CONFIG_COMPAT) += drm_ioc32.o

drm-usb-y   := drm_usb.o

drm_kms_helper-y := drm_fb_helper.o drm_crtc_helper.o drm_dp_i2c_helper.o
drm_kms_helper-$(CONFIG_DRM_LOAD_EDID_FIRMWARE) += drm_edid_load.o

obj-$(CONFIG_DRM_KMS_HELPER) += drm_kms_helper.o

CFLAGS_drm_trace_points.o := -I$(src)

obj-$(CONFIG_DRM)	+= drm.o
obj-$(CONFIG_DRM_USB)   += drm_usb.o
obj-$(CONFIG_DRM_TTM)	+= ttm/
obj-$(CONFIG_DRM_TDFX)	+= tdfx/
obj-$(CONFIG_DRM_R128)	+= r128/
obj-$(CONFIG_DRM_RADEON)+= radeon/
obj-$(CONFIG_DRM_MGA)	+= mga/
obj-$(CONFIG_DRM_I810)	+= i810/
obj-$(CONFIG_DRM_I915)  += i915/
obj-$(CONFIG_DRM_SIS)   += sis/
obj-$(CONFIG_DRM_SAVAGE)+= savage/
obj-$(CONFIG_DRM_VMWGFX)+= vmwgfx/
obj-$(CONFIG_DRM_VIA)	+=via/
obj-$(CONFIG_DRM_NOUVEAU) +=nouveau/
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_DRM_EXYNOS) +=exynos/
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
ifeq ($(CONFIG_NAPLES_COMMON),y)
else
obj-$(CONFIG_DRM_EXYNOS) +=exynos/
endif
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_DRM_GMA500) += gma500/
obj-$(CONFIG_DRM_UDL) += udl/
obj-y			+= i2c/
