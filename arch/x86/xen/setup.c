/*
 * Machine specific setup for xen
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pm.h>
#include <linux/memblock.h>
<<<<<<< HEAD
#include <linux/cpuidle.h>
#include <linux/cpufreq.h>
=======
<<<<<<< HEAD
#include <linux/cpuidle.h>
#include <linux/cpufreq.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <asm/elf.h>
#include <asm/vdso.h>
#include <asm/e820.h>
#include <asm/setup.h>
#include <asm/acpi.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <asm/numa.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/xen/hypervisor.h>
#include <asm/xen/hypercall.h>

#include <xen/xen.h>
#include <xen/page.h>
#include <xen/interface/callback.h>
#include <xen/interface/memory.h>
#include <xen/interface/physdev.h>
#include <xen/features.h>

#include "xen-ops.h"
#include "vdso.h"

/* These are code, but not functions.  Defined in entry.S */
extern const char xen_hypervisor_callback[];
extern const char xen_failsafe_callback[];
extern void xen_sysenter_target(void);
extern void xen_syscall_target(void);
extern void xen_syscall32_target(void);

/* Amount of extra memory space we add to the e820 ranges */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct xen_memory_region xen_extra_mem[XEN_EXTRA_MEM_MAX_REGIONS] __initdata;

/* Number of pages released from the initial allocation. */
unsigned long xen_released_pages;
<<<<<<< HEAD
=======
=======
phys_addr_t xen_extra_mem_start, xen_extra_mem_size;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* 
 * The maximum amount of extra memory compared to the base size.  The
 * main scaling factor is the size of struct page.  At extreme ratios
 * of base:extra, all the base memory can be filled with page
 * structures for the extra memory, leaving no space for anything
 * else.
 * 
 * 10x seems like a reasonable balance between scaling flexibility and
 * leaving a practically usable system.
 */
#define EXTRA_MEM_RATIO		(10)

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void __init xen_add_extra_mem(u64 start, u64 size)
{
	unsigned long pfn;
	int i;

	for (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++) {
		/* Add new region. */
		if (xen_extra_mem[i].size == 0) {
			xen_extra_mem[i].start = start;
			xen_extra_mem[i].size  = size;
			break;
		}
		/* Append to existing region. */
		if (xen_extra_mem[i].start + xen_extra_mem[i].size == start) {
			xen_extra_mem[i].size += size;
			break;
		}
	}
	if (i == XEN_EXTRA_MEM_MAX_REGIONS)
		printk(KERN_WARNING "Warning: not enough extra memory regions\n");

	memblock_reserve(start, size);

	xen_max_p2m_pfn = PFN_DOWN(start + size);

	for (pfn = PFN_DOWN(start); pfn <= xen_max_p2m_pfn; pfn++)
		__set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
}

static unsigned long __init xen_release_chunk(unsigned long start,
					      unsigned long end)
<<<<<<< HEAD
=======
=======
static void __init xen_add_extra_mem(unsigned long pages)
{
	unsigned long pfn;

	u64 size = (u64)pages * PAGE_SIZE;
	u64 extra_start = xen_extra_mem_start + xen_extra_mem_size;

	if (!pages)
		return;

	e820_add_region(extra_start, size, E820_RAM);
	sanitize_e820_map(e820.map, ARRAY_SIZE(e820.map), &e820.nr_map);

	memblock_x86_reserve_range(extra_start, extra_start + size, "XEN EXTRA");

	xen_extra_mem_size += size;

	xen_max_p2m_pfn = PFN_DOWN(extra_start + size);

	for (pfn = PFN_DOWN(extra_start); pfn <= xen_max_p2m_pfn; pfn++)
		__set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
}

static unsigned long __init xen_release_chunk(phys_addr_t start_addr,
					      phys_addr_t end_addr)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct xen_memory_reservation reservation = {
		.address_bits = 0,
		.extent_order = 0,
		.domid        = DOMID_SELF
	};
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	unsigned long start, end;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long len = 0;
	unsigned long pfn;
	int ret;

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	start = PFN_UP(start_addr);
	end = PFN_DOWN(end_addr);

	if (end <= start)
		return 0;

	printk(KERN_INFO "xen_release_chunk: looking at area pfn %lx-%lx: ",
	       start, end);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for(pfn = start; pfn < end; pfn++) {
		unsigned long mfn = pfn_to_mfn(pfn);

		/* Make sure pfn exists to start with */
		if (mfn == INVALID_P2M_ENTRY || mfn_to_pfn(mfn) != pfn)
			continue;

		set_xen_guest_handle(reservation.extent_start, &mfn);
		reservation.nr_extents = 1;

		ret = HYPERVISOR_memory_op(XENMEM_decrease_reservation,
					   &reservation);
<<<<<<< HEAD
		WARN(ret != 1, "Failed to release pfn %lx err=%d\n", pfn, ret);
=======
<<<<<<< HEAD
		WARN(ret != 1, "Failed to release pfn %lx err=%d\n", pfn, ret);
=======
		WARN(ret != 1, "Failed to release memory %lx-%lx err=%d\n",
		     start, end, ret);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (ret == 1) {
			__set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
			len++;
		}
	}
<<<<<<< HEAD
	printk(KERN_INFO "Freeing  %lx-%lx pfn range: %lu pages freed\n",
	       start, end, len);
=======
<<<<<<< HEAD
	printk(KERN_INFO "Freeing  %lx-%lx pfn range: %lu pages freed\n",
	       start, end, len);
=======
	printk(KERN_CONT "%ld pages freed\n", len);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return len;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static unsigned long __init xen_set_identity_and_release(
	const struct e820entry *list, size_t map_size, unsigned long nr_pages)
{
	phys_addr_t start = 0;
	unsigned long released = 0;
	unsigned long identity = 0;
	const struct e820entry *entry;
	int i;

	/*
	 * Combine non-RAM regions and gaps until a RAM region (or the
	 * end of the map) is reached, then set the 1:1 map and
	 * release the pages (if available) in those non-RAM regions.
	 *
	 * The combined non-RAM regions are rounded to a whole number
	 * of pages so any partial pages are accessible via the 1:1
	 * mapping.  This is needed for some BIOSes that put (for
	 * example) the DMI tables in a reserved region that begins on
	 * a non-page boundary.
	 */
	for (i = 0, entry = list; i < map_size; i++, entry++) {
		phys_addr_t end = entry->addr + entry->size;

		if (entry->type == E820_RAM || i == map_size - 1) {
			unsigned long start_pfn = PFN_DOWN(start);
			unsigned long end_pfn = PFN_UP(end);

			if (entry->type == E820_RAM)
				end_pfn = PFN_UP(entry->addr);

			if (start_pfn < end_pfn) {
				if (start_pfn < nr_pages)
					released += xen_release_chunk(
						start_pfn, min(end_pfn, nr_pages));

				identity += set_phys_range_identity(
					start_pfn, end_pfn);
			}
			start = end;
		}
	}

	printk(KERN_INFO "Released %lu pages of unused memory\n", released);
	printk(KERN_INFO "Set %ld page(s) to 1-1 mapping\n", identity);

	return released;
<<<<<<< HEAD
=======
=======
static unsigned long __init xen_return_unused_memory(unsigned long max_pfn,
						     const struct e820map *e820)
{
	phys_addr_t max_addr = PFN_PHYS(max_pfn);
	phys_addr_t last_end = ISA_END_ADDRESS;
	unsigned long released = 0;
	int i;

	/* Free any unused memory above the low 1Mbyte. */
	for (i = 0; i < e820->nr_map && last_end < max_addr; i++) {
		phys_addr_t end = e820->map[i].addr;
		end = min(max_addr, end);

		if (last_end < end)
			released += xen_release_chunk(last_end, end);
		last_end = max(last_end, e820->map[i].addr + e820->map[i].size);
	}

	if (last_end < max_addr)
		released += xen_release_chunk(last_end, max_addr);

	printk(KERN_INFO "released %ld pages of unused memory\n", released);
	return released;
}

static unsigned long __init xen_set_identity(const struct e820entry *list,
					     ssize_t map_size)
{
	phys_addr_t last = xen_initial_domain() ? 0 : ISA_END_ADDRESS;
	phys_addr_t start_pci = last;
	const struct e820entry *entry;
	unsigned long identity = 0;
	int i;

	for (i = 0, entry = list; i < map_size; i++, entry++) {
		phys_addr_t start = entry->addr;
		phys_addr_t end = start + entry->size;

		if (start < last)
			start = last;

		if (end <= start)
			continue;

		/* Skip over the 1MB region. */
		if (last > end)
			continue;

		if ((entry->type == E820_RAM) || (entry->type == E820_UNUSABLE)) {
			if (start > start_pci)
				identity += set_phys_range_identity(
						PFN_UP(start_pci), PFN_DOWN(start));

			/* Without saving 'last' we would gooble RAM too
			 * at the end of the loop. */
			last = end;
			start_pci = end;
			continue;
		}
		start_pci = min(start, start_pci);
		last = end;
	}
	if (last > start_pci)
		identity += set_phys_range_identity(
					PFN_UP(start_pci), PFN_DOWN(last));
	return identity;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static unsigned long __init xen_get_max_pages(void)
{
	unsigned long max_pages = MAX_DOMAIN_PAGES;
	domid_t domid = DOMID_SELF;
	int ret;

	/*
	 * For the initial domain we use the maximum reservation as
	 * the maximum page.
	 *
	 * For guest domains the current maximum reservation reflects
	 * the current maximum rather than the static maximum. In this
	 * case the e820 map provided to us will cover the static
	 * maximum region.
	 */
	if (xen_initial_domain()) {
		ret = HYPERVISOR_memory_op(XENMEM_maximum_reservation, &domid);
		if (ret > 0)
			max_pages = ret;
	}

	return min(max_pages, MAX_DOMAIN_PAGES);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void xen_align_and_add_e820_region(u64 start, u64 size, int type)
{
	u64 end = start + size;

	/* Align RAM regions to page boundaries. */
	if (type == E820_RAM) {
		start = PAGE_ALIGN(start);
		end &= ~((u64)PAGE_SIZE - 1);
	}

	e820_add_region(start, end - start, type);
}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/**
 * machine_specific_memory_setup - Hook for machine specific memory setup.
 **/
char * __init xen_memory_setup(void)
{
	static struct e820entry map[E820MAX] __initdata;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	static struct e820entry map_raw[E820MAX] __initdata;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	unsigned long max_pfn = xen_start_info->nr_pages;
	unsigned long long mem_end;
	int rc;
	struct xen_memory_map memmap;
<<<<<<< HEAD
	unsigned long max_pages;
	unsigned long extra_pages = 0;
=======
<<<<<<< HEAD
	unsigned long max_pages;
	unsigned long extra_pages = 0;
=======
	unsigned long extra_pages = 0;
	unsigned long extra_limit;
	unsigned long identity_pages = 0;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int i;
	int op;

	max_pfn = min(MAX_DOMAIN_PAGES, max_pfn);
	mem_end = PFN_PHYS(max_pfn);

	memmap.nr_entries = E820MAX;
	set_xen_guest_handle(memmap.buffer, map);

	op = xen_initial_domain() ?
		XENMEM_machine_memory_map :
		XENMEM_memory_map;
	rc = HYPERVISOR_memory_op(op, &memmap);
	if (rc == -ENOSYS) {
		BUG_ON(xen_initial_domain());
		memmap.nr_entries = 1;
		map[0].addr = 0ULL;
		map[0].size = mem_end;
		/* 8MB slack (to balance backend allocations). */
		map[0].size += 8ULL << 20;
		map[0].type = E820_RAM;
		rc = 0;
	}
	BUG_ON(rc);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Make sure the Xen-supplied memory map is well-ordered. */
	sanitize_e820_map(map, memmap.nr_entries, &memmap.nr_entries);

	max_pages = xen_get_max_pages();
	if (max_pages > max_pfn)
		extra_pages += max_pages - max_pfn;

	/*
	 * Set P2M for all non-RAM pages and E820 gaps to be identity
	 * type PFNs.  Any RAM pages that would be made inaccesible by
	 * this are first released.
	 */
	xen_released_pages = xen_set_identity_and_release(
		map, memmap.nr_entries, max_pfn);
	extra_pages += xen_released_pages;

	/*
	 * Clamp the amount of extra memory to a EXTRA_MEM_RATIO
	 * factor the base size.  On non-highmem systems, the base
	 * size is the full initial memory allocation; on highmem it
	 * is limited to the max size of lowmem, so that it doesn't
	 * get completely filled.
	 *
	 * In principle there could be a problem in lowmem systems if
	 * the initial memory is also very large with respect to
	 * lowmem, but we won't try to deal with that here.
	 */
	extra_pages = min(EXTRA_MEM_RATIO * min(max_pfn, PFN_DOWN(MAXMEM)),
			  extra_pages);

	i = 0;
	while (i < memmap.nr_entries) {
		u64 addr = map[i].addr;
		u64 size = map[i].size;
		u32 type = map[i].type;

		if (type == E820_RAM) {
			if (addr < mem_end) {
				size = min(size, mem_end - addr);
			} else if (extra_pages) {
				size = min(size, (u64)extra_pages * PAGE_SIZE);
				extra_pages -= size / PAGE_SIZE;
				xen_add_extra_mem(addr, size);
			} else
				type = E820_UNUSABLE;
		}

		xen_align_and_add_e820_region(addr, size, type);

		map[i].addr += size;
		map[i].size -= size;
		if (map[i].size == 0)
			i++;
	}
<<<<<<< HEAD
=======
=======
	memcpy(map_raw, map, sizeof(map));
	e820.nr_map = 0;
	xen_extra_mem_start = mem_end;
	for (i = 0; i < memmap.nr_entries; i++) {
		unsigned long long end;

		/* Guard against non-page aligned E820 entries. */
		if (map[i].type == E820_RAM)
			map[i].size -= (map[i].size + map[i].addr) % PAGE_SIZE;

		end = map[i].addr + map[i].size;
		if (map[i].type == E820_RAM && end > mem_end) {
			/* RAM off the end - may be partially included */
			u64 delta = min(map[i].size, end - mem_end);

			map[i].size -= delta;
			end -= delta;

			extra_pages += PFN_DOWN(delta);
			/*
			 * Set RAM below 4GB that is not for us to be unusable.
			 * This prevents "System RAM" address space from being
			 * used as potential resource for I/O address (happens
			 * when 'allocate_resource' is called).
			 */
			if (delta &&
				(xen_initial_domain() && end < 0x100000000ULL))
				e820_add_region(end, delta, E820_UNUSABLE);
		}

		if (map[i].size > 0 && end > xen_extra_mem_start)
			xen_extra_mem_start = end;

		/* Add region if any remains */
		if (map[i].size > 0)
			e820_add_region(map[i].addr, map[i].size, map[i].type);
	}
	/* Align the balloon area so that max_low_pfn does not get set
	 * to be at the _end_ of the PCI gap at the far end (fee01000).
	 * Note that xen_extra_mem_start gets set in the loop above to be
	 * past the last E820 region. */
	if (xen_initial_domain() && (xen_extra_mem_start < (1ULL<<32)))
		xen_extra_mem_start = (1ULL<<32);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * In domU, the ISA region is normal, usable memory, but we
	 * reserve ISA memory anyway because too many things poke
	 * about in there.
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	 *
	 * In Dom0, the host E820 information can leave gaps in the
	 * ISA range, which would cause us to release those pages.  To
	 * avoid this, we unconditionally reserve them here.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	e820_add_region(ISA_START_ADDRESS, ISA_END_ADDRESS - ISA_START_ADDRESS,
			E820_RESERVED);

	/*
	 * Reserve Xen bits:
	 *  - mfn_list
	 *  - xen_start_info
	 * See comment above "struct start_info" in <xen/interface/xen.h>
	 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	memblock_reserve(__pa(xen_start_info->mfn_list),
			 xen_start_info->pt_base - xen_start_info->mfn_list);

	sanitize_e820_map(e820.map, ARRAY_SIZE(e820.map), &e820.nr_map);

<<<<<<< HEAD
=======
=======
	memblock_x86_reserve_range(__pa(xen_start_info->mfn_list),
		      __pa(xen_start_info->pt_base),
			"XEN START INFO");

	sanitize_e820_map(e820.map, ARRAY_SIZE(e820.map), &e820.nr_map);

	extra_limit = xen_get_max_pages();
	if (max_pfn + extra_pages > extra_limit) {
		if (extra_limit > max_pfn)
			extra_pages = extra_limit - max_pfn;
		else
			extra_pages = 0;
	}

	extra_pages += xen_return_unused_memory(xen_start_info->nr_pages, &e820);

	/*
	 * Clamp the amount of extra memory to a EXTRA_MEM_RATIO
	 * factor the base size.  On non-highmem systems, the base
	 * size is the full initial memory allocation; on highmem it
	 * is limited to the max size of lowmem, so that it doesn't
	 * get completely filled.
	 *
	 * In principle there could be a problem in lowmem systems if
	 * the initial memory is also very large with respect to
	 * lowmem, but we won't try to deal with that here.
	 */
	extra_limit = min(EXTRA_MEM_RATIO * min(max_pfn, PFN_DOWN(MAXMEM)),
			  max_pfn + extra_pages);

	if (extra_limit >= max_pfn)
		extra_pages = extra_limit - max_pfn;
	else
		extra_pages = 0;

	xen_add_extra_mem(extra_pages);

	/*
	 * Set P2M for all non-RAM pages and E820 gaps to be identity
	 * type PFNs. We supply it with the non-sanitized version
	 * of the E820.
	 */
	identity_pages = xen_set_identity(map_raw, memmap.nr_entries);
	printk(KERN_INFO "Set %ld page(s) to 1-1 mapping.\n", identity_pages);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return "Xen";
}

/*
 * Set the bit indicating "nosegneg" library variants should be used.
 * We only need to bother in pure 32-bit mode; compat 32-bit processes
 * can have un-truncated segments, so wrapping around is allowed.
 */
static void __init fiddle_vdso(void)
{
#ifdef CONFIG_X86_32
	u32 *mask;
	mask = VDSO32_SYMBOL(&vdso32_int80_start, NOTE_MASK);
	*mask |= 1 << VDSO_NOTE_NONEGSEG_BIT;
	mask = VDSO32_SYMBOL(&vdso32_sysenter_start, NOTE_MASK);
	*mask |= 1 << VDSO_NOTE_NONEGSEG_BIT;
#endif
}

static int __cpuinit register_callback(unsigned type, const void *func)
{
	struct callback_register callback = {
		.type = type,
		.address = XEN_CALLBACK(__KERNEL_CS, func),
		.flags = CALLBACKF_mask_events,
	};

	return HYPERVISOR_callback_op(CALLBACKOP_register, &callback);
}

void __cpuinit xen_enable_sysenter(void)
{
	int ret;
	unsigned sysenter_feature;

#ifdef CONFIG_X86_32
	sysenter_feature = X86_FEATURE_SEP;
#else
	sysenter_feature = X86_FEATURE_SYSENTER32;
#endif

	if (!boot_cpu_has(sysenter_feature))
		return;

	ret = register_callback(CALLBACKTYPE_sysenter, xen_sysenter_target);
	if(ret != 0)
		setup_clear_cpu_cap(sysenter_feature);
}

void __cpuinit xen_enable_syscall(void)
{
#ifdef CONFIG_X86_64
	int ret;

	ret = register_callback(CALLBACKTYPE_syscall, xen_syscall_target);
	if (ret != 0) {
		printk(KERN_ERR "Failed to set syscall callback: %d\n", ret);
		/* Pretty fatal; 64-bit userspace has no other
		   mechanism for syscalls. */
	}

	if (boot_cpu_has(X86_FEATURE_SYSCALL32)) {
		ret = register_callback(CALLBACKTYPE_syscall32,
					xen_syscall32_target);
		if (ret != 0)
			setup_clear_cpu_cap(X86_FEATURE_SYSCALL32);
	}
#endif /* CONFIG_X86_64 */
}

void __init xen_arch_setup(void)
{
	xen_panic_handler_init();

	HYPERVISOR_vm_assist(VMASST_CMD_enable, VMASST_TYPE_4gb_segments);
	HYPERVISOR_vm_assist(VMASST_CMD_enable, VMASST_TYPE_writable_pagetables);

	if (!xen_feature(XENFEAT_auto_translated_physmap))
		HYPERVISOR_vm_assist(VMASST_CMD_enable,
				     VMASST_TYPE_pae_extended_cr3);

	if (register_callback(CALLBACKTYPE_event, xen_hypervisor_callback) ||
	    register_callback(CALLBACKTYPE_failsafe, xen_failsafe_callback))
		BUG();

	xen_enable_sysenter();
	xen_enable_syscall();

#ifdef CONFIG_ACPI
	if (!(xen_start_info->flags & SIF_INITDOMAIN)) {
		printk(KERN_INFO "ACPI in unprivileged domain disabled\n");
		disable_acpi();
	}
#endif

	memcpy(boot_command_line, xen_start_info->cmd_line,
	       MAX_GUEST_CMDLINE > COMMAND_LINE_SIZE ?
	       COMMAND_LINE_SIZE : MAX_GUEST_CMDLINE);

	/* Set up idle, making sure it calls safe_halt() pvop */
#ifdef CONFIG_X86_32
	boot_cpu_data.hlt_works_ok = 1;
#endif
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	disable_cpuidle();
	disable_cpufreq();
	WARN_ON(set_pm_idle_to_default());
	fiddle_vdso();
<<<<<<< HEAD
=======
=======
	pm_idle = default_idle;
	boot_option_idle_override = IDLE_HALT;

	fiddle_vdso();
#ifdef CONFIG_NUMA
	numa_off = 1;
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
