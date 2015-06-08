#ifndef _ASM_X86_IA32_UNISTD_H
#define _ASM_X86_IA32_UNISTD_H

/*
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * This file contains the system call numbers of the ia32 compat ABI,
 * this is for the kernel only.
 */
#define __SYSCALL_ia32_NR(x) (x)
#include <asm/unistd_32_ia32.h>
<<<<<<< HEAD
=======
=======
 * This file contains the system call numbers of the ia32 port,
 * this is for the kernel only.
 * Only add syscalls here where some part of the kernel needs to know
 * the number. This should be otherwise in sync with asm-x86/unistd_32.h. -AK
 */

#define __NR_ia32_restart_syscall 0
#define __NR_ia32_exit		  1
#define __NR_ia32_read		  3
#define __NR_ia32_write		  4
#define __NR_ia32_sigreturn	119
#define __NR_ia32_rt_sigreturn	173
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* _ASM_X86_IA32_UNISTD_H */
