#ifndef __NPC_H_
#define __NPC_H_

#define NPC_COUNT 2

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
void npc_add(Npc **headPtr, double posx, double posy, NpcState state);

#endif
