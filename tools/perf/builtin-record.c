/*
 * builtin-record.c
 *
 * Builtin record command: Record the profile of a workload
 * (or a CPU, or a PID) into the perf.data output file - for
 * later analysis via perf report.
 */
#define _FILE_OFFSET_BITS 64

#include "builtin.h"

#include "perf.h"

#include "util/build-id.h"
#include "util/util.h"
#include "util/parse-options.h"
#include "util/parse-events.h"

#include "util/header.h"
#include "util/event.h"
#include "util/evlist.h"
#include "util/evsel.h"
#include "util/debug.h"
#include "util/session.h"
<<<<<<< HEAD
#include "util/tool.h"
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#include "util/symbol.h"
#include "util/cpumap.h"
#include "util/thread_map.h"

#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>

<<<<<<< HEAD
=======
#define FD(e, x, y) (*(int *)xyarray__entry(e->fd, x, y))

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
enum write_mode_t {
	WRITE_FORCE,
	WRITE_APPEND
};

<<<<<<< HEAD
struct perf_record {
	struct perf_tool	tool;
	struct perf_record_opts	opts;
	u64			bytes_written;
	const char		*output_name;
	struct perf_evlist	*evlist;
	struct perf_session	*session;
	const char		*progname;
	const char		*uid_str;
	int			output;
	unsigned int		page_size;
	int			realtime_prio;
	enum write_mode_t	write_mode;
	bool			no_buildid;
	bool			no_buildid_cache;
	bool			force;
	bool			file_new;
	bool			append_file;
	long			samples;
	off_t			post_processing_offset;
};

static void advance_output(struct perf_record *rec, size_t size)
{
	rec->bytes_written += size;
}

static void write_output(struct perf_record *rec, void *buf, size_t size)
{
	while (size) {
		int ret = write(rec->output, buf, size);
=======
static u64			user_interval			= ULLONG_MAX;
static u64			default_interval		=      0;

static unsigned int		page_size;
static unsigned int		mmap_pages			= UINT_MAX;
static unsigned int		user_freq 			= UINT_MAX;
static int			freq				=   1000;
static int			output;
static int			pipe_output			=      0;
static const char		*output_name			= NULL;
static int			group				=      0;
static int			realtime_prio			=      0;
static bool			nodelay				=  false;
static bool			raw_samples			=  false;
static bool			sample_id_all_avail		=   true;
static bool			system_wide			=  false;
static pid_t			target_pid			=     -1;
static pid_t			target_tid			=     -1;
static pid_t			child_pid			=     -1;
static bool			no_inherit			=  false;
static enum write_mode_t	write_mode			= WRITE_FORCE;
static bool			call_graph			=  false;
static bool			inherit_stat			=  false;
static bool			no_samples			=  false;
static bool			sample_address			=  false;
static bool			sample_time			=  false;
static bool			no_buildid			=  false;
static bool			no_buildid_cache		=  false;
static struct perf_evlist	*evsel_list;

static long			samples				=      0;
static u64			bytes_written			=      0;

static int			file_new			=      1;
static off_t			post_processing_offset;

static struct perf_session	*session;
static const char		*cpu_list;

static void advance_output(size_t size)
{
	bytes_written += size;
}

static void write_output(void *buf, size_t size)
{
	while (size) {
		int ret = write(output, buf, size);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

		if (ret < 0)
			die("failed to write");

		size -= ret;
		buf += ret;

<<<<<<< HEAD
		rec->bytes_written += ret;
	}
}

static int process_synthesized_event(struct perf_tool *tool,
				     union perf_event *event,
				     struct perf_sample *sample __used,
				     struct machine *machine __used)
{
	struct perf_record *rec = container_of(tool, struct perf_record, tool);
	write_output(rec, event, event->header.size);
	return 0;
}

static void perf_record__mmap_read(struct perf_record *rec,
				   struct perf_mmap *md)
{
	unsigned int head = perf_mmap__read_head(md);
	unsigned int old = md->prev;
	unsigned char *data = md->base + rec->page_size;
=======
		bytes_written += ret;
	}
}

static int process_synthesized_event(union perf_event *event,
				     struct perf_sample *sample __used,
				     struct perf_session *self __used)
{
	write_output(event, event->header.size);
	return 0;
}

static void mmap_read(struct perf_mmap *md)
{
	unsigned int head = perf_mmap__read_head(md);
	unsigned int old = md->prev;
	unsigned char *data = md->base + page_size;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	unsigned long size;
	void *buf;

	if (old == head)
		return;

<<<<<<< HEAD
	rec->samples++;
=======
	samples++;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	size = head - old;

	if ((old & md->mask) + size != (head & md->mask)) {
		buf = &data[old & md->mask];
		size = md->mask + 1 - (old & md->mask);
		old += size;

<<<<<<< HEAD
		write_output(rec, buf, size);
=======
		write_output(buf, size);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	buf = &data[old & md->mask];
	size = head - old;
	old += size;

<<<<<<< HEAD
	write_output(rec, buf, size);
=======
	write_output(buf, size);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	md->prev = old;
	perf_mmap__write_tail(md, old);
}

static volatile int done = 0;
static volatile int signr = -1;
<<<<<<< HEAD
static volatile int child_finished = 0;

static void sig_handler(int sig)
{
	if (sig == SIGCHLD)
		child_finished = 1;

=======

static void sig_handler(int sig)
{
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	done = 1;
	signr = sig;
}

<<<<<<< HEAD
static void perf_record__sig_exit(int exit_status __used, void *arg)
{
	struct perf_record *rec = arg;
	int status;

	if (rec->evlist->workload.pid > 0) {
		if (!child_finished)
			kill(rec->evlist->workload.pid, SIGTERM);

		wait(&status);
		if (WIFSIGNALED(status))
			psignal(WTERMSIG(status), rec->progname);
	}
=======
static void sig_atexit(void)
{
	if (child_pid > 0)
		kill(child_pid, SIGTERM);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (signr == -1 || signr == SIGUSR1)
		return;

	signal(signr, SIG_DFL);
	kill(getpid(), signr);
}

<<<<<<< HEAD
=======
static void config_attr(struct perf_evsel *evsel, struct perf_evlist *evlist)
{
	struct perf_event_attr *attr = &evsel->attr;
	int track = !evsel->idx; /* only the first counter needs these */

	attr->inherit		= !no_inherit;
	attr->read_format	= PERF_FORMAT_TOTAL_TIME_ENABLED |
				  PERF_FORMAT_TOTAL_TIME_RUNNING |
				  PERF_FORMAT_ID;

	attr->sample_type	|= PERF_SAMPLE_IP | PERF_SAMPLE_TID;

	if (evlist->nr_entries > 1)
		attr->sample_type |= PERF_SAMPLE_ID;

	/*
	 * We default some events to a 1 default interval. But keep
	 * it a weak assumption overridable by the user.
	 */
	if (!attr->sample_period || (user_freq != UINT_MAX &&
				     user_interval != ULLONG_MAX)) {
		if (freq) {
			attr->sample_type	|= PERF_SAMPLE_PERIOD;
			attr->freq		= 1;
			attr->sample_freq	= freq;
		} else {
			attr->sample_period = default_interval;
		}
	}

	if (no_samples)
		attr->sample_freq = 0;

	if (inherit_stat)
		attr->inherit_stat = 1;

	if (sample_address) {
		attr->sample_type	|= PERF_SAMPLE_ADDR;
		attr->mmap_data = track;
	}

	if (call_graph)
		attr->sample_type	|= PERF_SAMPLE_CALLCHAIN;

	if (system_wide)
		attr->sample_type	|= PERF_SAMPLE_CPU;

	if (sample_id_all_avail &&
	    (sample_time || system_wide || !no_inherit || cpu_list))
		attr->sample_type	|= PERF_SAMPLE_TIME;

	if (raw_samples) {
		attr->sample_type	|= PERF_SAMPLE_TIME;
		attr->sample_type	|= PERF_SAMPLE_RAW;
		attr->sample_type	|= PERF_SAMPLE_CPU;
	}

	if (nodelay) {
		attr->watermark = 0;
		attr->wakeup_events = 1;
	}

	attr->mmap		= track;
	attr->comm		= track;

	if (target_pid == -1 && target_tid == -1 && !system_wide) {
		attr->disabled = 1;
		attr->enable_on_exec = 1;
	}
}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
static bool perf_evlist__equal(struct perf_evlist *evlist,
			       struct perf_evlist *other)
{
	struct perf_evsel *pos, *pair;

	if (evlist->nr_entries != other->nr_entries)
		return false;

	pair = list_entry(other->entries.next, struct perf_evsel, node);

	list_for_each_entry(pos, &evlist->entries, node) {
		if (memcmp(&pos->attr, &pair->attr, sizeof(pos->attr) != 0))
			return false;
		pair = list_entry(pair->node.next, struct perf_evsel, node);
	}

	return true;
}

<<<<<<< HEAD
static void perf_record__open(struct perf_record *rec)
{
	struct perf_evsel *pos, *first;
	struct perf_evlist *evlist = rec->evlist;
	struct perf_session *session = rec->session;
	struct perf_record_opts *opts = &rec->opts;

	first = list_entry(evlist->entries.next, struct perf_evsel, node);

	perf_evlist__config_attrs(evlist, opts);

	list_for_each_entry(pos, &evlist->entries, node) {
		struct perf_event_attr *attr = &pos->attr;
		struct xyarray *group_fd = NULL;
=======
static void open_counters(struct perf_evlist *evlist)
{
	struct perf_evsel *pos;

	if (evlist->cpus->map[0] < 0)
		no_inherit = true;

	list_for_each_entry(pos, &evlist->entries, node) {
		struct perf_event_attr *attr = &pos->attr;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		/*
		 * Check if parse_single_tracepoint_event has already asked for
		 * PERF_SAMPLE_TIME.
		 *
		 * XXX this is kludgy but short term fix for problems introduced by
		 * eac23d1c that broke 'perf script' by having different sample_types
		 * when using multiple tracepoint events when we use a perf binary
		 * that tries to use sample_id_all on an older kernel.
		 *
		 * We need to move counter creation to perf_session, support
		 * different sample_types, etc.
		 */
		bool time_needed = attr->sample_type & PERF_SAMPLE_TIME;

<<<<<<< HEAD
		if (opts->group && pos != first)
			group_fd = first->fd;
fallback_missing_features:
		if (opts->exclude_guest_missing)
			attr->exclude_guest = attr->exclude_host = 0;
retry_sample_id:
		attr->sample_id_all = opts->sample_id_all_missing ? 0 : 1;
try_again:
		if (perf_evsel__open(pos, evlist->cpus, evlist->threads,
				     opts->group, group_fd) < 0) {
			int err = errno;

			if (err == EPERM || err == EACCES) {
				ui__error_paranoid();
				exit(EXIT_FAILURE);
			} else if (err ==  ENODEV && opts->cpu_list) {
				die("No such device - did you specify"
					" an out-of-range profile CPU?\n");
			} else if (err == EINVAL) {
				if (!opts->exclude_guest_missing &&
				    (attr->exclude_guest || attr->exclude_host)) {
					pr_debug("Old kernel, cannot exclude "
						 "guest or host samples.\n");
					opts->exclude_guest_missing = true;
					goto fallback_missing_features;
				} else if (!opts->sample_id_all_missing) {
					/*
					 * Old kernel, no attr->sample_id_type_all field
					 */
					opts->sample_id_all_missing = true;
					if (!opts->sample_time && !opts->raw_samples && !time_needed)
						attr->sample_type &= ~PERF_SAMPLE_TIME;

					goto retry_sample_id;
				}
=======
		config_attr(pos, evlist);
retry_sample_id:
		attr->sample_id_all = sample_id_all_avail ? 1 : 0;
try_again:
		if (perf_evsel__open(pos, evlist->cpus, evlist->threads, group) < 0) {
			int err = errno;

			if (err == EPERM || err == EACCES) {
				ui__warning_paranoid();
				exit(EXIT_FAILURE);
			} else if (err ==  ENODEV && cpu_list) {
				die("No such device - did you specify"
					" an out-of-range profile CPU?\n");
			} else if (err == EINVAL && sample_id_all_avail) {
				/*
				 * Old kernel, no attr->sample_id_type_all field
				 */
				sample_id_all_avail = false;
				if (!sample_time && !raw_samples && !time_needed)
					attr->sample_type &= ~PERF_SAMPLE_TIME;

				goto retry_sample_id;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			}

			/*
			 * If it's cycles then fall back to hrtimer
			 * based cpu-clock-tick sw counter, which
			 * is always available even if no PMU support:
			 */
			if (attr->type == PERF_TYPE_HARDWARE
					&& attr->config == PERF_COUNT_HW_CPU_CYCLES) {

				if (verbose)
					ui__warning("The cycles event is not supported, "
						    "trying to fall back to cpu-clock-ticks\n");
				attr->type = PERF_TYPE_SOFTWARE;
				attr->config = PERF_COUNT_SW_CPU_CLOCK;
				goto try_again;
			}

			if (err == ENOENT) {
				ui__warning("The %s event is not supported.\n",
					    event_name(pos));
				exit(EXIT_FAILURE);
			}

			printf("\n");
			error("sys_perf_event_open() syscall returned with %d (%s).  /bin/dmesg may provide additional information.\n",
			      err, strerror(err));

#if defined(__i386__) || defined(__x86_64__)
			if (attr->type == PERF_TYPE_HARDWARE && err == EOPNOTSUPP)
				die("No hardware sampling interrupt available."
				    " No APIC? If so then you can boot the kernel"
				    " with the \"lapic\" boot parameter to"
				    " force-enable it.\n");
#endif

			die("No CONFIG_PERF_EVENTS=y kernel support configured?\n");
		}
	}

	if (perf_evlist__set_filters(evlist)) {
		error("failed to set filter with %d (%s)\n", errno,
			strerror(errno));
		exit(-1);
	}

<<<<<<< HEAD
	if (perf_evlist__mmap(evlist, opts->mmap_pages, false) < 0) {
		if (errno == EPERM)
			die("Permission error mapping pages.\n"
			    "Consider increasing "
			    "/proc/sys/kernel/perf_event_mlock_kb,\n"
			    "or try again with a smaller value of -m/--mmap_pages.\n"
			    "(current value: %d)\n", opts->mmap_pages);
		else if (!is_power_of_2(opts->mmap_pages))
			die("--mmap_pages/-m value must be a power of two.");

		die("failed to mmap with %d (%s)\n", errno, strerror(errno));
	}

	if (rec->file_new)
=======
	if (perf_evlist__mmap(evlist, mmap_pages, false) < 0)
		die("failed to mmap with %d (%s)\n", errno, strerror(errno));

	if (file_new)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		session->evlist = evlist;
	else {
		if (!perf_evlist__equal(session->evlist, evlist)) {
			fprintf(stderr, "incompatible append\n");
			exit(-1);
		}
 	}

	perf_session__update_sample_type(session);
}

<<<<<<< HEAD
static int process_buildids(struct perf_record *rec)
{
	u64 size = lseek(rec->output, 0, SEEK_CUR);
=======
static int process_buildids(void)
{
	u64 size = lseek(output, 0, SEEK_CUR);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (size == 0)
		return 0;

<<<<<<< HEAD
	rec->session->fd = rec->output;
	return __perf_session__process_events(rec->session, rec->post_processing_offset,
					      size - rec->post_processing_offset,
					      size, &build_id__mark_dso_hit_ops);
}

static void perf_record__exit(int status __used, void *arg)
{
	struct perf_record *rec = arg;

	if (!rec->opts.pipe_output) {
		rec->session->header.data_size += rec->bytes_written;

		if (!rec->no_buildid)
			process_buildids(rec);
		perf_session__write_header(rec->session, rec->evlist,
					   rec->output, true);
		perf_session__delete(rec->session);
		perf_evlist__delete(rec->evlist);
=======
	session->fd = output;
	return __perf_session__process_events(session, post_processing_offset,
					      size - post_processing_offset,
					      size, &build_id__mark_dso_hit_ops);
}

static void atexit_header(void)
{
	if (!pipe_output) {
		session->header.data_size += bytes_written;

		if (!no_buildid)
			process_buildids();
		perf_session__write_header(session, evsel_list, output, true);
		perf_session__delete(session);
		perf_evlist__delete(evsel_list);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		symbol__exit();
	}
}

static void perf_event__synthesize_guest_os(struct machine *machine, void *data)
{
	int err;
<<<<<<< HEAD
	struct perf_tool *tool = data;
=======
	struct perf_session *psession = data;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (machine__is_host(machine))
		return;

	/*
	 *As for guest kernel when processing subcommand record&report,
	 *we arrange module mmap prior to guest kernel mmap and trigger
	 *a preload dso because default guest module symbols are loaded
	 *from guest kallsyms instead of /lib/modules/XXX/XXX. This
	 *method is used to avoid symbol missing when the first addr is
	 *in module instead of in guest kernel.
	 */
<<<<<<< HEAD
	err = perf_event__synthesize_modules(tool, process_synthesized_event,
					     machine);
=======
	err = perf_event__synthesize_modules(process_synthesized_event,
					     psession, machine);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (err < 0)
		pr_err("Couldn't record guest kernel [%d]'s reference"
		       " relocation symbol.\n", machine->pid);

	/*
	 * We use _stext for guest kernel because guest kernel's /proc/kallsyms
	 * have no _text sometimes.
	 */
<<<<<<< HEAD
	err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
						 machine, "_text");
	if (err < 0)
		err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
							 machine, "_stext");
=======
	err = perf_event__synthesize_kernel_mmap(process_synthesized_event,
						 psession, machine, "_text");
	if (err < 0)
		err = perf_event__synthesize_kernel_mmap(process_synthesized_event,
							 psession, machine,
							 "_stext");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (err < 0)
		pr_err("Couldn't record guest kernel [%d]'s reference"
		       " relocation symbol.\n", machine->pid);
}

static struct perf_event_header finished_round_event = {
	.size = sizeof(struct perf_event_header),
	.type = PERF_RECORD_FINISHED_ROUND,
};

<<<<<<< HEAD
static void perf_record__mmap_read_all(struct perf_record *rec)
{
	int i;

	for (i = 0; i < rec->evlist->nr_mmaps; i++) {
		if (rec->evlist->mmap[i].base)
			perf_record__mmap_read(rec, &rec->evlist->mmap[i]);
	}

	if (perf_header__has_feat(&rec->session->header, HEADER_TRACE_INFO))
		write_output(rec, &finished_round_event, sizeof(finished_round_event));
}

static int __cmd_record(struct perf_record *rec, int argc, const char **argv)
{
	struct stat st;
	int flags;
	int err, output, feat;
	unsigned long waking = 0;
	const bool forks = argc > 0;
	struct machine *machine;
	struct perf_tool *tool = &rec->tool;
	struct perf_record_opts *opts = &rec->opts;
	struct perf_evlist *evsel_list = rec->evlist;
	const char *output_name = rec->output_name;
	struct perf_session *session;

	rec->progname = argv[0];

	rec->page_size = sysconf(_SC_PAGE_SIZE);

	on_exit(perf_record__sig_exit, rec);
=======
static void mmap_read_all(void)
{
	int i;

	for (i = 0; i < evsel_list->nr_mmaps; i++) {
		if (evsel_list->mmap[i].base)
			mmap_read(&evsel_list->mmap[i]);
	}

	if (perf_header__has_feat(&session->header, HEADER_TRACE_INFO))
		write_output(&finished_round_event, sizeof(finished_round_event));
}

static int __cmd_record(int argc, const char **argv)
{
	int i;
	struct stat st;
	int flags;
	int err;
	unsigned long waking = 0;
	int child_ready_pipe[2], go_pipe[2];
	const bool forks = argc > 0;
	char buf;
	struct machine *machine;

	page_size = sysconf(_SC_PAGE_SIZE);

	atexit(sig_atexit);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	signal(SIGCHLD, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGUSR1, sig_handler);

<<<<<<< HEAD
	if (!output_name) {
		if (!fstat(STDOUT_FILENO, &st) && S_ISFIFO(st.st_mode))
			opts->pipe_output = true;
		else
			rec->output_name = output_name = "perf.data";
	}
	if (output_name) {
		if (!strcmp(output_name, "-"))
			opts->pipe_output = true;
		else if (!stat(output_name, &st) && st.st_size) {
			if (rec->write_mode == WRITE_FORCE) {
=======
	if (forks && (pipe(child_ready_pipe) < 0 || pipe(go_pipe) < 0)) {
		perror("failed to create pipes");
		exit(-1);
	}

	if (!output_name) {
		if (!fstat(STDOUT_FILENO, &st) && S_ISFIFO(st.st_mode))
			pipe_output = 1;
		else
			output_name = "perf.data";
	}
	if (output_name) {
		if (!strcmp(output_name, "-"))
			pipe_output = 1;
		else if (!stat(output_name, &st) && st.st_size) {
			if (write_mode == WRITE_FORCE) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				char oldname[PATH_MAX];
				snprintf(oldname, sizeof(oldname), "%s.old",
					 output_name);
				unlink(oldname);
				rename(output_name, oldname);
			}
<<<<<<< HEAD
		} else if (rec->write_mode == WRITE_APPEND) {
			rec->write_mode = WRITE_FORCE;
=======
		} else if (write_mode == WRITE_APPEND) {
			write_mode = WRITE_FORCE;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		}
	}

	flags = O_CREAT|O_RDWR;
<<<<<<< HEAD
	if (rec->write_mode == WRITE_APPEND)
		rec->file_new = 0;
	else
		flags |= O_TRUNC;

	if (opts->pipe_output)
=======
	if (write_mode == WRITE_APPEND)
		file_new = 0;
	else
		flags |= O_TRUNC;

	if (pipe_output)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		output = STDOUT_FILENO;
	else
		output = open(output_name, flags, S_IRUSR | S_IWUSR);
	if (output < 0) {
		perror("failed to create output file");
		exit(-1);
	}

<<<<<<< HEAD
	rec->output = output;

	session = perf_session__new(output_name, O_WRONLY,
				    rec->write_mode == WRITE_FORCE, false, NULL);
=======
	session = perf_session__new(output_name, O_WRONLY,
				    write_mode == WRITE_FORCE, false, NULL);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (session == NULL) {
		pr_err("Not enough memory for reading perf file header\n");
		return -1;
	}

<<<<<<< HEAD
	rec->session = session;

	for (feat = HEADER_FIRST_FEATURE; feat < HEADER_LAST_FEATURE; feat++)
		perf_header__set_feat(&session->header, feat);

	if (rec->no_buildid)
		perf_header__clear_feat(&session->header, HEADER_BUILD_ID);

	if (!have_tracepoints(&evsel_list->entries))
		perf_header__clear_feat(&session->header, HEADER_TRACE_INFO);

	if (!rec->opts.branch_stack)
		perf_header__clear_feat(&session->header, HEADER_BRANCH_STACK);

	if (!rec->file_new) {
=======
	if (!no_buildid)
		perf_header__set_feat(&session->header, HEADER_BUILD_ID);

	if (!file_new) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		err = perf_session__read_header(session, output);
		if (err < 0)
			goto out_delete_session;
	}

<<<<<<< HEAD
	if (forks) {
		err = perf_evlist__prepare_workload(evsel_list, opts, argv);
		if (err < 0) {
			pr_err("Couldn't run the workload!\n");
			goto out_delete_session;
		}
	}

	perf_record__open(rec);

	/*
	 * perf_session__delete(session) will be called at perf_record__exit()
	 */
	on_exit(perf_record__exit, rec);

	if (opts->pipe_output) {
		err = perf_header__write_pipe(output);
		if (err < 0)
			return err;
	} else if (rec->file_new) {
=======
	if (have_tracepoints(&evsel_list->entries))
		perf_header__set_feat(&session->header, HEADER_TRACE_INFO);

	/* 512 kiB: default amount of unprivileged mlocked memory */
	if (mmap_pages == UINT_MAX)
		mmap_pages = (512 * 1024) / page_size;

	if (forks) {
		child_pid = fork();
		if (child_pid < 0) {
			perror("failed to fork");
			exit(-1);
		}

		if (!child_pid) {
			if (pipe_output)
				dup2(2, 1);
			close(child_ready_pipe[0]);
			close(go_pipe[1]);
			fcntl(go_pipe[0], F_SETFD, FD_CLOEXEC);

			/*
			 * Do a dummy execvp to get the PLT entry resolved,
			 * so we avoid the resolver overhead on the real
			 * execvp call.
			 */
			execvp("", (char **)argv);

			/*
			 * Tell the parent we're ready to go
			 */
			close(child_ready_pipe[1]);

			/*
			 * Wait until the parent tells us to go.
			 */
			if (read(go_pipe[0], &buf, 1) == -1)
				perror("unable to read pipe");

			execvp(argv[0], (char **)argv);

			perror(argv[0]);
			kill(getppid(), SIGUSR1);
			exit(-1);
		}

		if (!system_wide && target_tid == -1 && target_pid == -1)
			evsel_list->threads->map[0] = child_pid;

		close(child_ready_pipe[1]);
		close(go_pipe[0]);
		/*
		 * wait for child to settle
		 */
		if (read(child_ready_pipe[0], &buf, 1) == -1) {
			perror("unable to read pipe");
			exit(-1);
		}
		close(child_ready_pipe[0]);
	}

	open_counters(evsel_list);

	/*
	 * perf_session__delete(session) will be called at atexit_header()
	 */
	atexit(atexit_header);

	if (pipe_output) {
		err = perf_header__write_pipe(output);
		if (err < 0)
			return err;
	} else if (file_new) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		err = perf_session__write_header(session, evsel_list,
						 output, false);
		if (err < 0)
			return err;
	}

<<<<<<< HEAD
	if (!rec->no_buildid
	    && !perf_header__has_feat(&session->header, HEADER_BUILD_ID)) {
		pr_err("Couldn't generate buildids. "
		       "Use --no-buildid to profile anyway.\n");
		return -1;
	}

	rec->post_processing_offset = lseek(output, 0, SEEK_CUR);

	machine = perf_session__find_host_machine(session);
	if (!machine) {
		pr_err("Couldn't find native kernel information.\n");
		return -1;
	}

	if (opts->pipe_output) {
		err = perf_event__synthesize_attrs(tool, session,
						   process_synthesized_event);
=======
	post_processing_offset = lseek(output, 0, SEEK_CUR);

	if (pipe_output) {
		err = perf_session__synthesize_attrs(session,
						     process_synthesized_event);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (err < 0) {
			pr_err("Couldn't synthesize attrs.\n");
			return err;
		}

<<<<<<< HEAD
		err = perf_event__synthesize_event_types(tool, process_synthesized_event,
							 machine);
=======
		err = perf_event__synthesize_event_types(process_synthesized_event,
							 session);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (err < 0) {
			pr_err("Couldn't synthesize event_types.\n");
			return err;
		}

		if (have_tracepoints(&evsel_list->entries)) {
			/*
			 * FIXME err <= 0 here actually means that
			 * there were no tracepoints so its not really
			 * an error, just that we don't need to
			 * synthesize anything.  We really have to
			 * return this more properly and also
			 * propagate errors that now are calling die()
			 */
<<<<<<< HEAD
			err = perf_event__synthesize_tracing_data(tool, output, evsel_list,
								  process_synthesized_event);
=======
			err = perf_event__synthesize_tracing_data(output, evsel_list,
								  process_synthesized_event,
								  session);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			if (err <= 0) {
				pr_err("Couldn't record tracing data.\n");
				return err;
			}
<<<<<<< HEAD
			advance_output(rec, err);
		}
	}

	err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
						 machine, "_text");
	if (err < 0)
		err = perf_event__synthesize_kernel_mmap(tool, process_synthesized_event,
							 machine, "_stext");
=======
			advance_output(err);
		}
	}

	machine = perf_session__find_host_machine(session);
	if (!machine) {
		pr_err("Couldn't find native kernel information.\n");
		return -1;
	}

	err = perf_event__synthesize_kernel_mmap(process_synthesized_event,
						 session, machine, "_text");
	if (err < 0)
		err = perf_event__synthesize_kernel_mmap(process_synthesized_event,
							 session, machine, "_stext");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (err < 0)
		pr_err("Couldn't record kernel reference relocation symbol\n"
		       "Symbol resolution may be skewed if relocation was used (e.g. kexec).\n"
		       "Check /proc/kallsyms permission or run as root.\n");

<<<<<<< HEAD
	err = perf_event__synthesize_modules(tool, process_synthesized_event,
					     machine);
=======
	err = perf_event__synthesize_modules(process_synthesized_event,
					     session, machine);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (err < 0)
		pr_err("Couldn't record kernel module information.\n"
		       "Symbol resolution may be skewed if relocation was used (e.g. kexec).\n"
		       "Check /proc/modules permission or run as root.\n");

	if (perf_guest)
<<<<<<< HEAD
		perf_session__process_machines(session, tool,
					       perf_event__synthesize_guest_os);

	if (!opts->system_wide)
		perf_event__synthesize_thread_map(tool, evsel_list->threads,
						  process_synthesized_event,
						  machine);
	else
		perf_event__synthesize_threads(tool, process_synthesized_event,
					       machine);

	if (rec->realtime_prio) {
		struct sched_param param;

		param.sched_priority = rec->realtime_prio;
=======
		perf_session__process_machines(session,
					       perf_event__synthesize_guest_os);

	if (!system_wide)
		perf_event__synthesize_thread_map(evsel_list->threads,
						  process_synthesized_event,
						  session);
	else
		perf_event__synthesize_threads(process_synthesized_event,
					       session);

	if (realtime_prio) {
		struct sched_param param;

		param.sched_priority = realtime_prio;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (sched_setscheduler(0, SCHED_FIFO, &param)) {
			pr_err("Could not set realtime priority.\n");
			exit(-1);
		}
	}

<<<<<<< HEAD
	perf_evlist__enable(evsel_list);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	/*
	 * Let the child rip
	 */
	if (forks)
<<<<<<< HEAD
		perf_evlist__start_workload(evsel_list);

	for (;;) {
		int hits = rec->samples;

		perf_record__mmap_read_all(rec);

		if (hits == rec->samples) {
=======
		close(go_pipe[1]);

	for (;;) {
		int hits = samples;
		int thread;

		mmap_read_all();

		if (hits == samples) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			if (done)
				break;
			err = poll(evsel_list->pollfd, evsel_list->nr_fds, -1);
			waking++;
		}

<<<<<<< HEAD
		if (done)
			perf_evlist__disable(evsel_list);
=======
		if (done) {
			for (i = 0; i < evsel_list->cpus->nr; i++) {
				struct perf_evsel *pos;

				list_for_each_entry(pos, &evsel_list->entries, node) {
					for (thread = 0;
						thread < evsel_list->threads->nr;
						thread++)
						ioctl(FD(pos, i, thread),
							PERF_EVENT_IOC_DISABLE);
				}
			}
		}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	if (quiet || signr == SIGUSR1)
		return 0;

	fprintf(stderr, "[ perf record: Woken up %ld times to write data ]\n", waking);

	/*
	 * Approximate RIP event size: 24 bytes.
	 */
	fprintf(stderr,
		"[ perf record: Captured and wrote %.3f MB %s (~%" PRIu64 " samples) ]\n",
<<<<<<< HEAD
		(double)rec->bytes_written / 1024.0 / 1024.0,
		output_name,
		rec->bytes_written / 24);
=======
		(double)bytes_written / 1024.0 / 1024.0,
		output_name,
		bytes_written / 24);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	return 0;

out_delete_session:
	perf_session__delete(session);
	return err;
}

<<<<<<< HEAD
#define BRANCH_OPT(n, m) \
	{ .name = n, .mode = (m) }

#define BRANCH_END { .name = NULL }

struct branch_mode {
	const char *name;
	int mode;
};

static const struct branch_mode branch_modes[] = {
	BRANCH_OPT("u", PERF_SAMPLE_BRANCH_USER),
	BRANCH_OPT("k", PERF_SAMPLE_BRANCH_KERNEL),
	BRANCH_OPT("hv", PERF_SAMPLE_BRANCH_HV),
	BRANCH_OPT("any", PERF_SAMPLE_BRANCH_ANY),
	BRANCH_OPT("any_call", PERF_SAMPLE_BRANCH_ANY_CALL),
	BRANCH_OPT("any_ret", PERF_SAMPLE_BRANCH_ANY_RETURN),
	BRANCH_OPT("ind_call", PERF_SAMPLE_BRANCH_IND_CALL),
	BRANCH_END
};

static int
parse_branch_stack(const struct option *opt, const char *str, int unset)
{
#define ONLY_PLM \
	(PERF_SAMPLE_BRANCH_USER	|\
	 PERF_SAMPLE_BRANCH_KERNEL	|\
	 PERF_SAMPLE_BRANCH_HV)

	uint64_t *mode = (uint64_t *)opt->value;
	const struct branch_mode *br;
	char *s, *os = NULL, *p;
	int ret = -1;

	if (unset)
		return 0;

	/*
	 * cannot set it twice, -b + --branch-filter for instance
	 */
	if (*mode)
		return -1;

	/* str may be NULL in case no arg is passed to -b */
	if (str) {
		/* because str is read-only */
		s = os = strdup(str);
		if (!s)
			return -1;

		for (;;) {
			p = strchr(s, ',');
			if (p)
				*p = '\0';

			for (br = branch_modes; br->name; br++) {
				if (!strcasecmp(s, br->name))
					break;
			}
			if (!br->name) {
				ui__warning("unknown branch filter %s,"
					    " check man page\n", s);
				goto error;
			}

			*mode |= br->mode;

			if (!p)
				break;

			s = p + 1;
		}
	}
	ret = 0;

	/* default to any branch */
	if ((*mode & ~ONLY_PLM) == 0) {
		*mode = PERF_SAMPLE_BRANCH_ANY;
	}
error:
	free(os);
	return ret;
}

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
static const char * const record_usage[] = {
	"perf record [<options>] [<command>]",
	"perf record [<options>] -- <command> [<options>]",
	NULL
};

<<<<<<< HEAD
/*
 * XXX Ideally would be local to cmd_record() and passed to a perf_record__new
 * because we need to have access to it in perf_record__exit, that is called
 * after cmd_record() exits, but since record_options need to be accessible to
 * builtin-script, leave it here.
 *
 * At least we don't ouch it in all the other functions here directly.
 *
 * Just say no to tons of global variables, sigh.
 */
static struct perf_record record = {
	.opts = {
		.mmap_pages	     = UINT_MAX,
		.user_freq	     = UINT_MAX,
		.user_interval	     = ULLONG_MAX,
		.freq		     = 1000,
	},
	.write_mode = WRITE_FORCE,
	.file_new   = true,
};

/*
 * XXX Will stay a global variable till we fix builtin-script.c to stop messing
 * with it and switch to use the library functions in perf_evlist that came
 * from builtin-record.c, i.e. use perf_record_opts,
 * perf_evlist__prepare_workload, etc instead of fork+exec'in 'perf record',
 * using pipes, etc.
 */
const struct option record_options[] = {
	OPT_CALLBACK('e', "event", &record.evlist, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events_option),
	OPT_CALLBACK(0, "filter", &record.evlist, "filter",
		     "event filter", parse_filter),
	OPT_STRING('p', "pid", &record.opts.target_pid, "pid",
		    "record events on existing process id"),
	OPT_STRING('t', "tid", &record.opts.target_tid, "tid",
		    "record events on existing thread id"),
	OPT_INTEGER('r', "realtime", &record.realtime_prio,
		    "collect data with this RT SCHED_FIFO priority"),
	OPT_BOOLEAN('D', "no-delay", &record.opts.no_delay,
		    "collect data without buffering"),
	OPT_BOOLEAN('R', "raw-samples", &record.opts.raw_samples,
		    "collect raw sample records from all opened counters"),
	OPT_BOOLEAN('a', "all-cpus", &record.opts.system_wide,
			    "system-wide collection from all CPUs"),
	OPT_BOOLEAN('A', "append", &record.append_file,
			    "append to the output file to do incremental profiling"),
	OPT_STRING('C', "cpu", &record.opts.cpu_list, "cpu",
		    "list of cpus to monitor"),
	OPT_BOOLEAN('f', "force", &record.force,
			"overwrite existing data file (deprecated)"),
	OPT_U64('c', "count", &record.opts.user_interval, "event period to sample"),
	OPT_STRING('o', "output", &record.output_name, "file",
		    "output file name"),
	OPT_BOOLEAN('i', "no-inherit", &record.opts.no_inherit,
		    "child tasks do not inherit counters"),
	OPT_UINTEGER('F', "freq", &record.opts.user_freq, "profile at this frequency"),
	OPT_UINTEGER('m', "mmap-pages", &record.opts.mmap_pages,
		     "number of mmap data pages"),
	OPT_BOOLEAN(0, "group", &record.opts.group,
		    "put the counters into a counter group"),
	OPT_BOOLEAN('g', "call-graph", &record.opts.call_graph,
=======
static bool force, append_file;

const struct option record_options[] = {
	OPT_CALLBACK('e', "event", &evsel_list, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events),
	OPT_CALLBACK(0, "filter", &evsel_list, "filter",
		     "event filter", parse_filter),
	OPT_INTEGER('p', "pid", &target_pid,
		    "record events on existing process id"),
	OPT_INTEGER('t', "tid", &target_tid,
		    "record events on existing thread id"),
	OPT_INTEGER('r', "realtime", &realtime_prio,
		    "collect data with this RT SCHED_FIFO priority"),
	OPT_BOOLEAN('D', "no-delay", &nodelay,
		    "collect data without buffering"),
	OPT_BOOLEAN('R', "raw-samples", &raw_samples,
		    "collect raw sample records from all opened counters"),
	OPT_BOOLEAN('a', "all-cpus", &system_wide,
			    "system-wide collection from all CPUs"),
	OPT_BOOLEAN('A', "append", &append_file,
			    "append to the output file to do incremental profiling"),
	OPT_STRING('C', "cpu", &cpu_list, "cpu",
		    "list of cpus to monitor"),
	OPT_BOOLEAN('f', "force", &force,
			"overwrite existing data file (deprecated)"),
	OPT_U64('c', "count", &user_interval, "event period to sample"),
	OPT_STRING('o', "output", &output_name, "file",
		    "output file name"),
	OPT_BOOLEAN('i', "no-inherit", &no_inherit,
		    "child tasks do not inherit counters"),
	OPT_UINTEGER('F', "freq", &user_freq, "profile at this frequency"),
	OPT_UINTEGER('m', "mmap-pages", &mmap_pages, "number of mmap data pages"),
	OPT_BOOLEAN('g', "call-graph", &call_graph,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		    "do call-graph (stack chain/backtrace) recording"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show counter open errors, etc)"),
	OPT_BOOLEAN('q', "quiet", &quiet, "don't print any message"),
<<<<<<< HEAD
	OPT_BOOLEAN('s', "stat", &record.opts.inherit_stat,
		    "per thread counts"),
	OPT_BOOLEAN('d', "data", &record.opts.sample_address,
		    "Sample addresses"),
	OPT_BOOLEAN('T', "timestamp", &record.opts.sample_time, "Sample timestamps"),
	OPT_BOOLEAN('P', "period", &record.opts.period, "Sample period"),
	OPT_BOOLEAN('n', "no-samples", &record.opts.no_samples,
		    "don't sample"),
	OPT_BOOLEAN('N', "no-buildid-cache", &record.no_buildid_cache,
		    "do not update the buildid cache"),
	OPT_BOOLEAN('B', "no-buildid", &record.no_buildid,
		    "do not collect buildids in perf.data"),
	OPT_CALLBACK('G', "cgroup", &record.evlist, "name",
		     "monitor event in cgroup name only",
		     parse_cgroups),
	OPT_STRING('u', "uid", &record.uid_str, "user", "user to profile"),

	OPT_CALLBACK_NOOPT('b', "branch-any", &record.opts.branch_stack,
		     "branch any", "sample any taken branches",
		     parse_branch_stack),

	OPT_CALLBACK('j', "branch-filter", &record.opts.branch_stack,
		     "branch filter mask", "branch stack filter modes",
		     parse_branch_stack),
=======
	OPT_BOOLEAN('s', "stat", &inherit_stat,
		    "per thread counts"),
	OPT_BOOLEAN('d', "data", &sample_address,
		    "Sample addresses"),
	OPT_BOOLEAN('T', "timestamp", &sample_time, "Sample timestamps"),
	OPT_BOOLEAN('n', "no-samples", &no_samples,
		    "don't sample"),
	OPT_BOOLEAN('N', "no-buildid-cache", &no_buildid_cache,
		    "do not update the buildid cache"),
	OPT_BOOLEAN('B', "no-buildid", &no_buildid,
		    "do not collect buildids in perf.data"),
	OPT_CALLBACK('G', "cgroup", &evsel_list, "name",
		     "monitor event in cgroup name only",
		     parse_cgroups),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	OPT_END()
};

int cmd_record(int argc, const char **argv, const char *prefix __used)
{
	int err = -ENOMEM;
	struct perf_evsel *pos;
<<<<<<< HEAD
	struct perf_evlist *evsel_list;
	struct perf_record *rec = &record;

	perf_header__set_cmdline(argc, argv);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	evsel_list = perf_evlist__new(NULL, NULL);
	if (evsel_list == NULL)
		return -ENOMEM;

<<<<<<< HEAD
	rec->evlist = evsel_list;

	argc = parse_options(argc, argv, record_options, record_usage,
			    PARSE_OPT_STOP_AT_NON_OPTION);
	if (!argc && !rec->opts.target_pid && !rec->opts.target_tid &&
		!rec->opts.system_wide && !rec->opts.cpu_list && !rec->uid_str)
		usage_with_options(record_usage, record_options);

	if (rec->force && rec->append_file) {
		fprintf(stderr, "Can't overwrite and append at the same time."
				" You need to choose between -f and -A");
		usage_with_options(record_usage, record_options);
	} else if (rec->append_file) {
		rec->write_mode = WRITE_APPEND;
	} else {
		rec->write_mode = WRITE_FORCE;
	}

	if (nr_cgroups && !rec->opts.system_wide) {
=======
	argc = parse_options(argc, argv, record_options, record_usage,
			    PARSE_OPT_STOP_AT_NON_OPTION);
	if (!argc && target_pid == -1 && target_tid == -1 &&
		!system_wide && !cpu_list)
		usage_with_options(record_usage, record_options);

	if (force && append_file) {
		fprintf(stderr, "Can't overwrite and append at the same time."
				" You need to choose between -f and -A");
		usage_with_options(record_usage, record_options);
	} else if (append_file) {
		write_mode = WRITE_APPEND;
	} else {
		write_mode = WRITE_FORCE;
	}

	if (nr_cgroups && !system_wide) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		fprintf(stderr, "cgroup monitoring only available in"
			" system-wide mode\n");
		usage_with_options(record_usage, record_options);
	}

	symbol__init();

	if (symbol_conf.kptr_restrict)
		pr_warning(
"WARNING: Kernel address maps (/proc/{kallsyms,modules}) are restricted,\n"
"check /proc/sys/kernel/kptr_restrict.\n\n"
"Samples in kernel functions may not be resolved if a suitable vmlinux\n"
"file is not found in the buildid cache or in the vmlinux path.\n\n"
"Samples in kernel modules won't be resolved at all.\n\n"
"If some relocation was applied (e.g. kexec) symbols may be misresolved\n"
"even with a suitable vmlinux or kallsyms file.\n\n");

<<<<<<< HEAD
	if (rec->no_buildid_cache || rec->no_buildid)
=======
	if (no_buildid_cache || no_buildid)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		disable_buildid_cache();

	if (evsel_list->nr_entries == 0 &&
	    perf_evlist__add_default(evsel_list) < 0) {
		pr_err("Not enough memory for event selector list\n");
		goto out_symbol_exit;
	}

<<<<<<< HEAD
	rec->opts.uid = parse_target_uid(rec->uid_str, rec->opts.target_tid,
					 rec->opts.target_pid);
	if (rec->uid_str != NULL && rec->opts.uid == UINT_MAX - 1)
		goto out_free_fd;

	if (rec->opts.target_pid)
		rec->opts.target_tid = rec->opts.target_pid;

	if (perf_evlist__create_maps(evsel_list, rec->opts.target_pid,
				     rec->opts.target_tid, rec->opts.uid,
				     rec->opts.cpu_list) < 0)
		usage_with_options(record_usage, record_options);

	list_for_each_entry(pos, &evsel_list->entries, node) {
=======
	if (target_pid != -1)
		target_tid = target_pid;

	if (perf_evlist__create_maps(evsel_list, target_pid,
				     target_tid, cpu_list) < 0)
		usage_with_options(record_usage, record_options);

	list_for_each_entry(pos, &evsel_list->entries, node) {
		if (perf_evsel__alloc_fd(pos, evsel_list->cpus->nr,
					 evsel_list->threads->nr) < 0)
			goto out_free_fd;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (perf_header__push_event(pos->attr.config, event_name(pos)))
			goto out_free_fd;
	}

<<<<<<< HEAD
	if (rec->opts.user_interval != ULLONG_MAX)
		rec->opts.default_interval = rec->opts.user_interval;
	if (rec->opts.user_freq != UINT_MAX)
		rec->opts.freq = rec->opts.user_freq;
=======
	if (perf_evlist__alloc_pollfd(evsel_list) < 0)
		goto out_free_fd;

	if (user_interval != ULLONG_MAX)
		default_interval = user_interval;
	if (user_freq != UINT_MAX)
		freq = user_freq;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	/*
	 * User specified count overrides default frequency.
	 */
<<<<<<< HEAD
	if (rec->opts.default_interval)
		rec->opts.freq = 0;
	else if (rec->opts.freq) {
		rec->opts.default_interval = rec->opts.freq;
=======
	if (default_interval)
		freq = 0;
	else if (freq) {
		default_interval = freq;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	} else {
		fprintf(stderr, "frequency and count are zero, aborting\n");
		err = -EINVAL;
		goto out_free_fd;
	}

<<<<<<< HEAD
	err = __cmd_record(&record, argc, argv);
=======
	err = __cmd_record(argc, argv);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
out_free_fd:
	perf_evlist__delete_maps(evsel_list);
out_symbol_exit:
	symbol__exit();
	return err;
}
