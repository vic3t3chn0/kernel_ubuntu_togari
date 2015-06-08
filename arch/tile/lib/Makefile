#
# Makefile for TILE-specific library files..
#

lib-y = cacheflush.o checksum.o cpumask.o delay.o uaccess.o \
	memmove.o memcpy_$(BITS).o memchr_$(BITS).o memset_$(BITS).o \
	strchr_$(BITS).o strlen_$(BITS).o

ifeq ($(CONFIG_TILEGX),y)
<<<<<<< HEAD
CFLAGS_REMOVE_memcpy_user_64.o = -fno-omit-frame-pointer
=======
<<<<<<< HEAD
CFLAGS_REMOVE_memcpy_user_64.o = -fno-omit-frame-pointer
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
lib-y += memcpy_user_64.o
else
lib-y += atomic_32.o atomic_asm_32.o memcpy_tile64.o
endif

lib-$(CONFIG_SMP) += spinlock_$(BITS).o usercopy_$(BITS).o

obj-$(CONFIG_MODULES) += exports.o
