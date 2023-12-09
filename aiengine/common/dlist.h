
#ifndef __COMMON_DLIST__
#define __COMMON_DLIST__

#include <stddef.h>

typedef struct ListNode {
	struct ListNode *prev;
	struct ListNode *next;
} ListNode;

#define OffsetOf(type, member) ((int)((char *)&((type *)0)->member))
#define ContainerOf(ptr, type, member) \
  ((type *)((char *)(ptr) - (char *)(&(((type *)0)->member))))


static inline void dlist_append_tail(struct ListNode *dist, struct ListNode *item) {
	if (dist == NULL) {
		return;
	}
	dist->next = item;
	item->prev = dist;
}

static inline void dlist_insert(struct ListNode *dist, struct ListNode *item) {
	if (dist == NULL) {
		return;
	}
	if (dist->next == NULL) {
		dist->next = item;
		item->prev = dist;
		return;
	}
	if (dist->next != NULL) {
		item->next = dist->next;
		dist->next->prev = item;
		dist->next = item;
		item->prev = dist;
	}
}

#endif /* __COMMON_DLIST__ */