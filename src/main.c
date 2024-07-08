#include "player.h"
#include <raylib.h>
#include <stdlib.h>
#include "main.h"

int main(void) {
	InitWindow(SCR_W, SCR_H, "knight game");
	ToggleFullscreen();
	SetExitKey(KEY_NULL);

	Player *player = InitPlayer();

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		MovePlayer(player);

		BeginDrawing();

		ClearBackground(BLACK);
		DrawTextureV(player->sprite, player->pos, WHITE);
		// DrawCircleV(player->pos, 5, RED);

		EndDrawing();
	}

	CloseWindow();
	free(player);

	return 0;
}
