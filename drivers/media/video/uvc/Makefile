uvcvideo-objs  := uvc_driver.o uvc_queue.o uvc_v4l2.o uvc_video.o uvc_ctrl.o \
<<<<<<< HEAD
		  uvc_status.o uvc_isight.o uvc_debugfs.o
=======
		  uvc_status.o uvc_isight.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
ifeq ($(CONFIG_MEDIA_CONTROLLER),y)
uvcvideo-objs  += uvc_entity.o
endif
obj-$(CONFIG_USB_VIDEO_CLASS) += uvcvideo.o
