#
#  Makefile for the Linux Controller Area Network drivers.
#

obj-$(CONFIG_CAN_VCAN)		+= vcan.o
obj-$(CONFIG_CAN_SLCAN)		+= slcan.o

obj-$(CONFIG_CAN_DEV)		+= can-dev.o
can-dev-y			:= dev.o

obj-y				+= usb/
obj-y				+= softing/

obj-$(CONFIG_CAN_SJA1000)	+= sja1000/
obj-$(CONFIG_CAN_MSCAN)		+= mscan/
obj-$(CONFIG_CAN_C_CAN)		+= c_can/
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_CAN_CC770)		+= cc770/
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_CAN_AT91)		+= at91_can.o
obj-$(CONFIG_CAN_TI_HECC)	+= ti_hecc.o
obj-$(CONFIG_CAN_MCP251X)	+= mcp251x.o
obj-$(CONFIG_CAN_BFIN)		+= bfin_can.o
obj-$(CONFIG_CAN_JANZ_ICAN3)	+= janz-ican3.o
obj-$(CONFIG_CAN_FLEXCAN)	+= flexcan.o
obj-$(CONFIG_PCH_CAN)		+= pch_can.o

ccflags-$(CONFIG_CAN_DEBUG_DEVICES) := -DDEBUG
