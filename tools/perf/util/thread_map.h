#ifndef __PERF_THREAD_MAP_H
#define __PERF_THREAD_MAP_H

#include <sys/types.h>
<<<<<<< HEAD
#include <stdio.h>
=======
<<<<<<< HEAD
#include <stdio.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct thread_map {
	int nr;
	int map[];
};

struct thread_map *thread_map__new_by_pid(pid_t pid);
struct thread_map *thread_map__new_by_tid(pid_t tid);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct thread_map *thread_map__new_by_uid(uid_t uid);
struct thread_map *thread_map__new(pid_t pid, pid_t tid, uid_t uid);

struct thread_map *thread_map__new_str(const char *pid,
		const char *tid, uid_t uid);

void thread_map__delete(struct thread_map *threads);

size_t thread_map__fprintf(struct thread_map *threads, FILE *fp);

<<<<<<< HEAD
=======
=======
struct thread_map *thread_map__new(pid_t pid, pid_t tid);
void thread_map__delete(struct thread_map *threads);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif	/* __PERF_THREAD_MAP_H */
