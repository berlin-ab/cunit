#include <stdlib.h>

#include "list.h"

struct ListItemData {
	ListItem *next;
	void *value;
};

struct ListData {
	ListItem *first;
};

/*
 * List Functions
 */
List *make_list(void) {
	List *list = calloc(1, sizeof(List));
	list->first = NULL;
	return list;
}


void add_to_list(List *list, void *value) {
	ListItem *item = calloc(1, sizeof(ListItem));
	item->next = NULL;
	item->value = value;

	if (list->first == NULL) {
		list->first = item;
		return;
	}

	ListItem *list_item;

	for(list_item = list->first; list_item->next != NULL; list_item = list_item->next) {}

	list_item->next = item;
}


int list_size(List *list) {
	int size = 1;

	if (list->first == NULL)
		return 0;

	ListItem *list_item;

	for(list_item = list->first; list_item->next != NULL; list_item = list_item->next) {
		size++;
	}

	return size;
}