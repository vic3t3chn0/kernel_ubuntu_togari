#define S_SIZE (1024 - (sizeof(unsigned int) + 1))

struct sbuff {
	unsigned int	count;
	char		buf[S_SIZE + 1];
};
static struct sbuff emergency, *emergency_ptr = &emergency;

<<<<<<< HEAD
static __printf(2, 3) int sb_add(struct sbuff *m, const char *f, ...)
=======
<<<<<<< HEAD
static __printf(2, 3) int sb_add(struct sbuff *m, const char *f, ...)
=======
static int sb_add(struct sbuff *m, const char *f, ...)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	va_list args;
	int len;

	if (likely(m->count < S_SIZE)) {
		va_start(args, f);
		len = vsnprintf(m->buf + m->count, S_SIZE - m->count, f, args);
		va_end(args);
		if (likely(m->count + len < S_SIZE)) {
			m->count += len;
			return 0;
		}
	}
	m->count = S_SIZE;
	printk_once(KERN_ERR KBUILD_MODNAME " please increase S_SIZE\n");
	return -1;
}

static struct sbuff *sb_open(void)
{
	struct sbuff *m = kmalloc(sizeof(*m), GFP_ATOMIC);

	if (unlikely(!m)) {
		local_bh_disable();
		do {
			m = xchg(&emergency_ptr, NULL);
		} while (!m);
	}
	m->count = 0;
	return m;
}

static void sb_close(struct sbuff *m)
{
	m->buf[m->count] = 0;
	printk("%s\n", m->buf);

	if (likely(m != &emergency))
		kfree(m);
	else {
<<<<<<< HEAD
		emergency_ptr = m;
=======
<<<<<<< HEAD
		emergency_ptr = m;
=======
		xchg(&emergency_ptr, m);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		local_bh_enable();
	}
}

