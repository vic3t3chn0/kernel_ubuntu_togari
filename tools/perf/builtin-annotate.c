/*
 * builtin-annotate.c
 *
 * Builtin annotate command: Analyze the perf.data input file,
 * look up and read DSOs and symbol information and display
 * a histogram of results, along various sorting keys.
 */
#include "builtin.h"

#include "util/util.h"
#include "util/color.h"
#include <linux/list.h>
#include "util/cache.h"
#include <linux/rbtree.h>
#include "util/symbol.h"

#include "perf.h"
#include "util/debug.h"

#include "util/evlist.h"
#include "util/evsel.h"
#include "util/annotate.h"
#include "util/event.h"
#include "util/parse-options.h"
#include "util/parse-events.h"
#include "util/thread.h"
#include "util/sort.h"
#include "util/hist.h"
#include "util/session.h"
<<<<<<< HEAD
#include "util/tool.h"

#include <linux/bitmap.h>

struct perf_annotate {
	struct perf_tool tool;
	char const *input_name;
	bool	   force, use_tui, use_stdio;
	bool	   full_paths;
	bool	   print_line;
	const char *sym_hist_filter;
	const char *cpu_list;
	DECLARE_BITMAP(cpu_bitmap, MAX_NR_CPUS);
};

static int perf_evsel__add_sample(struct perf_evsel *evsel,
				  struct perf_sample *sample,
				  struct addr_location *al,
				  struct perf_annotate *ann)
=======

static char		const *input_name = "perf.data";

static bool		force, use_tui, use_stdio;

static bool		full_paths;

static bool		print_line;

static const char *sym_hist_filter;

static int perf_evlist__add_sample(struct perf_evlist *evlist,
				   struct perf_sample *sample,
				   struct perf_evsel *evsel,
				   struct addr_location *al)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	struct hist_entry *he;
	int ret;

<<<<<<< HEAD
	if (ann->sym_hist_filter != NULL &&
	    (al->sym == NULL ||
	     strcmp(ann->sym_hist_filter, al->sym->name) != 0)) {
=======
	if (sym_hist_filter != NULL &&
	    (al->sym == NULL || strcmp(sym_hist_filter, al->sym->name) != 0)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		/* We're only interested in a symbol named sym_hist_filter */
		if (al->sym != NULL) {
			rb_erase(&al->sym->rb_node,
				 &al->map->dso->symbols[al->map->type]);
			symbol__delete(al->sym);
		}
		return 0;
	}

	he = __hists__add_entry(&evsel->hists, al, NULL, 1);
	if (he == NULL)
		return -ENOMEM;

	ret = 0;
	if (he->ms.sym != NULL) {
		struct annotation *notes = symbol__annotation(he->ms.sym);
<<<<<<< HEAD
		if (notes->src == NULL && symbol__alloc_hist(he->ms.sym) < 0)
=======
		if (notes->src == NULL &&
		    symbol__alloc_hist(he->ms.sym, evlist->nr_entries) < 0)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			return -ENOMEM;

		ret = hist_entry__inc_addr_samples(he, evsel->idx, al->addr);
	}

	evsel->hists.stats.total_period += sample->period;
	hists__inc_nr_events(&evsel->hists, PERF_RECORD_SAMPLE);
	return ret;
}

<<<<<<< HEAD
static int process_sample_event(struct perf_tool *tool,
				union perf_event *event,
				struct perf_sample *sample,
				struct perf_evsel *evsel,
				struct machine *machine)
{
	struct perf_annotate *ann = container_of(tool, struct perf_annotate, tool);
	struct addr_location al;

	if (perf_event__preprocess_sample(event, machine, &al, sample,
=======
static int process_sample_event(union perf_event *event,
				struct perf_sample *sample,
				struct perf_evsel *evsel,
				struct perf_session *session)
{
	struct addr_location al;

	if (perf_event__preprocess_sample(event, session, &al, sample,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					  symbol__annotate_init) < 0) {
		pr_warning("problem processing %d event, skipping it.\n",
			   event->header.type);
		return -1;
	}

<<<<<<< HEAD
	if (ann->cpu_list && !test_bit(sample->cpu, ann->cpu_bitmap))
		return 0;

	if (!al.filtered && perf_evsel__add_sample(evsel, sample, &al, ann)) {
=======
	if (!al.filtered &&
	    perf_evlist__add_sample(session->evlist, sample, evsel, &al)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		pr_warning("problem incrementing symbol count, "
			   "skipping event\n");
		return -1;
	}

	return 0;
}

<<<<<<< HEAD
static int hist_entry__tty_annotate(struct hist_entry *he, int evidx,
				    struct perf_annotate *ann)
{
	return symbol__tty_annotate(he->ms.sym, he->ms.map, evidx,
				    ann->print_line, ann->full_paths, 0, 0);
}

static void hists__find_annotations(struct hists *self, int evidx,
				    struct perf_annotate *ann)
{
	struct rb_node *nd = rb_first(&self->entries), *next;
	int key = K_RIGHT;
=======
static int hist_entry__tty_annotate(struct hist_entry *he, int evidx)
{
	return symbol__tty_annotate(he->ms.sym, he->ms.map, evidx,
				    print_line, full_paths, 0, 0);
}

static void hists__find_annotations(struct hists *self, int evidx)
{
	struct rb_node *nd = rb_first(&self->entries), *next;
	int key = KEY_RIGHT;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	while (nd) {
		struct hist_entry *he = rb_entry(nd, struct hist_entry, rb_node);
		struct annotation *notes;

		if (he->ms.sym == NULL || he->ms.map->dso->annotate_warned)
			goto find_next;

		notes = symbol__annotation(he->ms.sym);
		if (notes->src == NULL) {
find_next:
<<<<<<< HEAD
			if (key == K_LEFT)
=======
			if (key == KEY_LEFT)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				nd = rb_prev(nd);
			else
				nd = rb_next(nd);
			continue;
		}

		if (use_browser > 0) {
<<<<<<< HEAD
			key = hist_entry__tui_annotate(he, evidx, NULL, NULL, 0);
			switch (key) {
			case K_RIGHT:
				next = rb_next(nd);
				break;
			case K_LEFT:
=======
			key = hist_entry__tui_annotate(he, evidx);
			switch (key) {
			case KEY_RIGHT:
				next = rb_next(nd);
				break;
			case KEY_LEFT:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				next = rb_prev(nd);
				break;
			default:
				return;
			}

			if (next != NULL)
				nd = next;
		} else {
<<<<<<< HEAD
			hist_entry__tty_annotate(he, evidx, ann);
=======
			hist_entry__tty_annotate(he, evidx);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			nd = rb_next(nd);
			/*
			 * Since we have a hist_entry per IP for the same
			 * symbol, free he->ms.sym->src to signal we already
			 * processed this symbol.
			 */
			free(notes->src);
			notes->src = NULL;
		}
	}
}

<<<<<<< HEAD
static int __cmd_annotate(struct perf_annotate *ann)
=======
static struct perf_event_ops event_ops = {
	.sample	= process_sample_event,
	.mmap	= perf_event__process_mmap,
	.comm	= perf_event__process_comm,
	.fork	= perf_event__process_task,
	.ordered_samples = true,
	.ordering_requires_timestamps = true,
};

static int __cmd_annotate(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	int ret;
	struct perf_session *session;
	struct perf_evsel *pos;
	u64 total_nr_samples;

<<<<<<< HEAD
	session = perf_session__new(ann->input_name, O_RDONLY,
				    ann->force, false, &ann->tool);
	if (session == NULL)
		return -ENOMEM;

	if (ann->cpu_list) {
		ret = perf_session__cpu_bitmap(session, ann->cpu_list,
					       ann->cpu_bitmap);
		if (ret)
			goto out_delete;
	}

	ret = perf_session__process_events(session, &ann->tool);
=======
	session = perf_session__new(input_name, O_RDONLY, force, false, &event_ops);
	if (session == NULL)
		return -ENOMEM;

	ret = perf_session__process_events(session, &event_ops);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (ret)
		goto out_delete;

	if (dump_trace) {
		perf_session__fprintf_nr_events(session, stdout);
		goto out_delete;
	}

	if (verbose > 3)
		perf_session__fprintf(session, stdout);

	if (verbose > 2)
		perf_session__fprintf_dsos(session, stdout);

	total_nr_samples = 0;
	list_for_each_entry(pos, &session->evlist->entries, node) {
		struct hists *hists = &pos->hists;
		u32 nr_samples = hists->stats.nr_events[PERF_RECORD_SAMPLE];

		if (nr_samples > 0) {
			total_nr_samples += nr_samples;
			hists__collapse_resort(hists);
			hists__output_resort(hists);
<<<<<<< HEAD
			hists__find_annotations(hists, pos->idx, ann);
=======
			hists__find_annotations(hists, pos->idx);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		}
	}

	if (total_nr_samples == 0) {
<<<<<<< HEAD
		ui__warning("The %s file has no samples!\n", session->filename);
=======
		ui__warning("The %s file has no samples!\n", input_name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		goto out_delete;
	}
out_delete:
	/*
	 * Speed up the exit process, for large files this can
	 * take quite a while.
	 *
	 * XXX Enable this when using valgrind or if we ever
	 * librarize this command.
	 *
	 * Also experiment with obstacks to see how much speed
	 * up we'll get here.
	 *
	 * perf_session__delete(session);
	 */
	return ret;
}

static const char * const annotate_usage[] = {
<<<<<<< HEAD
	"perf annotate [<options>]",
	NULL
};

int cmd_annotate(int argc, const char **argv, const char *prefix __used)
{
	struct perf_annotate annotate = {
		.tool = {
			.sample	= process_sample_event,
			.mmap	= perf_event__process_mmap,
			.comm	= perf_event__process_comm,
			.fork	= perf_event__process_task,
			.ordered_samples = true,
			.ordering_requires_timestamps = true,
		},
	};
	const struct option options[] = {
	OPT_STRING('i', "input", &annotate.input_name, "file",
		    "input file name"),
	OPT_STRING('d', "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these dsos"),
	OPT_STRING('s', "symbol", &annotate.sym_hist_filter, "symbol",
		    "symbol to annotate"),
	OPT_BOOLEAN('f', "force", &annotate.force, "don't complain, do it"),
=======
	"perf annotate [<options>] <command>",
	NULL
};

static const struct option options[] = {
	OPT_STRING('i', "input", &input_name, "file",
		    "input file name"),
	OPT_STRING('d', "dsos", &symbol_conf.dso_list_str, "dso[,dso...]",
		   "only consider symbols in these dsos"),
	OPT_STRING('s', "symbol", &sym_hist_filter, "symbol",
		    "symbol to annotate"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, do it"),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace,
		    "dump raw trace in ASCII"),
<<<<<<< HEAD
	OPT_BOOLEAN(0, "tui", &annotate.use_tui, "Use the TUI interface"),
	OPT_BOOLEAN(0, "stdio", &annotate.use_stdio, "Use the stdio interface"),
=======
	OPT_BOOLEAN(0, "tui", &use_tui, "Use the TUI interface"),
	OPT_BOOLEAN(0, "stdio", &use_stdio, "Use the stdio interface"),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_BOOLEAN('m', "modules", &symbol_conf.use_modules,
		    "load module symbols - WARNING: use only with -k and LIVE kernel"),
<<<<<<< HEAD
	OPT_BOOLEAN('l', "print-line", &annotate.print_line,
		    "print matching source lines (may be slow)"),
	OPT_BOOLEAN('P', "full-paths", &annotate.full_paths,
		    "Don't shorten the displayed pathnames"),
	OPT_STRING('C', "cpu", &annotate.cpu_list, "cpu", "list of cpus to profile"),
	OPT_STRING(0, "symfs", &symbol_conf.symfs, "directory",
		   "Look for files with symbols relative to this directory"),
	OPT_BOOLEAN(0, "source", &symbol_conf.annotate_src,
		    "Interleave source code with assembly code (default)"),
	OPT_BOOLEAN(0, "asm-raw", &symbol_conf.annotate_asm_raw,
		    "Display raw encoding of assembly instructions (default)"),
	OPT_STRING('M', "disassembler-style", &disassembler_style, "disassembler style",
		   "Specify disassembler style (e.g. -M intel for intel syntax)"),
	OPT_END()
	};

	argc = parse_options(argc, argv, options, annotate_usage, 0);

	if (annotate.use_stdio)
		use_browser = 0;
	else if (annotate.use_tui)
=======
	OPT_BOOLEAN('l', "print-line", &print_line,
		    "print matching source lines (may be slow)"),
	OPT_BOOLEAN('P', "full-paths", &full_paths,
		    "Don't shorten the displayed pathnames"),
	OPT_END()
};

int cmd_annotate(int argc, const char **argv, const char *prefix __used)
{
	argc = parse_options(argc, argv, options, annotate_usage, 0);

	if (use_stdio)
		use_browser = 0;
	else if (use_tui)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		use_browser = 1;

	setup_browser(true);

	symbol_conf.priv_size = sizeof(struct annotation);
	symbol_conf.try_vmlinux_path = true;

	if (symbol__init() < 0)
		return -1;

	setup_sorting(annotate_usage, options);

	if (argc) {
		/*
		 * Special case: if there's an argument left then assume tha
		 * it's a symbol filter:
		 */
		if (argc > 1)
			usage_with_options(annotate_usage, options);

<<<<<<< HEAD
		annotate.sym_hist_filter = argv[0];
	}

	return __cmd_annotate(&annotate);
=======
		sym_hist_filter = argv[0];
	}

	if (field_sep && *field_sep == '.') {
		pr_err("'.' is the only non valid --field-separator argument\n");
		return -1;
	}

	return __cmd_annotate();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}
