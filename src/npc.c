#include <stdlib.h>
#include <stdio.h>
#include "npc.h"

// Get a pointer to the last element of the Npc list
Npc	*npc_list_get_last(Npc *list)
{
	if (list == NULL)
		return (NULL);

	Npc	*iter = list;
	while (iter->next != NULL) {
		iter = iter->next;
	}

	return iter;
}

void npc_list_add(Npc **headPtr, double posx, double posy, NpcState state)
{
	Npc	*last;
	Npc	*new;

	new = (Npc *) malloc(1 * sizeof(Npc));
	if (new == NULL) {
		printf("Error: npc_add() allocation failure.\n");
		exit(EXIT_FAILURE);
	}

	new->posx = posx;
	new->posy = posy;
	new->state = state;
	new->next = NULL;

	if (*headPtr == NULL) {
		*headPtr = new;
	} else {
		last = npc_list_get_last(*headPtr);
		last->next = new;
	}
}

void npc_list_free_all(Npc *head)
{
	while (head != NULL) {
		Npc *to_free = head;
		head = head->next;
		free(to_free);
		to_free = NULL; // actually have to get a headPtr in order to truly NULL them
	}
}
