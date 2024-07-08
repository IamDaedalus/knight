#include "player.h"
#include <raylib.h>
#include <stdlib.h>

void MovePlayer(Player *player) {
	if (IsKeyDown(KEY_RIGHT)) {
		player->pos.x += 2.0f;
	} else if (IsKeyDown(KEY_LEFT)) {
		player->pos.x -= 2.0f;
	} else if (IsKeyDown(KEY_UP)) {
		player->pos.y -= 2.0f;
	} else if (IsKeyDown(KEY_DOWN)) {
		player->pos.y += 2.0f;
	}
}

Player *InitPlayer(void) {
	Player *player = malloc(sizeof(Player));
	Image img = LoadImage("./assets/graphics/player1.png");

	player->sprite = LoadTextureFromImage(img);
	SetTextureFilter(player->sprite, TEXTURE_FILTER_POINT);
	Vector2 playerPos = {(float)SCR_H/2, (float)SCR_W/2};
	player->pos = playerPos;

	UnloadImage(img);
	return player;
}
