#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"
#include "entity_manager.h"

void FreeLevelGrid(Entity ***objs);
void FreeLevelData(char **levelData);
char **LoadLevelData(const char *levelPath);
int PopulateLevelGrid(Entity ***objs, char **levelData, EntityManager *manager);
Entity ***LoadLevel(char **levelData, EntityManager *manager);
Entity ***AllocateLevelGrid(void);


#endif
