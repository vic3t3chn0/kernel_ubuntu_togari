#ifndef BENCH_H
#define BENCH_H

extern int bench_sched_messaging(int argc, const char **argv, const char *prefix);
extern int bench_sched_pipe(int argc, const char **argv, const char *prefix);
extern int bench_mem_memcpy(int argc, const char **argv, const char *prefix __used);
<<<<<<< HEAD
extern int bench_mem_memset(int argc, const char **argv, const char *prefix);
=======
<<<<<<< HEAD
extern int bench_mem_memset(int argc, const char **argv, const char *prefix);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define BENCH_FORMAT_DEFAULT_STR	"default"
#define BENCH_FORMAT_DEFAULT		0
#define BENCH_FORMAT_SIMPLE_STR		"simple"
#define BENCH_FORMAT_SIMPLE		1

#define BENCH_FORMAT_UNKNOWN		-1

extern int bench_format;

#endif
