#include "Game.h"

int main(int argc, char** argv) {
	Ball ball = { 0, 0, 0, 0, 0 };
	Player player = { 0, 0, 0, 0, 0 };
	Player opponent = { 0, 0, 0, 0, 0 };

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	InitAudioDevice();
	SetTargetFPS(60);

	LoadConfig("Config.txt");
	MainMenu(&ball, &player, &opponent);
	StoreConfig("Config.txt");

	CloseAudioDevice();
	CloseWindow();
	return 0;
}