#ifndef PERF_BUILD_ID_H_
#define PERF_BUILD_ID_H_ 1

#include "session.h"

<<<<<<< HEAD
extern struct perf_tool build_id__mark_dso_hit_ops;
=======
<<<<<<< HEAD
extern struct perf_tool build_id__mark_dso_hit_ops;
=======
extern struct perf_event_ops build_id__mark_dso_hit_ops;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

char *dso__build_id_filename(struct dso *self, char *bf, size_t size);

#endif
