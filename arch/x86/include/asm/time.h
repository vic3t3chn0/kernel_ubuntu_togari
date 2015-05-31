#ifndef _ASM_X86_TIME_H
#define _ASM_X86_TIME_H

<<<<<<< HEAD
#include <linux/clocksource.h>
#include <asm/mc146818rtc.h>

extern void hpet_time_init(void);
extern void time_init(void);

extern struct clock_event_device *global_clock_event;

=======
extern void hpet_time_init(void);

#include <asm/mc146818rtc.h>

extern void time_init(void);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /* _ASM_X86_TIME_H */
