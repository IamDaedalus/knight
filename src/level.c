#include "level.h"
#include "entity.h"

#include <string.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **LoadLevelData(const char *levelPath) {
	/* allocate memory for the pointers to rows */
	char **levelData = malloc(sizeof(char*) * WORLD_DIV);
	if (levelData == NULL) {
		return NULL;
	}

	FILE *file = fopen(levelPath, "r");
	if (file == NULL) {
		printf("Couldn't load the level file data\n");
		free(levelData); /* free allocated memory before returning */
		return NULL;
	}

	short lineNumber = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, file)) != -1) {
		levelData[lineNumber] = malloc(sizeof(char) * (WORLD_DIV + 1)); /* allocate memory for the row */
		if (levelData[lineNumber] == NULL) {
			for (int i = 0; i < lineNumber; i++) {
				free(levelData[i]);
			}
			free(levelData);
			free(line);
			fclose(file);
			return NULL;
		}

		strncpy(levelData[lineNumber], line, WORLD_DIV); /* copy line data */
		levelData[lineNumber][WORLD_DIV] = '\0'; /* ensure null termination */

		lineNumber++;
		/* this may or may not be needed because I may include write metadata to level files */
		if (lineNumber >= WORLD_DIV) {
			break; /* prevent overflow if file has more lines than expected */
		}
	}

	free(line);
	fclose(file);

	return levelData;
}

// Function to free the loaded level data
void FreeLevelData(char **levelData) {
	if (levelData == NULL) {
		return;
	}

	for (int i = 0; i < WORLD_DIV; i++) {
		free(levelData[i]);
	}
	free(levelData);
}

Entity ***LoadLevel(char **levelData, EntityManager *manager) {
	Entity ***objs = AllocateLevelGrid();
	if (objs == NULL) {
		return NULL;
	}

	if (PopulateLevelGrid(objs, levelData, manager) != 0) {
		FreeLevelGrid(objs);
		return NULL;
	}

	return objs;
}

Entity ***AllocateLevelGrid(void) {
	Entity ***objs = malloc(WORLD_DIV * sizeof(Entity**));
	if (objs == NULL) {
		printf("error: memory allocation failed for objs\n");
		return NULL;
	}

	for (int i = 0; i < WORLD_DIV; i++) {
		objs[i] = malloc(WORLD_DIV * sizeof(Entity*));
		if (objs[i] == NULL) {
			printf("error: memory allocation failed for objs[%d]\n", i);
			for (int j = 0; j < i; j++) {
				free(objs[j]);
			}
			free(objs);
			return NULL;
		}
	}

	return objs;
}

void FreeLevelGrid(Entity ***objs) {
	for (int i = 0; i < WORLD_DIV; i++) {
		for (int j = 0; j < WORLD_DIV; j++) {
			if (objs[i][j] != NULL) {
				free(objs[i][j]);
			}
		}
		free(objs[i]);
	}
	free(objs);
}

int PopulateLevelGrid(Entity ***objs, char **levelData, EntityManager *manager) {
	int i, j;
	for (i = 0; i < WORLD_DIV; i++) {
		for (j = 0; j < WORLD_DIV; j++) {
			switch (levelData[i][j]) {
				case 'P':
					objs[i][j] = GetEntityByTag(manager, TAG_PLAYER);
					break;
				case '#':
					objs[i][j] = GetEntityByTag(manager, TAG_TERRAIN);
					break;
				default:
					objs[i][j] = NULL;
					break;
			}
		}
	}

	return 0;
}
