#ifndef SAVE_H
#define SAVE_H

#include "entity.h"
#include <raylib.h>

typedef struct {
	Entity *entity;
	bool curSave;
} SavePoint;

void SavePointLogic(SavePoint *save, Vector2 pos);
SavePoint *InitSavePoint(bool isSavePoint, Vector2 pos);

#endif
