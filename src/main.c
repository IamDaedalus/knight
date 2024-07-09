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
		BeginDrawing();

		HandlePlayerActions(player);
		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();
	free(player);

	return 0;
}

void HandlePlayerActions(Player *player) {
	MovePlayer(player);
	// PlayerAttack(player);
	DrawTextureRec(player->curSprite, PlayerDirectionRec(*player), player->pos, WHITE);
	RenderIndicator(player);
}
