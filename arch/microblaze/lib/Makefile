#
# Makefile
#

ifdef CONFIG_FUNCTION_TRACER
CFLAGS_REMOVE_ashldi3.o = -pg
CFLAGS_REMOVE_ashrdi3.o = -pg
CFLAGS_REMOVE_lshrdi3.o = -pg
endif

lib-y :=  memset.o

ifeq ($(CONFIG_OPT_LIB_ASM),y)
lib-y += fastcopy.o
else
lib-y += memcpy.o memmove.o
endif

lib-y += uaccess_old.o

lib-y += ashldi3.o
lib-y += ashrdi3.o
<<<<<<< HEAD
lib-y += cmpdi2.o
=======
<<<<<<< HEAD
lib-y += cmpdi2.o
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
lib-y += divsi3.o
lib-y += lshrdi3.o
lib-y += modsi3.o
lib-y += muldi3.o
lib-y += mulsi3.o
<<<<<<< HEAD
lib-y += ucmpdi2.o
=======
<<<<<<< HEAD
lib-y += ucmpdi2.o
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
lib-y += udivsi3.o
lib-y += umodsi3.o
