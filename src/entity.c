#include "entity.h"
#include "animator.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

char **AssetAcquisition(int bot, int top, int arrLen) {
	if ((top - bot) > arrLen) {
		printf("hey there's not enough space");
		return NULL;
	}

	char **indicatorNames = malloc(sizeof(char*) * arrLen);
	if (indicatorNames == NULL) {
		return NULL;
	}

	// hey I'm a programmer after all
	for (int i = bot; i <= top; i++) {
		indicatorNames[i-bot] = malloc(MAX_PATH);
		if (indicatorNames[i-bot] == NULL) {
			// free previously allocated memory
			for (int j = 0; j < i-bot; j++) {
				free(indicatorNames[j]);
			}
			free(indicatorNames);
			return NULL;
		}
		snprintf(indicatorNames[i-bot], MAX_PATH, "./assets/graphics/assets%d.png", i);
	}
	return indicatorNames;
}

void FreeAcquisitionArr(char **arr, int arrLen) {
	if (arr == NULL) {
		return;
	}
	for (int i = 0; i < arrLen; i++) {
		free(arr[i]);
	}

	free(arr);
}

CPlayer *AddPlayerComp() {
	CPlayer *player = malloc(sizeof(CPlayer));
	if (player == NULL) {
		return NULL;
	}
	char **indicatorNames = AssetAcquisition(3, 6, 4);
	if (indicatorNames == NULL) {
		free(player);
		return NULL;
	}


	player->attackDir = ATK_RIGHT;
	LoadGraphicsFor(player->indicators, 4, indicatorNames);
	FreeAcquisitionArr(indicatorNames, 4);

	return player;
}

CRender *AddRenderComp(int bot, int top) {
	CRender *render = malloc(sizeof(CRender));
	if (render == NULL) {
		return NULL;
	}
	int assetCount = (top-bot)+1;
	char **textureNames = AssetAcquisition(bot, top, assetCount);
	if (textureNames == NULL) {
		free(render);
		return NULL;
	}

	LoadGraphicsFor(render->sprites, assetCount, textureNames);
	render->curSprite = render->sprites[0];

	FreeAcquisitionArr(textureNames, assetCount);

	return render;
}

CTransform *AddTransformComp(Vector2 pos, Rectangle coll2D) {
	CTransform *transform = malloc(sizeof(CTransform));
	if (transform == NULL) {
		return NULL;
	}

	transform->pos = pos;
	transform->coll2D = coll2D;

	return transform;
}

Entity *EmptyEntity(Vector2 pos) {
	Entity *e = malloc(sizeof(Entity));
	if (e == NULL) {
		return NULL;
	}

	e->transform = AddTransformComp(pos, (Rectangle){pos.x, pos.y, PIXEL_CNT, PIXEL_CNT});

	return e;
}

void CleanUpEntity(Entity *entity) {
	if (entity == NULL) {
		return;
	}

	if (entity->render) {
		// UnloadGraphicsFor(entity->render->sprites, MAX_ASSET_COUNT);
		free(entity->render);
	}
	if (entity->player) {
		// UnloadGraphicsFor(entity->player->indicators, 4);
		free(entity->player);
	}

	free(entity->transform);
	free(entity);
}
