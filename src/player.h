#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include <raylib.h>

#define MOVE_BLOCK 10

typedef struct {
	Vector2 pos;
	Texture2D sprite;
	Rectangle coll2D;
} Player;

void MovePlayer(Player *player);
bool PlayerFacingLeft(void);
Player *InitPlayer(void);

#endif
