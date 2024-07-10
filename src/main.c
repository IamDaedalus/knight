#include "main.h"
#include "player.h"
#include "save.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int main(void) {
	SetTraceLogLevel(LOG_NONE);
	InitWindow(SCR_W, SCR_H, "knight game");
	// ToggleFullscreen();
	SetExitKey(KEY_NULL);

	Player *player = InitPlayer();
	if (player == NULL) {
		printf("Player object couldn't be created. Exiting...");
		return -1;
	}

	SavePoint *save = InitSavePoint(false);
	if (save == NULL) {
		printf("Save object couldn't be created. Exiting...");
		return -1;
	}

	SavePoint *newSave = InitSavePoint(true);
	if (newSave == NULL) {
		printf("Save object couldn't be created. Exiting...");
		return -1;
	}

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		HandlePlayerActions(player);
		ClearBackground(BLACK);
		SavePointLogic(save, (Vector2){100, 100});
		SavePointLogic(newSave, (Vector2){200, 200});

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
