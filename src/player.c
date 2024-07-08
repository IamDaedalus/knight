#include "player.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

static float moveTimer = 0.25f;
static bool flipped = false;

bool PlayerFacingLeft(void) {
	return flipped;
}

void MovePlayer(Player *player) {
	if (moveTimer > 0) {
		moveTimer -= GetFrameTime();
	} else {
		if (IsKeyDown(KEY_D)) {
			player->pos.x += MOVE_BLOCK;
			flipped = false;
			moveTimer = 0.25f;
		} else if (IsKeyDown(KEY_A)) {
			player->pos.x -= MOVE_BLOCK;
			flipped = true;
			moveTimer = 0.25f;
		} else if (IsKeyDown(KEY_W)) {
			player->pos.y -= MOVE_BLOCK;
			moveTimer = 0.25f;
		} else if (IsKeyDown(KEY_S)) {
			player->pos.y += MOVE_BLOCK;
			moveTimer = 0.25f;
		}
	}
}

Player *InitPlayer(void) {
	Player *player = malloc(sizeof(Player));
	Image img = LoadImage("./assets/graphics/player1.png");
	Vector2 playerPos = {(float)SCR_H/2, (float)SCR_W/2};

	player->sprite = LoadTextureFromImage(img);
	SetTextureFilter(player->sprite, TEXTURE_FILTER_POINT);
	player->pos = playerPos;

	UnloadImage(img);
	return player;
}
