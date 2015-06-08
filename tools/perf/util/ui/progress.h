#ifndef _PERF_UI_PROGRESS_H_
#define _PERF_UI_PROGRESS_H_ 1

<<<<<<< HEAD
#include <../types.h>

void ui_progress__update(u64 curr, u64 total, const char *title);
=======
<<<<<<< HEAD
#include <../types.h>

void ui_progress__update(u64 curr, u64 total, const char *title);
=======
struct ui_progress;

struct ui_progress *ui_progress__new(const char *title, u64 total);
void ui_progress__delete(struct ui_progress *self);

void ui_progress__update(struct ui_progress *self, u64 curr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif
