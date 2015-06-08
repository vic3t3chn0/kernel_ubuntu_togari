<<<<<<< HEAD
<<<<<<< HEAD
AM_CPPFLAGS = -I$(top_srcdir)/libsrc -DUSBIDS_FILE='"@USBIDS_DIR@/usb.ids"'
AM_CFLAGS   = @EXTRA_CFLAGS@ @PACKAGE_CFLAGS@
LDADD       = $(top_builddir)/libsrc/libusbip.la @PACKAGE_LIBS@

sbin_PROGRAMS := usbip usbipd

usbip_SOURCES := usbip.c utils.c usbip_network.c \
		 usbip_attach.c usbip_detach.c usbip_list.c \
		 usbip_bind.c usbip_unbind.c

usbipd_SOURCES := usbipd.c usbip_network.c
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
AM_CPPFLAGS := -I$(top_srcdir)/libsrc -DUSBIDS_FILE='"@USBIDS_DIR@/usb.ids"'
AM_CFLAGS   := @EXTRA_CFLAGS@ @PACKAGE_CFLAGS@
LDADD       := $(top_srcdir)/libsrc/libusbip.la @PACKAGE_LIBS@

sbin_PROGRAMS := usbip usbipd usbip_bind_driver

usbip_SOURCES := usbip.c usbip_network.c usbip_network.h
usbipd_SOURCES := usbipd.c usbip_network.c usbip_network.h
usbip_bind_driver_SOURCES := bind-driver.c utils.c utils.h \
			     usbip_network.h usbip_network.c
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
