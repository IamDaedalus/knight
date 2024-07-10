#include <raylib.h>
#include <stdio.h>
#include "animator.h"

static size_t curFrame = 0;
static float frameTimer = 0;
static float frameLifetime = 0.25f;


Animator CreateAnimator(Texture2D frames[], size_t frameCount, float frameLifetime, Vector2 position) {
	Animator animator = {
		.frames = frames,
		.frameCount = frameCount,
		.currentFrame = 0,
		.frameTimer = 0,
		.frameLifetime = frameLifetime,
		.position = position
	};
	return animator;
}

void UpdateAndDrawAnimator(Animator *animator) {
	animator->frameTimer += GetFrameTime();

	if (animator->frameTimer >= animator->frameLifetime) {
		animator->currentFrame = (animator->currentFrame + 1) % animator->frameCount;
		animator->frameTimer -= animator->frameLifetime;  // Reset timer, keeping remainder
	}

	DrawTextureV(animator->frames[animator->currentFrame], animator->position, WHITE);
}

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
void LoadGraphicsFor(Texture2D *arr, size_t len, char *names[]) {
	char path[MAX_PATH];

	for (size_t i = 0; i < len; i++) {
		snprintf(path, MAX_PATH, "./assets/graphics/%s", names[i]);
		Image img = LoadImage(path);
		if (img.data) {
			arr[i] = LoadTextureFromImage(img);
			SetTextureFilter(arr[i], TEXTURE_FILTER_POINT);
			UnloadImage(img);
		} else {
			printf("Failed to load image: %s\n", names[i]);
		}
	}
}
