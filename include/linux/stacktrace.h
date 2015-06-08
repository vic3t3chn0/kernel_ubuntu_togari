#ifndef __LINUX_STACKTRACE_H
#define __LINUX_STACKTRACE_H

struct task_struct;
struct pt_regs;

#ifdef CONFIG_STACKTRACE
struct task_struct;

struct stack_trace {
	unsigned int nr_entries, max_entries;
	unsigned long *entries;
	int skip;	/* input argument: How many entries to skip */
};

extern void save_stack_trace(struct stack_trace *trace);
<<<<<<< HEAD
extern void save_stack_trace_regs(struct pt_regs *regs,
				  struct stack_trace *trace);
=======
<<<<<<< HEAD
extern void save_stack_trace_regs(struct pt_regs *regs,
				  struct stack_trace *trace);
=======
extern void save_stack_trace_regs(struct stack_trace *trace,
				  struct pt_regs *regs);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern void save_stack_trace_tsk(struct task_struct *tsk,
				struct stack_trace *trace);

extern void print_stack_trace(struct stack_trace *trace, int spaces);

#ifdef CONFIG_USER_STACKTRACE_SUPPORT
extern void save_stack_trace_user(struct stack_trace *trace);
#else
# define save_stack_trace_user(trace)              do { } while (0)
#endif

#else
# define save_stack_trace(trace)			do { } while (0)
# define save_stack_trace_tsk(tsk, trace)		do { } while (0)
# define save_stack_trace_user(trace)			do { } while (0)
# define print_stack_trace(trace, spaces)		do { } while (0)
#endif

#endif
