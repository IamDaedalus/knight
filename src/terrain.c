#include "terrain.h"
#include "entity.h"
#include <stdlib.h>
#include <raylib.h>

Entity *InitTerrain(TerrainType terrain) {
	Entity *t = malloc(sizeof(Entity));
	if (t == NULL) {
		return NULL;
	}

	t->tag = TAG_TERRAIN;
	t->render = AddRenderComp(11, 11);
	if (t->render == NULL) {
		free(t);
		return NULL;
	}
	t->render->curSprite = t->render->sprites[terrain];

	t->transform = AddTransformComp((Vector2){0, 0}, (Rectangle){0,0,WORLD_DIV, WORLD_DIV});
	if (t->transform == NULL) {
		free(t->render);
		free(t);
		return NULL;
	}

	t->isStatic = true;

	return t;
}
