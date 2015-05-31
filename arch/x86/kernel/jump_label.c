/*
 * jump label x86 support
 *
 * Copyright (C) 2009 Jason Baron <jbaron@redhat.com>
 *
 */
#include <linux/jump_label.h>
#include <linux/memory.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/jhash.h>
#include <linux/cpu.h>
#include <asm/kprobes.h>
#include <asm/alternative.h>

#ifdef HAVE_JUMP_LABEL

union jump_code_union {
	char code[JUMP_LABEL_NOP_SIZE];
	struct {
		char jump;
		int offset;
	} __attribute__((packed));
};

<<<<<<< HEAD
static void __jump_label_transform(struct jump_entry *entry,
				   enum jump_label_type type,
				   void *(*poker)(void *, const void *, size_t))
=======
void arch_jump_label_transform(struct jump_entry *entry,
			       enum jump_label_type type)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	union jump_code_union code;

	if (type == JUMP_LABEL_ENABLE) {
		code.jump = 0xe9;
		code.offset = entry->target -
				(entry->code + JUMP_LABEL_NOP_SIZE);
	} else
		memcpy(&code, ideal_nops[NOP_ATOMIC5], JUMP_LABEL_NOP_SIZE);
<<<<<<< HEAD

	(*poker)((void *)entry->code, &code, JUMP_LABEL_NOP_SIZE);
}

void arch_jump_label_transform(struct jump_entry *entry,
			       enum jump_label_type type)
{
	get_online_cpus();
	mutex_lock(&text_mutex);
	__jump_label_transform(entry, type, text_poke_smp);
=======
	get_online_cpus();
	mutex_lock(&text_mutex);
	text_poke_smp((void *)entry->code, &code, JUMP_LABEL_NOP_SIZE);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	mutex_unlock(&text_mutex);
	put_online_cpus();
}

<<<<<<< HEAD
__init_or_module void arch_jump_label_transform_static(struct jump_entry *entry,
				      enum jump_label_type type)
{
	__jump_label_transform(entry, type, text_poke_early);
=======
void arch_jump_label_text_poke_early(jump_label_t addr)
{
	text_poke_early((void *)addr, ideal_nops[NOP_ATOMIC5],
			JUMP_LABEL_NOP_SIZE);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

#endif
