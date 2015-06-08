#ifndef LINUX_PAGE_DEBUG_FLAGS_H
#define  LINUX_PAGE_DEBUG_FLAGS_H

/*
 * page->debug_flags bits:
 *
 * PAGE_DEBUG_FLAG_POISON is set for poisoned pages. This is used to
 * implement generic debug pagealloc feature. The pages are filled with
 * poison patterns and set this flag after free_pages(). The poisoned
 * pages are verified whether the patterns are not corrupted and clear
 * the flag before alloc_pages().
 */

enum page_debug_flags {
	PAGE_DEBUG_FLAG_POISON,		/* Page is poisoned */
<<<<<<< HEAD
	PAGE_DEBUG_FLAG_GUARD,
=======
<<<<<<< HEAD
	PAGE_DEBUG_FLAG_GUARD,
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/*
 * Ensure that CONFIG_WANT_PAGE_DEBUG_FLAGS reliably
 * gets turned off when no debug features are enabling it!
 */

#ifdef CONFIG_WANT_PAGE_DEBUG_FLAGS
<<<<<<< HEAD
#if !defined(CONFIG_PAGE_POISONING) && \
    !defined(CONFIG_PAGE_GUARD) \
=======
<<<<<<< HEAD
#if !defined(CONFIG_PAGE_POISONING) && \
    !defined(CONFIG_PAGE_GUARD) \
=======
#if !defined(CONFIG_PAGE_POISONING) \
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* && !defined(CONFIG_PAGE_DEBUG_SOMETHING_ELSE) && ... */
#error WANT_PAGE_DEBUG_FLAGS is turned on with no debug features!
#endif
#endif /* CONFIG_WANT_PAGE_DEBUG_FLAGS */

#endif /* LINUX_PAGE_DEBUG_FLAGS_H */
