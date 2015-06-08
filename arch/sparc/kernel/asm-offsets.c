/*
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate asm statements containing #defines,
 * compile this file to assembler, and then extract the
 * #defines from the assembly-language output.
 *
 * On sparc, thread_info data is static and TI_XXX offsets are computed by hand.
 */

#include <linux/sched.h>
// #include <linux/mm.h>
#include <linux/kbuild.h>

#ifdef CONFIG_SPARC32
int sparc32_foo(void)
{
	DEFINE(AOFF_thread_fork_kpsr,
			offsetof(struct thread_struct, fork_kpsr));
	return 0;
}
#else
int sparc64_foo(void)
{
	return 0;
}
#endif

int foo(void)
{
	BLANK();
	DEFINE(AOFF_task_thread, offsetof(struct task_struct, thread));
	BLANK();
	DEFINE(AOFF_mm_context, offsetof(struct mm_struct, context));
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	BLANK();
	DEFINE(VMA_VM_MM,    offsetof(struct vm_area_struct, vm_mm));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* DEFINE(NUM_USER_SEGMENTS, TASK_SIZE>>28); */
	return 0;
}

