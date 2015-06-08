/*
 *	Variables and functions used by the code in sleep.c
 */

#include <asm/trampoline.h>
<<<<<<< HEAD
#include <linux/linkage.h>
=======
<<<<<<< HEAD
#include <linux/linkage.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

extern unsigned long saved_video_mode;
extern long saved_magic;

extern int wakeup_pmode_return;

<<<<<<< HEAD
extern u8 wake_sleep_flags;
extern asmlinkage void acpi_enter_s3(void);

=======
<<<<<<< HEAD
extern u8 wake_sleep_flags;
extern asmlinkage void acpi_enter_s3(void);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern unsigned long acpi_copy_wakeup_routine(unsigned long);
extern void wakeup_long64(void);

extern void do_suspend_lowlevel(void);
