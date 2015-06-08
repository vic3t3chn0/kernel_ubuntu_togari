#------------------------------------------------------------------------------
# Copyright (c) 2004-2011 Atheros Communications Inc.
# Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
# All rights reserved.
#
#
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#
#
# Author(s): ="Atheros"
#------------------------------------------------------------------------------

<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_ATH6KL) += ath6kl_core.o
ath6kl_core-y += debug.o
ath6kl_core-y += hif.o
ath6kl_core-y += htc.o
ath6kl_core-y += bmi.o
ath6kl_core-y += cfg80211.o
ath6kl_core-y += init.o
ath6kl_core-y += main.o
ath6kl_core-y += txrx.o
ath6kl_core-y += wmi.o
ath6kl_core-y += core.o
ath6kl_core-$(CONFIG_NL80211_TESTMODE) += testmode.o

obj-$(CONFIG_ATH6KL_SDIO) += ath6kl_sdio.o
ath6kl_sdio-y += sdio.o

obj-$(CONFIG_ATH6KL_USB) += ath6kl_usb.o
ath6kl_usb-y += usb.o
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
obj-$(CONFIG_ATH6KL_SDIO) := ath6kl_sdio.o
ath6kl_sdio-y += debug.o
ath6kl_sdio-y += debugfs_pri.o
ath6kl_sdio-y += hif.o
ath6kl_sdio-y += htc.o
ath6kl_sdio-y += bmi.o
ath6kl_sdio-y += cfg80211.o
ath6kl_sdio-y += cfg80211_btcoex.o
ath6kl_sdio-y += pm.o
ath6kl_sdio-y += init.o
ath6kl_sdio-y += main.o
ath6kl_sdio-y += txrx.o
ath6kl_sdio-y += wmi.o
ath6kl_sdio-y += wmi_btcoex.o
ath6kl_sdio-y += sdio.o
ifeq ($(CONFIG_MACH_PX),y)
ath6kl_sdio-y += c210.o
else
ath6kl_sdio-y += msm.o
endif
ath6kl_sdio-y += softmac.o
ath6kl_sdio-y += wmiconfig.o
ath6kl_sdio-$(CONFIG_NL80211_TESTMODE) += testmode.o

obj-$(CONFIG_ATH6KL_USB) += ath6kl_usb.o
ath6kl_usb-y += debug.o
ath6kl_usb-y += hif.o
ath6kl_usb-y += htc.o
ath6kl_usb-y += bmi.o
ath6kl_usb-y += cfg80211.o
ath6kl_usb-y += cfg80211_btcoex.o
ath6kl_usb-y += pm.o
ath6kl_usb-y += init.o
ath6kl_usb-y += main.o
ath6kl_usb-y += txrx.o
ath6kl_usb-y += wmi.o
ath6kl_usb-y += wmi_btcoex.o
ath6kl_usb-y += usb.o
ath6kl_usb-y += wmiconfig.o
ath6kl_usb-$(CONFIG_NL80211_TESTMODE) += testmode.o

ccflags-y += -D__CHECK_ENDIAN__
# 5GHz channels setting
ifeq ($(CONFIG_5GH_WLAN_COUNTRY_CODE),y)
ccflags-y += -DGLOBALCONFIG_WLAN_COUNTRY_CODE
endif
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
