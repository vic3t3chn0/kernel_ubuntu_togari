#ifndef _ASM_X86_IDLE_H
#define _ASM_X86_IDLE_H

#ifdef CONFIG_X86_64
void enter_idle(void);
void exit_idle(void);
#else /* !CONFIG_X86_64 */
static inline void enter_idle(void) { }
static inline void exit_idle(void) { }
<<<<<<< HEAD
static inline void __exit_idle(void) { }
=======
<<<<<<< HEAD
static inline void __exit_idle(void) { }
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* CONFIG_X86_64 */

void amd_e400_remove_cpu(int cpu);

#endif /* _ASM_X86_IDLE_H */
