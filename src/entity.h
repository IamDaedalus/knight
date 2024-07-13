#ifndef ACTOR_H
#define ACTOR_H

#include <stdlib.h>
#include <raylib.h>

#define WORLD_DIV 10
#define MAX_ASSET_COUNT 5


typedef enum {
	TAG_PLAYER = 0,
	TAG_SAVE_POINT,
	TAG_BEETLE,
	TAG_GRASS,
	TAG_TERRAIN,
}Tag ;

typedef enum {
	ATK_UP = 0,
	ATK_RIGHT,
	ATK_DOWN,
	ATK_LEFT,
}PlayerAttackDir;

typedef struct {
	Vector2 pos;
	Rectangle coll2D;
} CTransform;

typedef struct {
	Texture2D sprites[MAX_ASSET_COUNT];
	Texture2D curSprite;
} CRender;

typedef struct {
	PlayerAttackDir attackDir;
	Texture2D indicators[4];
} CPlayer;

typedef struct {
	CTransform *transform;
	CRender *render;
	CPlayer *player;
	Tag tag;
	bool isStatic;
} Entity;

char **AssetAcquisition(int bot, int top, int arrLen);
void FreeAcquisitionArr(char **arr, int arrLen);

void CleanUpEntity(Entity *entity);
CPlayer *AddPlayerComp();
CRender *AddRenderComp(int bot, int top);
CTransform *AddTransformComp(Vector2 pos, Rectangle coll2D);

#endif
