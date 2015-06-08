SUBDIRS := libsrc src
<<<<<<< HEAD
<<<<<<< HEAD
includedir = @includedir@/usbip
include_HEADERS := $(addprefix libsrc/, \
		     usbip_common.h vhci_driver.h usbip_host_driver.h)

dist_man_MANS := $(addprefix doc/, usbip.8 usbipd.8 usbip_bind_driver.8)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
includedir := @includedir@/usbip
include_HEADERS := $(addprefix libsrc/, \
		     usbip.h usbip_common.h vhci_driver.h stub_driver.h)

dist_man_MANS := $(addprefix doc/, usbip.8 usbipd.8 usbip_bind_driver.8)

if INSTALL_USBIDS
pkgdata_DATA := usb.ids
EXTRA_DIST := $(pkgdata_DATA)
endif
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
