#ifndef XEN_HVC_CONSOLE_H
#define XEN_HVC_CONSOLE_H

extern struct console xenboot_console;

#ifdef CONFIG_HVC_XEN
void xen_console_resume(void);
void xen_raw_console_write(const char *str);
<<<<<<< HEAD
__printf(1, 2)
=======
<<<<<<< HEAD
__printf(1, 2)
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void xen_raw_printk(const char *fmt, ...);
#else
static inline void xen_console_resume(void) { }
static inline void xen_raw_console_write(const char *str) { }
<<<<<<< HEAD
static inline __printf(1, 2)
void xen_raw_printk(const char *fmt, ...) { }
=======
<<<<<<< HEAD
static inline __printf(1, 2)
void xen_raw_printk(const char *fmt, ...) { }
=======
static inline void xen_raw_printk(const char *fmt, ...) { }
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif

#endif	/* XEN_HVC_CONSOLE_H */
