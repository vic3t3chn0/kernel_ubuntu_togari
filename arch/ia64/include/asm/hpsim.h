#ifndef _ASMIA64_HPSIM_H
#define _ASMIA64_HPSIM_H

#ifndef CONFIG_HP_SIMSERIAL_CONSOLE
static inline int simcons_register(void) { return 1; }
#else
int simcons_register(void);
#endif

struct tty_driver;
extern struct tty_driver *hp_simserial_driver;

<<<<<<< HEAD
extern int hpsim_get_irq(int intr);
=======
<<<<<<< HEAD
extern int hpsim_get_irq(int intr);
=======
void ia64_ssc_connect_irq(long intr, long irq);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void ia64_ctl_trace(long on);

#endif
