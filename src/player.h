#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"

typedef struct {
	Vector2 pos;
	Texture2D sprite;
} Player;

void MovePlayer(Player *player);
Player *InitPlayer(void);

#endif
