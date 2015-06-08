#!/bin/bash
#
# This script serves following purpose:
#
# 1. It generates native version information by querying
#    automerger maintained database to see where src/include
#    came from
# 2. For select components, as listed in compvers.sh
#    it generates component version files
#
# Copyright 2005, Broadcom, Inc.
#
<<<<<<< HEAD
<<<<<<< HEAD
# $Id: Makefile 241686 2011-02-19 00:22:45Z $
#

SRCBASE := ..
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
# $Id: Makefile 347587 2012-07-27 09:13:31Z prakashd $
#

export SRCBASE:=..
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

TARGETS := epivers.h

ifdef VERBOSE
export VERBOSE
endif

all release: epivers compvers

<<<<<<< HEAD
<<<<<<< HEAD
# Generate epivers.h for native branch version
epivers:
	bash epivers.sh

# Generate epivers.h for native branch version
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
# Generate epivers.h for native branch url
epivers:
	bash epivers.sh

# Generate component versions based on component url
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
compvers:
	@if [ -s "compvers.sh" ]; then \
		echo "Generating component versions, if any"; \
		bash compvers.sh; \
	else \
		echo "Skipping component version generation"; \
	fi

# Generate epivers.h for native branch version
clean_compvers:
	@if [ -s "compvers.sh" ]; then \
		echo "bash compvers.sh clean"; \
		bash compvers.sh clean; \
	else \
		echo "Skipping component version clean"; \
	fi

clean:
	rm -f $(TARGETS) *.prev

clean_all: clean clean_compvers

.PHONY: all release clean epivers compvers clean_compvers
