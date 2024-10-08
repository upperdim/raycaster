#ifndef __NPC_H_
#define __NPC_H_

typedef enum {
	ALIVE = 0,
	DEAD
} NpcState;

typedef struct s_Npc {
	double posx;
	double posy;
	int state;
	struct s_Npc *next;
} Npc;

Npc	*npc_list_get_last(Npc *list);
void npc_list_add(Npc **headPtr, double posx, double posy, NpcState state);
void npc_list_free_all(Npc *head);

#endif
