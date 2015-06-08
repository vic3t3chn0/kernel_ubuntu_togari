#include <linux/kernel.h>
#include <linux/crash_dump.h>
#include <linux/init.h>
#include <linux/errno.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/module.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * If we have booted due to a crash, max_pfn will be a very low value. We need
 * to know the amount of memory that the previous kernel used.
 */
unsigned long saved_max_pfn;

/*
 * stores the physical address of elf header of crash image
 *
 * Note: elfcorehdr_addr is not just limited to vmcore. It is also used by
 * is_kdump_kernel() to determine if we are booting after a panic. Hence put
 * it under CONFIG_CRASH_DUMP and not CONFIG_PROC_VMCORE.
 */
unsigned long long elfcorehdr_addr = ELFCORE_ADDR_MAX;

/*
<<<<<<< HEAD
<<<<<<< HEAD
 * stores the size of elf header of crash image
 */
unsigned long long elfcorehdr_size;

/*
 * elfcorehdr= specifies the location of elf core header stored by the crashed
 * kernel. This option will be passed by kexec loader to the capture kernel.
 *
 * Syntax: elfcorehdr=[size[KMG]@]offset[KMG]
=======
 * elfcorehdr= specifies the location of elf core header stored by the crashed
 * kernel. This option will be passed by kexec loader to the capture kernel.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * elfcorehdr= specifies the location of elf core header stored by the crashed
 * kernel. This option will be passed by kexec loader to the capture kernel.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int __init setup_elfcorehdr(char *arg)
{
	char *end;
	if (!arg)
		return -EINVAL;
	elfcorehdr_addr = memparse(arg, &end);
<<<<<<< HEAD
<<<<<<< HEAD
	if (*end == '@') {
		elfcorehdr_size = elfcorehdr_addr;
		elfcorehdr_addr = memparse(end + 1, &end);
	}
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return end > arg ? 0 : -EINVAL;
}
early_param("elfcorehdr", setup_elfcorehdr);
