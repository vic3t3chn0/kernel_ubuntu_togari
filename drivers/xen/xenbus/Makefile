obj-y	+= xenbus.o
<<<<<<< HEAD
obj-y	+= xenbus_dev_frontend.o
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

xenbus-objs =
xenbus-objs += xenbus_client.o
xenbus-objs += xenbus_comms.o
xenbus-objs += xenbus_xs.o
xenbus-objs += xenbus_probe.o

xenbus-be-objs-$(CONFIG_XEN_BACKEND) += xenbus_probe_backend.o
xenbus-objs += $(xenbus-be-objs-y)

<<<<<<< HEAD
obj-$(CONFIG_XEN_BACKEND) += xenbus_dev_backend.o
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
obj-$(CONFIG_XEN_XENBUS_FRONTEND) += xenbus_probe_frontend.o
