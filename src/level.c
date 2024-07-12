#include "entity.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Entity *LoadLevel(const char *levelPath) {
	// entities pool as reference for generating the level
	Entity *objs = malloc(sizeof(Entity) * (WORLD_DIV * WORLD_DIV));
	if (objs == NULL) {
		return NULL;
	}

	printf("%s", levelPath);

	return objs;
}
