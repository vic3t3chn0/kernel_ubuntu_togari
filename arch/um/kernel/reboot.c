/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 */

#include "linux/sched.h"
#include "linux/slab.h"
#include "kern_util.h"
#include "os.h"
#include "skas.h"

void (*pm_power_off)(void);

static void kill_off_processes(void)
{
	if (proc_mm)
		/*
		 * FIXME: need to loop over userspace_pids
		 */
		os_kill_ptraced_process(userspace_pid[0], 1);
	else {
		struct task_struct *p;
<<<<<<< HEAD
		int pid;

=======
<<<<<<< HEAD
		int pid;

=======
		int pid, me;

		me = os_getpid();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		for_each_process(p) {
			if (p->mm == NULL)
				continue;

			pid = p->mm->context.id.u.pid;
			os_kill_ptraced_process(pid, 1);
		}
	}
}

void uml_cleanup(void)
{
	kmalloc_ok = 0;
	do_uml_exitcalls();
	kill_off_processes();
}

void machine_restart(char * __unused)
{
	uml_cleanup();
	reboot_skas();
}

void machine_power_off(void)
{
	uml_cleanup();
	halt_skas();
}

void machine_halt(void)
{
	machine_power_off();
}
