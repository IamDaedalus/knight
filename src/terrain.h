#ifndef TERRAIN_H
#define TERRAIN_H

#include "entity.h"
typedef enum {
	TYPE_GRASS,
	TYPE_DIRT,
	TYPE_ROCK,
} TerrainType;

Entity *InitTerrain(TerrainType type);

#endif
