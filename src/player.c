#include "player.h"
#include "entity.h"
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>

static float moveTimer = MOVE_TIMER_RESET;
static bool flipped = false;

/* InitPlayer sets the player's properties for the game */
Entity *InitPlayer(void) {
	Vector2 pos = (Vector2){100, 100};
	Rectangle coll2D = (Rectangle){pos.x, pos.y, WORLD_DIV, WORLD_DIV};
	Entity *player =malloc(sizeof(Entity));
	if (player == NULL) {
		return NULL;
	}

	player->render = AddRenderComp(1, 2);
	if (player->render == NULL) return NULL;
	player->player = AddPlayerComp();
	if (player->player == NULL) return NULL;
	player->transform = AddTransformComp(pos, coll2D);
	if (player->transform == NULL) return NULL;

	return player;
}

Rectangle PlayerDirectionRec(Entity player) {
	int f = flipped ? -WORLD_DIV : WORLD_DIV;

	return (Rectangle){player.transform->pos.x, player.transform->pos.y, f, WORLD_DIV};
}

void MovePlayer(Entity *player) {
	if (moveTimer > 0) {
		moveTimer -= GetFrameTime();
	} else {
		if (IsKeyDown(KEY_D)) {
			player->transform->pos.x += WORLD_DIV;
			player->player->attackDir = ATK_RIGHT;
			flipped = false;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_A)) {
			player->transform->pos.x -= WORLD_DIV;
			player->player->attackDir = ATK_LEFT;
			flipped = true;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_W)) {
			player->transform->pos.y -= WORLD_DIV;
			player->player->attackDir = ATK_UP;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_S)) {
			player->player->attackDir = ATK_DOWN;
			player->transform->pos.y += WORLD_DIV;
			moveTimer = MOVE_TIMER_RESET;
		}
	}
}

/* RenderIndicator renders the arrow to show how far an attack can hit */
void RenderIndicator(Entity *player) {
	int attackDir = player->player->attackDir;
	// entity->positions for the indicator to be
	Vector2 DIRECTION_OFFSETS[] = {
		{player->transform->pos.x,player->transform->pos.y - WORLD_DIV},  	// UP
		{player->transform->pos.x + WORLD_DIV, player->transform->pos.y},   	// RIGHT
		{player->transform->pos.x,player->transform->pos.y + WORLD_DIV},  	// DOWN
		{player->transform->pos.x - WORLD_DIV, player->transform->pos.y},   	// LEFT
	};

	DrawTextureV(player->player->indicators[attackDir], DIRECTION_OFFSETS[attackDir], WHITE);
}

