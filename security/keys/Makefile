#
# Makefile for key management
#

obj-y := \
	gc.o \
	key.o \
	keyring.o \
	keyctl.o \
	permission.o \
	process_keys.o \
	request_key.o \
	request_key_auth.o \
	user_defined.o

obj-$(CONFIG_TRUSTED_KEYS) += trusted.o
<<<<<<< HEAD
obj-$(CONFIG_ENCRYPTED_KEYS) += encrypted-keys/
=======
<<<<<<< HEAD
obj-$(CONFIG_ENCRYPTED_KEYS) += encrypted-keys/
=======
obj-$(CONFIG_ENCRYPTED_KEYS) += encrypted.o
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_KEYS_COMPAT) += compat.o
obj-$(CONFIG_PROC_FS) += proc.o
obj-$(CONFIG_SYSCTL) += sysctl.o
