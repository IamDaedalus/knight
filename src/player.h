#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define MOVE_BLOCK 10
#define MAX_PATH 256
#define MOVE_TIMER_RESET 0.25f


enum PlayerAttackDir {
	ATK_UP = 0,
	ATK_RIGHT,
	ATK_DOWN,
	ATK_LEFT,
};

typedef struct {
	Texture2D indicator;
	Vector2 pos;
} Indicator;

typedef struct {
	Vector2 pos;
	Texture2D sprite;
	Texture2D indicators[4];
	Rectangle coll2D;
	enum PlayerAttackDir attackDir;
} Player;

void MovePlayer(Player *player);
void PlayerAttack(Player *player);
void RenderIndicator(Player *player);
Rectangle PlayerDirectionRec(Player player);
Player *InitPlayer(void);

#endif
