#include <raylib.h>
#include <iostream>

using namespace std;

int main()
{
	cout << "Starting the game" << endl;
	const int screenWidth = 1200;
	const int screenHeight = 700;
	InitWindow(screenWidth, screenHeight, "Pong - VM Games");
	SetTargetFPS(60);

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		DrawFPS(10, 10);
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}