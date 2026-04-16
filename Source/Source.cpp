#include <raylib.h>

#define SCREEN_X 1200
#define SCREEN_Y 700
#define WINDOW_TITLE "Game"

int main()
{
	InitWindow(SCREEN_X, SCREEN_Y, WINDOW_TITLE);
	InitAudioDevice();

	// main game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}