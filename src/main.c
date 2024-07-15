#include "main.h"
#include "entity.h"
#include "entity_manager.h"
#include "level.h"
#include "player.h"
#include "terrain.h"
#include "utilities.h"

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
		CleanUpEntity(player);
		printf("terrain couldn't be created. exiting...");
		return -1;
	}

	AddEntityToPool(manager, player);
	AddEntityToPool(manager, terrain);

	return 0;
}

int main(void) {
	SetTraceLogLevel(LOG_NONE);
	InitWindow(SCR_W, SCR_H, "Knight Game");
	// ToggleFullscreen();
	SetExitKey(KEY_ESCAPE);

	/* create entity manager */
	EntityManager *manager = CreatePool();
	if (manager == NULL) {
		printf("failed to create entity manager. exiting...\n");
		CloseWindow();
		return -1;
	}

	/* initialize entities (assuming init function includes player and terrain) */
	if (Init(manager) == -1) {
		printf("initialization failed. exiting...\n");
		CloseWindow();
		return -1;
	}

	/* load level data */
	char **levelData = LoadLevelData("./assets/scenes/001");
	if (levelData == NULL) {
		printf("failed to load level data. exiting...\n");
		CleanUpPool(manager);
		CloseWindow();
		return -1;
	}

	/* load level entities */
	Entity ***currentLevel = LoadLevel(levelData, manager);
	if (currentLevel == NULL) {
		printf("failed to load level entities. exiting...\n");
		FreeLevelData(levelData);
		CloseWindow();
		return -1;
	}

	Entity *player = GetEntityByTag(manager, TAG_PLAYER);
	if (player == NULL) {
		CleanUpPool(manager);
		FreeLevelData(levelData);
		FreeLevelGrid(currentLevel);
		CloseWindow();
		return -1;
	}
	player->transform->pos = (Vector2){(float)SCR_W/3, (float)SCR_H/3};

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		/* draw entities in current level */
		for (int i = 0; i < WORLD_DIV; i++) {
			for (int j = 0; j < WORLD_DIV; j++) {
				Entity *e = currentLevel[i][j];
				if (e != NULL) {
					e->transform->pos = (Vector2){(float)SCR_W/3 + ((float)j * PIXEL_CNT), (float)SCR_H/3+((float)i * PIXEL_CNT)};
					DrawTextureV(e->render->curSprite, e->transform->pos, WHITE);
					UpdateEntityCollisionRec(&e->transform->coll2D, e->transform->pos);
					DrawRectangleRec(e->transform->coll2D, (Color){255, 0, 0, 100});
				}
			}
		}

		Vector2 p = WorldToLocalSpace(player->transform->pos);
		printf("local (%.2f, %.2f)\n", p.x, p.y);
		Vector2 k = LocalToWorldSpace(WorldToLocalSpace(player->transform->pos));
		printf("world (%.2f, %.2f)\n", k.x, k.y);
		HandlePlayerActions(player);

		EndDrawing();
	}

	FreeLevelData(levelData);
	FreeLevelGrid(currentLevel);
	CleanUpPool(manager);
	if (player != NULL) {
		free(player);
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
