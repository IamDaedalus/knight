#ifndef SAVE_H
#define SAVE_H

#include <raylib.h>

typedef struct {
	Vector2 pos;
	bool curSave;
	Texture2D curSprite;
	Texture2D sprites[4];
} SavePoint;

void SavePointLogic(SavePoint *save, Vector2 pos);
SavePoint *InitSavePoint(bool isSavePoint);

#endif
