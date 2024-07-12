#ifndef MAIN_H
#define MAIN_H

#include "entity.h"
#include "player.h"
#include <raylib.h>

#define SCR_W 600
#define SCR_H 600

void HandlePlayerActions(Entity *player);
void OnCollisionEnter(Entity *player, Entity *incoming);

#endif
