#include "animator.h"
#include "save.h"
#include <raylib.h>
#include <stdlib.h>

SavePoint *InitSavePoint(bool isSavePoint) {
	SavePoint *save = malloc(sizeof(SavePoint));
	if (!save) {
		return NULL;
	}

	LoadGraphicsFor(save->sprites, 4, (char*[]){"assets7.png","assets8.png","assets9.png","assets10.png"});
	save->curSave = isSavePoint;

	return save;
}

void SavePointLogic(SavePoint *save, Vector2 pos){
	if (save->curSave) {
		AnimateThing(save->sprites, pos, 3);
		return;
	}

	save->curSprite = save->sprites[3];
	DrawTextureV(save->curSprite, pos, WHITE);
}
