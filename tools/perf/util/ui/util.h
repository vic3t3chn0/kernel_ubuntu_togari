#ifndef _PERF_UI_UTIL_H_
#define _PERF_UI_UTIL_H_ 1

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <stdarg.h>

int ui__getch(int delay_secs);
int ui__popup_menu(int argc, char * const argv[]);
int ui__help_window(const char *text);
int ui__dialog_yesno(const char *msg);
int ui__question_window(const char *title, const char *text,
			const char *exit_msg, int delay_secs);
int __ui__warning(const char *title, const char *format, va_list args);
<<<<<<< HEAD
=======
=======
#include <stdbool.h>

int ui__popup_menu(int argc, char * const argv[]);
int ui__help_window(const char *text);
bool ui__dialog_yesno(const char *msg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* _PERF_UI_UTIL_H_ */
