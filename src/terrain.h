#ifndef TERRAIN_H
#define TERRAIN_H

#include "entity.h"

/* struct to determine which terrain texture to render */
typedef enum {
	TYPE_GRASS,
	TYPE_DIRT,
	TYPE_ROCK,
} TerrainType;

Entity *InitTerrain(TerrainType type);

#endif
