/*
 * Common EFI (Extensible Firmware Interface) support functions
 * Based on Extensible Firmware Interface Specification version 1.0
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999-2002 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2005-2008 Intel Co.
 *	Fenghua Yu <fenghua.yu@intel.com>
 *	Bibo Mao <bibo.mao@intel.com>
 *	Chandramouli Narayanan <mouli@linux.intel.com>
 *	Huang Ying <ying.huang@intel.com>
 *
 * Copied from efi_32.c to eliminate the duplicated code between EFI
 * 32/64 support code. --ying 2007-10-26
 *
 * All EFI Runtime Services are not implemented yet as EFI only
 * supports physical mode addressing on SoftSDV. This is to be fixed
 * in a future version.  --drummond 1999-07-20
 *
 * Implemented EFI runtime services and virtual mode calls.  --davidm
 *
 * Goutham Rao: <goutham.rao@intel.com>
 *	Skip non-WB memory and ignore empty memory ranges.
 */

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/efi.h>
#include <linux/export.h>
<<<<<<< HEAD
=======
=======
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/efi.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/bootmem.h>
#include <linux/memblock.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include <linux/io.h>
#include <linux/reboot.h>
#include <linux/bcd.h>

#include <asm/setup.h>
#include <asm/efi.h>
#include <asm/time.h>
#include <asm/cacheflush.h>
#include <asm/tlbflush.h>
#include <asm/x86_init.h>

#define EFI_DEBUG	1
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define PFX 		"EFI: "
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int efi_enabled;
EXPORT_SYMBOL(efi_enabled);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct efi __read_mostly efi = {
	.mps        = EFI_INVALID_TABLE_ADDR,
	.acpi       = EFI_INVALID_TABLE_ADDR,
	.acpi20     = EFI_INVALID_TABLE_ADDR,
	.smbios     = EFI_INVALID_TABLE_ADDR,
	.sal_systab = EFI_INVALID_TABLE_ADDR,
	.boot_info  = EFI_INVALID_TABLE_ADDR,
	.hcdp       = EFI_INVALID_TABLE_ADDR,
	.uga        = EFI_INVALID_TABLE_ADDR,
	.uv_systab  = EFI_INVALID_TABLE_ADDR,
};
<<<<<<< HEAD
=======
=======
struct efi efi;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
EXPORT_SYMBOL(efi);

struct efi_memory_map memmap;

<<<<<<< HEAD
bool efi_64bit;
static bool efi_native;

=======
<<<<<<< HEAD
bool efi_64bit;
static bool efi_native;

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct efi efi_phys __initdata;
static efi_system_table_t efi_systab __initdata;

static int __init setup_noefi(char *arg)
{
	efi_enabled = 0;
	return 0;
}
early_param("noefi", setup_noefi);

int add_efi_memmap;
EXPORT_SYMBOL(add_efi_memmap);

static int __init setup_add_efi_memmap(char *arg)
{
	add_efi_memmap = 1;
	return 0;
}
early_param("add_efi_memmap", setup_add_efi_memmap);


static efi_status_t virt_efi_get_time(efi_time_t *tm, efi_time_cap_t *tc)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long flags;
	efi_status_t status;

	spin_lock_irqsave(&rtc_lock, flags);
	status = efi_call_virt2(get_time, tm, tc);
	spin_unlock_irqrestore(&rtc_lock, flags);
	return status;
<<<<<<< HEAD
=======
=======
	return efi_call_virt2(get_time, tm, tc);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static efi_status_t virt_efi_set_time(efi_time_t *tm)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long flags;
	efi_status_t status;

	spin_lock_irqsave(&rtc_lock, flags);
	status = efi_call_virt1(set_time, tm);
	spin_unlock_irqrestore(&rtc_lock, flags);
	return status;
<<<<<<< HEAD
=======
=======
	return efi_call_virt1(set_time, tm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static efi_status_t virt_efi_get_wakeup_time(efi_bool_t *enabled,
					     efi_bool_t *pending,
					     efi_time_t *tm)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long flags;
	efi_status_t status;

	spin_lock_irqsave(&rtc_lock, flags);
	status = efi_call_virt3(get_wakeup_time,
				enabled, pending, tm);
	spin_unlock_irqrestore(&rtc_lock, flags);
	return status;
<<<<<<< HEAD
=======
=======
	return efi_call_virt3(get_wakeup_time,
			      enabled, pending, tm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static efi_status_t virt_efi_set_wakeup_time(efi_bool_t enabled, efi_time_t *tm)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long flags;
	efi_status_t status;

	spin_lock_irqsave(&rtc_lock, flags);
	status = efi_call_virt2(set_wakeup_time,
				enabled, tm);
	spin_unlock_irqrestore(&rtc_lock, flags);
	return status;
<<<<<<< HEAD
=======
=======
	return efi_call_virt2(set_wakeup_time,
			      enabled, tm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static efi_status_t virt_efi_get_variable(efi_char16_t *name,
					  efi_guid_t *vendor,
					  u32 *attr,
					  unsigned long *data_size,
					  void *data)
{
	return efi_call_virt5(get_variable,
			      name, vendor, attr,
			      data_size, data);
}

static efi_status_t virt_efi_get_next_variable(unsigned long *name_size,
					       efi_char16_t *name,
					       efi_guid_t *vendor)
{
	return efi_call_virt3(get_next_variable,
			      name_size, name, vendor);
}

static efi_status_t virt_efi_set_variable(efi_char16_t *name,
					  efi_guid_t *vendor,
<<<<<<< HEAD
					  u32 attr,
=======
<<<<<<< HEAD
					  u32 attr,
=======
					  unsigned long attr,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					  unsigned long data_size,
					  void *data)
{
	return efi_call_virt5(set_variable,
			      name, vendor, attr,
			      data_size, data);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static efi_status_t virt_efi_query_variable_info(u32 attr,
						 u64 *storage_space,
						 u64 *remaining_space,
						 u64 *max_variable_size)
{
	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	return efi_call_virt4(query_variable_info, attr, storage_space,
			      remaining_space, max_variable_size);
}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static efi_status_t virt_efi_get_next_high_mono_count(u32 *count)
{
	return efi_call_virt1(get_next_high_mono_count, count);
}

static void virt_efi_reset_system(int reset_type,
				  efi_status_t status,
				  unsigned long data_size,
				  efi_char16_t *data)
{
	efi_call_virt4(reset_system, reset_type, status,
		       data_size, data);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static efi_status_t virt_efi_update_capsule(efi_capsule_header_t **capsules,
					    unsigned long count,
					    unsigned long sg_list)
{
	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	return efi_call_virt3(update_capsule, capsules, count, sg_list);
}

static efi_status_t virt_efi_query_capsule_caps(efi_capsule_header_t **capsules,
						unsigned long count,
						u64 *max_size,
						int *reset_type)
{
	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	return efi_call_virt4(query_capsule_caps, capsules, count, max_size,
			      reset_type);
}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static efi_status_t __init phys_efi_set_virtual_address_map(
	unsigned long memory_map_size,
	unsigned long descriptor_size,
	u32 descriptor_version,
	efi_memory_desc_t *virtual_map)
{
	efi_status_t status;

	efi_call_phys_prelog();
	status = efi_call_phys4(efi_phys.set_virtual_address_map,
				memory_map_size, descriptor_size,
				descriptor_version, virtual_map);
	efi_call_phys_epilog();
	return status;
}

static efi_status_t __init phys_efi_get_time(efi_time_t *tm,
					     efi_time_cap_t *tc)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long flags;
	efi_status_t status;

	spin_lock_irqsave(&rtc_lock, flags);
	efi_call_phys_prelog();
	status = efi_call_phys2(efi_phys.get_time, virt_to_phys(tm),
				virt_to_phys(tc));
	efi_call_phys_epilog();
	spin_unlock_irqrestore(&rtc_lock, flags);
<<<<<<< HEAD
=======
=======
	efi_status_t status;

	efi_call_phys_prelog();
	status = efi_call_phys2(efi_phys.get_time, tm, tc);
	efi_call_phys_epilog();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return status;
}

int efi_set_rtc_mmss(unsigned long nowtime)
{
	int real_seconds, real_minutes;
	efi_status_t 	status;
	efi_time_t 	eft;
	efi_time_cap_t 	cap;

	status = efi.get_time(&eft, &cap);
	if (status != EFI_SUCCESS) {
<<<<<<< HEAD
		pr_err("Oops: efitime: can't read time!\n");
=======
<<<<<<< HEAD
		pr_err("Oops: efitime: can't read time!\n");
=======
		printk(KERN_ERR "Oops: efitime: can't read time!\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -1;
	}

	real_seconds = nowtime % 60;
	real_minutes = nowtime / 60;
	if (((abs(real_minutes - eft.minute) + 15)/30) & 1)
		real_minutes += 30;
	real_minutes %= 60;
	eft.minute = real_minutes;
	eft.second = real_seconds;

	status = efi.set_time(&eft);
	if (status != EFI_SUCCESS) {
<<<<<<< HEAD
		pr_err("Oops: efitime: can't write time!\n");
=======
<<<<<<< HEAD
		pr_err("Oops: efitime: can't write time!\n");
=======
		printk(KERN_ERR "Oops: efitime: can't write time!\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -1;
	}
	return 0;
}

unsigned long efi_get_time(void)
{
	efi_status_t status;
	efi_time_t eft;
	efi_time_cap_t cap;

	status = efi.get_time(&eft, &cap);
	if (status != EFI_SUCCESS)
<<<<<<< HEAD
		pr_err("Oops: efitime: can't read time!\n");
=======
<<<<<<< HEAD
		pr_err("Oops: efitime: can't read time!\n");
=======
		printk(KERN_ERR "Oops: efitime: can't read time!\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return mktime(eft.year, eft.month, eft.day, eft.hour,
		      eft.minute, eft.second);
}

/*
 * Tell the kernel about the EFI memory map.  This might include
 * more than the max 128 entries that can fit in the e820 legacy
 * (zeropage) memory map.
 */

static void __init do_add_efi_memmap(void)
{
	void *p;

	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		efi_memory_desc_t *md = p;
		unsigned long long start = md->phys_addr;
		unsigned long long size = md->num_pages << EFI_PAGE_SHIFT;
		int e820_type;

		switch (md->type) {
		case EFI_LOADER_CODE:
		case EFI_LOADER_DATA:
		case EFI_BOOT_SERVICES_CODE:
		case EFI_BOOT_SERVICES_DATA:
		case EFI_CONVENTIONAL_MEMORY:
			if (md->attribute & EFI_MEMORY_WB)
				e820_type = E820_RAM;
			else
				e820_type = E820_RESERVED;
			break;
		case EFI_ACPI_RECLAIM_MEMORY:
			e820_type = E820_ACPI;
			break;
		case EFI_ACPI_MEMORY_NVS:
			e820_type = E820_NVS;
			break;
		case EFI_UNUSABLE_MEMORY:
			e820_type = E820_UNUSABLE;
			break;
		default:
			/*
			 * EFI_RESERVED_TYPE EFI_RUNTIME_SERVICES_CODE
			 * EFI_RUNTIME_SERVICES_DATA EFI_MEMORY_MAPPED_IO
			 * EFI_MEMORY_MAPPED_IO_PORT_SPACE EFI_PAL_CODE
			 */
			e820_type = E820_RESERVED;
			break;
		}
		e820_add_region(start, size, e820_type);
	}
	sanitize_e820_map(e820.map, ARRAY_SIZE(e820.map), &e820.nr_map);
}

<<<<<<< HEAD
int __init efi_memblock_x86_reserve_range(void)
=======
<<<<<<< HEAD
int __init efi_memblock_x86_reserve_range(void)
=======
void __init efi_memblock_x86_reserve_range(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	unsigned long pmap;

#ifdef CONFIG_X86_32
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Can't handle data above 4GB at this time */
	if (boot_params.efi_info.efi_memmap_hi) {
		pr_err("Memory map is above 4GB, disabling EFI.\n");
		return -EINVAL;
	}
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	pmap = boot_params.efi_info.efi_memmap;
#else
	pmap = (boot_params.efi_info.efi_memmap |
		((__u64)boot_params.efi_info.efi_memmap_hi<<32));
#endif
	memmap.phys_map = (void *)pmap;
	memmap.nr_map = boot_params.efi_info.efi_memmap_size /
		boot_params.efi_info.efi_memdesc_size;
	memmap.desc_version = boot_params.efi_info.efi_memdesc_version;
	memmap.desc_size = boot_params.efi_info.efi_memdesc_size;
<<<<<<< HEAD
	memblock_reserve(pmap, memmap.nr_map * memmap.desc_size);

	return 0;
=======
<<<<<<< HEAD
	memblock_reserve(pmap, memmap.nr_map * memmap.desc_size);

	return 0;
=======
	memblock_x86_reserve_range(pmap, pmap + memmap.nr_map * memmap.desc_size,
		      "EFI memmap");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

#if EFI_DEBUG
static void __init print_efi_memmap(void)
{
	efi_memory_desc_t *md;
	void *p;
	int i;

	for (p = memmap.map, i = 0;
	     p < memmap.map_end;
	     p += memmap.desc_size, i++) {
		md = p;
<<<<<<< HEAD
		pr_info("mem%02u: type=%u, attr=0x%llx, "
=======
<<<<<<< HEAD
		pr_info("mem%02u: type=%u, attr=0x%llx, "
=======
		printk(KERN_INFO PFX "mem%02u: type=%u, attr=0x%llx, "
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			"range=[0x%016llx-0x%016llx) (%lluMB)\n",
			i, md->type, md->attribute, md->phys_addr,
			md->phys_addr + (md->num_pages << EFI_PAGE_SHIFT),
			(md->num_pages >> (20 - EFI_PAGE_SHIFT)));
	}
}
#endif  /*  EFI_DEBUG  */

void __init efi_reserve_boot_services(void)
{
	void *p;

	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		efi_memory_desc_t *md = p;
		u64 start = md->phys_addr;
		u64 size = md->num_pages << EFI_PAGE_SHIFT;

		if (md->type != EFI_BOOT_SERVICES_CODE &&
		    md->type != EFI_BOOT_SERVICES_DATA)
			continue;
		/* Only reserve where possible:
		 * - Not within any already allocated areas
		 * - Not over any memory area (really needed, if above?)
		 * - Not within any part of the kernel
		 * - Not the bios reserved area
		*/
		if ((start+size >= virt_to_phys(_text)
				&& start <= virt_to_phys(_end)) ||
			!e820_all_mapped(start, start+size, E820_RAM) ||
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			memblock_is_region_reserved(start, size)) {
			/* Could not reserve, skip it */
			md->num_pages = 0;
			memblock_dbg("Could not reserve boot range "
					"[0x%010llx-0x%010llx]\n",
						start, start+size-1);
		} else
			memblock_reserve(start, size);
<<<<<<< HEAD
=======
=======
			memblock_x86_check_reserved_size(&start, &size,
							1<<EFI_PAGE_SHIFT)) {
			/* Could not reserve, skip it */
			md->num_pages = 0;
			memblock_dbg(PFX "Could not reserve boot range "
					"[0x%010llx-0x%010llx]\n",
						start, start+size-1);
		} else
			memblock_x86_reserve_range(start, start+size,
							"EFI Boot");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
}

static void __init efi_free_boot_services(void)
{
	void *p;

	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		efi_memory_desc_t *md = p;
		unsigned long long start = md->phys_addr;
		unsigned long long size = md->num_pages << EFI_PAGE_SHIFT;

		if (md->type != EFI_BOOT_SERVICES_CODE &&
		    md->type != EFI_BOOT_SERVICES_DATA)
			continue;

		/* Could not reserve boot area */
		if (!size)
			continue;

		free_bootmem_late(start, size);
	}
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init efi_systab_init(void *phys)
{
	if (efi_64bit) {
		efi_system_table_64_t *systab64;
		u64 tmp = 0;

		systab64 = early_ioremap((unsigned long)phys,
					 sizeof(*systab64));
		if (systab64 == NULL) {
			pr_err("Couldn't map the system table!\n");
			return -ENOMEM;
		}

		efi_systab.hdr = systab64->hdr;
		efi_systab.fw_vendor = systab64->fw_vendor;
		tmp |= systab64->fw_vendor;
		efi_systab.fw_revision = systab64->fw_revision;
		efi_systab.con_in_handle = systab64->con_in_handle;
		tmp |= systab64->con_in_handle;
		efi_systab.con_in = systab64->con_in;
		tmp |= systab64->con_in;
		efi_systab.con_out_handle = systab64->con_out_handle;
		tmp |= systab64->con_out_handle;
		efi_systab.con_out = systab64->con_out;
		tmp |= systab64->con_out;
		efi_systab.stderr_handle = systab64->stderr_handle;
		tmp |= systab64->stderr_handle;
		efi_systab.stderr = systab64->stderr;
		tmp |= systab64->stderr;
		efi_systab.runtime = (void *)(unsigned long)systab64->runtime;
		tmp |= systab64->runtime;
		efi_systab.boottime = (void *)(unsigned long)systab64->boottime;
		tmp |= systab64->boottime;
		efi_systab.nr_tables = systab64->nr_tables;
		efi_systab.tables = systab64->tables;
		tmp |= systab64->tables;

		early_iounmap(systab64, sizeof(*systab64));
#ifdef CONFIG_X86_32
		if (tmp >> 32) {
			pr_err("EFI data located above 4GB, disabling EFI.\n");
			return -EINVAL;
		}
#endif
	} else {
		efi_system_table_32_t *systab32;

		systab32 = early_ioremap((unsigned long)phys,
					 sizeof(*systab32));
		if (systab32 == NULL) {
			pr_err("Couldn't map the system table!\n");
			return -ENOMEM;
		}

		efi_systab.hdr = systab32->hdr;
		efi_systab.fw_vendor = systab32->fw_vendor;
		efi_systab.fw_revision = systab32->fw_revision;
		efi_systab.con_in_handle = systab32->con_in_handle;
		efi_systab.con_in = systab32->con_in;
		efi_systab.con_out_handle = systab32->con_out_handle;
		efi_systab.con_out = systab32->con_out;
		efi_systab.stderr_handle = systab32->stderr_handle;
		efi_systab.stderr = systab32->stderr;
		efi_systab.runtime = (void *)(unsigned long)systab32->runtime;
		efi_systab.boottime = (void *)(unsigned long)systab32->boottime;
		efi_systab.nr_tables = systab32->nr_tables;
		efi_systab.tables = systab32->tables;

		early_iounmap(systab32, sizeof(*systab32));
	}

<<<<<<< HEAD
=======
=======
void __init efi_init(void)
{
	efi_config_table_t *config_tables;
	efi_runtime_services_t *runtime;
	efi_char16_t *c16;
	char vendor[100] = "unknown";
	int i = 0;
	void *tmp;

#ifdef CONFIG_X86_32
	efi_phys.systab = (efi_system_table_t *)boot_params.efi_info.efi_systab;
#else
	efi_phys.systab = (efi_system_table_t *)
		(boot_params.efi_info.efi_systab |
		 ((__u64)boot_params.efi_info.efi_systab_hi<<32));
#endif

	efi.systab = early_ioremap((unsigned long)efi_phys.systab,
				   sizeof(efi_system_table_t));
	if (efi.systab == NULL)
		printk(KERN_ERR "Couldn't map the EFI system table!\n");
	memcpy(&efi_systab, efi.systab, sizeof(efi_system_table_t));
	early_iounmap(efi.systab, sizeof(efi_system_table_t));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	efi.systab = &efi_systab;

	/*
	 * Verify the EFI Table
	 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (efi.systab->hdr.signature != EFI_SYSTEM_TABLE_SIGNATURE) {
		pr_err("System table signature incorrect!\n");
		return -EINVAL;
	}
	if ((efi.systab->hdr.revision >> 16) == 0)
		pr_err("Warning: System table version "
<<<<<<< HEAD
=======
=======
	if (efi.systab->hdr.signature != EFI_SYSTEM_TABLE_SIGNATURE)
		printk(KERN_ERR "EFI system table signature incorrect!\n");
	if ((efi.systab->hdr.revision >> 16) == 0)
		printk(KERN_ERR "Warning: EFI system table version "
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		       "%d.%02d, expected 1.00 or greater!\n",
		       efi.systab->hdr.revision >> 16,
		       efi.systab->hdr.revision & 0xffff);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static int __init efi_config_init(u64 tables, int nr_tables)
{
	void *config_tables, *tablep;
	int i, sz;

	if (efi_64bit)
		sz = sizeof(efi_config_table_64_t);
	else
		sz = sizeof(efi_config_table_32_t);
<<<<<<< HEAD
=======
=======
	/*
	 * Show what we know for posterity
	 */
	c16 = tmp = early_ioremap(efi.systab->fw_vendor, 2);
	if (c16) {
		for (i = 0; i < sizeof(vendor) - 1 && *c16; ++i)
			vendor[i] = *c16++;
		vendor[i] = '\0';
	} else
		printk(KERN_ERR PFX "Could not map the firmware vendor!\n");
	early_iounmap(tmp, 2);

	printk(KERN_INFO "EFI v%u.%.02u by %s\n",
	       efi.systab->hdr.revision >> 16,
	       efi.systab->hdr.revision & 0xffff, vendor);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * Let's see what config tables the firmware passed to us.
	 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	config_tables = early_ioremap(tables, nr_tables * sz);
	if (config_tables == NULL) {
		pr_err("Could not map Configuration table!\n");
		return -ENOMEM;
	}

	tablep = config_tables;
	pr_info("");
	for (i = 0; i < efi.systab->nr_tables; i++) {
		efi_guid_t guid;
		unsigned long table;

		if (efi_64bit) {
			u64 table64;
			guid = ((efi_config_table_64_t *)tablep)->guid;
			table64 = ((efi_config_table_64_t *)tablep)->table;
			table = table64;
#ifdef CONFIG_X86_32
			if (table64 >> 32) {
				pr_cont("\n");
				pr_err("Table located above 4GB, disabling EFI.\n");
				early_iounmap(config_tables,
					      efi.systab->nr_tables * sz);
				return -EINVAL;
			}
#endif
		} else {
			guid = ((efi_config_table_32_t *)tablep)->guid;
			table = ((efi_config_table_32_t *)tablep)->table;
		}
		if (!efi_guidcmp(guid, MPS_TABLE_GUID)) {
			efi.mps = table;
			pr_cont(" MPS=0x%lx ", table);
		} else if (!efi_guidcmp(guid, ACPI_20_TABLE_GUID)) {
			efi.acpi20 = table;
			pr_cont(" ACPI 2.0=0x%lx ", table);
		} else if (!efi_guidcmp(guid, ACPI_TABLE_GUID)) {
			efi.acpi = table;
			pr_cont(" ACPI=0x%lx ", table);
		} else if (!efi_guidcmp(guid, SMBIOS_TABLE_GUID)) {
			efi.smbios = table;
			pr_cont(" SMBIOS=0x%lx ", table);
#ifdef CONFIG_X86_UV
		} else if (!efi_guidcmp(guid, UV_SYSTEM_TABLE_GUID)) {
			efi.uv_systab = table;
			pr_cont(" UVsystab=0x%lx ", table);
#endif
		} else if (!efi_guidcmp(guid, HCDP_TABLE_GUID)) {
			efi.hcdp = table;
			pr_cont(" HCDP=0x%lx ", table);
		} else if (!efi_guidcmp(guid, UGA_IO_PROTOCOL_GUID)) {
			efi.uga = table;
			pr_cont(" UGA=0x%lx ", table);
		}
		tablep += sz;
	}
	pr_cont("\n");
	early_iounmap(config_tables, efi.systab->nr_tables * sz);
	return 0;
}

static int __init efi_runtime_init(void)
{
	efi_runtime_services_t *runtime;
<<<<<<< HEAD
=======
=======
	config_tables = early_ioremap(
		efi.systab->tables,
		efi.systab->nr_tables * sizeof(efi_config_table_t));
	if (config_tables == NULL)
		printk(KERN_ERR "Could not map EFI Configuration Table!\n");

	printk(KERN_INFO);
	for (i = 0; i < efi.systab->nr_tables; i++) {
		if (!efi_guidcmp(config_tables[i].guid, MPS_TABLE_GUID)) {
			efi.mps = config_tables[i].table;
			printk(" MPS=0x%lx ", config_tables[i].table);
		} else if (!efi_guidcmp(config_tables[i].guid,
					ACPI_20_TABLE_GUID)) {
			efi.acpi20 = config_tables[i].table;
			printk(" ACPI 2.0=0x%lx ", config_tables[i].table);
		} else if (!efi_guidcmp(config_tables[i].guid,
					ACPI_TABLE_GUID)) {
			efi.acpi = config_tables[i].table;
			printk(" ACPI=0x%lx ", config_tables[i].table);
		} else if (!efi_guidcmp(config_tables[i].guid,
					SMBIOS_TABLE_GUID)) {
			efi.smbios = config_tables[i].table;
			printk(" SMBIOS=0x%lx ", config_tables[i].table);
#ifdef CONFIG_X86_UV
		} else if (!efi_guidcmp(config_tables[i].guid,
					UV_SYSTEM_TABLE_GUID)) {
			efi.uv_systab = config_tables[i].table;
			printk(" UVsystab=0x%lx ", config_tables[i].table);
#endif
		} else if (!efi_guidcmp(config_tables[i].guid,
					HCDP_TABLE_GUID)) {
			efi.hcdp = config_tables[i].table;
			printk(" HCDP=0x%lx ", config_tables[i].table);
		} else if (!efi_guidcmp(config_tables[i].guid,
					UGA_IO_PROTOCOL_GUID)) {
			efi.uga = config_tables[i].table;
			printk(" UGA=0x%lx ", config_tables[i].table);
		}
	}
	printk("\n");
	early_iounmap(config_tables,
			  efi.systab->nr_tables * sizeof(efi_config_table_t));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * Check out the runtime services table. We need to map
	 * the runtime services table so that we can grab the physical
	 * address of several of the EFI runtime functions, needed to
	 * set the firmware into virtual mode.
	 */
	runtime = early_ioremap((unsigned long)efi.systab->runtime,
				sizeof(efi_runtime_services_t));
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!runtime) {
		pr_err("Could not map the runtime service table!\n");
		return -ENOMEM;
	}
	/*
	 * We will only need *early* access to the following
	 * two EFI runtime services before set_virtual_address_map
	 * is invoked.
	 */
	efi_phys.get_time = (efi_get_time_t *)runtime->get_time;
	efi_phys.set_virtual_address_map =
		(efi_set_virtual_address_map_t *)
		runtime->set_virtual_address_map;
	/*
	 * Make efi_get_time can be called before entering
	 * virtual mode.
	 */
	efi.get_time = phys_efi_get_time;
	early_iounmap(runtime, sizeof(efi_runtime_services_t));

	return 0;
}

static int __init efi_memmap_init(void)
{
	/* Map the EFI memory map */
	memmap.map = early_ioremap((unsigned long)memmap.phys_map,
				   memmap.nr_map * memmap.desc_size);
	if (memmap.map == NULL) {
		pr_err("Could not map the memory map!\n");
		return -ENOMEM;
	}
	memmap.map_end = memmap.map + (memmap.nr_map * memmap.desc_size);

	if (add_efi_memmap)
		do_add_efi_memmap();

	return 0;
}

void __init efi_init(void)
{
	efi_char16_t *c16;
	char vendor[100] = "unknown";
	int i = 0;
	void *tmp;

#ifdef CONFIG_X86_32
	if (boot_params.efi_info.efi_systab_hi ||
	    boot_params.efi_info.efi_memmap_hi) {
		pr_info("Table located above 4GB, disabling EFI.\n");
		efi_enabled = 0;
		return;
	}
	efi_phys.systab = (efi_system_table_t *)boot_params.efi_info.efi_systab;
	efi_native = !efi_64bit;
#else
	efi_phys.systab = (efi_system_table_t *)
			  (boot_params.efi_info.efi_systab |
			  ((__u64)boot_params.efi_info.efi_systab_hi<<32));
	efi_native = efi_64bit;
#endif

	if (efi_systab_init(efi_phys.systab)) {
		efi_enabled = 0;
		return;
	}

	/*
	 * Show what we know for posterity
	 */
	c16 = tmp = early_ioremap(efi.systab->fw_vendor, 2);
	if (c16) {
		for (i = 0; i < sizeof(vendor) - 1 && *c16; ++i)
			vendor[i] = *c16++;
		vendor[i] = '\0';
	} else
		pr_err("Could not map the firmware vendor!\n");
	early_iounmap(tmp, 2);

	pr_info("EFI v%u.%.02u by %s\n",
		efi.systab->hdr.revision >> 16,
		efi.systab->hdr.revision & 0xffff, vendor);

	if (efi_config_init(efi.systab->tables, efi.systab->nr_tables)) {
		efi_enabled = 0;
		return;
	}

	/*
	 * Note: We currently don't support runtime services on an EFI
	 * that doesn't match the kernel 32/64-bit mode.
	 */

	if (!efi_native)
		pr_info("No EFI runtime due to 32/64-bit mismatch with kernel\n");
	else if (efi_runtime_init()) {
		efi_enabled = 0;
		return;
	}

	if (efi_memmap_init()) {
		efi_enabled = 0;
		return;
	}
#ifdef CONFIG_X86_32
	if (efi_native) {
		x86_platform.get_wallclock = efi_get_time;
		x86_platform.set_wallclock = efi_set_rtc_mmss;
	}
<<<<<<< HEAD
=======
=======
	if (runtime != NULL) {
		/*
		 * We will only need *early* access to the following
		 * two EFI runtime services before set_virtual_address_map
		 * is invoked.
		 */
		efi_phys.get_time = (efi_get_time_t *)runtime->get_time;
		efi_phys.set_virtual_address_map =
			(efi_set_virtual_address_map_t *)
			runtime->set_virtual_address_map;
		/*
		 * Make efi_get_time can be called before entering
		 * virtual mode.
		 */
		efi.get_time = phys_efi_get_time;
	} else
		printk(KERN_ERR "Could not map the EFI runtime service "
		       "table!\n");
	early_iounmap(runtime, sizeof(efi_runtime_services_t));

	/* Map the EFI memory map */
	memmap.map = early_ioremap((unsigned long)memmap.phys_map,
				   memmap.nr_map * memmap.desc_size);
	if (memmap.map == NULL)
		printk(KERN_ERR "Could not map the EFI memory map!\n");
	memmap.map_end = memmap.map + (memmap.nr_map * memmap.desc_size);

	if (memmap.desc_size != sizeof(efi_memory_desc_t))
		printk(KERN_WARNING
		  "Kernel-defined memdesc doesn't match the one from EFI!\n");

	if (add_efi_memmap)
		do_add_efi_memmap();

#ifdef CONFIG_X86_32
	x86_platform.get_wallclock = efi_get_time;
	x86_platform.set_wallclock = efi_set_rtc_mmss;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif

#if EFI_DEBUG
	print_efi_memmap();
#endif
}

void __init efi_set_executable(efi_memory_desc_t *md, bool executable)
{
	u64 addr, npages;

	addr = md->virt_addr;
	npages = md->num_pages;

	memrange_efi_to_native(&addr, &npages);

	if (executable)
		set_memory_x(addr, npages);
	else
		set_memory_nx(addr, npages);
}

static void __init runtime_code_page_mkexec(void)
{
	efi_memory_desc_t *md;
	void *p;

	/* Make EFI runtime service code area executable */
	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		md = p;

		if (md->type != EFI_RUNTIME_SERVICES_CODE)
			continue;

		efi_set_executable(md, true);
	}
}

/*
 * This function will switch the EFI runtime services to virtual mode.
 * Essentially, look through the EFI memmap and map every region that
 * has the runtime attribute bit set in its memory descriptor and update
 * that memory descriptor with the virtual address obtained from ioremap().
 * This enables the runtime services to be called without having to
 * thunk back into physical mode for every invocation.
 */
void __init efi_enter_virtual_mode(void)
{
	efi_memory_desc_t *md, *prev_md = NULL;
	efi_status_t status;
	unsigned long size;
	u64 end, systab, addr, npages, end_pfn;
	void *p, *va, *new_memmap = NULL;
	int count = 0;

	efi.systab = NULL;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * We don't do virtual mode, since we don't do runtime services, on
	 * non-native EFI
	 */

	if (!efi_native)
		goto out;

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Merge contiguous regions of the same type and attribute */
	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		u64 prev_size;
		md = p;

		if (!prev_md) {
			prev_md = md;
			continue;
		}

		if (prev_md->type != md->type ||
		    prev_md->attribute != md->attribute) {
			prev_md = md;
			continue;
		}

		prev_size = prev_md->num_pages << EFI_PAGE_SHIFT;

		if (md->phys_addr == (prev_md->phys_addr + prev_size)) {
			prev_md->num_pages += md->num_pages;
			md->type = EFI_RESERVED_TYPE;
			md->attribute = 0;
			continue;
		}
		prev_md = md;
	}

	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		md = p;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!(md->attribute & EFI_MEMORY_RUNTIME) &&
		    md->type != EFI_BOOT_SERVICES_CODE &&
		    md->type != EFI_BOOT_SERVICES_DATA)
			continue;
<<<<<<< HEAD
=======
=======
		if (!(md->attribute & EFI_MEMORY_RUNTIME)) {
#ifdef CONFIG_X86_64
			if (md->type != EFI_BOOT_SERVICES_CODE &&
			    md->type != EFI_BOOT_SERVICES_DATA)
#endif
				continue;
		}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		size = md->num_pages << EFI_PAGE_SHIFT;
		end = md->phys_addr + size;

		end_pfn = PFN_UP(end);
		if (end_pfn <= max_low_pfn_mapped
		    || (end_pfn > (1UL << (32 - PAGE_SHIFT))
			&& end_pfn <= max_pfn_mapped))
			va = __va(md->phys_addr);
		else
			va = efi_ioremap(md->phys_addr, size, md->type);

		md->virt_addr = (u64) (unsigned long) va;

		if (!va) {
<<<<<<< HEAD
			pr_err("ioremap of 0x%llX failed!\n",
=======
<<<<<<< HEAD
			pr_err("ioremap of 0x%llX failed!\n",
=======
			printk(KERN_ERR PFX "ioremap of 0x%llX failed!\n",
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			       (unsigned long long)md->phys_addr);
			continue;
		}

		if (!(md->attribute & EFI_MEMORY_WB)) {
			addr = md->virt_addr;
			npages = md->num_pages;
			memrange_efi_to_native(&addr, &npages);
			set_memory_uc(addr, npages);
		}

		systab = (u64) (unsigned long) efi_phys.systab;
		if (md->phys_addr <= systab && systab < end) {
			systab += md->virt_addr - md->phys_addr;
			efi.systab = (efi_system_table_t *) (unsigned long) systab;
		}
		new_memmap = krealloc(new_memmap,
				      (count + 1) * memmap.desc_size,
				      GFP_KERNEL);
		memcpy(new_memmap + (count * memmap.desc_size), md,
		       memmap.desc_size);
		count++;
	}

	BUG_ON(!efi.systab);

	status = phys_efi_set_virtual_address_map(
		memmap.desc_size * count,
		memmap.desc_size,
		memmap.desc_version,
		(efi_memory_desc_t *)__pa(new_memmap));

	if (status != EFI_SUCCESS) {
<<<<<<< HEAD
		pr_alert("Unable to switch EFI into virtual mode "
			 "(status=%lx)!\n", status);
=======
<<<<<<< HEAD
		pr_alert("Unable to switch EFI into virtual mode "
			 "(status=%lx)!\n", status);
=======
		printk(KERN_ALERT "Unable to switch EFI into virtual mode "
		       "(status=%lx)!\n", status);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		panic("EFI call to SetVirtualAddressMap() failed!");
	}

	/*
	 * Thankfully, it does seem that no runtime services other than
	 * SetVirtualAddressMap() will touch boot services code, so we can
	 * get rid of it all at this point
	 */
	efi_free_boot_services();

	/*
	 * Now that EFI is in virtual mode, update the function
	 * pointers in the runtime service table to the new virtual addresses.
	 *
	 * Call EFI services through wrapper functions.
	 */
	efi.get_time = virt_efi_get_time;
	efi.set_time = virt_efi_set_time;
	efi.get_wakeup_time = virt_efi_get_wakeup_time;
	efi.set_wakeup_time = virt_efi_set_wakeup_time;
	efi.get_variable = virt_efi_get_variable;
	efi.get_next_variable = virt_efi_get_next_variable;
	efi.set_variable = virt_efi_set_variable;
	efi.get_next_high_mono_count = virt_efi_get_next_high_mono_count;
	efi.reset_system = virt_efi_reset_system;
	efi.set_virtual_address_map = NULL;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	efi.query_variable_info = virt_efi_query_variable_info;
	efi.update_capsule = virt_efi_update_capsule;
	efi.query_capsule_caps = virt_efi_query_capsule_caps;
	if (__supported_pte_mask & _PAGE_NX)
		runtime_code_page_mkexec();

out:
<<<<<<< HEAD
=======
=======
	if (__supported_pte_mask & _PAGE_NX)
		runtime_code_page_mkexec();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	early_iounmap(memmap.map, memmap.nr_map * memmap.desc_size);
	memmap.map = NULL;
	kfree(new_memmap);
}

/*
 * Convenience functions to obtain memory types and attributes
 */
u32 efi_mem_type(unsigned long phys_addr)
{
	efi_memory_desc_t *md;
	void *p;

	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		md = p;
		if ((md->phys_addr <= phys_addr) &&
		    (phys_addr < (md->phys_addr +
				  (md->num_pages << EFI_PAGE_SHIFT))))
			return md->type;
	}
	return 0;
}

u64 efi_mem_attributes(unsigned long phys_addr)
{
	efi_memory_desc_t *md;
	void *p;

	for (p = memmap.map; p < memmap.map_end; p += memmap.desc_size) {
		md = p;
		if ((md->phys_addr <= phys_addr) &&
		    (phys_addr < (md->phys_addr +
				  (md->num_pages << EFI_PAGE_SHIFT))))
			return md->attribute;
	}
	return 0;
}
