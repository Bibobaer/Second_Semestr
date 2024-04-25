#pragma once
#include "raylib.h"
#include <errno.h>
#include <stdio.h>

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	800

#define SCREEN_TITLE	"Ping Ping. Please give me 12 points (^-^)"

unsigned int Player_Score;
unsigned int Opponent_Score;
int SpeedRotation;

Sound FX;
Sound ClickFX;

Texture2D BackGround;
Texture2D BallTex;

Rectangle sourse;
Rectangle dest;

typedef struct Ball {
	int ball_x, ball_y;
	int ball_speed_x, ball_speed_y;
	float ball_radius;
}Ball;

typedef struct Player{
	int pl_x, pl_y;
	int pl_width, pl_height;
	int pl_speed;
}Player;

typedef struct Button {
	Rectangle Form;
	const char* Message;
	_Bool Action;
	Color color;
}Button;

typedef struct SettingsConfig {
	unsigned int isPlayWithBot;
	unsigned int isWithMusic;
	unsigned int isWithTexture;
}SettingsConfig;

SettingsConfig Config;

typedef void(*OpponentFunc)(Player*, Ball);

void Update_Ball(Ball* ball);
void Update_Player(Player* player);
void Update_Opponent_Bot(Player* opponent, Ball ball);
void Update_Opponent_Player(Player* opponent, Ball ball);

void DrawForms(Ball* ball, Player* player, Player* opponent);

void ResetBallPos(Ball* ball);

void CheckMousePosition(Button* button);
void CheckPlayerCollision(Player* player);

void Game_Start(Ball* ball, Player* player, Player* opponent);
void SettingsMenu(Music mus);
void MainMenu(Ball* ball, Player* player, Player* opponent);

errno_t LoadConfig(const char* configPath);
errno_t StoreConfig(const char* configPath);