extern void	pstore_set_kmsg_bytes(int);
<<<<<<< HEAD
extern void	pstore_get_records(int);
extern int	pstore_mkfile(enum pstore_type_id, char *psname, u64 id,
			      char *data, size_t size,
			      struct timespec time, struct pstore_info *psi);
=======
extern void	pstore_get_records(void);
extern int	pstore_mkfile(enum pstore_type_id, char *psname, u64 id,
			      char *data, size_t size,
			      struct timespec time, int (*erase)(u64));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
extern int	pstore_is_mounted(void);
