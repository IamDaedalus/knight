#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <raylib.h>

#define MOVE_BLOCK 10
#define MOVE_TIMER_RESET 0.25f


enum PlayerAttackDir {
	ATK_UP = 0,
	ATK_RIGHT,
	ATK_DOWN,
	ATK_LEFT,
};

typedef struct {
	Vector2 pos;
	Rectangle coll2D;
	Texture2D curSprite;
	Texture2D sprites[2];
	Texture2D indicators[4];
	enum PlayerAttackDir attackDir;
} Player;

void MovePlayer(Player *player);
void PlayerAttack(Player *player);
void RenderIndicator(Player *player);
Rectangle PlayerDirectionRec(Player player);
Player *InitPlayer(void);

#endif
