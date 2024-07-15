#include "main.h"
#include <raylib.h>

Vector2 WorldToLocalSpace(Vector2 pos) {
	Vector2 local = {0};

	local.x = ((((int)pos.x % (SCR_H/3)) / 2) / WORLD_DIV) + 1;
	local.y = ((((int)pos.y % (SCR_H/3)) / 2) / WORLD_DIV) + 1;

	return local;
}

Vector2 LocalToWorldSpace(Vector2 pos) {
	Vector2 world = {0};

	world.x = ((((pos.x - 1) * 10) * 2) + 200);
	world.y = ((((pos.y - 1) * 10) * 2) + 200);

	return world;
}
