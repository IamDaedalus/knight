#include "player.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

static float moveTimer = MOVE_TIMER_RESET;
static bool flipped = false;
static Texture2D indicators[4];

Rectangle PlayerDirectionRec(Player player) {
	int f = flipped ? -MOVE_BLOCK : MOVE_BLOCK;

	return (Rectangle){player.pos.x, player.pos.y, f, MOVE_BLOCK};
}

void MovePlayer(Player *player) {
	if (moveTimer > 0) {
		moveTimer -= GetFrameTime();
	} else {
		if (IsKeyDown(KEY_D)) {
			player->pos.x += MOVE_BLOCK;
			player->attackDir = ATK_RIGHT;
			flipped = false;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_A)) {
			player->pos.x -= MOVE_BLOCK;
			player->attackDir = ATK_LEFT;
			flipped = true;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_W)) {
			player->pos.y -= MOVE_BLOCK;
			player->attackDir = ATK_UP;
			moveTimer = MOVE_TIMER_RESET;
		} else if (IsKeyDown(KEY_S)) {
			player->attackDir = ATK_DOWN;
			player->pos.y += MOVE_BLOCK;
			moveTimer = MOVE_TIMER_RESET;
		}
	}
}

// void PlayerAttack(Player *player) {
// 	if (IsKeyDown(KEY_I)) {
// 		player->attackDir = ATK_UP;
// 	} else if (IsKeyDown(KEY_L)) {
// 		player->attackDir = ATK_RIGHT;
// 	} else if (IsKeyDown(KEY_K)) {
// 		player->attackDir = ATK_DOWN;
// 	} else if (IsKeyDown(KEY_J)) {
// 		player->attackDir = ATK_LEFT;
// 	}
// }

void RenderIndicator(Player *player) {
	int attackDir = player->attackDir;
	Vector2 DIRECTION_OFFSETS[] = {
		{player->pos.x,player->pos.y - MOVE_BLOCK},  	// UP
		{player->pos.x + MOVE_BLOCK, player->pos.y},   	// RIGHT
		{player->pos.x,player->pos.y + MOVE_BLOCK},  	// DOWN
		{player->pos.x - MOVE_BLOCK, player->pos.y},   	// LEFT
	};

	DrawTextureV(player->indicators[attackDir], DIRECTION_OFFSETS[attackDir], WHITE);
}

void InitIndicators() {
	char indicatorAsset[MAX_PATH];

	for (int i = 0; i < 4; i++) {
		snprintf(indicatorAsset, MAX_PATH, "./assets/graphics/assets%d.png", i+3);
		Image img = LoadImage(indicatorAsset);
		if (img.data) {
			indicators[i] = LoadTextureFromImage(img);
			UnloadImage(img);
		} else {
			printf("Failed to load image: %s\n", indicatorAsset);
		}
	}
}

Player *InitPlayer(void) {
	Image img = LoadImage("./assets/graphics/assets1.png");
	Vector2 playerPos = {(float)SCR_H/2, (float)SCR_W/2};
	Player *player = malloc(sizeof(Player));
	if (!player) {
		exit(EXIT_FAILURE);
	}

	InitIndicators();

	player->sprite = LoadTextureFromImage(img);
	SetTextureFilter(player->sprite, TEXTURE_FILTER_POINT);
	player->pos = playerPos;
	player->attackDir = ATK_RIGHT;
	memcpy(player->indicators, indicators, 4 * sizeof(Texture2D));

	UnloadImage(img);
	return player;
}
