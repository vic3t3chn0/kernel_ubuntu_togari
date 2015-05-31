#
# ia64/platform/dig/Makefile
#
# Copyright (C) 1999 Silicon Graphics, Inc.
# Copyright (C) Srinivasa Thirumalachar (sprasad@engr.sgi.com)
#

obj-y := setup.o
<<<<<<< HEAD
ifeq ($(CONFIG_INTEL_IOMMU), y)
=======
ifeq ($(CONFIG_DMAR), y)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
obj-$(CONFIG_IA64_GENERIC) += machvec.o machvec_vtd.o
else
obj-$(CONFIG_IA64_GENERIC) += machvec.o
endif

