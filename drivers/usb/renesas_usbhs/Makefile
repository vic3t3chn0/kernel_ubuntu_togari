#
# for Renesas USB
#

obj-$(CONFIG_USB_RENESAS_USBHS)	+= renesas_usbhs.o

<<<<<<< HEAD
renesas_usbhs-y			:= common.o mod.o pipe.o fifo.o

ifneq ($(CONFIG_USB_RENESAS_USBHS_HCD),)
	renesas_usbhs-y		+= mod_host.o
endif

ifneq ($(CONFIG_USB_RENESAS_USBHS_UDC),)
	renesas_usbhs-y		+= mod_gadget.o
endif
=======
renesas_usbhs-y			:= common.o mod.o pipe.o

renesas_usbhs-$(CONFIG_USB_RENESAS_USBHS_UDC)	+= mod_gadget.o
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
