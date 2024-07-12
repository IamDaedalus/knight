#include "animator.h"
#include "entity.h"
#include "save.h"
#include <raylib.h>
#include <stdlib.h>

// SavePoint *InitSavePoint(bool isSavePoint, Vector2 pos) {
// 	Entity *save = malloc(sizeof(Entity));
// 	if (!save) {
// 		return NULL;
// 	}
//
// 	save = CreateEntity(4,
// 			(char*[]){"assets7.png","assets8.png","assets9.png","assets10.png"}, 
// 			(Rectangle){pos.x - WORLD_DIV, pos.y, 3*WORLD_DIV, 3*WORLD_DIV},
// 			TAG_SAVE_POINT
// 	);
// 	save->curSave = isSavePoint;
//
// 	return save;
// }
//
// void SavePointLogic(SavePoint *save, Vector2 pos){
// 	if (save->curSave) {
// 		AnimateThing(save->render->sprites, pos, 3);
// 		return;
// 	}
//
// 	DrawTextureV(save->render->sprites[3], pos, WHITE);
// }
