#include <raylib.h>
#include <iostream>
#include <string>

using namespace std;

int playerScore = 0;
int cpuScore = 0;

class Ball
{
public:
	float x, y;
	float speed_x, speed_y;
	float radius;

	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}

	void Update()
	{
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
			speed_y *= -1;
		if (x + radius >= GetScreenWidth())
		{
			playerScore++; 
			ResetBall();
		}
		if (x - radius <= 0)
		{
			cpuScore++; 
			ResetBall();
		}
	}

	void ResetBall()
	{
		x = GetScreenWidth() / 2.f;
		y = GetScreenHeight() / 2.f;
		int speed_choices[2] = { -1, 1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
};

class Paddle
{
public:
	float x, y;
	float width, height;
	float speed;

	void Draw()
	{
		DrawRectangle(x, y, width, height, WHITE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP) && y > 0)
		{
			y -= speed;
		}
		if (IsKeyDown(KEY_DOWN) && y + height < GetScreenHeight())
		{
			y += speed;
		}
	}
};

class CPUPaddle : public Paddle
{
public:
	void Update(int yBall)
	{
		if (y + height/2 > yBall && y > 0)
		{
			y -= speed;
		}
		if (y + height / 2 < yBall && y + height < GetScreenHeight())
		{
			y += speed;
		}
	}
};

Ball ball;
Paddle player;
CPUPaddle cpuPaddle;

int main()
{
	cout << "Starting the game" << endl;
	const int screenWidth = 1280;
	const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Pong - VM Games");
	SetTargetFPS(60);
	int value = 0;

	ball.radius = 20.f;
	ball.x = screenWidth / 2.f;
	ball.y = screenHeight / 2.f;
	ball.speed_x = 8;
	ball.speed_y = 8;

	player.speed = 6.f;
	player.width = 25.f;
	player.height = 120.f;
	player.x = 10;
	player.y = (screenHeight / 2) - (player.height / 2);

	cpuPaddle.speed = 6.f;
	cpuPaddle.width = 25.f;
	cpuPaddle.height = 120.f;
	cpuPaddle.x = screenWidth - cpuPaddle.width - 10;
	cpuPaddle.y = (screenHeight / 2) - (cpuPaddle.height / 2);

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		// Update
		ball.Update();
		player.Update();
		cpuPaddle.Update(ball.y);

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, 
			Rectangle{ player.x, player.y, player.width, player.height }))
		{
			ball.speed_x *= -1;
			value++;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
			Rectangle{ cpuPaddle.x, cpuPaddle.y, cpuPaddle.width, cpuPaddle.height }))
		{
			ball.speed_x *= -1;
		}

		// Drawing
		ClearBackground(BLACK);
		DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
		ball.Draw();
		player.Draw();
		cpuPaddle.Draw();
		DrawFPS(10, 10);
		DrawText(TextFormat("%i", playerScore), screenWidth / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", cpuScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}