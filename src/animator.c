#include <raylib.h>
#include <stdio.h>
#include "animator.h"

static size_t curFrame = 0;
static float frameTimer = 0;
static float frameLifetime = 0.25f;

void AnimateThing(Texture2D frames[], Vector2 pos, size_t len) {
	if (frameTimer < frameLifetime) {
		frameTimer += GetFrameTime();
		DrawTextureV(frames[curFrame], pos, WHITE);
	} else {
		curFrame = (curFrame+1) == len ? 0 : curFrame + 1;
		frameTimer = 0;
	}
}

/* LoadGraphics loads images into memory based on their names and for use later */
void LoadGraphicsFor(Texture2D arr[], size_t len, char *names[]) {
	for (size_t i = 0; i < len; i++) {
			arr[i] = LoadTexture(names[i]);
			SetTextureFilter(arr[i], TEXTURE_FILTER_POINT);
		if (arr[i].id == 0) {
			printf("Failed to load image: %s\n", names[i]);
		}
	}
}

void UnloadGraphicsFor(Texture2D arr[], size_t len) {
	if (arr == NULL) return;

	for (size_t i = 0; i < len; i++) {
		if (arr[i].id != 0) {
			UnloadTexture(arr[i]);
		}
	}
}
