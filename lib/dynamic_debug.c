/*
 * lib/dynamic_debug.c
 *
 * make pr_debug()/dev_dbg() calls runtime configurable based upon their
 * source module.
 *
 * Copyright (C) 2008 Jason Baron <jbaron@redhat.com>
 * By Greg Banks <gnb@melbourne.sgi.com>
 * Copyright (c) 2008 Silicon Graphics Inc.  All Rights Reserved.
 * Copyright (C) 2011 Bart Van Assche.  All Rights Reserved.
 */

<<<<<<< HEAD
#define pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

=======
<<<<<<< HEAD
#define pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kallsyms.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <linux/version.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/list.h>
#include <linux/sysctl.h>
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/dynamic_debug.h>
#include <linux/debugfs.h>
#include <linux/slab.h>
#include <linux/jump_label.h>
#include <linux/hardirq.h>
#include <linux/sched.h>
<<<<<<< HEAD
#include <linux/device.h>
#include <linux/netdevice.h>
=======
<<<<<<< HEAD
#include <linux/device.h>
#include <linux/netdevice.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

extern struct _ddebug __start___verbose[];
extern struct _ddebug __stop___verbose[];

struct ddebug_table {
	struct list_head link;
	char *mod_name;
	unsigned int num_ddebugs;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	unsigned int num_enabled;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct _ddebug *ddebugs;
};

struct ddebug_query {
	const char *filename;
	const char *module;
	const char *function;
	const char *format;
	unsigned int first_lineno, last_lineno;
};

struct ddebug_iter {
	struct ddebug_table *table;
	unsigned int idx;
};

static DEFINE_MUTEX(ddebug_lock);
static LIST_HEAD(ddebug_tables);
static int verbose = 0;
<<<<<<< HEAD
module_param(verbose, int, 0644);
=======
<<<<<<< HEAD
module_param(verbose, int, 0644);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* Return the last part of a pathname */
static inline const char *basename(const char *path)
{
	const char *tail = strrchr(path, '/');
	return tail ? tail+1 : path;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* Return the path relative to source root */
static inline const char *trim_prefix(const char *path)
{
	int skip = strlen(__FILE__) - strlen("lib/dynamic_debug.c");

	if (strncmp(path, __FILE__, skip))
		skip = 0; /* prefix mismatch, don't skip */

	return path + skip;
}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct { unsigned flag:8; char opt_char; } opt_array[] = {
	{ _DPRINTK_FLAGS_PRINT, 'p' },
	{ _DPRINTK_FLAGS_INCL_MODNAME, 'm' },
	{ _DPRINTK_FLAGS_INCL_FUNCNAME, 'f' },
	{ _DPRINTK_FLAGS_INCL_LINENO, 'l' },
	{ _DPRINTK_FLAGS_INCL_TID, 't' },
<<<<<<< HEAD
	{ _DPRINTK_FLAGS_NONE, '_' },
=======
<<<<<<< HEAD
	{ _DPRINTK_FLAGS_NONE, '_' },
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/* format a string into buf[] which describes the _ddebug's flags */
static char *ddebug_describe_flags(struct _ddebug *dp, char *buf,
				    size_t maxlen)
{
	char *p = buf;
	int i;

<<<<<<< HEAD
	BUG_ON(maxlen < 6);
=======
<<<<<<< HEAD
	BUG_ON(maxlen < 6);
=======
	BUG_ON(maxlen < 4);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for (i = 0; i < ARRAY_SIZE(opt_array); ++i)
		if (dp->flags & opt_array[i].flag)
			*p++ = opt_array[i].opt_char;
	if (p == buf)
<<<<<<< HEAD
		*p++ = '_';
=======
<<<<<<< HEAD
		*p++ = '_';
=======
		*p++ = '-';
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	*p = '\0';

	return buf;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define vpr_info_dq(q, msg)						\
do {									\
	if (verbose)							\
		/* trim last char off format print */			\
		pr_info("%s: func=\"%s\" file=\"%s\" "			\
			"module=\"%s\" format=\"%.*s\" "		\
			"lineno=%u-%u",					\
			msg,						\
			q->function ? q->function : "",			\
			q->filename ? q->filename : "",			\
			q->module ? q->module : "",			\
			(int)(q->format ? strlen(q->format) - 1 : 0),	\
			q->format ? q->format : "",			\
			q->first_lineno, q->last_lineno);		\
} while (0)

/*
 * Search the tables for _ddebug's which match the given `query' and
 * apply the `flags' and `mask' to them.  Returns number of matching
 * callsites, normally the same as number of changes.  If verbose,
 * logs the changes.  Takes ddebug_lock.
 */
static int ddebug_change(const struct ddebug_query *query,
			unsigned int flags, unsigned int mask)
<<<<<<< HEAD
=======
=======
/*
 * Search the tables for _ddebug's which match the given
 * `query' and apply the `flags' and `mask' to them.  Tells
 * the user which ddebug's were changed, or whether none
 * were matched.
 */
static void ddebug_change(const struct ddebug_query *query,
			   unsigned int flags, unsigned int mask)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int i;
	struct ddebug_table *dt;
	unsigned int newflags;
	unsigned int nfound = 0;
<<<<<<< HEAD
	char flagbuf[10];
=======
<<<<<<< HEAD
	char flagbuf[10];
=======
	char flagbuf[8];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* search for matching ddebugs */
	mutex_lock(&ddebug_lock);
	list_for_each_entry(dt, &ddebug_tables, link) {

		/* match against the module name */
<<<<<<< HEAD
		if (query->module && strcmp(query->module, dt->mod_name))
=======
<<<<<<< HEAD
		if (query->module && strcmp(query->module, dt->mod_name))
=======
		if (query->module != NULL &&
		    strcmp(query->module, dt->mod_name))
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			continue;

		for (i = 0 ; i < dt->num_ddebugs ; i++) {
			struct _ddebug *dp = &dt->ddebugs[i];

			/* match against the source filename */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (query->filename &&
			    strcmp(query->filename, dp->filename) &&
			    strcmp(query->filename, basename(dp->filename)) &&
			    strcmp(query->filename, trim_prefix(dp->filename)))
				continue;

			/* match against the function */
			if (query->function &&
<<<<<<< HEAD
=======
=======
			if (query->filename != NULL &&
			    strcmp(query->filename, dp->filename) &&
			    strcmp(query->filename, basename(dp->filename)))
				continue;

			/* match against the function */
			if (query->function != NULL &&
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    strcmp(query->function, dp->function))
				continue;

			/* match against the format */
<<<<<<< HEAD
			if (query->format &&
			    !strstr(dp->format, query->format))
=======
<<<<<<< HEAD
			if (query->format &&
			    !strstr(dp->format, query->format))
=======
			if (query->format != NULL &&
			    strstr(dp->format, query->format) == NULL)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				continue;

			/* match against the line number range */
			if (query->first_lineno &&
			    dp->lineno < query->first_lineno)
				continue;
			if (query->last_lineno &&
			    dp->lineno > query->last_lineno)
				continue;

			nfound++;

			newflags = (dp->flags & mask) | flags;
			if (newflags == dp->flags)
				continue;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			dp->flags = newflags;
			if (verbose)
				pr_info("changed %s:%d [%s]%s =%s\n",
					trim_prefix(dp->filename), dp->lineno,
<<<<<<< HEAD
=======
=======

			if (!newflags)
				dt->num_enabled--;
			else if (!dp->flags)
				dt->num_enabled++;
			dp->flags = newflags;
			if (newflags)
				dp->enabled = 1;
			else
				dp->enabled = 0;
			if (verbose)
				printk(KERN_INFO
					"ddebug: changed %s:%d [%s]%s %s\n",
					dp->filename, dp->lineno,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					dt->mod_name, dp->function,
					ddebug_describe_flags(dp, flagbuf,
							sizeof(flagbuf)));
		}
	}
	mutex_unlock(&ddebug_lock);

	if (!nfound && verbose)
<<<<<<< HEAD
		pr_info("no matches for query\n");

	return nfound;
=======
<<<<<<< HEAD
		pr_info("no matches for query\n");

	return nfound;
=======
		printk(KERN_INFO "ddebug: no matches for query\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/*
 * Split the buffer `buf' into space-separated words.
 * Handles simple " and ' quoting, i.e. without nested,
 * embedded or escaped \".  Return the number of words
 * or <0 on error.
 */
static int ddebug_tokenize(char *buf, char *words[], int maxwords)
{
	int nwords = 0;

	while (*buf) {
		char *end;

		/* Skip leading whitespace */
		buf = skip_spaces(buf);
		if (!*buf)
			break;	/* oh, it was trailing whitespace */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (*buf == '#')
			break;	/* token starts comment, skip rest of line */

		/* find `end' of word, whitespace separated or quoted */
<<<<<<< HEAD
=======
=======

		/* Run `end' over a word, either whitespace separated or quoted */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (*buf == '"' || *buf == '\'') {
			int quote = *buf++;
			for (end = buf ; *end && *end != quote ; end++)
				;
			if (!*end)
				return -EINVAL;	/* unclosed quote */
		} else {
			for (end = buf ; *end && !isspace(*end) ; end++)
				;
			BUG_ON(end == buf);
		}
<<<<<<< HEAD

		/* `buf' is start of word, `end' is one past its end */
=======
<<<<<<< HEAD

		/* `buf' is start of word, `end' is one past its end */
=======
		/* Here `buf' is the start of the word, `end' is one past the end */

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (nwords == maxwords)
			return -EINVAL;	/* ran out of words[] before bytes */
		if (*end)
			*end++ = '\0';	/* terminate the word */
		words[nwords++] = buf;
		buf = end;
	}

	if (verbose) {
		int i;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		pr_info("split into words:");
		for (i = 0 ; i < nwords ; i++)
			pr_cont(" \"%s\"", words[i]);
		pr_cont("\n");
<<<<<<< HEAD
=======
=======
		printk(KERN_INFO "%s: split into words:", __func__);
		for (i = 0 ; i < nwords ; i++)
			printk(" \"%s\"", words[i]);
		printk("\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return nwords;
}

/*
 * Parse a single line number.  Note that the empty string ""
 * is treated as a special case and converted to zero, which
 * is later treated as a "don't care" value.
 */
static inline int parse_lineno(const char *str, unsigned int *val)
{
	char *end = NULL;
	BUG_ON(str == NULL);
	if (*str == '\0') {
		*val = 0;
		return 0;
	}
	*val = simple_strtoul(str, &end, 10);
	return end == NULL || end == str || *end != '\0' ? -EINVAL : 0;
}

/*
 * Undo octal escaping in a string, inplace.  This is useful to
 * allow the user to express a query which matches a format
 * containing embedded spaces.
 */
#define isodigit(c)		((c) >= '0' && (c) <= '7')
static char *unescape(char *str)
{
	char *in = str;
	char *out = str;

	while (*in) {
		if (*in == '\\') {
			if (in[1] == '\\') {
				*out++ = '\\';
				in += 2;
				continue;
			} else if (in[1] == 't') {
				*out++ = '\t';
				in += 2;
				continue;
			} else if (in[1] == 'n') {
				*out++ = '\n';
				in += 2;
				continue;
			} else if (isodigit(in[1]) &&
			         isodigit(in[2]) &&
			         isodigit(in[3])) {
				*out++ = ((in[1] - '0')<<6) |
				          ((in[2] - '0')<<3) |
				          (in[3] - '0');
				in += 4;
				continue;
			}
		}
		*out++ = *in++;
	}
	*out = '\0';

	return str;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int check_set(const char **dest, char *src, char *name)
{
	int rc = 0;

	if (*dest) {
		rc = -EINVAL;
		pr_err("match-spec:%s val:%s overridden by %s",
			name, *dest, src);
	}
	*dest = src;
	return rc;
}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Parse words[] as a ddebug query specification, which is a series
 * of (keyword, value) pairs chosen from these possibilities:
 *
 * func <function-name>
 * file <full-pathname>
 * file <base-filename>
 * module <module-name>
 * format <escaped-string-to-find-in-format>
 * line <lineno>
 * line <first-lineno>-<last-lineno> // where either may be empty
<<<<<<< HEAD
 *
 * Only 1 of each type is allowed.
 * Returns 0 on success, <0 on error.
=======
<<<<<<< HEAD
 *
 * Only 1 of each type is allowed.
 * Returns 0 on success, <0 on error.
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int ddebug_parse_query(char *words[], int nwords,
			       struct ddebug_query *query)
{
	unsigned int i;
<<<<<<< HEAD
	int rc;
=======
<<<<<<< HEAD
	int rc;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* check we have an even number of words */
	if (nwords % 2 != 0)
		return -EINVAL;
	memset(query, 0, sizeof(*query));

	for (i = 0 ; i < nwords ; i += 2) {
		if (!strcmp(words[i], "func"))
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			rc = check_set(&query->function, words[i+1], "func");
		else if (!strcmp(words[i], "file"))
			rc = check_set(&query->filename, words[i+1], "file");
		else if (!strcmp(words[i], "module"))
			rc = check_set(&query->module, words[i+1], "module");
		else if (!strcmp(words[i], "format"))
			rc = check_set(&query->format, unescape(words[i+1]),
				"format");
		else if (!strcmp(words[i], "line")) {
			char *first = words[i+1];
			char *last = strchr(first, '-');
			if (query->first_lineno || query->last_lineno) {
				pr_err("match-spec:line given 2 times\n");
				return -EINVAL;
			}
<<<<<<< HEAD
=======
=======
			query->function = words[i+1];
		else if (!strcmp(words[i], "file"))
			query->filename = words[i+1];
		else if (!strcmp(words[i], "module"))
			query->module = words[i+1];
		else if (!strcmp(words[i], "format"))
			query->format = unescape(words[i+1]);
		else if (!strcmp(words[i], "line")) {
			char *first = words[i+1];
			char *last = strchr(first, '-');
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (last)
				*last++ = '\0';
			if (parse_lineno(first, &query->first_lineno) < 0)
				return -EINVAL;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (last) {
				/* range <first>-<last> */
				if (parse_lineno(last, &query->last_lineno)
				    < query->first_lineno) {
					pr_err("last-line < 1st-line\n");
					return -EINVAL;
				}
<<<<<<< HEAD
=======
=======
			if (last != NULL) {
				/* range <first>-<last> */
				if (parse_lineno(last, &query->last_lineno) < 0)
					return -EINVAL;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			} else {
				query->last_lineno = query->first_lineno;
			}
		} else {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			pr_err("unknown keyword \"%s\"\n", words[i]);
			return -EINVAL;
		}
		if (rc)
			return rc;
	}
	vpr_info_dq(query, "parsed");
<<<<<<< HEAD
=======
=======
			if (verbose)
				printk(KERN_ERR "%s: unknown keyword \"%s\"\n",
					__func__, words[i]);
			return -EINVAL;
		}
	}

	if (verbose)
		printk(KERN_INFO "%s: q->function=\"%s\" q->filename=\"%s\" "
		       "q->module=\"%s\" q->format=\"%s\" q->lineno=%u-%u\n",
			__func__, query->function, query->filename,
			query->module, query->format, query->first_lineno,
			query->last_lineno);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

/*
 * Parse `str' as a flags specification, format [-+=][p]+.
 * Sets up *maskp and *flagsp to be used when changing the
 * flags fields of matched _ddebug's.  Returns 0 on success
 * or <0 on error.
 */
static int ddebug_parse_flags(const char *str, unsigned int *flagsp,
			       unsigned int *maskp)
{
	unsigned flags = 0;
	int op = '=', i;

	switch (*str) {
	case '+':
	case '-':
	case '=':
		op = *str++;
		break;
	default:
		return -EINVAL;
	}
	if (verbose)
<<<<<<< HEAD
		pr_info("op='%c'\n", op);
=======
<<<<<<< HEAD
		pr_info("op='%c'\n", op);
=======
		printk(KERN_INFO "%s: op='%c'\n", __func__, op);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	for ( ; *str ; ++str) {
		for (i = ARRAY_SIZE(opt_array) - 1; i >= 0; i--) {
			if (*str == opt_array[i].opt_char) {
				flags |= opt_array[i].flag;
				break;
			}
		}
		if (i < 0)
			return -EINVAL;
	}
<<<<<<< HEAD
	if (verbose)
		pr_info("flags=0x%x\n", flags);
=======
<<<<<<< HEAD
	if (verbose)
		pr_info("flags=0x%x\n", flags);
=======
	if (flags == 0)
		return -EINVAL;
	if (verbose)
		printk(KERN_INFO "%s: flags=0x%x\n", __func__, flags);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* calculate final *flagsp, *maskp according to mask and op */
	switch (op) {
	case '=':
		*maskp = 0;
		*flagsp = flags;
		break;
	case '+':
		*maskp = ~0U;
		*flagsp = flags;
		break;
	case '-':
		*maskp = ~flags;
		*flagsp = 0;
		break;
	}
	if (verbose)
<<<<<<< HEAD
		pr_info("*flagsp=0x%x *maskp=0x%x\n", *flagsp, *maskp);
=======
<<<<<<< HEAD
		pr_info("*flagsp=0x%x *maskp=0x%x\n", *flagsp, *maskp);
=======
		printk(KERN_INFO "%s: *flagsp=0x%x *maskp=0x%x\n",
			__func__, *flagsp, *maskp);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static int ddebug_exec_query(char *query_string)
{
	unsigned int flags = 0, mask = 0;
	struct ddebug_query query;
#define MAXWORDS 9
<<<<<<< HEAD
	int nwords, nfound;
=======
<<<<<<< HEAD
	int nwords, nfound;
=======
	int nwords;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	char *words[MAXWORDS];

	nwords = ddebug_tokenize(query_string, words, MAXWORDS);
	if (nwords <= 0)
		return -EINVAL;
	if (ddebug_parse_query(words, nwords-1, &query))
		return -EINVAL;
	if (ddebug_parse_flags(words[nwords-1], &flags, &mask))
		return -EINVAL;

	/* actually go and implement the change */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	nfound = ddebug_change(&query, flags, mask);
	vpr_info_dq((&query), (nfound) ? "applied" : "no-match");

	return nfound;
}

/* handle multiple queries in query string, continue on error, return
   last error or number of matching callsites.  Module name is either
   in param (for boot arg) or perhaps in query string.
*/
static int ddebug_exec_queries(char *query)
{
	char *split;
	int i, errs = 0, exitcode = 0, rc, nfound = 0;

	for (i = 0; query; query = split) {
		split = strpbrk(query, ";\n");
		if (split)
			*split++ = '\0';

		query = skip_spaces(query);
		if (!query || !*query || *query == '#')
			continue;

		if (verbose)
			pr_info("query %d: \"%s\"\n", i, query);

		rc = ddebug_exec_query(query);
		if (rc < 0) {
			errs++;
			exitcode = rc;
		} else
			nfound += rc;
		i++;
	}
	pr_info("processed %d queries, with %d matches, %d errs\n",
		 i, nfound, errs);

	if (exitcode)
		return exitcode;
	return nfound;
}

#define PREFIX_SIZE 64

static int remaining(int wrote)
{
	if (PREFIX_SIZE - wrote > 0)
		return PREFIX_SIZE - wrote;
	return 0;
}

static char *dynamic_emit_prefix(const struct _ddebug *desc, char *buf)
{
	int pos_after_tid;
	int pos = 0;

	pos += snprintf(buf + pos, remaining(pos), "%s", KERN_DEBUG);
	if (desc->flags & _DPRINTK_FLAGS_INCL_TID) {
		if (in_interrupt())
			pos += snprintf(buf + pos, remaining(pos), "%s ",
						"<intr>");
		else
			pos += snprintf(buf + pos, remaining(pos), "[%d] ",
						task_pid_vnr(current));
	}
	pos_after_tid = pos;
	if (desc->flags & _DPRINTK_FLAGS_INCL_MODNAME)
		pos += snprintf(buf + pos, remaining(pos), "%s:",
					desc->modname);
	if (desc->flags & _DPRINTK_FLAGS_INCL_FUNCNAME)
		pos += snprintf(buf + pos, remaining(pos), "%s:",
					desc->function);
	if (desc->flags & _DPRINTK_FLAGS_INCL_LINENO)
		pos += snprintf(buf + pos, remaining(pos), "%d:",
					desc->lineno);
	if (pos - pos_after_tid)
		pos += snprintf(buf + pos, remaining(pos), " ");
	if (pos >= PREFIX_SIZE)
		buf[PREFIX_SIZE - 1] = '\0';

	return buf;
}

<<<<<<< HEAD
=======
=======
	ddebug_change(&query, flags, mask);
	return 0;
}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int __dynamic_pr_debug(struct _ddebug *descriptor, const char *fmt, ...)
{
	va_list args;
	int res;
<<<<<<< HEAD
	struct va_format vaf;
	char buf[PREFIX_SIZE];
=======
<<<<<<< HEAD
	struct va_format vaf;
	char buf[PREFIX_SIZE];
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	va_start(args, fmt);
<<<<<<< HEAD
	vaf.fmt = fmt;
	vaf.va = &args;
	res = printk("%s%pV", dynamic_emit_prefix(descriptor, buf), &vaf);
=======
<<<<<<< HEAD
	vaf.fmt = fmt;
	vaf.va = &args;
	res = printk("%s%pV", dynamic_emit_prefix(descriptor, buf), &vaf);
=======
	res = printk(KERN_DEBUG);
	if (descriptor->flags & _DPRINTK_FLAGS_INCL_TID) {
		if (in_interrupt())
			res += printk(KERN_CONT "<intr> ");
		else
			res += printk(KERN_CONT "[%d] ", task_pid_vnr(current));
	}
	if (descriptor->flags & _DPRINTK_FLAGS_INCL_MODNAME)
		res += printk(KERN_CONT "%s:", descriptor->modname);
	if (descriptor->flags & _DPRINTK_FLAGS_INCL_FUNCNAME)
		res += printk(KERN_CONT "%s:", descriptor->function);
	if (descriptor->flags & _DPRINTK_FLAGS_INCL_LINENO)
		res += printk(KERN_CONT "%d ", descriptor->lineno);
	res += vprintk(fmt, args);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	va_end(args);

	return res;
}
EXPORT_SYMBOL(__dynamic_pr_debug);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int __dynamic_dev_dbg(struct _ddebug *descriptor,
		      const struct device *dev, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;
	int res;
	char buf[PREFIX_SIZE];

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	va_start(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	res = __dev_printk(dynamic_emit_prefix(descriptor, buf), dev, &vaf);
	va_end(args);

	return res;
}
EXPORT_SYMBOL(__dynamic_dev_dbg);

#ifdef CONFIG_NET

int __dynamic_netdev_dbg(struct _ddebug *descriptor,
		      const struct net_device *dev, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;
	int res;
	char buf[PREFIX_SIZE];

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	va_start(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	res = __netdev_printk(dynamic_emit_prefix(descriptor, buf), dev, &vaf);
	va_end(args);

	return res;
}
EXPORT_SYMBOL(__dynamic_netdev_dbg);

#endif

#define DDEBUG_STRING_SIZE 1024
static __initdata char ddebug_setup_string[DDEBUG_STRING_SIZE];

static __init int ddebug_setup_query(char *str)
{
	if (strlen(str) >= DDEBUG_STRING_SIZE) {
		pr_warn("ddebug boot param string too large\n");
		return 0;
	}
	strlcpy(ddebug_setup_string, str, DDEBUG_STRING_SIZE);
<<<<<<< HEAD
=======
=======
static __initdata char ddebug_setup_string[1024];
static __init int ddebug_setup_query(char *str)
{
	if (strlen(str) >= 1024) {
		pr_warning("ddebug boot param string too large\n");
		return 0;
	}
	strcpy(ddebug_setup_string, str);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 1;
}

__setup("ddebug_query=", ddebug_setup_query);

/*
 * File_ops->write method for <debugfs>/dynamic_debug/conrol.  Gathers the
 * command text from userspace, parses and executes it.
 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define USER_BUF_PAGE 4096
static ssize_t ddebug_proc_write(struct file *file, const char __user *ubuf,
				  size_t len, loff_t *offp)
{
	char *tmpbuf;
<<<<<<< HEAD
=======
=======
static ssize_t ddebug_proc_write(struct file *file, const char __user *ubuf,
				  size_t len, loff_t *offp)
{
	char tmpbuf[256];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	if (len == 0)
		return 0;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (len > USER_BUF_PAGE - 1) {
		pr_warn("expected <%d bytes into control\n", USER_BUF_PAGE);
		return -E2BIG;
	}
	tmpbuf = kmalloc(len + 1, GFP_KERNEL);
	if (!tmpbuf)
		return -ENOMEM;
	if (copy_from_user(tmpbuf, ubuf, len)) {
		kfree(tmpbuf);
		return -EFAULT;
	}
	tmpbuf[len] = '\0';
	if (verbose)
		pr_info("read %d bytes from userspace\n", (int)len);

	ret = ddebug_exec_queries(tmpbuf);
	kfree(tmpbuf);
	if (ret < 0)
<<<<<<< HEAD
=======
=======
	/* we don't check *offp -- multiple writes() are allowed */
	if (len > sizeof(tmpbuf)-1)
		return -E2BIG;
	if (copy_from_user(tmpbuf, ubuf, len))
		return -EFAULT;
	tmpbuf[len] = '\0';
	if (verbose)
		printk(KERN_INFO "%s: read %d bytes from userspace\n",
			__func__, (int)len);

	ret = ddebug_exec_query(tmpbuf);
	if (ret)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ret;

	*offp += len;
	return len;
}

/*
 * Set the iterator to point to the first _ddebug object
 * and return a pointer to that first object.  Returns
 * NULL if there are no _ddebugs at all.
 */
static struct _ddebug *ddebug_iter_first(struct ddebug_iter *iter)
{
	if (list_empty(&ddebug_tables)) {
		iter->table = NULL;
		iter->idx = 0;
		return NULL;
	}
	iter->table = list_entry(ddebug_tables.next,
				 struct ddebug_table, link);
	iter->idx = 0;
	return &iter->table->ddebugs[iter->idx];
}

/*
 * Advance the iterator to point to the next _ddebug
 * object from the one the iterator currently points at,
 * and returns a pointer to the new _ddebug.  Returns
 * NULL if the iterator has seen all the _ddebugs.
 */
static struct _ddebug *ddebug_iter_next(struct ddebug_iter *iter)
{
	if (iter->table == NULL)
		return NULL;
	if (++iter->idx == iter->table->num_ddebugs) {
		/* iterate to next table */
		iter->idx = 0;
		if (list_is_last(&iter->table->link, &ddebug_tables)) {
			iter->table = NULL;
			return NULL;
		}
		iter->table = list_entry(iter->table->link.next,
					 struct ddebug_table, link);
	}
	return &iter->table->ddebugs[iter->idx];
}

/*
 * Seq_ops start method.  Called at the start of every
 * read() call from userspace.  Takes the ddebug_lock and
 * seeks the seq_file's iterator to the given position.
 */
static void *ddebug_proc_start(struct seq_file *m, loff_t *pos)
{
	struct ddebug_iter *iter = m->private;
	struct _ddebug *dp;
	int n = *pos;

	if (verbose)
<<<<<<< HEAD
		pr_info("called m=%p *pos=%lld\n", m, (unsigned long long)*pos);
=======
<<<<<<< HEAD
		pr_info("called m=%p *pos=%lld\n", m, (unsigned long long)*pos);
=======
		printk(KERN_INFO "%s: called m=%p *pos=%lld\n",
			__func__, m, (unsigned long long)*pos);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&ddebug_lock);

	if (!n)
		return SEQ_START_TOKEN;
	if (n < 0)
		return NULL;
	dp = ddebug_iter_first(iter);
	while (dp != NULL && --n > 0)
		dp = ddebug_iter_next(iter);
	return dp;
}

/*
 * Seq_ops next method.  Called several times within a read()
 * call from userspace, with ddebug_lock held.  Walks to the
 * next _ddebug object with a special case for the header line.
 */
static void *ddebug_proc_next(struct seq_file *m, void *p, loff_t *pos)
{
	struct ddebug_iter *iter = m->private;
	struct _ddebug *dp;

	if (verbose)
<<<<<<< HEAD
		pr_info("called m=%p p=%p *pos=%lld\n",
			m, p, (unsigned long long)*pos);
=======
<<<<<<< HEAD
		pr_info("called m=%p p=%p *pos=%lld\n",
			m, p, (unsigned long long)*pos);
=======
		printk(KERN_INFO "%s: called m=%p p=%p *pos=%lld\n",
			__func__, m, p, (unsigned long long)*pos);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (p == SEQ_START_TOKEN)
		dp = ddebug_iter_first(iter);
	else
		dp = ddebug_iter_next(iter);
	++*pos;
	return dp;
}

/*
 * Seq_ops show method.  Called several times within a read()
 * call from userspace, with ddebug_lock held.  Formats the
 * current _ddebug as a single human-readable line, with a
 * special case for the header line.
 */
static int ddebug_proc_show(struct seq_file *m, void *p)
{
	struct ddebug_iter *iter = m->private;
	struct _ddebug *dp = p;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	char flagsbuf[10];

	if (verbose)
		pr_info("called m=%p p=%p\n", m, p);
<<<<<<< HEAD
=======
=======
	char flagsbuf[8];

	if (verbose)
		printk(KERN_INFO "%s: called m=%p p=%p\n",
			__func__, m, p);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (p == SEQ_START_TOKEN) {
		seq_puts(m,
			"# filename:lineno [module]function flags format\n");
		return 0;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	seq_printf(m, "%s:%u [%s]%s =%s \"",
		trim_prefix(dp->filename), dp->lineno,
		iter->table->mod_name, dp->function,
		ddebug_describe_flags(dp, flagsbuf, sizeof(flagsbuf)));
<<<<<<< HEAD
=======
=======
	seq_printf(m, "%s:%u [%s]%s %s \"",
		   dp->filename, dp->lineno,
		   iter->table->mod_name, dp->function,
		   ddebug_describe_flags(dp, flagsbuf, sizeof(flagsbuf)));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	seq_escape(m, dp->format, "\t\r\n\"");
	seq_puts(m, "\"\n");

	return 0;
}

/*
 * Seq_ops stop method.  Called at the end of each read()
 * call from userspace.  Drops ddebug_lock.
 */
static void ddebug_proc_stop(struct seq_file *m, void *p)
{
	if (verbose)
<<<<<<< HEAD
		pr_info("called m=%p p=%p\n", m, p);
=======
<<<<<<< HEAD
		pr_info("called m=%p p=%p\n", m, p);
=======
		printk(KERN_INFO "%s: called m=%p p=%p\n",
			__func__, m, p);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_unlock(&ddebug_lock);
}

static const struct seq_operations ddebug_proc_seqops = {
	.start = ddebug_proc_start,
	.next = ddebug_proc_next,
	.show = ddebug_proc_show,
	.stop = ddebug_proc_stop
};

/*
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * File_ops->open method for <debugfs>/dynamic_debug/control.  Does
 * the seq_file setup dance, and also creates an iterator to walk the
 * _ddebugs.  Note that we create a seq_file always, even for O_WRONLY
 * files where it's not needed, as doing so simplifies the ->release
 * method.
<<<<<<< HEAD
=======
=======
 * File_ops->open method for <debugfs>/dynamic_debug/control.  Does the seq_file
 * setup dance, and also creates an iterator to walk the _ddebugs.
 * Note that we create a seq_file always, even for O_WRONLY files
 * where it's not needed, as doing so simplifies the ->release method.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int ddebug_proc_open(struct inode *inode, struct file *file)
{
	struct ddebug_iter *iter;
	int err;

	if (verbose)
<<<<<<< HEAD
		pr_info("called\n");
=======
<<<<<<< HEAD
		pr_info("called\n");
=======
		printk(KERN_INFO "%s: called\n", __func__);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	iter = kzalloc(sizeof(*iter), GFP_KERNEL);
	if (iter == NULL)
		return -ENOMEM;

	err = seq_open(file, &ddebug_proc_seqops);
	if (err) {
		kfree(iter);
		return err;
	}
	((struct seq_file *) file->private_data)->private = iter;
	return 0;
}

static const struct file_operations ddebug_proc_fops = {
	.owner = THIS_MODULE,
	.open = ddebug_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release_private,
	.write = ddebug_proc_write
};

/*
 * Allocate a new ddebug_table for the given module
 * and add it to the global list.
 */
int ddebug_add_module(struct _ddebug *tab, unsigned int n,
			     const char *name)
{
	struct ddebug_table *dt;
	char *new_name;

	dt = kzalloc(sizeof(*dt), GFP_KERNEL);
	if (dt == NULL)
		return -ENOMEM;
	new_name = kstrdup(name, GFP_KERNEL);
	if (new_name == NULL) {
		kfree(dt);
		return -ENOMEM;
	}
	dt->mod_name = new_name;
	dt->num_ddebugs = n;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	dt->num_enabled = 0;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dt->ddebugs = tab;

	mutex_lock(&ddebug_lock);
	list_add_tail(&dt->link, &ddebug_tables);
	mutex_unlock(&ddebug_lock);

	if (verbose)
<<<<<<< HEAD
		pr_info("%u debug prints in module %s\n", n, dt->mod_name);
=======
<<<<<<< HEAD
		pr_info("%u debug prints in module %s\n", n, dt->mod_name);
=======
		printk(KERN_INFO "%u debug prints in module %s\n",
				 n, dt->mod_name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}
EXPORT_SYMBOL_GPL(ddebug_add_module);

static void ddebug_table_free(struct ddebug_table *dt)
{
	list_del_init(&dt->link);
	kfree(dt->mod_name);
	kfree(dt);
}

/*
 * Called in response to a module being unloaded.  Removes
 * any ddebug_table's which point at the module.
 */
int ddebug_remove_module(const char *mod_name)
{
	struct ddebug_table *dt, *nextdt;
	int ret = -ENOENT;

	if (verbose)
<<<<<<< HEAD
		pr_info("removing module \"%s\"\n", mod_name);
=======
<<<<<<< HEAD
		pr_info("removing module \"%s\"\n", mod_name);
=======
		printk(KERN_INFO "%s: removing module \"%s\"\n",
				__func__, mod_name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&ddebug_lock);
	list_for_each_entry_safe(dt, nextdt, &ddebug_tables, link) {
		if (!strcmp(dt->mod_name, mod_name)) {
			ddebug_table_free(dt);
			ret = 0;
		}
	}
	mutex_unlock(&ddebug_lock);
	return ret;
}
EXPORT_SYMBOL_GPL(ddebug_remove_module);

static void ddebug_remove_all_tables(void)
{
	mutex_lock(&ddebug_lock);
	while (!list_empty(&ddebug_tables)) {
		struct ddebug_table *dt = list_entry(ddebug_tables.next,
						      struct ddebug_table,
						      link);
		ddebug_table_free(dt);
	}
	mutex_unlock(&ddebug_lock);
}

static __initdata int ddebug_init_success;

static int __init dynamic_debug_init_debugfs(void)
{
	struct dentry *dir, *file;

	if (!ddebug_init_success)
		return -ENODEV;

	dir = debugfs_create_dir("dynamic_debug", NULL);
	if (!dir)
		return -ENOMEM;
	file = debugfs_create_file("control", 0644, dir, NULL,
					&ddebug_proc_fops);
	if (!file) {
		debugfs_remove(dir);
		return -ENOMEM;
	}
	return 0;
}

static int __init dynamic_debug_init(void)
{
	struct _ddebug *iter, *iter_start;
	const char *modname = NULL;
	int ret = 0;
	int n = 0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (__start___verbose == __stop___verbose) {
		pr_warn("_ddebug table is empty in a "
			"CONFIG_DYNAMIC_DEBUG build");
		return 1;
	}
	iter = __start___verbose;
	modname = iter->modname;
	iter_start = iter;
	for (; iter < __stop___verbose; iter++) {
		if (strcmp(modname, iter->modname)) {
			ret = ddebug_add_module(iter_start, n, modname);
			if (ret)
				goto out_free;
			n = 0;
			modname = iter->modname;
			iter_start = iter;
		}
		n++;
	}
	ret = ddebug_add_module(iter_start, n, modname);
	if (ret)
		goto out_free;

	/* ddebug_query boot param got passed -> set it up */
	if (ddebug_setup_string[0] != '\0') {
		ret = ddebug_exec_queries(ddebug_setup_string);
		if (ret < 0)
			pr_warn("Invalid ddebug boot param %s",
				ddebug_setup_string);
		else
			pr_info("%d changes by ddebug_query\n", ret);

		/* keep tables even on ddebug_query parse error */
		ret = 0;
<<<<<<< HEAD
=======
=======
	if (__start___verbose != __stop___verbose) {
		iter = __start___verbose;
		modname = iter->modname;
		iter_start = iter;
		for (; iter < __stop___verbose; iter++) {
			if (strcmp(modname, iter->modname)) {
				ret = ddebug_add_module(iter_start, n, modname);
				if (ret)
					goto out_free;
				n = 0;
				modname = iter->modname;
				iter_start = iter;
			}
			n++;
		}
		ret = ddebug_add_module(iter_start, n, modname);
	}

	/* ddebug_query boot param got passed -> set it up */
	if (ddebug_setup_string[0] != '\0') {
		ret = ddebug_exec_query(ddebug_setup_string);
		if (ret)
			pr_warning("Invalid ddebug boot param %s",
				   ddebug_setup_string);
		else
			pr_info("ddebug initialized with string %s",
				ddebug_setup_string);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

out_free:
	if (ret)
		ddebug_remove_all_tables();
	else
		ddebug_init_success = 1;
	return 0;
}
/* Allow early initialization for boot messages via boot param */
arch_initcall(dynamic_debug_init);
/* Debugfs setup must be done later */
module_init(dynamic_debug_init_debugfs);
