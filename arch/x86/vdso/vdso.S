<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/page_types.h>
#include <linux/linkage.h>
#include <linux/init.h>

__PAGE_ALIGNED_DATA

	.globl vdso_start, vdso_end
	.align PAGE_SIZE
vdso_start:
	.incbin "arch/x86/vdso/vdso.so"
vdso_end:
	.align PAGE_SIZE /* extra data here leaks to userspace. */

.previous

	.globl vdso_pages
	.bss
	.align 8
	.type vdso_pages, @object
vdso_pages:
	.zero (vdso_end - vdso_start + PAGE_SIZE - 1) / PAGE_SIZE * 8
	.size vdso_pages, .-vdso_pages
<<<<<<< HEAD
=======
=======
#include <linux/init.h>

__INITDATA

	.globl vdso_start, vdso_end
vdso_start:
	.incbin "arch/x86/vdso/vdso.so"
vdso_end:

__FINIT
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
