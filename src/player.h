#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <stdlib.h>
#include <raylib.h>

#define MOVE_TIMER_RESET 0.25f

void MovePlayer(Entity *player);
void PlayerAttack(Entity *player);
void RenderIndicator(Entity *player);
Rectangle PlayerDirectionRec(Entity player);
Entity *InitPlayer(void);

#endif
