#include "player.h"
#include "main.h"
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>

static float moveTimer = MOVE_TIMER_RESET;
static bool flipped = false;

/* InitPlayer sets the player's properties for the game */
Player *InitPlayer(void) {
	Vector2 playerPos = {(float)SCR_H/2, (float)SCR_W/2};
	Player *player = malloc(sizeof(Player));
	if (!player) {
		exit(EXIT_FAILURE);
	}

	LoadGraphicsFor(player->sprites, 2, (char*[]){"assets1.png", "assets2.png"});
	LoadGraphicsFor(player->indicators, 4, (char*[]){"assets3.png", "assets4.png", "assets5.png", "assets6.png"});
	player->curSprite = player->sprites[0];
	player->pos = playerPos;
	player->attackDir = ATK_RIGHT;

	return player;
}

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

/* RenderIndicator renders the arrow to show how far an attack can hit */
void RenderIndicator(Player *player) {
	int attackDir = player->attackDir;
	// positions for the indicator to be
	Vector2 DIRECTION_OFFSETS[] = {
		{player->pos.x,player->pos.y - MOVE_BLOCK},  	// UP
		{player->pos.x + MOVE_BLOCK, player->pos.y},   	// RIGHT
		{player->pos.x,player->pos.y + MOVE_BLOCK},  	// DOWN
		{player->pos.x - MOVE_BLOCK, player->pos.y},   	// LEFT
	};

	DrawTextureV(player->indicators[attackDir], DIRECTION_OFFSETS[attackDir], WHITE);
}

/* LoadGraphics loads images into memory based on their names and for use later */
void LoadGraphicsFor(Texture2D *arr, size_t len, char *names[]) {
	char path[MAX_PATH];

	for (size_t i = 0; i < len; i++) {
		snprintf(path, MAX_PATH, "./assets/graphics/%s", names[i]);
		Image img = LoadImage(path);
		if (img.data) {
			arr[i] = LoadTextureFromImage(img);
			SetTextureFilter(arr[i], TEXTURE_FILTER_POINT);
			UnloadImage(img);
		} else {
			printf("Failed to load image: %s\n", names[i]);
		}
	}
}
