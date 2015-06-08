#ifndef _PERF_UI_HELPLINE_H_
#define _PERF_UI_HELPLINE_H_ 1

<<<<<<< HEAD
#include <stdio.h>
#include <stdarg.h>

=======
<<<<<<< HEAD
#include <stdio.h>
#include <stdarg.h>

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void ui_helpline__init(void);
void ui_helpline__pop(void);
void ui_helpline__push(const char *msg);
void ui_helpline__vpush(const char *fmt, va_list ap);
void ui_helpline__fpush(const char *fmt, ...);
void ui_helpline__puts(const char *msg);

<<<<<<< HEAD
extern char ui_helpline__current[];

=======
<<<<<<< HEAD
extern char ui_helpline__current[];

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* _PERF_UI_HELPLINE_H_ */
