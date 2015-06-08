#ifndef __PERF_EVLIST_H
#define __PERF_EVLIST_H 1

#include <linux/list.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <stdio.h>
#include "../perf.h"
#include "event.h"
#include "util.h"
#include <unistd.h>
<<<<<<< HEAD
=======
=======
#include "../perf.h"
#include "event.h"
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct pollfd;
struct thread_map;
struct cpu_map;
<<<<<<< HEAD
struct perf_record_opts;
=======
<<<<<<< HEAD
struct perf_record_opts;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define PERF_EVLIST__HLIST_BITS 8
#define PERF_EVLIST__HLIST_SIZE (1 << PERF_EVLIST__HLIST_BITS)

struct perf_evlist {
	struct list_head entries;
	struct hlist_head heads[PERF_EVLIST__HLIST_SIZE];
	int		 nr_entries;
	int		 nr_fds;
	int		 nr_mmaps;
	int		 mmap_len;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct {
		int	cork_fd;
		pid_t	pid;
	} workload;
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	bool		 overwrite;
	union perf_event event_copy;
	struct perf_mmap *mmap;
	struct pollfd	 *pollfd;
	struct thread_map *threads;
	struct cpu_map	  *cpus;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct perf_evsel *selected;
};

struct perf_evsel_str_handler {
	const char *name;
	void	   *handler;
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct perf_evsel;

struct perf_evlist *perf_evlist__new(struct cpu_map *cpus,
				     struct thread_map *threads);
void perf_evlist__init(struct perf_evlist *evlist, struct cpu_map *cpus,
		       struct thread_map *threads);
void perf_evlist__exit(struct perf_evlist *evlist);
void perf_evlist__delete(struct perf_evlist *evlist);

void perf_evlist__add(struct perf_evlist *evlist, struct perf_evsel *entry);
int perf_evlist__add_default(struct perf_evlist *evlist);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int perf_evlist__add_attrs(struct perf_evlist *evlist,
			   struct perf_event_attr *attrs, size_t nr_attrs);
int perf_evlist__add_tracepoints(struct perf_evlist *evlist,
				 const char *tracepoints[], size_t nr_tracepoints);
int perf_evlist__set_tracepoints_handlers(struct perf_evlist *evlist,
					  const struct perf_evsel_str_handler *assocs,
					  size_t nr_assocs);

#define perf_evlist__add_attrs_array(evlist, array) \
	perf_evlist__add_attrs(evlist, array, ARRAY_SIZE(array))

#define perf_evlist__add_tracepoints_array(evlist, array) \
	perf_evlist__add_tracepoints(evlist, array, ARRAY_SIZE(array))

#define perf_evlist__set_tracepoints_handlers_array(evlist, array) \
	perf_evlist__set_tracepoints_handlers(evlist, array, ARRAY_SIZE(array))
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void perf_evlist__id_add(struct perf_evlist *evlist, struct perf_evsel *evsel,
			 int cpu, int thread, u64 id);

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
int perf_evlist__alloc_pollfd(struct perf_evlist *evlist);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void perf_evlist__add_pollfd(struct perf_evlist *evlist, int fd);

struct perf_evsel *perf_evlist__id2evsel(struct perf_evlist *evlist, u64 id);

union perf_event *perf_evlist__mmap_read(struct perf_evlist *self, int idx);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int perf_evlist__open(struct perf_evlist *evlist, bool group);

void perf_evlist__config_attrs(struct perf_evlist *evlist,
			       struct perf_record_opts *opts);

int perf_evlist__prepare_workload(struct perf_evlist *evlist,
				  struct perf_record_opts *opts,
				  const char *argv[]);
int perf_evlist__start_workload(struct perf_evlist *evlist);

int perf_evlist__mmap(struct perf_evlist *evlist, unsigned int pages,
		      bool overwrite);
void perf_evlist__munmap(struct perf_evlist *evlist);

void perf_evlist__disable(struct perf_evlist *evlist);
void perf_evlist__enable(struct perf_evlist *evlist);

void perf_evlist__set_selected(struct perf_evlist *evlist,
			       struct perf_evsel *evsel);

<<<<<<< HEAD
=======
=======
int perf_evlist__alloc_mmap(struct perf_evlist *evlist);
int perf_evlist__mmap(struct perf_evlist *evlist, int pages, bool overwrite);
void perf_evlist__munmap(struct perf_evlist *evlist);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline void perf_evlist__set_maps(struct perf_evlist *evlist,
					 struct cpu_map *cpus,
					 struct thread_map *threads)
{
	evlist->cpus	= cpus;
	evlist->threads	= threads;
}

<<<<<<< HEAD
int perf_evlist__create_maps(struct perf_evlist *evlist, const char *target_pid,
			     const char *tid, uid_t uid, const char *cpu_list);
=======
<<<<<<< HEAD
int perf_evlist__create_maps(struct perf_evlist *evlist, const char *target_pid,
			     const char *tid, uid_t uid, const char *cpu_list);
=======
int perf_evlist__create_maps(struct perf_evlist *evlist, pid_t target_pid,
			     pid_t target_tid, const char *cpu_list);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void perf_evlist__delete_maps(struct perf_evlist *evlist);
int perf_evlist__set_filters(struct perf_evlist *evlist);

u64 perf_evlist__sample_type(const struct perf_evlist *evlist);
bool perf_evlist__sample_id_all(const const struct perf_evlist *evlist);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
u16 perf_evlist__id_hdr_size(const struct perf_evlist *evlist);

bool perf_evlist__valid_sample_type(const struct perf_evlist *evlist);
bool perf_evlist__valid_sample_id_all(const struct perf_evlist *evlist);

void perf_evlist__splice_list_tail(struct perf_evlist *evlist,
				   struct list_head *list,
				   int nr_entries);

<<<<<<< HEAD
=======
=======

bool perf_evlist__valid_sample_type(const struct perf_evlist *evlist);
bool perf_evlist__valid_sample_id_all(const struct perf_evlist *evlist);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* __PERF_EVLIST_H */
