#include "main.h"
#include "entity.h"
#include "player.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int main(void) {
	// SetTraceLogLevel(LOG_NONE);
	InitWindow(SCR_W, SCR_H, "knight game");
	// ToggleFullscreen();
	SetExitKey(KEY_NULL);

	Entity *player = InitPlayer();
	if (player == NULL) {
		printf("Player object couldn't be created. Exiting...");
		return -1;
	}

	// SavePoint *save = InitSavePoint(false, (Vector2){100, 100});
	// if (save == NULL) {
	// 	printf("Save object couldn't be created. Exiting...");
	// 	return -1;
	// }
	//
	// SavePoint *newSave = InitSavePoint(true, (Vector2){200, 200});
	// if (newSave == NULL) {
	// 	printf("Save object couldn't be created. Exiting...");
	// 	return -1;
	// }

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		HandlePlayerActions(player);
		ClearBackground(BLACK);
		// SavePointLogic(save, (Vector2){100, 100});
		// SavePointLogic(newSave, (Vector2){200, 200});

		EndDrawing();
	}

	CloseWindow();
	// CleanUpEntity(player);


	return 0;
}

void HandlePlayerActions(Entity *player) {
	MovePlayer(player);
	// PlayerAttack(player);
	DrawTextureRec(player->render->curSprite, PlayerDirectionRec(*player), player->transform->pos, WHITE);
	RenderIndicator(player);
}

// this should be used in conjuction with the level spawning logic
// void OnCollisionEnter(Entity *player, Entity *incoming) {
// 	if (player == NULL || incoming == NULL) {
// 		return;
// 	}
// 	Tag incomingTag = incoming->tag;
//
// 	if (CheckCollisionRecs(player->coll2D, incoming->coll2D)) {
// 	}
//
// 	switch (incomingTag) {
// 		case TAG_SAVE_POINT:
// 			printf("collided with a savepoint\r");
// 			break;
// 		default:
// 			break;
// 	}
// }
