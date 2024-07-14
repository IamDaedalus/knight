#include "entity.h"
#include "entity_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EntityManager *CreatePool() {
	EntityManager *manager = malloc(sizeof(EntityManager));
	if (manager == NULL) {
		return NULL;
	}

	manager->count = 0;
	manager->capacity = 10;
	manager->entities = malloc(sizeof(Entity*) * manager->capacity);
	if (manager->entities == NULL) {
		free(manager);
		return NULL;
	}

	return manager;
}

int AddEntityToPool(EntityManager *manager, Entity *entity) {
	if (manager == NULL || entity == NULL) {
		printf("Either your entity or manager is NULL. Double check.\n");
		return -1;
	}

	if (manager->count >= manager->capacity) {
		size_t newCapacity = manager->capacity * 2;
		Entity **newEntities = realloc(manager->entities, sizeof(Entity*) * newCapacity);
		if (newEntities == NULL) {
			printf("Failed to realloc memory for entity pool.\n");
			return -1;
		}
		manager->entities = newEntities;
		manager->capacity = newCapacity;
	}
	manager->entities[manager->count] = entity;
	manager->count += 1;

	return 0;
}

void CleanUpPool(EntityManager *manager) {
	if (manager == NULL) {
		printf("there's nothing to clean up in the pool\r");
		return;
	}

	for (size_t i = 0; i < manager->count; i++) {
		CleanUpEntity(manager->entities[i]);
	}

	free(manager->entities);
	free(manager);
}

/* GetEntityByTag returns a copy of the gameobject  */
Entity *GetEntityByTag(EntityManager *manager, Tag tag) {
	if (manager == NULL) {
		printf("manager is NULL; it might have been freed or isn't initialized yet\r");
		return NULL;
	}

	for (size_t i = 0; i < manager->count; i++) {
		if (manager->entities[i]->tag == tag) {
			/* create and return a copy of the gameobject */
			Entity *entity = malloc(sizeof(Entity));
			if (entity == NULL) {
				return NULL;
			}

			memcpy(entity, manager->entities[i], sizeof(Entity));
			return entity;
		}
	}

	return NULL;
}
