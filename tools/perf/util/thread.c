#include "../perf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "session.h"
#include "thread.h"
#include "util.h"
#include "debug.h"

static struct thread *thread__new(pid_t pid)
{
	struct thread *self = zalloc(sizeof(*self));

	if (self != NULL) {
		map_groups__init(&self->mg);
		self->pid = pid;
		self->comm = malloc(32);
		if (self->comm)
			snprintf(self->comm, 32, ":%d", self->pid);
	}

	return self;
}

void thread__delete(struct thread *self)
{
	map_groups__exit(&self->mg);
	free(self->comm);
	free(self);
}

int thread__set_comm(struct thread *self, const char *comm)
{
	int err;

	if (self->comm)
		free(self->comm);
	self->comm = strdup(comm);
	err = self->comm == NULL ? -ENOMEM : 0;
	if (!err) {
		self->comm_set = true;
		map_groups__flush(&self->mg);
	}
	return err;
}

int thread__comm_len(struct thread *self)
{
	if (!self->comm_len) {
		if (!self->comm)
			return 0;
		self->comm_len = strlen(self->comm);
	}

	return self->comm_len;
}

static size_t thread__fprintf(struct thread *self, FILE *fp)
{
	return fprintf(fp, "Thread %d %s\n", self->pid, self->comm) +
	       map_groups__fprintf(&self->mg, verbose, fp);
}

<<<<<<< HEAD
struct thread *machine__findnew_thread(struct machine *self, pid_t pid)
=======
<<<<<<< HEAD
struct thread *machine__findnew_thread(struct machine *self, pid_t pid)
=======
struct thread *perf_session__findnew(struct perf_session *self, pid_t pid)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct rb_node **p = &self->threads.rb_node;
	struct rb_node *parent = NULL;
	struct thread *th;

	/*
	 * Font-end cache - PID lookups come in blocks,
	 * so most of the time we dont have to look up
	 * the full rbtree:
	 */
	if (self->last_match && self->last_match->pid == pid)
		return self->last_match;

	while (*p != NULL) {
		parent = *p;
		th = rb_entry(parent, struct thread, rb_node);

		if (th->pid == pid) {
			self->last_match = th;
			return th;
		}

		if (pid < th->pid)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}

	th = thread__new(pid);
	if (th != NULL) {
		rb_link_node(&th->rb_node, parent, p);
		rb_insert_color(&th->rb_node, &self->threads);
		self->last_match = th;
	}

	return th;
}

void thread__insert_map(struct thread *self, struct map *map)
{
	map_groups__fixup_overlappings(&self->mg, map, verbose, stderr);
	map_groups__insert(&self->mg, map);
}

int thread__fork(struct thread *self, struct thread *parent)
{
	int i;

	if (parent->comm_set) {
		if (self->comm)
			free(self->comm);
		self->comm = strdup(parent->comm);
		if (!self->comm)
			return -ENOMEM;
		self->comm_set = true;
	}

	for (i = 0; i < MAP__NR_TYPES; ++i)
		if (map_groups__clone(&self->mg, &parent->mg, i) < 0)
			return -ENOMEM;
	return 0;
}

<<<<<<< HEAD
size_t machine__fprintf(struct machine *machine, FILE *fp)
=======
<<<<<<< HEAD
size_t machine__fprintf(struct machine *machine, FILE *fp)
=======
size_t perf_session__fprintf(struct perf_session *self, FILE *fp)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	size_t ret = 0;
	struct rb_node *nd;

<<<<<<< HEAD
	for (nd = rb_first(&machine->threads); nd; nd = rb_next(nd)) {
=======
<<<<<<< HEAD
	for (nd = rb_first(&machine->threads); nd; nd = rb_next(nd)) {
=======
	for (nd = rb_first(&self->threads); nd; nd = rb_next(nd)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		struct thread *pos = rb_entry(nd, struct thread, rb_node);

		ret += thread__fprintf(pos, fp);
	}

	return ret;
}
