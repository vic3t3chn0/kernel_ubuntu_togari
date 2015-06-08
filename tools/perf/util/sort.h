#ifndef __PERF_SORT_H
#define __PERF_SORT_H
#include "../builtin.h"

#include "util.h"

#include "color.h"
#include <linux/list.h>
#include "cache.h"
#include <linux/rbtree.h>
#include "symbol.h"
#include "string.h"
#include "callchain.h"
#include "strlist.h"
#include "values.h"

#include "../perf.h"
#include "debug.h"
#include "header.h"

#include "parse-options.h"
#include "parse-events.h"

#include "thread.h"
#include "sort.h"

extern regex_t parent_regex;
extern const char *sort_order;
extern const char default_parent_pattern[];
extern const char *parent_pattern;
extern const char default_sort_order[];
extern int sort__need_collapse;
extern int sort__has_parent;
<<<<<<< HEAD
extern int sort__branch_mode;
=======
<<<<<<< HEAD
extern int sort__branch_mode;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern char *field_sep;
extern struct sort_entry sort_comm;
extern struct sort_entry sort_dso;
extern struct sort_entry sort_sym;
extern struct sort_entry sort_parent;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern struct sort_entry sort_dso_from;
extern struct sort_entry sort_dso_to;
extern struct sort_entry sort_sym_from;
extern struct sort_entry sort_sym_to;
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern enum sort_type sort__first_dimension;

/**
 * struct hist_entry - histogram entry
 *
 * @row_offset - offset from the first callchain expanded to appear on screen
 * @nr_rows - rows expanded in callchain, recalculated on folding/unfolding
 */
struct hist_entry {
<<<<<<< HEAD
	struct rb_node		rb_node_in;
=======
<<<<<<< HEAD
	struct rb_node		rb_node_in;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct rb_node		rb_node;
	u64			period;
	u64			period_sys;
	u64			period_us;
	u64			period_guest_sys;
	u64			period_guest_us;
	struct map_symbol	ms;
	struct thread		*thread;
	u64			ip;
	s32			cpu;
	u32			nr_events;

	/* XXX These two should move to some tree widget lib */
	u16			row_offset;
	u16			nr_rows;

	bool			init_have_children;
	char			level;
<<<<<<< HEAD
	bool			used;
=======
<<<<<<< HEAD
	bool			used;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8			filtered;
	struct symbol		*parent;
	union {
		unsigned long	  position;
		struct hist_entry *pair;
		struct rb_root	  sorted_chain;
	};
<<<<<<< HEAD
	struct branch_info	*branch_info;
=======
<<<<<<< HEAD
	struct branch_info	*branch_info;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct callchain_root	callchain[0];
};

enum sort_type {
	SORT_PID,
	SORT_COMM,
	SORT_DSO,
	SORT_SYM,
	SORT_PARENT,
	SORT_CPU,
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	SORT_DSO_FROM,
	SORT_DSO_TO,
	SORT_SYM_FROM,
	SORT_SYM_TO,
	SORT_MISPREDICT,
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/*
 * configurable sorting bits
 */

struct sort_entry {
	struct list_head list;

	const char *se_header;

	int64_t (*se_cmp)(struct hist_entry *, struct hist_entry *);
	int64_t (*se_collapse)(struct hist_entry *, struct hist_entry *);
	int	(*se_snprintf)(struct hist_entry *self, char *bf, size_t size,
			       unsigned int width);
	u8	se_width_idx;
	bool	elide;
};

extern struct sort_entry sort_thread;
extern struct list_head hist_entry__sort_list;

void setup_sorting(const char * const usagestr[], const struct option *opts);
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

extern size_t sort__thread_print(FILE *, struct hist_entry *, unsigned int);
extern size_t sort__comm_print(FILE *, struct hist_entry *, unsigned int);
extern size_t sort__dso_print(FILE *, struct hist_entry *, unsigned int);
extern size_t sort__sym_print(FILE *, struct hist_entry *, unsigned int __used);
extern int64_t cmp_null(void *, void *);
extern int64_t sort__thread_cmp(struct hist_entry *, struct hist_entry *);
extern int64_t sort__comm_cmp(struct hist_entry *, struct hist_entry *);
extern int64_t sort__comm_collapse(struct hist_entry *, struct hist_entry *);
extern int64_t sort__dso_cmp(struct hist_entry *, struct hist_entry *);
extern int64_t sort__sym_cmp(struct hist_entry *, struct hist_entry *);
extern int64_t sort__parent_cmp(struct hist_entry *, struct hist_entry *);
int64_t sort__cpu_cmp(struct hist_entry *left, struct hist_entry *right);
extern size_t sort__parent_print(FILE *, struct hist_entry *, unsigned int);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int sort_dimension__add(const char *);
void sort_entry__setup_elide(struct sort_entry *self, struct strlist *list,
			     const char *list_name, FILE *fp);

#endif	/* __PERF_SORT_H */
