#include "player.h"
#include "entity.h"
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

static float moveTimer = MOVE_TIMER_RESET;
static bool flipped = false;

/* InitPlayer sets the player's properties for the game */
Entity *InitPlayer(void) {
	Entity *player = calloc(1, sizeof(Entity));
	if (player == NULL) {
		return NULL;
	}

	player->isStatic = false;
	player->render = AddRenderComp(1, 2);
	if (player->render == NULL) {
		free(player);
		return NULL;
	}

	player->player = AddPlayerComp();
	if (player->player == NULL) {
		free(player->render);
		free(player);
		return NULL;
	}

	Vector2 pos = (Vector2){100, 100};
	Rectangle coll2D = (Rectangle){pos.x, pos.y, PIXEL_CNT, PIXEL_CNT};
	player->transform = AddTransformComp(pos, coll2D);
	/* might have to call cleanentity here */
	if (player->transform == NULL) {
		free(player->render);
		free(player->player);
		free(player);
		return NULL;
	}

	return player;
}

Rectangle PlayerDirectionRec(Entity player) {
	int f = flipped ? -PIXEL_CNT : PIXEL_CNT;

	return (Rectangle){player.transform->pos.x, player.transform->pos.y, f, PIXEL_CNT};
}

void MovePlayer(Entity *player) {
	if (moveTimer > 0) {
		moveTimer -= GetFrameTime();
	} else {
		if (IsKeyDown(KEY_D)) {
			player->transform->pos.x += PIXEL_CNT;
			player->player->attackDir = ATK_RIGHT;
			flipped = false;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_A)) {
			player->transform->pos.x -= PIXEL_CNT;
			player->player->attackDir = ATK_LEFT;
			flipped = true;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_W)) {
			player->transform->pos.y -= PIXEL_CNT;
			player->player->attackDir = ATK_UP;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_S)) {
			player->player->attackDir = ATK_DOWN;
			player->transform->pos.y += PIXEL_CNT;
			moveTimer = MOVE_TIMER_RESET;
		}
	}
}

/* RenderIndicator renders the arrow to show how far an attack can hit */
void RenderIndicator(Entity *player) {
	int attackDir = player->player->attackDir;
	// entity->positions for the indicator to be
	Vector2 DIRECTION_OFFSETS[] = {
		{player->transform->pos.x,player->transform->pos.y - PIXEL_CNT},  	// UP
		{player->transform->pos.x + PIXEL_CNT, player->transform->pos.y},   	// RIGHT
		{player->transform->pos.x,player->transform->pos.y + PIXEL_CNT},  	// DOWN
		{player->transform->pos.x - PIXEL_CNT, player->transform->pos.y},   	// LEFT
	};

	DrawTextureV(player->player->indicators[attackDir], DIRECTION_OFFSETS[attackDir], WHITE);
}

