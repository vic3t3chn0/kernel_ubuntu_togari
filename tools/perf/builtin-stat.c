/*
 * builtin-stat.c
 *
 * Builtin stat command: Give a precise performance counters summary
 * overview about any workload, CPU or specific PID.
 *
 * Sample output:

   $ perf stat ./hackbench 10

  Time: 0.118

  Performance counter stats for './hackbench 10':

       1708.761321 task-clock                #   11.037 CPUs utilized
            41,190 context-switches          #    0.024 M/sec
             6,735 CPU-migrations            #    0.004 M/sec
            17,318 page-faults               #    0.010 M/sec
     5,205,202,243 cycles                    #    3.046 GHz
     3,856,436,920 stalled-cycles-frontend   #   74.09% frontend cycles idle
     1,600,790,871 stalled-cycles-backend    #   30.75% backend  cycles idle
     2,603,501,247 instructions              #    0.50  insns per cycle
                                             #    1.48  stalled cycles per insn
       484,357,498 branches                  #  283.455 M/sec
         6,388,934 branch-misses             #    1.32% of all branches

        0.154822978  seconds time elapsed

 *
 * Copyright (C) 2008-2011, Red Hat Inc, Ingo Molnar <mingo@redhat.com>
 *
 * Improvements and fixes by:
 *
 *   Arjan van de Ven <arjan@linux.intel.com>
 *   Yanmin Zhang <yanmin.zhang@intel.com>
 *   Wu Fengguang <fengguang.wu@intel.com>
 *   Mike Galbraith <efault@gmx.de>
 *   Paul Mackerras <paulus@samba.org>
 *   Jaswinder Singh Rajput <jaswinder@kernel.org>
 *
 * Released under the GPL v2. (and only v2, not any later version)
 */

#include "perf.h"
#include "builtin.h"
#include "util/util.h"
#include "util/parse-options.h"
#include "util/parse-events.h"
#include "util/event.h"
#include "util/evlist.h"
#include "util/evsel.h"
#include "util/debug.h"
#include "util/color.h"
#include "util/header.h"
#include "util/cpumap.h"
#include "util/thread.h"
#include "util/thread_map.h"

#include <sys/prctl.h>
#include <math.h>
#include <locale.h>

#define DEFAULT_SEPARATOR	" "
<<<<<<< HEAD
#define CNTR_NOT_SUPPORTED	"<not supported>"
#define CNTR_NOT_COUNTED	"<not counted>"
=======
<<<<<<< HEAD
#define CNTR_NOT_SUPPORTED	"<not supported>"
#define CNTR_NOT_COUNTED	"<not counted>"
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static struct perf_event_attr default_attrs[] = {

  { .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_TASK_CLOCK		},
  { .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CONTEXT_SWITCHES	},
  { .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CPU_MIGRATIONS		},
  { .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_PAGE_FAULTS		},

  { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_CPU_CYCLES		},
  { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_FRONTEND	},
  { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_BACKEND	},
  { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_INSTRUCTIONS		},
  { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS	},
  { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_BRANCH_MISSES		},

};

/*
 * Detailed stats (-d), covering the L1 and last level data caches:
 */
static struct perf_event_attr detailed_attrs[] = {

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_LL			<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_LL			<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				},
};

/*
 * Very detailed stats (-d -d), covering the instruction cache and the TLB caches:
 */
static struct perf_event_attr very_detailed_attrs[] = {

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1I		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1I		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_DTLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_DTLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_ITLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_ITLB		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_READ		<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				},

};

/*
 * Very, very detailed stats (-d -d -d), adding prefetch events:
 */
static struct perf_event_attr very_very_detailed_attrs[] = {

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_PREFETCH	<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_ACCESS	<< 16)				},

  { .type = PERF_TYPE_HW_CACHE,
    .config =
	 PERF_COUNT_HW_CACHE_L1D		<<  0  |
	(PERF_COUNT_HW_CACHE_OP_PREFETCH	<<  8) |
	(PERF_COUNT_HW_CACHE_RESULT_MISS	<< 16)				},
};



struct perf_evlist		*evsel_list;

static bool			system_wide			=  false;
static int			run_idx				=  0;

static int			run_count			=  1;
static bool			no_inherit			= false;
static bool			scale				=  true;
static bool			no_aggr				= false;
<<<<<<< HEAD
static const char		*target_pid;
static const char		*target_tid;
=======
<<<<<<< HEAD
static const char		*target_pid;
static const char		*target_tid;
=======
static pid_t			target_pid			= -1;
static pid_t			target_tid			= -1;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static pid_t			child_pid			= -1;
static bool			null_run			=  false;
static int			detailed_run			=  0;
static bool			sync_run			=  false;
static bool			big_num				=  true;
static int			big_num_opt			=  -1;
static const char		*cpu_list;
static const char		*csv_sep			= NULL;
static bool			csv_output			= false;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static bool			group				= false;
static const char		*output_name			= NULL;
static FILE			*output				= NULL;
static int			output_fd;
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static volatile int done = 0;

struct stats
{
	double n, mean, M2;
};

struct perf_stat {
	struct stats	  res_stats[3];
};

static int perf_evsel__alloc_stat_priv(struct perf_evsel *evsel)
{
	evsel->priv = zalloc(sizeof(struct perf_stat));
	return evsel->priv == NULL ? -ENOMEM : 0;
}

static void perf_evsel__free_stat_priv(struct perf_evsel *evsel)
{
	free(evsel->priv);
	evsel->priv = NULL;
}

static void update_stats(struct stats *stats, u64 val)
{
	double delta;

	stats->n++;
	delta = val - stats->mean;
	stats->mean += delta / stats->n;
	stats->M2 += delta*(val - stats->mean);
}

static double avg_stats(struct stats *stats)
{
	return stats->mean;
}

/*
 * http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 *
 *       (\Sum n_i^2) - ((\Sum n_i)^2)/n
 * s^2 = -------------------------------
 *                  n - 1
 *
 * http://en.wikipedia.org/wiki/Stddev
 *
 * The std dev of the mean is related to the std dev by:
 *
 *             s
 * s_mean = -------
 *          sqrt(n)
 *
 */
static double stddev_stats(struct stats *stats)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	double variance, variance_mean;

	if (!stats->n)
		return 0.0;

	variance = stats->M2 / (stats->n - 1);
	variance_mean = variance / stats->n;
<<<<<<< HEAD
=======
=======
	double variance = stats->M2 / (stats->n - 1);
	double variance_mean = variance / stats->n;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return sqrt(variance_mean);
}

struct stats			runtime_nsecs_stats[MAX_NR_CPUS];
struct stats			runtime_cycles_stats[MAX_NR_CPUS];
struct stats			runtime_stalled_cycles_front_stats[MAX_NR_CPUS];
struct stats			runtime_stalled_cycles_back_stats[MAX_NR_CPUS];
struct stats			runtime_branches_stats[MAX_NR_CPUS];
struct stats			runtime_cacherefs_stats[MAX_NR_CPUS];
struct stats			runtime_l1_dcache_stats[MAX_NR_CPUS];
struct stats			runtime_l1_icache_stats[MAX_NR_CPUS];
struct stats			runtime_ll_cache_stats[MAX_NR_CPUS];
struct stats			runtime_itlb_cache_stats[MAX_NR_CPUS];
struct stats			runtime_dtlb_cache_stats[MAX_NR_CPUS];
struct stats			walltime_nsecs_stats;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int create_perf_stat_counter(struct perf_evsel *evsel,
				    struct perf_evsel *first)
{
	struct perf_event_attr *attr = &evsel->attr;
	struct xyarray *group_fd = NULL;
	bool exclude_guest_missing = false;
	int ret;

	if (group && evsel != first)
		group_fd = first->fd;
<<<<<<< HEAD
=======
=======
static int create_perf_stat_counter(struct perf_evsel *evsel)
{
	struct perf_event_attr *attr = &evsel->attr;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (scale)
		attr->read_format = PERF_FORMAT_TOTAL_TIME_ENABLED |
				    PERF_FORMAT_TOTAL_TIME_RUNNING;

	attr->inherit = !no_inherit;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
retry:
	if (exclude_guest_missing)
		evsel->attr.exclude_guest = evsel->attr.exclude_host = 0;

	if (system_wide) {
		ret = perf_evsel__open_per_cpu(evsel, evsel_list->cpus,
						group, group_fd);
		if (ret)
			goto check_ret;
		return 0;
	}

	if (!target_pid && !target_tid && (!group || evsel == first)) {
<<<<<<< HEAD
=======
=======
	if (system_wide)
		return perf_evsel__open_per_cpu(evsel, evsel_list->cpus, false);

	if (target_pid == -1 && target_tid == -1) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		attr->disabled = 1;
		attr->enable_on_exec = 1;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = perf_evsel__open_per_thread(evsel, evsel_list->threads,
					  group, group_fd);
	if (!ret)
		return 0;
	/* fall through */
check_ret:
	if (ret && errno == EINVAL) {
		if (!exclude_guest_missing &&
		    (evsel->attr.exclude_guest || evsel->attr.exclude_host)) {
			pr_debug("Old kernel, cannot exclude "
				 "guest or host samples.\n");
			exclude_guest_missing = true;
			goto retry;
		}
	}
	return ret;
<<<<<<< HEAD
=======
=======
	return perf_evsel__open_per_thread(evsel, evsel_list->threads, false);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/*
 * Does the counter have nsecs as a unit?
 */
static inline int nsec_counter(struct perf_evsel *evsel)
{
	if (perf_evsel__match(evsel, SOFTWARE, SW_CPU_CLOCK) ||
	    perf_evsel__match(evsel, SOFTWARE, SW_TASK_CLOCK))
		return 1;

	return 0;
}

/*
 * Update various tracking values we maintain to print
 * more semantic information such as miss/hit ratios,
 * instruction rates, etc:
 */
static void update_shadow_stats(struct perf_evsel *counter, u64 *count)
{
	if (perf_evsel__match(counter, SOFTWARE, SW_TASK_CLOCK))
		update_stats(&runtime_nsecs_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_CPU_CYCLES))
		update_stats(&runtime_cycles_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_FRONTEND))
		update_stats(&runtime_stalled_cycles_front_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_STALLED_CYCLES_BACKEND))
		update_stats(&runtime_stalled_cycles_back_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_BRANCH_INSTRUCTIONS))
		update_stats(&runtime_branches_stats[0], count[0]);
	else if (perf_evsel__match(counter, HARDWARE, HW_CACHE_REFERENCES))
		update_stats(&runtime_cacherefs_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_L1D))
		update_stats(&runtime_l1_dcache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_L1I))
		update_stats(&runtime_l1_icache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_LL))
		update_stats(&runtime_ll_cache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_DTLB))
		update_stats(&runtime_dtlb_cache_stats[0], count[0]);
	else if (perf_evsel__match(counter, HW_CACHE, HW_CACHE_ITLB))
		update_stats(&runtime_itlb_cache_stats[0], count[0]);
}

/*
 * Read out the results of a single counter:
 * aggregate counts across CPUs in system-wide mode
 */
static int read_counter_aggr(struct perf_evsel *counter)
{
	struct perf_stat *ps = counter->priv;
	u64 *count = counter->counts->aggr.values;
	int i;

	if (__perf_evsel__read(counter, evsel_list->cpus->nr,
			       evsel_list->threads->nr, scale) < 0)
		return -1;

	for (i = 0; i < 3; i++)
		update_stats(&ps->res_stats[i], count[i]);

	if (verbose) {
<<<<<<< HEAD
		fprintf(output, "%s: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n",
=======
<<<<<<< HEAD
		fprintf(output, "%s: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n",
=======
		fprintf(stderr, "%s: %" PRIu64 " %" PRIu64 " %" PRIu64 "\n",
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			event_name(counter), count[0], count[1], count[2]);
	}

	/*
	 * Save the full runtime - to allow normalization during printout:
	 */
	update_shadow_stats(counter, count);

	return 0;
}

/*
 * Read out the results of a single counter:
 * do not aggregate counts across CPUs in system-wide mode
 */
static int read_counter(struct perf_evsel *counter)
{
	u64 *count;
	int cpu;

	for (cpu = 0; cpu < evsel_list->cpus->nr; cpu++) {
		if (__perf_evsel__read_on_cpu(counter, cpu, 0, scale) < 0)
			return -1;

		count = counter->counts->cpu[cpu].values;

		update_shadow_stats(counter, count);
	}

	return 0;
}

static int run_perf_stat(int argc __used, const char **argv)
{
	unsigned long long t0, t1;
<<<<<<< HEAD
	struct perf_evsel *counter, *first;
=======
<<<<<<< HEAD
	struct perf_evsel *counter, *first;
=======
	struct perf_evsel *counter;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int status = 0;
	int child_ready_pipe[2], go_pipe[2];
	const bool forks = (argc > 0);
	char buf;

	if (forks && (pipe(child_ready_pipe) < 0 || pipe(go_pipe) < 0)) {
		perror("failed to create pipes");
		exit(1);
	}

	if (forks) {
		if ((child_pid = fork()) < 0)
			perror("failed to fork");

		if (!child_pid) {
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
			exit(-1);
		}

<<<<<<< HEAD
		if (!target_tid && !target_pid && !system_wide)
=======
<<<<<<< HEAD
		if (!target_tid && !target_pid && !system_wide)
=======
		if (target_tid == -1 && target_pid == -1 && !system_wide)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			evsel_list->threads->map[0] = child_pid;

		/*
		 * Wait for the child to be ready to exec.
		 */
		close(child_ready_pipe[1]);
		close(go_pipe[0]);
		if (read(child_ready_pipe[0], &buf, 1) == -1)
			perror("unable to read pipe");
		close(child_ready_pipe[0]);
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	first = list_entry(evsel_list->entries.next, struct perf_evsel, node);

	list_for_each_entry(counter, &evsel_list->entries, node) {
		if (create_perf_stat_counter(counter, first) < 0) {
			/*
			 * PPC returns ENXIO for HW counters until 2.6.37
			 * (behavior changed with commit b0a873e).
			 */
			if (errno == EINVAL || errno == ENOSYS ||
			    errno == ENOENT || errno == EOPNOTSUPP ||
			    errno == ENXIO) {
				if (verbose)
					ui__warning("%s event is not supported by the kernel.\n",
						    event_name(counter));
				counter->supported = false;
<<<<<<< HEAD
=======
=======
	list_for_each_entry(counter, &evsel_list->entries, node) {
		if (create_perf_stat_counter(counter) < 0) {
			if (errno == EINVAL || errno == ENOSYS || errno == ENOENT) {
				if (verbose)
					ui__warning("%s event is not supported by the kernel.\n",
						    event_name(counter));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				continue;
			}

			if (errno == EPERM || errno == EACCES) {
				error("You may not have permission to collect %sstats.\n"
				      "\t Consider tweaking"
				      " /proc/sys/kernel/perf_event_paranoid or running as root.",
				      system_wide ? "system-wide " : "");
			} else {
				error("open_counter returned with %d (%s). "
				      "/bin/dmesg may provide additional information.\n",
				       errno, strerror(errno));
			}
			if (child_pid != -1)
				kill(child_pid, SIGTERM);
			die("Not all events could be opened.\n");
			return -1;
		}
<<<<<<< HEAD
		counter->supported = true;
=======
<<<<<<< HEAD
		counter->supported = true;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if (perf_evlist__set_filters(evsel_list)) {
		error("failed to set filter with %d (%s)\n", errno,
			strerror(errno));
		return -1;
	}

	/*
	 * Enable counters and exec the command:
	 */
	t0 = rdclock();

	if (forks) {
		close(go_pipe[1]);
		wait(&status);
<<<<<<< HEAD
		if (WIFSIGNALED(status))
			psignal(WTERMSIG(status), argv[0]);
=======
<<<<<<< HEAD
		if (WIFSIGNALED(status))
			psignal(WTERMSIG(status), argv[0]);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	} else {
		while(!done) sleep(1);
	}

	t1 = rdclock();

	update_stats(&walltime_nsecs_stats, t1 - t0);

	if (no_aggr) {
		list_for_each_entry(counter, &evsel_list->entries, node) {
			read_counter(counter);
			perf_evsel__close_fd(counter, evsel_list->cpus->nr, 1);
		}
	} else {
		list_for_each_entry(counter, &evsel_list->entries, node) {
			read_counter_aggr(counter);
			perf_evsel__close_fd(counter, evsel_list->cpus->nr,
					     evsel_list->threads->nr);
		}
	}

	return WEXITSTATUS(status);
}

static void print_noise_pct(double total, double avg)
{
	double pct = 0.0;

	if (avg)
		pct = 100.0*total/avg;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (csv_output)
		fprintf(output, "%s%.2f%%", csv_sep, pct);
	else if (pct)
		fprintf(output, "  ( +-%6.2f%% )", pct);
<<<<<<< HEAD
=======
=======
	fprintf(stderr, "  ( +-%6.2f%% )", pct);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_noise(struct perf_evsel *evsel, double avg)
{
	struct perf_stat *ps;

	if (run_count == 1)
		return;

	ps = evsel->priv;
	print_noise_pct(stddev_stats(&ps->res_stats[0]), avg);
}

static void nsec_printout(int cpu, struct perf_evsel *evsel, double avg)
{
	double msecs = avg / 1e6;
	char cpustr[16] = { '\0', };
	const char *fmt = csv_output ? "%s%.6f%s%s" : "%s%18.6f%s%-25s";

	if (no_aggr)
		sprintf(cpustr, "CPU%*d%s",
			csv_output ? 0 : -4,
			evsel_list->cpus->map[cpu], csv_sep);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	fprintf(output, fmt, cpustr, msecs, csv_sep, event_name(evsel));

	if (evsel->cgrp)
		fprintf(output, "%s%s", csv_sep, evsel->cgrp->name);
<<<<<<< HEAD
=======
=======
	fprintf(stderr, fmt, cpustr, msecs, csv_sep, event_name(evsel));

	if (evsel->cgrp)
		fprintf(stderr, "%s%s", csv_sep, evsel->cgrp->name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (csv_output)
		return;

	if (perf_evsel__match(evsel, SOFTWARE, SW_TASK_CLOCK))
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		fprintf(output, " # %8.3f CPUs utilized          ",
			avg / avg_stats(&walltime_nsecs_stats));
	else
		fprintf(output, "                                   ");
}

/* used for get_ratio_color() */
enum grc_type {
	GRC_STALLED_CYCLES_FE,
	GRC_STALLED_CYCLES_BE,
	GRC_CACHE_MISSES,
	GRC_MAX_NR
};

static const char *get_ratio_color(enum grc_type type, double ratio)
{
	static const double grc_table[GRC_MAX_NR][3] = {
		[GRC_STALLED_CYCLES_FE] = { 50.0, 30.0, 10.0 },
		[GRC_STALLED_CYCLES_BE] = { 75.0, 50.0, 20.0 },
		[GRC_CACHE_MISSES] 	= { 20.0, 10.0, 5.0 },
	};
	const char *color = PERF_COLOR_NORMAL;

	if (ratio > grc_table[type][0])
		color = PERF_COLOR_RED;
	else if (ratio > grc_table[type][1])
		color = PERF_COLOR_MAGENTA;
	else if (ratio > grc_table[type][2])
		color = PERF_COLOR_YELLOW;

	return color;
<<<<<<< HEAD
=======
=======
		fprintf(stderr, " # %8.3f CPUs utilized          ", avg / avg_stats(&walltime_nsecs_stats));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_stalled_cycles_frontend(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_cycles_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_STALLED_CYCLES_FE, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " frontend cycles idle   ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 50.0)
		color = PERF_COLOR_RED;
	else if (ratio > 30.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 10.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " frontend cycles idle   ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_stalled_cycles_backend(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_cycles_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_STALLED_CYCLES_BE, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " backend  cycles idle   ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 75.0)
		color = PERF_COLOR_RED;
	else if (ratio > 50.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 20.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " backend  cycles idle   ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_branch_misses(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_branches_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " of all branches        ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 20.0)
		color = PERF_COLOR_RED;
	else if (ratio > 10.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 5.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " of all branches        ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_l1_dcache_misses(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_l1_dcache_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " of all L1-dcache hits  ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 20.0)
		color = PERF_COLOR_RED;
	else if (ratio > 10.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 5.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " of all L1-dcache hits  ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_l1_icache_misses(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_l1_icache_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " of all L1-icache hits  ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 20.0)
		color = PERF_COLOR_RED;
	else if (ratio > 10.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 5.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " of all L1-icache hits  ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_dtlb_cache_misses(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_dtlb_cache_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " of all dTLB cache hits ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 20.0)
		color = PERF_COLOR_RED;
	else if (ratio > 10.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 5.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " of all dTLB cache hits ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_itlb_cache_misses(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_itlb_cache_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " of all iTLB cache hits ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 20.0)
		color = PERF_COLOR_RED;
	else if (ratio > 10.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 5.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " of all iTLB cache hits ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void print_ll_cache_misses(int cpu, struct perf_evsel *evsel __used, double avg)
{
	double total, ratio = 0.0;
	const char *color;

	total = avg_stats(&runtime_ll_cache_stats[cpu]);

	if (total)
		ratio = avg / total * 100.0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	fprintf(output, " #  ");
	color_fprintf(output, color, "%6.2f%%", ratio);
	fprintf(output, " of all LL-cache hits   ");
<<<<<<< HEAD
=======
=======
	color = PERF_COLOR_NORMAL;
	if (ratio > 20.0)
		color = PERF_COLOR_RED;
	else if (ratio > 10.0)
		color = PERF_COLOR_MAGENTA;
	else if (ratio > 5.0)
		color = PERF_COLOR_YELLOW;

	fprintf(stderr, " #  ");
	color_fprintf(stderr, color, "%6.2f%%", ratio);
	fprintf(stderr, " of all LL-cache hits   ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void abs_printout(int cpu, struct perf_evsel *evsel, double avg)
{
	double total, ratio = 0.0;
	char cpustr[16] = { '\0', };
	const char *fmt;

	if (csv_output)
		fmt = "%s%.0f%s%s";
	else if (big_num)
		fmt = "%s%'18.0f%s%-25s";
	else
		fmt = "%s%18.0f%s%-25s";

	if (no_aggr)
		sprintf(cpustr, "CPU%*d%s",
			csv_output ? 0 : -4,
			evsel_list->cpus->map[cpu], csv_sep);
	else
		cpu = 0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	fprintf(output, fmt, cpustr, avg, csv_sep, event_name(evsel));

	if (evsel->cgrp)
		fprintf(output, "%s%s", csv_sep, evsel->cgrp->name);
<<<<<<< HEAD
=======
=======
	fprintf(stderr, fmt, cpustr, avg, csv_sep, event_name(evsel));

	if (evsel->cgrp)
		fprintf(stderr, "%s%s", csv_sep, evsel->cgrp->name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (csv_output)
		return;

	if (perf_evsel__match(evsel, HARDWARE, HW_INSTRUCTIONS)) {
		total = avg_stats(&runtime_cycles_stats[cpu]);

		if (total)
			ratio = avg / total;

<<<<<<< HEAD
		fprintf(output, " #   %5.2f  insns per cycle        ", ratio);
=======
<<<<<<< HEAD
		fprintf(output, " #   %5.2f  insns per cycle        ", ratio);
=======
		fprintf(stderr, " #   %5.2f  insns per cycle        ", ratio);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		total = avg_stats(&runtime_stalled_cycles_front_stats[cpu]);
		total = max(total, avg_stats(&runtime_stalled_cycles_back_stats[cpu]));

		if (total && avg) {
			ratio = total / avg;
<<<<<<< HEAD
			fprintf(output, "\n                                             #   %5.2f  stalled cycles per insn", ratio);
=======
<<<<<<< HEAD
			fprintf(output, "\n                                             #   %5.2f  stalled cycles per insn", ratio);
=======
			fprintf(stderr, "\n                                             #   %5.2f  stalled cycles per insn", ratio);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}

	} else if (perf_evsel__match(evsel, HARDWARE, HW_BRANCH_MISSES) &&
			runtime_branches_stats[cpu].n != 0) {
		print_branch_misses(cpu, evsel, avg);
	} else if (
		evsel->attr.type == PERF_TYPE_HW_CACHE &&
		evsel->attr.config ==  ( PERF_COUNT_HW_CACHE_L1D |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16)) &&
			runtime_l1_dcache_stats[cpu].n != 0) {
		print_l1_dcache_misses(cpu, evsel, avg);
	} else if (
		evsel->attr.type == PERF_TYPE_HW_CACHE &&
		evsel->attr.config ==  ( PERF_COUNT_HW_CACHE_L1I |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16)) &&
			runtime_l1_icache_stats[cpu].n != 0) {
		print_l1_icache_misses(cpu, evsel, avg);
	} else if (
		evsel->attr.type == PERF_TYPE_HW_CACHE &&
		evsel->attr.config ==  ( PERF_COUNT_HW_CACHE_DTLB |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16)) &&
			runtime_dtlb_cache_stats[cpu].n != 0) {
		print_dtlb_cache_misses(cpu, evsel, avg);
	} else if (
		evsel->attr.type == PERF_TYPE_HW_CACHE &&
		evsel->attr.config ==  ( PERF_COUNT_HW_CACHE_ITLB |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16)) &&
			runtime_itlb_cache_stats[cpu].n != 0) {
		print_itlb_cache_misses(cpu, evsel, avg);
	} else if (
		evsel->attr.type == PERF_TYPE_HW_CACHE &&
		evsel->attr.config ==  ( PERF_COUNT_HW_CACHE_LL |
					((PERF_COUNT_HW_CACHE_OP_READ) << 8) |
					((PERF_COUNT_HW_CACHE_RESULT_MISS) << 16)) &&
			runtime_ll_cache_stats[cpu].n != 0) {
		print_ll_cache_misses(cpu, evsel, avg);
	} else if (perf_evsel__match(evsel, HARDWARE, HW_CACHE_MISSES) &&
			runtime_cacherefs_stats[cpu].n != 0) {
		total = avg_stats(&runtime_cacherefs_stats[cpu]);

		if (total)
			ratio = avg * 100 / total;

<<<<<<< HEAD
		fprintf(output, " # %8.3f %% of all cache refs    ", ratio);
=======
<<<<<<< HEAD
		fprintf(output, " # %8.3f %% of all cache refs    ", ratio);
=======
		fprintf(stderr, " # %8.3f %% of all cache refs    ", ratio);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	} else if (perf_evsel__match(evsel, HARDWARE, HW_STALLED_CYCLES_FRONTEND)) {
		print_stalled_cycles_frontend(cpu, evsel, avg);
	} else if (perf_evsel__match(evsel, HARDWARE, HW_STALLED_CYCLES_BACKEND)) {
		print_stalled_cycles_backend(cpu, evsel, avg);
	} else if (perf_evsel__match(evsel, HARDWARE, HW_CPU_CYCLES)) {
		total = avg_stats(&runtime_nsecs_stats[cpu]);

		if (total)
			ratio = 1.0 * avg / total;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		fprintf(output, " # %8.3f GHz                    ", ratio);
	} else if (runtime_nsecs_stats[cpu].n != 0) {
		char unit = 'M';

<<<<<<< HEAD
=======
=======
		fprintf(stderr, " # %8.3f GHz                    ", ratio);
	} else if (runtime_nsecs_stats[cpu].n != 0) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		total = avg_stats(&runtime_nsecs_stats[cpu]);

		if (total)
			ratio = 1000.0 * avg / total;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (ratio < 0.001) {
			ratio *= 1000;
			unit = 'K';
		}

		fprintf(output, " # %8.3f %c/sec                  ", ratio, unit);
	} else {
		fprintf(output, "                                   ");
<<<<<<< HEAD
=======
=======

		fprintf(stderr, " # %8.3f M/sec                  ", ratio);
	} else {
		fprintf(stderr, "                                   ");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
}

/*
 * Print out the results of a single counter:
 * aggregated counts in system-wide mode
 */
static void print_counter_aggr(struct perf_evsel *counter)
{
	struct perf_stat *ps = counter->priv;
	double avg = avg_stats(&ps->res_stats[0]);
	int scaled = counter->counts->scaled;

	if (scaled == -1) {
<<<<<<< HEAD
		fprintf(output, "%*s%s%*s",
			csv_output ? 0 : 18,
			counter->supported ? CNTR_NOT_COUNTED : CNTR_NOT_SUPPORTED,
=======
<<<<<<< HEAD
		fprintf(output, "%*s%s%*s",
			csv_output ? 0 : 18,
			counter->supported ? CNTR_NOT_COUNTED : CNTR_NOT_SUPPORTED,
=======
		fprintf(stderr, "%*s%s%*s",
			csv_output ? 0 : 18,
			"<not counted>",
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			csv_sep,
			csv_output ? 0 : -24,
			event_name(counter));

		if (counter->cgrp)
<<<<<<< HEAD
			fprintf(output, "%s%s", csv_sep, counter->cgrp->name);

		fputc('\n', output);
=======
<<<<<<< HEAD
			fprintf(output, "%s%s", csv_sep, counter->cgrp->name);

		fputc('\n', output);
=======
			fprintf(stderr, "%s%s", csv_sep, counter->cgrp->name);

		fputc('\n', stderr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return;
	}

	if (nsec_counter(counter))
		nsec_printout(-1, counter, avg);
	else
		abs_printout(-1, counter, avg);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	print_noise(counter, avg);

	if (csv_output) {
		fputc('\n', output);
		return;
	}

<<<<<<< HEAD
=======
=======
	if (csv_output) {
		fputc('\n', stderr);
		return;
	}

	print_noise(counter, avg);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (scaled) {
		double avg_enabled, avg_running;

		avg_enabled = avg_stats(&ps->res_stats[1]);
		avg_running = avg_stats(&ps->res_stats[2]);

<<<<<<< HEAD
		fprintf(output, " [%5.2f%%]", 100 * avg_running / avg_enabled);
	}
	fprintf(output, "\n");
=======
<<<<<<< HEAD
		fprintf(output, " [%5.2f%%]", 100 * avg_running / avg_enabled);
	}
	fprintf(output, "\n");
=======
		fprintf(stderr, " [%5.2f%%]", 100 * avg_running / avg_enabled);
	}
	fprintf(stderr, "\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/*
 * Print out the results of a single counter:
 * does not use aggregated count in system-wide
 */
static void print_counter(struct perf_evsel *counter)
{
	u64 ena, run, val;
	int cpu;

	for (cpu = 0; cpu < evsel_list->cpus->nr; cpu++) {
		val = counter->counts->cpu[cpu].val;
		ena = counter->counts->cpu[cpu].ena;
		run = counter->counts->cpu[cpu].run;
		if (run == 0 || ena == 0) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			fprintf(output, "CPU%*d%s%*s%s%*s",
				csv_output ? 0 : -4,
				evsel_list->cpus->map[cpu], csv_sep,
				csv_output ? 0 : 18,
				counter->supported ? CNTR_NOT_COUNTED : CNTR_NOT_SUPPORTED,
				csv_sep,
<<<<<<< HEAD
=======
=======
			fprintf(stderr, "CPU%*d%s%*s%s%*s",
				csv_output ? 0 : -4,
				evsel_list->cpus->map[cpu], csv_sep,
				csv_output ? 0 : 18,
				"<not counted>", csv_sep,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				csv_output ? 0 : -24,
				event_name(counter));

			if (counter->cgrp)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				fprintf(output, "%s%s",
					csv_sep, counter->cgrp->name);

			fputc('\n', output);
<<<<<<< HEAD
=======
=======
				fprintf(stderr, "%s%s", csv_sep, counter->cgrp->name);

			fputc('\n', stderr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			continue;
		}

		if (nsec_counter(counter))
			nsec_printout(cpu, counter, val);
		else
			abs_printout(cpu, counter, val);

		if (!csv_output) {
			print_noise(counter, 1.0);

			if (run != ena)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				fprintf(output, "  (%.2f%%)",
					100.0 * run / ena);
		}
		fputc('\n', output);
<<<<<<< HEAD
=======
=======
				fprintf(stderr, "  (%.2f%%)", 100.0 * run / ena);
		}
		fputc('\n', stderr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
}

static void print_stat(int argc, const char **argv)
{
	struct perf_evsel *counter;
	int i;

	fflush(stdout);

	if (!csv_output) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		fprintf(output, "\n");
		fprintf(output, " Performance counter stats for ");
		if (!target_pid && !target_tid) {
			fprintf(output, "\'%s", argv[0]);
			for (i = 1; i < argc; i++)
				fprintf(output, " %s", argv[i]);
		} else if (target_pid)
			fprintf(output, "process id \'%s", target_pid);
		else
			fprintf(output, "thread id \'%s", target_tid);

		fprintf(output, "\'");
		if (run_count > 1)
			fprintf(output, " (%d runs)", run_count);
		fprintf(output, ":\n\n");
<<<<<<< HEAD
=======
=======
		fprintf(stderr, "\n");
		fprintf(stderr, " Performance counter stats for ");
		if(target_pid == -1 && target_tid == -1) {
			fprintf(stderr, "\'%s", argv[0]);
			for (i = 1; i < argc; i++)
				fprintf(stderr, " %s", argv[i]);
		} else if (target_pid != -1)
			fprintf(stderr, "process id \'%d", target_pid);
		else
			fprintf(stderr, "thread id \'%d", target_tid);

		fprintf(stderr, "\'");
		if (run_count > 1)
			fprintf(stderr, " (%d runs)", run_count);
		fprintf(stderr, ":\n\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if (no_aggr) {
		list_for_each_entry(counter, &evsel_list->entries, node)
			print_counter(counter);
	} else {
		list_for_each_entry(counter, &evsel_list->entries, node)
			print_counter_aggr(counter);
	}

	if (!csv_output) {
		if (!null_run)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			fprintf(output, "\n");
		fprintf(output, " %17.9f seconds time elapsed",
				avg_stats(&walltime_nsecs_stats)/1e9);
		if (run_count > 1) {
			fprintf(output, "                                        ");
			print_noise_pct(stddev_stats(&walltime_nsecs_stats),
					avg_stats(&walltime_nsecs_stats));
		}
		fprintf(output, "\n\n");
<<<<<<< HEAD
=======
=======
			fprintf(stderr, "\n");
		fprintf(stderr, " %17.9f seconds time elapsed",
				avg_stats(&walltime_nsecs_stats)/1e9);
		if (run_count > 1) {
			fprintf(stderr, "                                        ");
			print_noise_pct(stddev_stats(&walltime_nsecs_stats),
					avg_stats(&walltime_nsecs_stats));
		}
		fprintf(stderr, "\n\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
}

static volatile int signr = -1;

static void skip_signal(int signo)
{
	if(child_pid == -1)
		done = 1;

	signr = signo;
}

static void sig_atexit(void)
{
	if (child_pid != -1)
		kill(child_pid, SIGTERM);

	if (signr == -1)
		return;

	signal(signr, SIG_DFL);
	kill(getpid(), signr);
}

static const char * const stat_usage[] = {
	"perf stat [<options>] [<command>]",
	NULL
};

static int stat__set_big_num(const struct option *opt __used,
			     const char *s __used, int unset)
{
	big_num_opt = unset ? 0 : 1;
	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static bool append_file;

static const struct option options[] = {
	OPT_CALLBACK('e', "event", &evsel_list, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events_option),
<<<<<<< HEAD
=======
=======
static const struct option options[] = {
	OPT_CALLBACK('e', "event", &evsel_list, "event",
		     "event selector. use 'perf list' to list available events",
		     parse_events),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	OPT_CALLBACK(0, "filter", &evsel_list, "filter",
		     "event filter", parse_filter),
	OPT_BOOLEAN('i', "no-inherit", &no_inherit,
		    "child tasks do not inherit counters"),
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	OPT_STRING('p', "pid", &target_pid, "pid",
		   "stat events on existing process id"),
	OPT_STRING('t', "tid", &target_tid, "tid",
		   "stat events on existing thread id"),
	OPT_BOOLEAN('a', "all-cpus", &system_wide,
		    "system-wide collection from all CPUs"),
	OPT_BOOLEAN('g', "group", &group,
		    "put the counters into a counter group"),
<<<<<<< HEAD
=======
=======
	OPT_INTEGER('p', "pid", &target_pid,
		    "stat events on existing process id"),
	OPT_INTEGER('t', "tid", &target_tid,
		    "stat events on existing thread id"),
	OPT_BOOLEAN('a', "all-cpus", &system_wide,
		    "system-wide collection from all CPUs"),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	OPT_BOOLEAN('c', "scale", &scale,
		    "scale/normalize counters"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show counter open errors, etc)"),
	OPT_INTEGER('r', "repeat", &run_count,
		    "repeat command and print average + stddev (max: 100)"),
	OPT_BOOLEAN('n', "null", &null_run,
		    "null run - dont start any counters"),
	OPT_INCR('d', "detailed", &detailed_run,
		    "detailed run - start a lot of events"),
	OPT_BOOLEAN('S', "sync", &sync_run,
		    "call sync() before starting a run"),
	OPT_CALLBACK_NOOPT('B', "big-num", NULL, NULL, 
			   "print large numbers with thousands\' separators",
			   stat__set_big_num),
	OPT_STRING('C', "cpu", &cpu_list, "cpu",
		    "list of cpus to monitor in system-wide"),
	OPT_BOOLEAN('A', "no-aggr", &no_aggr,
		    "disable CPU count aggregation"),
	OPT_STRING('x', "field-separator", &csv_sep, "separator",
		   "print counts with custom separator"),
	OPT_CALLBACK('G', "cgroup", &evsel_list, "name",
		     "monitor event in cgroup name only",
		     parse_cgroups),
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	OPT_STRING('o', "output", &output_name, "file",
		    "output file name"),
	OPT_BOOLEAN(0, "append", &append_file, "append to the output file"),
	OPT_INTEGER(0, "log-fd", &output_fd,
		    "log output to fd, instead of stderr"),
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	OPT_END()
};

/*
 * Add default attributes, if there were no attributes specified or
 * if -d/--detailed, -d -d or -d -d -d is used:
 */
static int add_default_attributes(void)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	struct perf_evsel *pos;
	size_t attr_nr = 0;
	size_t c;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Set attrs if no event is selected and !null_run: */
	if (null_run)
		return 0;

	if (!evsel_list->nr_entries) {
<<<<<<< HEAD
		if (perf_evlist__add_attrs_array(evsel_list, default_attrs) < 0)
			return -1;
=======
<<<<<<< HEAD
		if (perf_evlist__add_attrs_array(evsel_list, default_attrs) < 0)
			return -1;
=======
		for (c = 0; c < ARRAY_SIZE(default_attrs); c++) {
			pos = perf_evsel__new(default_attrs + c, c + attr_nr);
			if (pos == NULL)
				return -1;
			perf_evlist__add(evsel_list, pos);
		}
		attr_nr += c;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	/* Detailed events get appended to the event list: */

	if (detailed_run <  1)
		return 0;

	/* Append detailed run extra attributes: */
<<<<<<< HEAD
	if (perf_evlist__add_attrs_array(evsel_list, detailed_attrs) < 0)
		return -1;
=======
<<<<<<< HEAD
	if (perf_evlist__add_attrs_array(evsel_list, detailed_attrs) < 0)
		return -1;
=======
	for (c = 0; c < ARRAY_SIZE(detailed_attrs); c++) {
		pos = perf_evsel__new(detailed_attrs + c, c + attr_nr);
		if (pos == NULL)
			return -1;
		perf_evlist__add(evsel_list, pos);
	}
	attr_nr += c;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (detailed_run < 2)
		return 0;

	/* Append very detailed run extra attributes: */
<<<<<<< HEAD
	if (perf_evlist__add_attrs_array(evsel_list, very_detailed_attrs) < 0)
		return -1;
=======
<<<<<<< HEAD
	if (perf_evlist__add_attrs_array(evsel_list, very_detailed_attrs) < 0)
		return -1;
=======
	for (c = 0; c < ARRAY_SIZE(very_detailed_attrs); c++) {
		pos = perf_evsel__new(very_detailed_attrs + c, c + attr_nr);
		if (pos == NULL)
			return -1;
		perf_evlist__add(evsel_list, pos);
	}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (detailed_run < 3)
		return 0;

	/* Append very, very detailed run extra attributes: */
<<<<<<< HEAD
	return perf_evlist__add_attrs_array(evsel_list, very_very_detailed_attrs);
=======
<<<<<<< HEAD
	return perf_evlist__add_attrs_array(evsel_list, very_very_detailed_attrs);
=======
	for (c = 0; c < ARRAY_SIZE(very_very_detailed_attrs); c++) {
		pos = perf_evsel__new(very_very_detailed_attrs + c, c + attr_nr);
		if (pos == NULL)
			return -1;
		perf_evlist__add(evsel_list, pos);
	}


	return 0;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

int cmd_stat(int argc, const char **argv, const char *prefix __used)
{
	struct perf_evsel *pos;
	int status = -ENOMEM;
<<<<<<< HEAD
	const char *mode;
=======
<<<<<<< HEAD
	const char *mode;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	setlocale(LC_ALL, "");

	evsel_list = perf_evlist__new(NULL, NULL);
	if (evsel_list == NULL)
		return -ENOMEM;

	argc = parse_options(argc, argv, options, stat_usage,
		PARSE_OPT_STOP_AT_NON_OPTION);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	output = stderr;
	if (output_name && strcmp(output_name, "-"))
		output = NULL;

	if (output_name && output_fd) {
		fprintf(stderr, "cannot use both --output and --log-fd\n");
		usage_with_options(stat_usage, options);
	}
	if (!output) {
		struct timespec tm;
		mode = append_file ? "a" : "w";

		output = fopen(output_name, mode);
		if (!output) {
			perror("failed to create output file");
			exit(-1);
		}
		clock_gettime(CLOCK_REALTIME, &tm);
		fprintf(output, "# started on %s\n", ctime(&tm.tv_sec));
	} else if (output_fd != 2) {
		mode = append_file ? "a" : "w";
		output = fdopen(output_fd, mode);
		if (!output) {
			perror("Failed opening logfd");
			return -errno;
		}
	}

	if (csv_sep) {
		csv_output = true;
		if (!strcmp(csv_sep, "\\t"))
			csv_sep = "\t";
	} else
<<<<<<< HEAD
=======
=======
	if (csv_sep)
		csv_output = true;
	else
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		csv_sep = DEFAULT_SEPARATOR;

	/*
	 * let the spreadsheet do the pretty-printing
	 */
	if (csv_output) {
<<<<<<< HEAD
		/* User explicitly passed -B? */
=======
<<<<<<< HEAD
		/* User explicitly passed -B? */
=======
		/* User explicitely passed -B? */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (big_num_opt == 1) {
			fprintf(stderr, "-B option not supported with -x\n");
			usage_with_options(stat_usage, options);
		} else /* Nope, so disable big number formatting */
			big_num = false;
	} else if (big_num_opt == 0) /* User passed --no-big-num */
		big_num = false;

<<<<<<< HEAD
	if (!argc && !target_pid && !target_tid)
=======
<<<<<<< HEAD
	if (!argc && !target_pid && !target_tid)
=======
	if (!argc && target_pid == -1 && target_tid == -1)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		usage_with_options(stat_usage, options);
	if (run_count <= 0)
		usage_with_options(stat_usage, options);

	/* no_aggr, cgroup are for system-wide only */
	if ((no_aggr || nr_cgroups) && !system_wide) {
		fprintf(stderr, "both cgroup and no-aggregation "
			"modes only available in system-wide mode\n");

		usage_with_options(stat_usage, options);
	}

	if (add_default_attributes())
		goto out;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (target_pid)
		target_tid = target_pid;

	evsel_list->threads = thread_map__new_str(target_pid,
						  target_tid, UINT_MAX);
<<<<<<< HEAD
=======
=======
	if (target_pid != -1)
		target_tid = target_pid;

	evsel_list->threads = thread_map__new(target_pid, target_tid);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (evsel_list->threads == NULL) {
		pr_err("Problems finding threads of monitor\n");
		usage_with_options(stat_usage, options);
	}

	if (system_wide)
		evsel_list->cpus = cpu_map__new(cpu_list);
	else
		evsel_list->cpus = cpu_map__dummy_new();

	if (evsel_list->cpus == NULL) {
		perror("failed to parse CPUs map");
		usage_with_options(stat_usage, options);
		return -1;
	}

	list_for_each_entry(pos, &evsel_list->entries, node) {
		if (perf_evsel__alloc_stat_priv(pos) < 0 ||
<<<<<<< HEAD
		    perf_evsel__alloc_counts(pos, evsel_list->cpus->nr) < 0)
=======
<<<<<<< HEAD
		    perf_evsel__alloc_counts(pos, evsel_list->cpus->nr) < 0)
=======
		    perf_evsel__alloc_counts(pos, evsel_list->cpus->nr) < 0 ||
		    perf_evsel__alloc_fd(pos, evsel_list->cpus->nr, evsel_list->threads->nr) < 0)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			goto out_free_fd;
	}

	/*
	 * We dont want to block the signals - that would cause
	 * child tasks to inherit that and Ctrl-C would not work.
	 * What we want is for Ctrl-C to work in the exec()-ed
	 * task, but being ignored by perf stat itself:
	 */
	atexit(sig_atexit);
	signal(SIGINT,  skip_signal);
	signal(SIGALRM, skip_signal);
	signal(SIGABRT, skip_signal);

	status = 0;
	for (run_idx = 0; run_idx < run_count; run_idx++) {
		if (run_count != 1 && verbose)
<<<<<<< HEAD
			fprintf(output, "[ perf stat: executing run #%d ... ]\n",
				run_idx + 1);
=======
<<<<<<< HEAD
			fprintf(output, "[ perf stat: executing run #%d ... ]\n",
				run_idx + 1);
=======
			fprintf(stderr, "[ perf stat: executing run #%d ... ]\n", run_idx + 1);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (sync_run)
			sync();

		status = run_perf_stat(argc, argv);
	}

	if (status != -1)
		print_stat(argc, argv);
out_free_fd:
	list_for_each_entry(pos, &evsel_list->entries, node)
		perf_evsel__free_stat_priv(pos);
	perf_evlist__delete_maps(evsel_list);
out:
	perf_evlist__delete(evsel_list);
	return status;
}
