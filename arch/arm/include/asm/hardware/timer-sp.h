<<<<<<< HEAD
void __sp804_clocksource_and_sched_clock_init(void __iomem *,
					      const char *, int);

static inline void sp804_clocksource_init(void __iomem *base, const char *name)
{
	__sp804_clocksource_and_sched_clock_init(base, name, 0);
}

static inline void sp804_clocksource_and_sched_clock_init(void __iomem *base,
							  const char *name)
{
	__sp804_clocksource_and_sched_clock_init(base, name, 1);
}

=======
void sp804_clocksource_init(void __iomem *, const char *);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
void sp804_clockevents_init(void __iomem *, unsigned int, const char *);
