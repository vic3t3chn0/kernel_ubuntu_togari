ccflags-y := -Werror

obj-$(CONFIG_OPROFILE) += oprofile.o

DRIVER_OBJS = $(addprefix ../../../drivers/oprofile/, \
		oprof.o cpu_buffer.o buffer_sync.o \
		event_buffer.o oprofile_files.o \
		oprofilefs.o oprofile_stats.o \
		timer_int.o )

<<<<<<< HEAD
oprofile-y				:= $(DRIVER_OBJS) common.o backtrace.o
=======
<<<<<<< HEAD
oprofile-y				:= $(DRIVER_OBJS) common.o backtrace.o
=======
oprofile-y				:= $(DRIVER_OBJS) common.o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

oprofile-$(CONFIG_CPU_MIPS32)		+= op_model_mipsxx.o
oprofile-$(CONFIG_CPU_MIPS64)		+= op_model_mipsxx.o
oprofile-$(CONFIG_CPU_R10000)		+= op_model_mipsxx.o
oprofile-$(CONFIG_CPU_SB1)		+= op_model_mipsxx.o
oprofile-$(CONFIG_CPU_RM9000)		+= op_model_rm9000.o
oprofile-$(CONFIG_CPU_LOONGSON2)	+= op_model_loongson2.o
