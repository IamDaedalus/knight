#include "main.h"
#include "entity.h"
#include "entity_manager.h"
#include "level.h"
#include "player.h"
#include "terrain.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int Init(EntityManager *manager) {
	Entity *player = InitPlayer();
	if (player == NULL) {
		printf("Player object couldn't be created. Exiting...");
		return -1;
	}

	Entity *terrain = InitTerrain(TYPE_GRASS);
	if (terrain == NULL) {
		printf("terrain couldn't be created. exiting...");
		return -1;
	}

	AddEntityToPool(manager, player);
	AddEntityToPool(manager, terrain);

	return 0;
}

int main(void) {
	// SetTraceLogLevel(LOG_NONE);
	InitWindow(SCR_W, SCR_H, "knight game");
	// ToggleFullscreen();
	SetExitKey(KEY_NULL);

	EntityManager *manager = CreatePool();
	if (manager == NULL) {
		printf("failed to create manager");
		return -1;
	}
	if (Init(manager) == -1) {
		printf("failed in Init\n");
		return -1;
	}
	char **levelData=LoadLevelData("./assets/scenes/000");
	if (levelData == NULL) {
		return -1;
	}

	Entity ***currentLevel = LoadLevel(levelData, manager);
	if (currentLevel == NULL) {
		return NULL;
	}


	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		HandlePlayerActions(GetEntityByTag(manager, TAG_PLAYER));
		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void HandlePlayerActions(Entity *player) {
	MovePlayer(player);
	// PlayerAttack(player);
	DrawTextureRec(player->render->curSprite, PlayerDirectionRec(*player), player->transform->pos, WHITE);
	RenderIndicator(player);
}
