#ifndef __PERF_CPUMAP_H
#define __PERF_CPUMAP_H

<<<<<<< HEAD
#include <stdio.h>

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
struct cpu_map {
	int nr;
	int map[];
};

struct cpu_map *cpu_map__new(const char *cpu_list);
struct cpu_map *cpu_map__dummy_new(void);
void cpu_map__delete(struct cpu_map *map);

<<<<<<< HEAD
size_t cpu_map__fprintf(struct cpu_map *map, FILE *fp);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /* __PERF_CPUMAP_H */
