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
	InitWindow(SCR_W, SCR_H, "Knight Game");
	ToggleFullscreen();
	SetExitKey(KEY_NULL);

	// Create entity manager
	EntityManager *manager = CreatePool();
	if (manager == NULL) {
		printf("Failed to create entity manager. Exiting...\n");
		CloseWindow();
		return -1;
	}

	// Initialize entities (assuming Init function includes player and terrain)
	if (Init(manager) == -1) {
		printf("Initialization failed. Exiting...\n");
		CloseWindow();
		return -1;
	}

	// Load level data
	char **levelData = LoadLevelData("./assets/scenes/000");
	if (levelData == NULL) {
		printf("Failed to load level data. Exiting...\n");
		CloseWindow();
		return -1;
	}

	// Load level entities
	Entity ***currentLevel = LoadLevel(levelData, manager);
	if (currentLevel == NULL) {
		printf("Failed to load level entities. Exiting...\n");
		CloseWindow();
		return -1;
	}

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		// Draw entities in current level
		for (int i = 0; i < WORLD_DIV; i++) {
			for (int j = 0; j < WORLD_DIV; j++) {
				if (currentLevel[i][j] != NULL) {
					Vector2 position = {(float)((float)j * WORLD_DIV), (float)((float)i * WORLD_DIV)};
					DrawTextureV(currentLevel[i][j]->render->curSprite, position, WHITE);
				}
			}
		}

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
