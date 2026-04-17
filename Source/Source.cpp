#include <raylib.h>
#include <string>
#include <array>
#include <iostream>
#include <vector>

#define SCREEN_X 1200
#define SCREEN_Y 700
#define WINDOW_TITLE "Sumo - VM Games"

struct Entity
{
	Rectangle rec;
	Color cor;
	float speed = 50.f;
	int life = 100;
	bool collision = false;
};

void MovePlayer(Entity &player)
{
	if (IsKeyDown(KEY_RIGHT))
	{
		player.rec.x += player.speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_LEFT))
	{
		player.rec.x -= player.speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_UP))
	{
		player.rec.y -= player.speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_DOWN))
	{
		player.rec.y += player.speed * GetFrameTime();
	}
}

int main()
{
	InitWindow(SCREEN_X, SCREEN_Y, WINDOW_TITLE);
	InitAudioDevice();
	
	Entity player{ Rectangle{SCREEN_X / 2.f, SCREEN_Y / 2.f, 50.f, 50.f}, BLUE, 300.f };
	Entity enemy{ Rectangle{SCREEN_X / 3.f, SCREEN_Y / 3.f, 50.f, 50.f}, RED, 0.f };

	std::vector<Entity> enemies;
	enemies.push_back(enemy);

	// main game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		DrawFPS(10, 10);
		DrawText(std::to_string(player.life).c_str(), SCREEN_X - 100, 0, 32, WHITE);
		MovePlayer(player);
		DrawRectangle(player.rec.x , player.rec.y, player.rec.width, player.rec.height, player.cor);
		DrawRectangle(enemies[0].rec.x, enemies[0].rec.y, enemies[0].rec.width, enemies[0].rec.height, enemies[0].cor);

		if (CheckCollisionRecs(player.rec, enemies[0].rec))
		{
			if (!enemies[0].collision)
			{
				player.life -= 10;
			}
			enemies[0].collision = true;
		}
		else
		{
			enemies[0].collision = false;
		}

		ClearBackground(BLACK);
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();

	return 0;
}