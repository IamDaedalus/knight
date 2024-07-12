#ifndef ANIMATOR_H
#define ANIMATOR_H

#define MAX_PATH 256

#include <raylib.h>
#include <stdlib.h>

typedef struct {
	Texture2D *frames;
	size_t frameCount;
	size_t currentFrame;
	float frameTimer;
	float frameLifetime;
	Vector2 position;
} Animator;


void LoadGraphicsFor(Texture2D arr[], size_t len, char *names[]);
void UnloadGraphicsFor(Texture2D arr[], size_t len);
void AnimateThing(Texture2D frames[], Vector2 pos, size_t len);

#endif 	/* ANIMATOR_H */
