#include "player.h"
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "main.h"

int main(void) {
	InitWindow(SCR_W, SCR_H, "knight game");
	// ToggleFullscreen();
	SetExitKey(KEY_NULL);

	Player *player = InitPlayer();
	bool flipped = false;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		MovePlayer(player);
		flipped = PlayerFacingLeft();

		BeginDrawing();

		printf("flipped is %d\r", flipped);
		DrawRectangleV(player->pos, (Vector2){10, 10}, RED);
		DrawTextureRec(
				player->sprite, 
				flipped ? (Rectangle){player->pos.x, player->pos.y, -10, 10} : (Rectangle){player->pos.x, player->pos.y, 10, 10},
				// (Rectangle){player->pos.x, player->pos.y, -10, 10},
				player->pos, WHITE
			);
		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();
	free(player);

	return 0;
}
