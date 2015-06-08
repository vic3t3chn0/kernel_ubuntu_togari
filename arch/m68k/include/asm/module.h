#ifndef _ASM_M68K_MODULE_H
#define _ASM_M68K_MODULE_H

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
enum m68k_fixup_type {
	m68k_fixup_memoffset,
	m68k_fixup_vnode_shift,
};

struct m68k_fixup_info {
	enum m68k_fixup_type type;
	void *addr;
};
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_MMU
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct mod_arch_specific {
	struct m68k_fixup_info *fixup_start, *fixup_end;
};

<<<<<<< HEAD
#ifdef CONFIG_MMU

=======
<<<<<<< HEAD
#ifdef CONFIG_MMU

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define MODULE_ARCH_INIT {				\
	.fixup_start		= __start_fixup,	\
	.fixup_end		= __stop_fixup,		\
}


<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
enum m68k_fixup_type {
	m68k_fixup_memoffset,
	m68k_fixup_vnode_shift,
};

struct m68k_fixup_info {
	enum m68k_fixup_type type;
	void *addr;
};

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define m68k_fixup(type, addr)			\
	"	.section \".m68k_fixup\",\"aw\"\n"	\
	"	.long " #type "," #addr "\n"	\
	"	.previous\n"

<<<<<<< HEAD
#endif /* CONFIG_MMU */

=======
<<<<<<< HEAD
#endif /* CONFIG_MMU */

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern struct m68k_fixup_info __start_fixup[], __stop_fixup[];

struct module;
extern void module_fixup(struct module *mod, struct m68k_fixup_info *start,
			 struct m68k_fixup_info *end);

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#else

struct mod_arch_specific {
};

#endif /* CONFIG_MMU */

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define Elf_Shdr Elf32_Shdr
#define Elf_Sym Elf32_Sym
#define Elf_Ehdr Elf32_Ehdr

#endif /* _ASM_M68K_MODULE_H */
