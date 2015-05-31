#include "annotate.h"
#include "util.h"
#include "build-id.h"
#include "hist.h"
#include "session.h"
#include "sort.h"
#include <math.h>

<<<<<<< HEAD
static bool hists__filter_entry_by_dso(struct hists *hists,
				       struct hist_entry *he);
static bool hists__filter_entry_by_thread(struct hists *hists,
					  struct hist_entry *he);
static bool hists__filter_entry_by_symbol(struct hists *hists,
					  struct hist_entry *he);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
enum hist_filter {
	HIST_FILTER__DSO,
	HIST_FILTER__THREAD,
	HIST_FILTER__PARENT,
<<<<<<< HEAD
	HIST_FILTER__SYMBOL,
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

struct callchain_param	callchain_param = {
	.mode	= CHAIN_GRAPH_REL,
<<<<<<< HEAD
	.min_percent = 0.5,
	.order  = ORDER_CALLEE
};

u16 hists__col_len(struct hists *hists, enum hist_column col)
{
	return hists->col_len[col];
}

void hists__set_col_len(struct hists *hists, enum hist_column col, u16 len)
{
	hists->col_len[col] = len;
}

bool hists__new_col_len(struct hists *hists, enum hist_column col, u16 len)
{
	if (len > hists__col_len(hists, col)) {
		hists__set_col_len(hists, col, len);
=======
	.min_percent = 0.5
};

u16 hists__col_len(struct hists *self, enum hist_column col)
{
	return self->col_len[col];
}

void hists__set_col_len(struct hists *self, enum hist_column col, u16 len)
{
	self->col_len[col] = len;
}

bool hists__new_col_len(struct hists *self, enum hist_column col, u16 len)
{
	if (len > hists__col_len(self, col)) {
		hists__set_col_len(self, col, len);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		return true;
	}
	return false;
}

<<<<<<< HEAD
static void hists__reset_col_len(struct hists *hists)
=======
static void hists__reset_col_len(struct hists *self)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	enum hist_column col;

	for (col = 0; col < HISTC_NR_COLS; ++col)
<<<<<<< HEAD
		hists__set_col_len(hists, col, 0);
}

static void hists__set_unres_dso_col_len(struct hists *hists, int dso)
{
	const unsigned int unresolved_col_width = BITS_PER_LONG / 4;

	if (hists__col_len(hists, dso) < unresolved_col_width &&
	    !symbol_conf.col_width_list_str && !symbol_conf.field_sep &&
	    !symbol_conf.dso_list)
		hists__set_col_len(hists, dso, unresolved_col_width);
}

static void hists__calc_col_len(struct hists *hists, struct hist_entry *h)
{
	const unsigned int unresolved_col_width = BITS_PER_LONG / 4;
	u16 len;

	if (h->ms.sym)
		hists__new_col_len(hists, HISTC_SYMBOL, h->ms.sym->namelen + 4);
	else
		hists__set_unres_dso_col_len(hists, HISTC_DSO);

	len = thread__comm_len(h->thread);
	if (hists__new_col_len(hists, HISTC_COMM, len))
		hists__set_col_len(hists, HISTC_THREAD, len + 6);

	if (h->ms.map) {
		len = dso__name_len(h->ms.map->dso);
		hists__new_col_len(hists, HISTC_DSO, len);
	}

	if (h->branch_info) {
		int symlen;
		/*
		 * +4 accounts for '[x] ' priv level info
		 * +2 account of 0x prefix on raw addresses
		 */
		if (h->branch_info->from.sym) {
			symlen = (int)h->branch_info->from.sym->namelen + 4;
			hists__new_col_len(hists, HISTC_SYMBOL_FROM, symlen);

			symlen = dso__name_len(h->branch_info->from.map->dso);
			hists__new_col_len(hists, HISTC_DSO_FROM, symlen);
		} else {
			symlen = unresolved_col_width + 4 + 2;
			hists__new_col_len(hists, HISTC_SYMBOL_FROM, symlen);
			hists__set_unres_dso_col_len(hists, HISTC_DSO_FROM);
		}

		if (h->branch_info->to.sym) {
			symlen = (int)h->branch_info->to.sym->namelen + 4;
			hists__new_col_len(hists, HISTC_SYMBOL_TO, symlen);

			symlen = dso__name_len(h->branch_info->to.map->dso);
			hists__new_col_len(hists, HISTC_DSO_TO, symlen);
		} else {
			symlen = unresolved_col_width + 4 + 2;
			hists__new_col_len(hists, HISTC_SYMBOL_TO, symlen);
			hists__set_unres_dso_col_len(hists, HISTC_DSO_TO);
		}
	}
}

static void hist_entry__add_cpumode_period(struct hist_entry *he,
=======
		hists__set_col_len(self, col, 0);
}

static void hists__calc_col_len(struct hists *self, struct hist_entry *h)
{
	u16 len;

	if (h->ms.sym)
		hists__new_col_len(self, HISTC_SYMBOL, h->ms.sym->namelen);
	else {
		const unsigned int unresolved_col_width = BITS_PER_LONG / 4;

		if (hists__col_len(self, HISTC_DSO) < unresolved_col_width &&
		    !symbol_conf.col_width_list_str && !symbol_conf.field_sep &&
		    !symbol_conf.dso_list)
			hists__set_col_len(self, HISTC_DSO,
					   unresolved_col_width);
	}

	len = thread__comm_len(h->thread);
	if (hists__new_col_len(self, HISTC_COMM, len))
		hists__set_col_len(self, HISTC_THREAD, len + 6);

	if (h->ms.map) {
		len = dso__name_len(h->ms.map->dso);
		hists__new_col_len(self, HISTC_DSO, len);
	}
}

static void hist_entry__add_cpumode_period(struct hist_entry *self,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					   unsigned int cpumode, u64 period)
{
	switch (cpumode) {
	case PERF_RECORD_MISC_KERNEL:
<<<<<<< HEAD
		he->period_sys += period;
		break;
	case PERF_RECORD_MISC_USER:
		he->period_us += period;
		break;
	case PERF_RECORD_MISC_GUEST_KERNEL:
		he->period_guest_sys += period;
		break;
	case PERF_RECORD_MISC_GUEST_USER:
		he->period_guest_us += period;
=======
		self->period_sys += period;
		break;
	case PERF_RECORD_MISC_USER:
		self->period_us += period;
		break;
	case PERF_RECORD_MISC_GUEST_KERNEL:
		self->period_guest_sys += period;
		break;
	case PERF_RECORD_MISC_GUEST_USER:
		self->period_guest_us += period;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		break;
	default:
		break;
	}
}

<<<<<<< HEAD
static void hist_entry__decay(struct hist_entry *he)
{
	he->period = (he->period * 7) / 8;
	he->nr_events = (he->nr_events * 7) / 8;
}

static bool hists__decay_entry(struct hists *hists, struct hist_entry *he)
{
	u64 prev_period = he->period;

	if (prev_period == 0)
		return true;

	hist_entry__decay(he);

	if (!he->filtered)
		hists->stats.total_period -= prev_period - he->period;

	return he->period == 0;
}

static void __hists__decay_entries(struct hists *hists, bool zap_user,
				   bool zap_kernel, bool threaded)
{
	struct rb_node *next = rb_first(&hists->entries);
	struct hist_entry *n;

	while (next) {
		n = rb_entry(next, struct hist_entry, rb_node);
		next = rb_next(&n->rb_node);
		/*
		 * We may be annotating this, for instance, so keep it here in
		 * case some it gets new samples, we'll eventually free it when
		 * the user stops browsing and it agains gets fully decayed.
		 */
		if (((zap_user && n->level == '.') ||
		     (zap_kernel && n->level != '.') ||
		     hists__decay_entry(hists, n)) &&
		    !n->used) {
			rb_erase(&n->rb_node, &hists->entries);

			if (sort__need_collapse || threaded)
				rb_erase(&n->rb_node_in, &hists->entries_collapsed);

			hist_entry__free(n);
			--hists->nr_entries;
		}
	}
}

void hists__decay_entries(struct hists *hists, bool zap_user, bool zap_kernel)
{
	return __hists__decay_entries(hists, zap_user, zap_kernel, false);
}

void hists__decay_entries_threaded(struct hists *hists,
				   bool zap_user, bool zap_kernel)
{
	return __hists__decay_entries(hists, zap_user, zap_kernel, true);
}

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
/*
 * histogram, sorted on item, collects periods
 */

static struct hist_entry *hist_entry__new(struct hist_entry *template)
{
	size_t callchain_size = symbol_conf.use_callchain ? sizeof(struct callchain_root) : 0;
<<<<<<< HEAD
	struct hist_entry *he = malloc(sizeof(*he) + callchain_size);

	if (he != NULL) {
		*he = *template;
		he->nr_events = 1;
		if (he->ms.map)
			he->ms.map->referenced = true;
		if (symbol_conf.use_callchain)
			callchain_init(he->callchain);
	}

	return he;
}

static void hists__inc_nr_entries(struct hists *hists, struct hist_entry *h)
{
	if (!h->filtered) {
		hists__calc_col_len(hists, h);
		++hists->nr_entries;
		hists->stats.total_period += h->period;
=======
	struct hist_entry *self = malloc(sizeof(*self) + callchain_size);

	if (self != NULL) {
		*self = *template;
		self->nr_events = 1;
		if (self->ms.map)
			self->ms.map->referenced = true;
		if (symbol_conf.use_callchain)
			callchain_init(self->callchain);
	}

	return self;
}

static void hists__inc_nr_entries(struct hists *self, struct hist_entry *h)
{
	if (!h->filtered) {
		hists__calc_col_len(self, h);
		++self->nr_entries;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}
}

static u8 symbol__parent_filter(const struct symbol *parent)
{
	if (symbol_conf.exclude_other && parent == NULL)
		return 1 << HIST_FILTER__PARENT;
	return 0;
}

<<<<<<< HEAD
static struct hist_entry *add_hist_entry(struct hists *hists,
				      struct hist_entry *entry,
				      struct addr_location *al,
				      u64 period)
{
	struct rb_node **p;
	struct rb_node *parent = NULL;
	struct hist_entry *he;
	int cmp;

	pthread_mutex_lock(&hists->lock);

	p = &hists->entries_in->rb_node;

	while (*p != NULL) {
		parent = *p;
		he = rb_entry(parent, struct hist_entry, rb_node_in);

		cmp = hist_entry__cmp(entry, he);
=======
struct hist_entry *__hists__add_entry(struct hists *self,
				      struct addr_location *al,
				      struct symbol *sym_parent, u64 period)
{
	struct rb_node **p = &self->entries.rb_node;
	struct rb_node *parent = NULL;
	struct hist_entry *he;
	struct hist_entry entry = {
		.thread	= al->thread,
		.ms = {
			.map	= al->map,
			.sym	= al->sym,
		},
		.cpu	= al->cpu,
		.ip	= al->addr,
		.level	= al->level,
		.period	= period,
		.parent = sym_parent,
		.filtered = symbol__parent_filter(sym_parent),
	};
	int cmp;

	while (*p != NULL) {
		parent = *p;
		he = rb_entry(parent, struct hist_entry, rb_node);

		cmp = hist_entry__cmp(&entry, he);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

		if (!cmp) {
			he->period += period;
			++he->nr_events;

			/* If the map of an existing hist_entry has
			 * become out-of-date due to an exec() or
			 * similar, update it.  Otherwise we will
			 * mis-adjust symbol addresses when computing
			 * the history counter to increment.
			 */
<<<<<<< HEAD
			if (he->ms.map != entry->ms.map) {
				he->ms.map = entry->ms.map;
=======
			if (he->ms.map != entry.ms.map) {
				he->ms.map = entry.ms.map;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				if (he->ms.map)
					he->ms.map->referenced = true;
			}
			goto out;
		}

		if (cmp < 0)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}

<<<<<<< HEAD
	he = hist_entry__new(entry);
	if (!he)
		goto out_unlock;

	rb_link_node(&he->rb_node_in, parent, p);
	rb_insert_color(&he->rb_node_in, hists->entries_in);
out:
	hist_entry__add_cpumode_period(he, al->cpumode, period);
out_unlock:
	pthread_mutex_unlock(&hists->lock);
	return he;
}

struct hist_entry *__hists__add_branch_entry(struct hists *self,
					     struct addr_location *al,
					     struct symbol *sym_parent,
					     struct branch_info *bi,
					     u64 period)
{
	struct hist_entry entry = {
		.thread	= al->thread,
		.ms = {
			.map	= bi->to.map,
			.sym	= bi->to.sym,
		},
		.cpu	= al->cpu,
		.ip	= bi->to.addr,
		.level	= al->level,
		.period	= period,
		.parent = sym_parent,
		.filtered = symbol__parent_filter(sym_parent),
		.branch_info = bi,
	};

	return add_hist_entry(self, &entry, al, period);
}

struct hist_entry *__hists__add_entry(struct hists *self,
				      struct addr_location *al,
				      struct symbol *sym_parent, u64 period)
{
	struct hist_entry entry = {
		.thread	= al->thread,
		.ms = {
			.map	= al->map,
			.sym	= al->sym,
		},
		.cpu	= al->cpu,
		.ip	= al->addr,
		.level	= al->level,
		.period	= period,
		.parent = sym_parent,
		.filtered = symbol__parent_filter(sym_parent),
	};

	return add_hist_entry(self, &entry, al, period);
}

=======
	he = hist_entry__new(&entry);
	if (!he)
		return NULL;
	rb_link_node(&he->rb_node, parent, p);
	rb_insert_color(&he->rb_node, &self->entries);
	hists__inc_nr_entries(self, he);
out:
	hist_entry__add_cpumode_period(he, al->cpumode, period);
	return he;
}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
int64_t
hist_entry__cmp(struct hist_entry *left, struct hist_entry *right)
{
	struct sort_entry *se;
	int64_t cmp = 0;

	list_for_each_entry(se, &hist_entry__sort_list, list) {
		cmp = se->se_cmp(left, right);
		if (cmp)
			break;
	}

	return cmp;
}

int64_t
hist_entry__collapse(struct hist_entry *left, struct hist_entry *right)
{
	struct sort_entry *se;
	int64_t cmp = 0;

	list_for_each_entry(se, &hist_entry__sort_list, list) {
		int64_t (*f)(struct hist_entry *, struct hist_entry *);

		f = se->se_collapse ?: se->se_cmp;

		cmp = f(left, right);
		if (cmp)
			break;
	}

	return cmp;
}

void hist_entry__free(struct hist_entry *he)
{
	free(he);
}

/*
 * collapse the histogram
 */

<<<<<<< HEAD
static bool hists__collapse_insert_entry(struct hists *hists,
=======
static bool hists__collapse_insert_entry(struct hists *self,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					 struct rb_root *root,
					 struct hist_entry *he)
{
	struct rb_node **p = &root->rb_node;
	struct rb_node *parent = NULL;
	struct hist_entry *iter;
	int64_t cmp;

	while (*p != NULL) {
		parent = *p;
<<<<<<< HEAD
		iter = rb_entry(parent, struct hist_entry, rb_node_in);
=======
		iter = rb_entry(parent, struct hist_entry, rb_node);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

		cmp = hist_entry__collapse(iter, he);

		if (!cmp) {
			iter->period += he->period;
<<<<<<< HEAD
			iter->nr_events += he->nr_events;
			if (symbol_conf.use_callchain) {
				callchain_cursor_reset(&hists->callchain_cursor);
				callchain_merge(&hists->callchain_cursor, iter->callchain,
=======
			if (symbol_conf.use_callchain) {
				callchain_cursor_reset(&self->callchain_cursor);
				callchain_merge(&self->callchain_cursor, iter->callchain,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
						he->callchain);
			}
			hist_entry__free(he);
			return false;
		}

		if (cmp < 0)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}

<<<<<<< HEAD
	rb_link_node(&he->rb_node_in, parent, p);
	rb_insert_color(&he->rb_node_in, root);
	return true;
}

static struct rb_root *hists__get_rotate_entries_in(struct hists *hists)
{
	struct rb_root *root;

	pthread_mutex_lock(&hists->lock);

	root = hists->entries_in;
	if (++hists->entries_in > &hists->entries_in_array[1])
		hists->entries_in = &hists->entries_in_array[0];

	pthread_mutex_unlock(&hists->lock);

	return root;
}

static void hists__apply_filters(struct hists *hists, struct hist_entry *he)
{
	hists__filter_entry_by_dso(hists, he);
	hists__filter_entry_by_thread(hists, he);
	hists__filter_entry_by_symbol(hists, he);
}

static void __hists__collapse_resort(struct hists *hists, bool threaded)
{
	struct rb_root *root;
	struct rb_node *next;
	struct hist_entry *n;

	if (!sort__need_collapse && !threaded)
		return;

	root = hists__get_rotate_entries_in(hists);
	next = rb_first(root);

	while (next) {
		n = rb_entry(next, struct hist_entry, rb_node_in);
		next = rb_next(&n->rb_node_in);

		rb_erase(&n->rb_node_in, root);
		if (hists__collapse_insert_entry(hists, &hists->entries_collapsed, n)) {
			/*
			 * If it wasn't combined with one of the entries already
			 * collapsed, we need to apply the filters that may have
			 * been set by, say, the hist_browser.
			 */
			hists__apply_filters(hists, n);
		}
	}
}

void hists__collapse_resort(struct hists *hists)
{
	return __hists__collapse_resort(hists, false);
}

void hists__collapse_resort_threaded(struct hists *hists)
{
	return __hists__collapse_resort(hists, true);
=======
	rb_link_node(&he->rb_node, parent, p);
	rb_insert_color(&he->rb_node, root);
	return true;
}

void hists__collapse_resort(struct hists *self)
{
	struct rb_root tmp;
	struct rb_node *next;
	struct hist_entry *n;

	if (!sort__need_collapse)
		return;

	tmp = RB_ROOT;
	next = rb_first(&self->entries);
	self->nr_entries = 0;
	hists__reset_col_len(self);

	while (next) {
		n = rb_entry(next, struct hist_entry, rb_node);
		next = rb_next(&n->rb_node);

		rb_erase(&n->rb_node, &self->entries);
		if (hists__collapse_insert_entry(self, &tmp, n))
			hists__inc_nr_entries(self, n);
	}

	self->entries = tmp;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/*
 * reverse the map, sort on period.
 */

static void __hists__insert_output_entry(struct rb_root *entries,
					 struct hist_entry *he,
					 u64 min_callchain_hits)
{
	struct rb_node **p = &entries->rb_node;
	struct rb_node *parent = NULL;
	struct hist_entry *iter;

	if (symbol_conf.use_callchain)
		callchain_param.sort(&he->sorted_chain, he->callchain,
				      min_callchain_hits, &callchain_param);

	while (*p != NULL) {
		parent = *p;
		iter = rb_entry(parent, struct hist_entry, rb_node);

		if (he->period > iter->period)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}

	rb_link_node(&he->rb_node, parent, p);
	rb_insert_color(&he->rb_node, entries);
}

<<<<<<< HEAD
static void __hists__output_resort(struct hists *hists, bool threaded)
{
	struct rb_root *root;
=======
void hists__output_resort(struct hists *self)
{
	struct rb_root tmp;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct rb_node *next;
	struct hist_entry *n;
	u64 min_callchain_hits;

<<<<<<< HEAD
	min_callchain_hits = hists->stats.total_period * (callchain_param.min_percent / 100);

	if (sort__need_collapse || threaded)
		root = &hists->entries_collapsed;
	else
		root = hists->entries_in;

	next = rb_first(root);
	hists->entries = RB_ROOT;

	hists->nr_entries = 0;
	hists->stats.total_period = 0;
	hists__reset_col_len(hists);

	while (next) {
		n = rb_entry(next, struct hist_entry, rb_node_in);
		next = rb_next(&n->rb_node_in);

		__hists__insert_output_entry(&hists->entries, n, min_callchain_hits);
		hists__inc_nr_entries(hists, n);
	}
}

void hists__output_resort(struct hists *hists)
{
	return __hists__output_resort(hists, false);
}

void hists__output_resort_threaded(struct hists *hists)
{
	return __hists__output_resort(hists, true);
=======
	min_callchain_hits = self->stats.total_period * (callchain_param.min_percent / 100);

	tmp = RB_ROOT;
	next = rb_first(&self->entries);

	self->nr_entries = 0;
	hists__reset_col_len(self);

	while (next) {
		n = rb_entry(next, struct hist_entry, rb_node);
		next = rb_next(&n->rb_node);

		rb_erase(&n->rb_node, &self->entries);
		__hists__insert_output_entry(&tmp, n, min_callchain_hits);
		hists__inc_nr_entries(self, n);
	}

	self->entries = tmp;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

static size_t callchain__fprintf_left_margin(FILE *fp, int left_margin)
{
	int i;
	int ret = fprintf(fp, "            ");

	for (i = 0; i < left_margin; i++)
		ret += fprintf(fp, " ");

	return ret;
}

static size_t ipchain__fprintf_graph_line(FILE *fp, int depth, int depth_mask,
					  int left_margin)
{
	int i;
	size_t ret = callchain__fprintf_left_margin(fp, left_margin);

	for (i = 0; i < depth; i++)
		if (depth_mask & (1 << i))
			ret += fprintf(fp, "|          ");
		else
			ret += fprintf(fp, "           ");

	ret += fprintf(fp, "\n");

	return ret;
}

static size_t ipchain__fprintf_graph(FILE *fp, struct callchain_list *chain,
				     int depth, int depth_mask, int period,
				     u64 total_samples, u64 hits,
				     int left_margin)
{
	int i;
	size_t ret = 0;

	ret += callchain__fprintf_left_margin(fp, left_margin);
	for (i = 0; i < depth; i++) {
		if (depth_mask & (1 << i))
			ret += fprintf(fp, "|");
		else
			ret += fprintf(fp, " ");
		if (!period && i == depth - 1) {
			double percent;

			percent = hits * 100.0 / total_samples;
			ret += percent_color_fprintf(fp, "--%2.2f%%-- ", percent);
		} else
			ret += fprintf(fp, "%s", "          ");
	}
	if (chain->ms.sym)
		ret += fprintf(fp, "%s\n", chain->ms.sym->name);
	else
		ret += fprintf(fp, "%p\n", (void *)(long)chain->ip);

	return ret;
}

static struct symbol *rem_sq_bracket;
static struct callchain_list rem_hits;

static void init_rem_hits(void)
{
	rem_sq_bracket = malloc(sizeof(*rem_sq_bracket) + 6);
	if (!rem_sq_bracket) {
		fprintf(stderr, "Not enough memory to display remaining hits\n");
		return;
	}

	strcpy(rem_sq_bracket->name, "[...]");
	rem_hits.ms.sym = rem_sq_bracket;
}

<<<<<<< HEAD
static size_t __callchain__fprintf_graph(FILE *fp, struct rb_root *root,
=======
static size_t __callchain__fprintf_graph(FILE *fp, struct callchain_node *self,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					 u64 total_samples, int depth,
					 int depth_mask, int left_margin)
{
	struct rb_node *node, *next;
	struct callchain_node *child;
	struct callchain_list *chain;
	int new_depth_mask = depth_mask;
<<<<<<< HEAD
=======
	u64 new_total;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	u64 remaining;
	size_t ret = 0;
	int i;
	uint entries_printed = 0;

<<<<<<< HEAD
	remaining = total_samples;

	node = rb_first(root);
	while (node) {
		u64 new_total;
=======
	if (callchain_param.mode == CHAIN_GRAPH_REL)
		new_total = self->children_hit;
	else
		new_total = total_samples;

	remaining = new_total;

	node = rb_first(&self->rb_root);
	while (node) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		u64 cumul;

		child = rb_entry(node, struct callchain_node, rb_node);
		cumul = callchain_cumul_hits(child);
		remaining -= cumul;

		/*
		 * The depth mask manages the output of pipes that show
		 * the depth. We don't want to keep the pipes of the current
		 * level for the last child of this depth.
		 * Except if we have remaining filtered hits. They will
		 * supersede the last child
		 */
		next = rb_next(node);
		if (!next && (callchain_param.mode != CHAIN_GRAPH_REL || !remaining))
			new_depth_mask &= ~(1 << (depth - 1));

		/*
		 * But we keep the older depth mask for the line separator
		 * to keep the level link until we reach the last child
		 */
		ret += ipchain__fprintf_graph_line(fp, depth, depth_mask,
						   left_margin);
		i = 0;
		list_for_each_entry(chain, &child->val, list) {
			ret += ipchain__fprintf_graph(fp, chain, depth,
						      new_depth_mask, i++,
<<<<<<< HEAD
						      total_samples,
						      cumul,
						      left_margin);
		}

		if (callchain_param.mode == CHAIN_GRAPH_REL)
			new_total = child->children_hit;
		else
			new_total = total_samples;

		ret += __callchain__fprintf_graph(fp, &child->rb_root, new_total,
=======
						      new_total,
						      cumul,
						      left_margin);
		}
		ret += __callchain__fprintf_graph(fp, child, new_total,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
						  depth + 1,
						  new_depth_mask | (1 << depth),
						  left_margin);
		node = next;
		if (++entries_printed == callchain_param.print_limit)
			break;
	}

	if (callchain_param.mode == CHAIN_GRAPH_REL &&
<<<<<<< HEAD
		remaining && remaining != total_samples) {
=======
		remaining && remaining != new_total) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

		if (!rem_sq_bracket)
			return ret;

		new_depth_mask &= ~(1 << (depth - 1));
<<<<<<< HEAD
		ret += ipchain__fprintf_graph(fp, &rem_hits, depth,
					      new_depth_mask, 0, total_samples,
=======

		ret += ipchain__fprintf_graph(fp, &rem_hits, depth,
					      new_depth_mask, 0, new_total,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					      remaining, left_margin);
	}

	return ret;
}

<<<<<<< HEAD
static size_t callchain__fprintf_graph(FILE *fp, struct rb_root *root,
				       u64 total_samples, int left_margin)
{
	struct callchain_node *cnode;
	struct callchain_list *chain;
	u32 entries_printed = 0;
	bool printed = false;
	struct rb_node *node;
	int i = 0;
	int ret;

	/*
	 * If have one single callchain root, don't bother printing
	 * its percentage (100 % in fractal mode and the same percentage
	 * than the hist in graph mode). This also avoid one level of column.
	 */
	node = rb_first(root);
	if (node && !rb_next(node)) {
		cnode = rb_entry(node, struct callchain_node, rb_node);
		list_for_each_entry(chain, &cnode->val, list) {
			/*
			 * If we sort by symbol, the first entry is the same than
			 * the symbol. No need to print it otherwise it appears as
			 * displayed twice.
			 */
			if (!i++ && sort__first_dimension == SORT_SYM)
				continue;
			if (!printed) {
				ret += callchain__fprintf_left_margin(fp, left_margin);
				ret += fprintf(fp, "|\n");
				ret += callchain__fprintf_left_margin(fp, left_margin);
				ret += fprintf(fp, "---");
				left_margin += 3;
				printed = true;
			} else
				ret += callchain__fprintf_left_margin(fp, left_margin);

			if (chain->ms.sym)
				ret += fprintf(fp, " %s\n", chain->ms.sym->name);
			else
				ret += fprintf(fp, " %p\n", (void *)(long)chain->ip);

			if (++entries_printed == callchain_param.print_limit)
				break;
		}
		root = &cnode->rb_root;
	}

	return __callchain__fprintf_graph(fp, root, total_samples,
					  1, 1, left_margin);
}

static size_t __callchain__fprintf_flat(FILE *fp,
					struct callchain_node *self,
					u64 total_samples)
=======
static size_t callchain__fprintf_graph(FILE *fp, struct callchain_node *self,
				       u64 total_samples, int left_margin)
{
	struct callchain_list *chain;
	bool printed = false;
	int i = 0;
	int ret = 0;
	u32 entries_printed = 0;

	list_for_each_entry(chain, &self->val, list) {
		if (!i++ && sort__first_dimension == SORT_SYM)
			continue;

		if (!printed) {
			ret += callchain__fprintf_left_margin(fp, left_margin);
			ret += fprintf(fp, "|\n");
			ret += callchain__fprintf_left_margin(fp, left_margin);
			ret += fprintf(fp, "---");

			left_margin += 3;
			printed = true;
		} else
			ret += callchain__fprintf_left_margin(fp, left_margin);

		if (chain->ms.sym)
			ret += fprintf(fp, " %s\n", chain->ms.sym->name);
		else
			ret += fprintf(fp, " %p\n", (void *)(long)chain->ip);

		if (++entries_printed == callchain_param.print_limit)
			break;
	}

	ret += __callchain__fprintf_graph(fp, self, total_samples, 1, 1, left_margin);

	return ret;
}

static size_t callchain__fprintf_flat(FILE *fp, struct callchain_node *self,
				      u64 total_samples)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	struct callchain_list *chain;
	size_t ret = 0;

	if (!self)
		return 0;

<<<<<<< HEAD
	ret += __callchain__fprintf_flat(fp, self->parent, total_samples);
=======
	ret += callchain__fprintf_flat(fp, self->parent, total_samples);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9


	list_for_each_entry(chain, &self->val, list) {
		if (chain->ip >= PERF_CONTEXT_MAX)
			continue;
		if (chain->ms.sym)
			ret += fprintf(fp, "                %s\n", chain->ms.sym->name);
		else
			ret += fprintf(fp, "                %p\n",
					(void *)(long)chain->ip);
	}

	return ret;
}

<<<<<<< HEAD
static size_t callchain__fprintf_flat(FILE *fp, struct rb_root *self,
				      u64 total_samples)
{
	size_t ret = 0;
	u32 entries_printed = 0;
	struct rb_node *rb_node;
	struct callchain_node *chain;

	rb_node = rb_first(self);
=======
static size_t hist_entry_callchain__fprintf(FILE *fp, struct hist_entry *self,
					    u64 total_samples, int left_margin)
{
	struct rb_node *rb_node;
	struct callchain_node *chain;
	size_t ret = 0;
	u32 entries_printed = 0;

	rb_node = rb_first(&self->sorted_chain);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	while (rb_node) {
		double percent;

		chain = rb_entry(rb_node, struct callchain_node, rb_node);
		percent = chain->hit * 100.0 / total_samples;
<<<<<<< HEAD

		ret = percent_color_fprintf(fp, "           %6.2f%%\n", percent);
		ret += __callchain__fprintf_flat(fp, chain, total_samples);
		ret += fprintf(fp, "\n");
		if (++entries_printed == callchain_param.print_limit)
			break;

=======
		switch (callchain_param.mode) {
		case CHAIN_FLAT:
			ret += percent_color_fprintf(fp, "           %6.2f%%\n",
						     percent);
			ret += callchain__fprintf_flat(fp, chain, total_samples);
			break;
		case CHAIN_GRAPH_ABS: /* Falldown */
		case CHAIN_GRAPH_REL:
			ret += callchain__fprintf_graph(fp, chain, total_samples,
							left_margin);
		case CHAIN_NONE:
		default:
			break;
		}
		ret += fprintf(fp, "\n");
		if (++entries_printed == callchain_param.print_limit)
			break;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		rb_node = rb_next(rb_node);
	}

	return ret;
}

<<<<<<< HEAD
static size_t hist_entry_callchain__fprintf(struct hist_entry *he,
					    u64 total_samples, int left_margin,
					    FILE *fp)
{
	switch (callchain_param.mode) {
	case CHAIN_GRAPH_REL:
		return callchain__fprintf_graph(fp, &he->sorted_chain, he->period,
						left_margin);
		break;
	case CHAIN_GRAPH_ABS:
		return callchain__fprintf_graph(fp, &he->sorted_chain, total_samples,
						left_margin);
		break;
	case CHAIN_FLAT:
		return callchain__fprintf_flat(fp, &he->sorted_chain, total_samples);
		break;
	case CHAIN_NONE:
		break;
	default:
		pr_err("Bad callchain mode\n");
	}

	return 0;
}

void hists__output_recalc_col_len(struct hists *hists, int max_rows)
{
	struct rb_node *next = rb_first(&hists->entries);
	struct hist_entry *n;
	int row = 0;

	hists__reset_col_len(hists);

	while (next && row++ < max_rows) {
		n = rb_entry(next, struct hist_entry, rb_node);
		if (!n->filtered)
			hists__calc_col_len(hists, n);
		next = rb_next(&n->rb_node);
	}
}

static int hist_entry__pcnt_snprintf(struct hist_entry *he, char *s,
				     size_t size, struct hists *pair_hists,
				     bool show_displacement, long displacement,
				     bool color, u64 total_period)
{
=======
int hist_entry__snprintf(struct hist_entry *self, char *s, size_t size,
			 struct hists *hists, struct hists *pair_hists,
			 bool show_displacement, long displacement,
			 bool color, u64 session_total)
{
	struct sort_entry *se;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	u64 period, total, period_sys, period_us, period_guest_sys, period_guest_us;
	u64 nr_events;
	const char *sep = symbol_conf.field_sep;
	int ret;

<<<<<<< HEAD
	if (symbol_conf.exclude_other && !he->parent)
		return 0;

	if (pair_hists) {
		period = he->pair ? he->pair->period : 0;
		nr_events = he->pair ? he->pair->nr_events : 0;
		total = pair_hists->stats.total_period;
		period_sys = he->pair ? he->pair->period_sys : 0;
		period_us = he->pair ? he->pair->period_us : 0;
		period_guest_sys = he->pair ? he->pair->period_guest_sys : 0;
		period_guest_us = he->pair ? he->pair->period_guest_us : 0;
	} else {
		period = he->period;
		nr_events = he->nr_events;
		total = total_period;
		period_sys = he->period_sys;
		period_us = he->period_us;
		period_guest_sys = he->period_guest_sys;
		period_guest_us = he->period_guest_us;
=======
	if (symbol_conf.exclude_other && !self->parent)
		return 0;

	if (pair_hists) {
		period = self->pair ? self->pair->period : 0;
		nr_events = self->pair ? self->pair->nr_events : 0;
		total = pair_hists->stats.total_period;
		period_sys = self->pair ? self->pair->period_sys : 0;
		period_us = self->pair ? self->pair->period_us : 0;
		period_guest_sys = self->pair ? self->pair->period_guest_sys : 0;
		period_guest_us = self->pair ? self->pair->period_guest_us : 0;
	} else {
		period = self->period;
		nr_events = self->nr_events;
		total = session_total;
		period_sys = self->period_sys;
		period_us = self->period_us;
		period_guest_sys = self->period_guest_sys;
		period_guest_us = self->period_guest_us;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	if (total) {
		if (color)
			ret = percent_color_snprintf(s, size,
						     sep ? "%.2f" : "   %6.2f%%",
						     (period * 100.0) / total);
		else
<<<<<<< HEAD
			ret = scnprintf(s, size, sep ? "%.2f" : "   %6.2f%%",
=======
			ret = snprintf(s, size, sep ? "%.2f" : "   %6.2f%%",
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				       (period * 100.0) / total);
		if (symbol_conf.show_cpu_utilization) {
			ret += percent_color_snprintf(s + ret, size - ret,
					sep ? "%.2f" : "   %6.2f%%",
					(period_sys * 100.0) / total);
			ret += percent_color_snprintf(s + ret, size - ret,
					sep ? "%.2f" : "   %6.2f%%",
					(period_us * 100.0) / total);
			if (perf_guest) {
				ret += percent_color_snprintf(s + ret,
						size - ret,
						sep ? "%.2f" : "   %6.2f%%",
						(period_guest_sys * 100.0) /
								total);
				ret += percent_color_snprintf(s + ret,
						size - ret,
						sep ? "%.2f" : "   %6.2f%%",
						(period_guest_us * 100.0) /
								total);
			}
		}
	} else
<<<<<<< HEAD
		ret = scnprintf(s, size, sep ? "%" PRIu64 : "%12" PRIu64 " ", period);

	if (symbol_conf.show_nr_samples) {
		if (sep)
			ret += scnprintf(s + ret, size - ret, "%c%" PRIu64, *sep, nr_events);
		else
			ret += scnprintf(s + ret, size - ret, "%11" PRIu64, nr_events);
	}

	if (symbol_conf.show_total_period) {
		if (sep)
			ret += scnprintf(s + ret, size - ret, "%c%" PRIu64, *sep, period);
		else
			ret += scnprintf(s + ret, size - ret, " %12" PRIu64, period);
=======
		ret = snprintf(s, size, sep ? "%" PRIu64 : "%12" PRIu64 " ", period);

	if (symbol_conf.show_nr_samples) {
		if (sep)
			ret += snprintf(s + ret, size - ret, "%c%" PRIu64, *sep, nr_events);
		else
			ret += snprintf(s + ret, size - ret, "%11" PRIu64, nr_events);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	if (pair_hists) {
		char bf[32];
		double old_percent = 0, new_percent = 0, diff;

		if (total > 0)
			old_percent = (period * 100.0) / total;
<<<<<<< HEAD
		if (total_period > 0)
			new_percent = (he->period * 100.0) / total_period;
=======
		if (session_total > 0)
			new_percent = (self->period * 100.0) / session_total;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

		diff = new_percent - old_percent;

		if (fabs(diff) >= 0.01)
<<<<<<< HEAD
			scnprintf(bf, sizeof(bf), "%+4.2F%%", diff);
		else
			scnprintf(bf, sizeof(bf), " ");

		if (sep)
			ret += scnprintf(s + ret, size - ret, "%c%s", *sep, bf);
		else
			ret += scnprintf(s + ret, size - ret, "%11.11s", bf);

		if (show_displacement) {
			if (displacement)
				scnprintf(bf, sizeof(bf), "%+4ld", displacement);
			else
				scnprintf(bf, sizeof(bf), " ");

			if (sep)
				ret += scnprintf(s + ret, size - ret, "%c%s", *sep, bf);
			else
				ret += scnprintf(s + ret, size - ret, "%6.6s", bf);
		}
	}

	return ret;
}

int hist_entry__snprintf(struct hist_entry *he, char *s, size_t size,
			 struct hists *hists)
{
	const char *sep = symbol_conf.field_sep;
	struct sort_entry *se;
	int ret = 0;

=======
			snprintf(bf, sizeof(bf), "%+4.2F%%", diff);
		else
			snprintf(bf, sizeof(bf), " ");

		if (sep)
			ret += snprintf(s + ret, size - ret, "%c%s", *sep, bf);
		else
			ret += snprintf(s + ret, size - ret, "%11.11s", bf);

		if (show_displacement) {
			if (displacement)
				snprintf(bf, sizeof(bf), "%+4ld", displacement);
			else
				snprintf(bf, sizeof(bf), " ");

			if (sep)
				ret += snprintf(s + ret, size - ret, "%c%s", *sep, bf);
			else
				ret += snprintf(s + ret, size - ret, "%6.6s", bf);
		}
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	list_for_each_entry(se, &hist_entry__sort_list, list) {
		if (se->elide)
			continue;

<<<<<<< HEAD
		ret += scnprintf(s + ret, size - ret, "%s", sep ?: "  ");
		ret += se->se_snprintf(he, s + ret, size - ret,
=======
		ret += snprintf(s + ret, size - ret, "%s", sep ?: "  ");
		ret += se->se_snprintf(self, s + ret, size - ret,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				       hists__col_len(hists, se->se_width_idx));
	}

	return ret;
}

<<<<<<< HEAD
static int hist_entry__fprintf(struct hist_entry *he, size_t size,
			       struct hists *hists, struct hists *pair_hists,
			       bool show_displacement, long displacement,
			       u64 total_period, FILE *fp)
{
	char bf[512];
	int ret;

	if (size == 0 || size > sizeof(bf))
		size = sizeof(bf);

	ret = hist_entry__pcnt_snprintf(he, bf, size, pair_hists,
					show_displacement, displacement,
					true, total_period);
	hist_entry__snprintf(he, bf + ret, size - ret, hists);
	return fprintf(fp, "%s\n", bf);
}

static size_t hist_entry__fprintf_callchain(struct hist_entry *he,
					    struct hists *hists,
					    u64 total_period, FILE *fp)
=======
int hist_entry__fprintf(struct hist_entry *self, struct hists *hists,
			struct hists *pair_hists, bool show_displacement,
			long displacement, FILE *fp, u64 session_total)
{
	char bf[512];
	hist_entry__snprintf(self, bf, sizeof(bf), hists, pair_hists,
			     show_displacement, displacement,
			     true, session_total);
	return fprintf(fp, "%s\n", bf);
}

static size_t hist_entry__fprintf_callchain(struct hist_entry *self,
					    struct hists *hists, FILE *fp,
					    u64 session_total)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	int left_margin = 0;

	if (sort__first_dimension == SORT_COMM) {
		struct sort_entry *se = list_first_entry(&hist_entry__sort_list,
							 typeof(*se), list);
		left_margin = hists__col_len(hists, se->se_width_idx);
<<<<<<< HEAD
		left_margin -= thread__comm_len(he->thread);
	}

	return hist_entry_callchain__fprintf(he, total_period, left_margin, fp);
}

size_t hists__fprintf(struct hists *hists, struct hists *pair,
		      bool show_displacement, bool show_header, int max_rows,
		      int max_cols, FILE *fp)
=======
		left_margin -= thread__comm_len(self->thread);
	}

	return hist_entry_callchain__fprintf(fp, self, session_total,
					     left_margin);
}

size_t hists__fprintf(struct hists *self, struct hists *pair,
		      bool show_displacement, FILE *fp)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	struct sort_entry *se;
	struct rb_node *nd;
	size_t ret = 0;
<<<<<<< HEAD
	u64 total_period;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	unsigned long position = 1;
	long displacement = 0;
	unsigned int width;
	const char *sep = symbol_conf.field_sep;
	const char *col_width = symbol_conf.col_width_list_str;
<<<<<<< HEAD
	int nr_rows = 0;

	init_rem_hits();

	if (!show_header)
		goto print_entries;

	fprintf(fp, "# %s", pair ? "Baseline" : "Overhead");

=======

	init_rem_hits();

	fprintf(fp, "# %s", pair ? "Baseline" : "Overhead");

	if (symbol_conf.show_nr_samples) {
		if (sep)
			fprintf(fp, "%cSamples", *sep);
		else
			fputs("  Samples  ", fp);
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (symbol_conf.show_cpu_utilization) {
		if (sep) {
			ret += fprintf(fp, "%csys", *sep);
			ret += fprintf(fp, "%cus", *sep);
			if (perf_guest) {
				ret += fprintf(fp, "%cguest sys", *sep);
				ret += fprintf(fp, "%cguest us", *sep);
			}
		} else {
<<<<<<< HEAD
			ret += fprintf(fp, "     sys  ");
			ret += fprintf(fp, "      us  ");
=======
			ret += fprintf(fp, "  sys  ");
			ret += fprintf(fp, "  us  ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			if (perf_guest) {
				ret += fprintf(fp, "  guest sys  ");
				ret += fprintf(fp, "  guest us  ");
			}
		}
	}

<<<<<<< HEAD
	if (symbol_conf.show_nr_samples) {
		if (sep)
			fprintf(fp, "%cSamples", *sep);
		else
			fputs("  Samples  ", fp);
	}

	if (symbol_conf.show_total_period) {
		if (sep)
			ret += fprintf(fp, "%cPeriod", *sep);
		else
			ret += fprintf(fp, "   Period    ");
	}

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (pair) {
		if (sep)
			ret += fprintf(fp, "%cDelta", *sep);
		else
			ret += fprintf(fp, "  Delta    ");

		if (show_displacement) {
			if (sep)
				ret += fprintf(fp, "%cDisplacement", *sep);
			else
				ret += fprintf(fp, " Displ");
		}
	}

	list_for_each_entry(se, &hist_entry__sort_list, list) {
		if (se->elide)
			continue;
		if (sep) {
			fprintf(fp, "%c%s", *sep, se->se_header);
			continue;
		}
		width = strlen(se->se_header);
		if (symbol_conf.col_width_list_str) {
			if (col_width) {
<<<<<<< HEAD
				hists__set_col_len(hists, se->se_width_idx,
=======
				hists__set_col_len(self, se->se_width_idx,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
						   atoi(col_width));
				col_width = strchr(col_width, ',');
				if (col_width)
					++col_width;
			}
		}
<<<<<<< HEAD
		if (!hists__new_col_len(hists, se->se_width_idx, width))
			width = hists__col_len(hists, se->se_width_idx);
		fprintf(fp, "  %*s", width, se->se_header);
	}

	fprintf(fp, "\n");
	if (max_rows && ++nr_rows >= max_rows)
		goto out;
=======
		if (!hists__new_col_len(self, se->se_width_idx, width))
			width = hists__col_len(self, se->se_width_idx);
		fprintf(fp, "  %*s", width, se->se_header);
	}
	fprintf(fp, "\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (sep)
		goto print_entries;

	fprintf(fp, "# ........");
<<<<<<< HEAD
	if (symbol_conf.show_cpu_utilization)
		fprintf(fp, "   .......   .......");
	if (symbol_conf.show_nr_samples)
		fprintf(fp, " ..........");
	if (symbol_conf.show_total_period)
		fprintf(fp, " ............");
=======
	if (symbol_conf.show_nr_samples)
		fprintf(fp, " ..........");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (pair) {
		fprintf(fp, " ..........");
		if (show_displacement)
			fprintf(fp, " .....");
	}
	list_for_each_entry(se, &hist_entry__sort_list, list) {
		unsigned int i;

		if (se->elide)
			continue;

		fprintf(fp, "  ");
<<<<<<< HEAD
		width = hists__col_len(hists, se->se_width_idx);
=======
		width = hists__col_len(self, se->se_width_idx);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (width == 0)
			width = strlen(se->se_header);
		for (i = 0; i < width; i++)
			fprintf(fp, ".");
	}

<<<<<<< HEAD
	fprintf(fp, "\n");
	if (max_rows && ++nr_rows >= max_rows)
		goto out;

	fprintf(fp, "#\n");
	if (max_rows && ++nr_rows >= max_rows)
		goto out;

print_entries:
	total_period = hists->stats.total_period;

	for (nd = rb_first(&hists->entries); nd; nd = rb_next(nd)) {
		struct hist_entry *h = rb_entry(nd, struct hist_entry, rb_node);

		if (h->filtered)
			continue;

=======
	fprintf(fp, "\n#\n");

print_entries:
	for (nd = rb_first(&self->entries); nd; nd = rb_next(nd)) {
		struct hist_entry *h = rb_entry(nd, struct hist_entry, rb_node);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (show_displacement) {
			if (h->pair != NULL)
				displacement = ((long)h->pair->position -
					        (long)position);
			else
				displacement = 0;
			++position;
		}
<<<<<<< HEAD
		ret += hist_entry__fprintf(h, max_cols, hists, pair, show_displacement,
					   displacement, total_period, fp);

		if (symbol_conf.use_callchain)
			ret += hist_entry__fprintf_callchain(h, hists, total_period, fp);
		if (max_rows && ++nr_rows >= max_rows)
			goto out;

=======
		ret += hist_entry__fprintf(h, self, pair, show_displacement,
					   displacement, fp, self->stats.total_period);

		if (symbol_conf.use_callchain)
			ret += hist_entry__fprintf_callchain(h, self, fp,
							     self->stats.total_period);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (h->ms.map == NULL && verbose > 1) {
			__map_groups__fprintf_maps(&h->thread->mg,
						   MAP__FUNCTION, verbose, fp);
			fprintf(fp, "%.10s end\n", graph_dotted_line);
		}
	}
<<<<<<< HEAD
out:
=======

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	free(rem_sq_bracket);

	return ret;
}

/*
 * See hists__fprintf to match the column widths
 */
<<<<<<< HEAD
unsigned int hists__sort_list_width(struct hists *hists)
=======
unsigned int hists__sort_list_width(struct hists *self)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	struct sort_entry *se;
	int ret = 9; /* total % */

	if (symbol_conf.show_cpu_utilization) {
		ret += 7; /* count_sys % */
		ret += 6; /* count_us % */
		if (perf_guest) {
			ret += 13; /* count_guest_sys % */
			ret += 12; /* count_guest_us % */
		}
	}

	if (symbol_conf.show_nr_samples)
		ret += 11;

<<<<<<< HEAD
	if (symbol_conf.show_total_period)
		ret += 13;

	list_for_each_entry(se, &hist_entry__sort_list, list)
		if (!se->elide)
			ret += 2 + hists__col_len(hists, se->se_width_idx);
=======
	list_for_each_entry(se, &hist_entry__sort_list, list)
		if (!se->elide)
			ret += 2 + hists__col_len(self, se->se_width_idx);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (verbose) /* Addr + origin */
		ret += 3 + BITS_PER_LONG / 4;

	return ret;
}

<<<<<<< HEAD
static void hists__remove_entry_filter(struct hists *hists, struct hist_entry *h,
=======
static void hists__remove_entry_filter(struct hists *self, struct hist_entry *h,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				       enum hist_filter filter)
{
	h->filtered &= ~(1 << filter);
	if (h->filtered)
		return;

<<<<<<< HEAD
	++hists->nr_entries;
	if (h->ms.unfolded)
		hists->nr_entries += h->nr_rows;
	h->row_offset = 0;
	hists->stats.total_period += h->period;
	hists->stats.nr_events[PERF_RECORD_SAMPLE] += h->nr_events;

	hists__calc_col_len(hists, h);
}


static bool hists__filter_entry_by_dso(struct hists *hists,
				       struct hist_entry *he)
{
	if (hists->dso_filter != NULL &&
	    (he->ms.map == NULL || he->ms.map->dso != hists->dso_filter)) {
		he->filtered |= (1 << HIST_FILTER__DSO);
		return true;
	}

	return false;
}

void hists__filter_by_dso(struct hists *hists)
{
	struct rb_node *nd;

	hists->nr_entries = hists->stats.total_period = 0;
	hists->stats.nr_events[PERF_RECORD_SAMPLE] = 0;
	hists__reset_col_len(hists);

	for (nd = rb_first(&hists->entries); nd; nd = rb_next(nd)) {
=======
	++self->nr_entries;
	if (h->ms.unfolded)
		self->nr_entries += h->nr_rows;
	h->row_offset = 0;
	self->stats.total_period += h->period;
	self->stats.nr_events[PERF_RECORD_SAMPLE] += h->nr_events;

	hists__calc_col_len(self, h);
}

void hists__filter_by_dso(struct hists *self, const struct dso *dso)
{
	struct rb_node *nd;

	self->nr_entries = self->stats.total_period = 0;
	self->stats.nr_events[PERF_RECORD_SAMPLE] = 0;
	hists__reset_col_len(self);

	for (nd = rb_first(&self->entries); nd; nd = rb_next(nd)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		struct hist_entry *h = rb_entry(nd, struct hist_entry, rb_node);

		if (symbol_conf.exclude_other && !h->parent)
			continue;

<<<<<<< HEAD
		if (hists__filter_entry_by_dso(hists, h))
			continue;

		hists__remove_entry_filter(hists, h, HIST_FILTER__DSO);
	}
}

static bool hists__filter_entry_by_thread(struct hists *hists,
					  struct hist_entry *he)
{
	if (hists->thread_filter != NULL &&
	    he->thread != hists->thread_filter) {
		he->filtered |= (1 << HIST_FILTER__THREAD);
		return true;
	}

	return false;
}

void hists__filter_by_thread(struct hists *hists)
{
	struct rb_node *nd;

	hists->nr_entries = hists->stats.total_period = 0;
	hists->stats.nr_events[PERF_RECORD_SAMPLE] = 0;
	hists__reset_col_len(hists);

	for (nd = rb_first(&hists->entries); nd; nd = rb_next(nd)) {
		struct hist_entry *h = rb_entry(nd, struct hist_entry, rb_node);

		if (hists__filter_entry_by_thread(hists, h))
			continue;

		hists__remove_entry_filter(hists, h, HIST_FILTER__THREAD);
	}
}

static bool hists__filter_entry_by_symbol(struct hists *hists,
					  struct hist_entry *he)
{
	if (hists->symbol_filter_str != NULL &&
	    (!he->ms.sym || strstr(he->ms.sym->name,
				   hists->symbol_filter_str) == NULL)) {
		he->filtered |= (1 << HIST_FILTER__SYMBOL);
		return true;
	}

	return false;
}

void hists__filter_by_symbol(struct hists *hists)
{
	struct rb_node *nd;

	hists->nr_entries = hists->stats.total_period = 0;
	hists->stats.nr_events[PERF_RECORD_SAMPLE] = 0;
	hists__reset_col_len(hists);

	for (nd = rb_first(&hists->entries); nd; nd = rb_next(nd)) {
		struct hist_entry *h = rb_entry(nd, struct hist_entry, rb_node);

		if (hists__filter_entry_by_symbol(hists, h))
			continue;

		hists__remove_entry_filter(hists, h, HIST_FILTER__SYMBOL);
=======
		if (dso != NULL && (h->ms.map == NULL || h->ms.map->dso != dso)) {
			h->filtered |= (1 << HIST_FILTER__DSO);
			continue;
		}

		hists__remove_entry_filter(self, h, HIST_FILTER__DSO);
	}
}

void hists__filter_by_thread(struct hists *self, const struct thread *thread)
{
	struct rb_node *nd;

	self->nr_entries = self->stats.total_period = 0;
	self->stats.nr_events[PERF_RECORD_SAMPLE] = 0;
	hists__reset_col_len(self);

	for (nd = rb_first(&self->entries); nd; nd = rb_next(nd)) {
		struct hist_entry *h = rb_entry(nd, struct hist_entry, rb_node);

		if (thread != NULL && h->thread != thread) {
			h->filtered |= (1 << HIST_FILTER__THREAD);
			continue;
		}

		hists__remove_entry_filter(self, h, HIST_FILTER__THREAD);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}
}

int hist_entry__inc_addr_samples(struct hist_entry *he, int evidx, u64 ip)
{
	return symbol__inc_addr_samples(he->ms.sym, he->ms.map, evidx, ip);
}

int hist_entry__annotate(struct hist_entry *he, size_t privsize)
{
	return symbol__annotate(he->ms.sym, he->ms.map, privsize);
}

<<<<<<< HEAD
void hists__inc_nr_events(struct hists *hists, u32 type)
{
	++hists->stats.nr_events[0];
	++hists->stats.nr_events[type];
}

size_t hists__fprintf_nr_events(struct hists *hists, FILE *fp)
=======
void hists__inc_nr_events(struct hists *self, u32 type)
{
	++self->stats.nr_events[0];
	++self->stats.nr_events[type];
}

size_t hists__fprintf_nr_events(struct hists *self, FILE *fp)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	int i;
	size_t ret = 0;

	for (i = 0; i < PERF_RECORD_HEADER_MAX; ++i) {
		const char *name;

<<<<<<< HEAD
		if (hists->stats.nr_events[i] == 0)
=======
		if (self->stats.nr_events[i] == 0)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			continue;

		name = perf_event__name(i);
		if (!strcmp(name, "UNKNOWN"))
			continue;

		ret += fprintf(fp, "%16s events: %10d\n", name,
<<<<<<< HEAD
			       hists->stats.nr_events[i]);
=======
			       self->stats.nr_events[i]);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	return ret;
}
