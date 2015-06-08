#ifndef _ASM_GENERIC_EMERGENCY_RESTART_H
#define _ASM_GENERIC_EMERGENCY_RESTART_H

static inline void machine_emergency_restart(void)
{
<<<<<<< HEAD
	machine_restart(NULL);
=======
<<<<<<< HEAD
	machine_restart(NULL);
=======
#ifdef CONFIG_ANDROID_WIP
	machine_restart("emergency");
#else
	machine_restart(NULL);
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

#endif /* _ASM_GENERIC_EMERGENCY_RESTART_H */
