obj-$(CONFIG_OPROFILE) += oprofile.o

DRIVER_OBJS = $(addprefix ../../../drivers/oprofile/, \
		oprof.o cpu_buffer.o buffer_sync.o \
		event_buffer.o oprofile_files.o \
		oprofilefs.o oprofile_stats.o  \
<<<<<<< HEAD
		timer_int.o nmi_timer_int.o )
=======
<<<<<<< HEAD
		timer_int.o nmi_timer_int.o )
=======
		timer_int.o )
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

oprofile-y				:= $(DRIVER_OBJS) init.o backtrace.o
oprofile-$(CONFIG_X86_LOCAL_APIC) 	+= nmi_int.o op_model_amd.o \
					   op_model_ppro.o op_model_p4.o
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
oprofile-$(CONFIG_X86_IO_APIC)		+= nmi_timer_int.o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
