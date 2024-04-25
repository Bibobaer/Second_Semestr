#include "Game.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void Update_Ball(Ball* ball) {
	ball->ball_x += ball->ball_speed_x;
	ball->ball_y += ball->ball_speed_y;

	if (ball->ball_x + ball->ball_radius >= SCREEN_WIDTH) {
		PlaySound(FX);
		Opponent_Score++;
		ResetBallPos(ball);
	}
	if (ball->ball_x - ball->ball_radius <= 0) {
		PlaySound(FX);
		Player_Score++;
		ResetBallPos(ball);
	}
	if (ball->ball_y + ball->ball_radius >= SCREEN_HEIGHT || ball->ball_y - ball->ball_radius <= 0) {
		PlaySound(FX);
		ball->ball_speed_y *= -1;
		SpeedRotation = (-1) * SpeedRotation;
	}
}

void Update_Player(Player* player) {
	if (IsKeyDown(KEY_UP))
		player->pl_y = player->pl_y - player->pl_speed;
	if (IsKeyDown(KEY_DOWN))
		player->pl_y = player->pl_y + player->pl_speed;

	CheckPlayerCollision(player);
}

void Update_Opponent_Bot(Player* opponent, Ball ball) {
	if (opponent->pl_y + opponent->pl_height / 2 > ball.ball_y)
		opponent->pl_y = opponent->pl_y - opponent->pl_speed;
	if (opponent->pl_y + opponent->pl_height / 2 <= ball.ball_y)
		opponent->pl_y = opponent->pl_y + opponent->pl_speed;

	CheckPlayerCollision(opponent);
}

void Update_Opponent_Player(Player* opponent, Ball ball) {
	if (IsKeyDown(KEY_W))
		opponent->pl_y = opponent->pl_y - opponent->pl_speed;
	if (IsKeyDown(KEY_S))
		opponent->pl_y = opponent->pl_y + opponent->pl_speed;

	CheckPlayerCollision(opponent);
}

void DrawForms(Ball* ball, Player* player, Player* opponent) {
	if (Config.isWithTexture == 1) {
		DrawTexture(BackGround, 0, 0, WHITE);
		//Ball
		DrawTexturePro(BallTex, sourse, dest, (Vector2) { ball->ball_radius, ball->ball_radius }, 45 * (float)GetTime() * SpeedRotation, WHITE);
	}
	else {
		ClearBackground(BLACK);
		DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, RAYWHITE);
		DrawCircleLines(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, RAYWHITE);
		//Ball
		DrawCircle(ball->ball_x, ball->ball_y, ball->ball_radius, WHITE);
	}
	//Players
	DrawRectangle(player->pl_x, player->pl_y, player->pl_width, player->pl_height, BLUE);
	DrawRectangleLines(player->pl_x, player->pl_y, player->pl_width, player->pl_height, GRAY);

	DrawRectangle(opponent->pl_x, opponent->pl_y, opponent->pl_width, opponent->pl_height, RED);
	DrawRectangleLines(opponent->pl_x, opponent->pl_y, opponent->pl_width, opponent->pl_height, GRAY);
	//Score
	DrawText(TextFormat("%i", Opponent_Score), SCREEN_WIDTH / 4 - 20, 20, 80, WHITE);
	DrawText(TextFormat("%i", Player_Score), 3 * SCREEN_WIDTH / 4 - 20, 20, 80, WHITE);
}

void ResetBallPos(Ball* ball) {
	ball->ball_x = SCREEN_WIDTH / 2;
	ball->ball_y = SCREEN_HEIGHT / 2;

	int Score_choices[2] = { -1, 1 };

	ball->ball_speed_x *= Score_choices[GetRandomValue(0, 1)];
	ball->ball_speed_y *= Score_choices[GetRandomValue(0, 1)];
}

void CheckMousePosition(Button* button) {
	if (CheckCollisionPointRec(GetMousePosition(), button->Form)) {
		button->color = DARKBLUE;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			PlaySound(ClickFX);
			button->Action = 1;
			button->color = RED;
		}
	}
	else {
		button->Action = 0;
		button->color = DARKGREEN;
	}
}

void CheckPlayerCollision(Player* player) {
	if (player->pl_y <= 0)
		player->pl_y = 0;
	if (player->pl_y + player->pl_height >= SCREEN_HEIGHT)
		player->pl_y = SCREEN_HEIGHT - player->pl_height;
}

void Game_Start(Ball* ball, Player* player, Player* opponent) {
	_Bool IsQuit = 0;
	//Ball
	ball->ball_x = SCREEN_WIDTH / 2;
	ball->ball_y = SCREEN_HEIGHT / 2;
	ball->ball_speed_x = 8;
	ball->ball_speed_y = 8;
	ball->ball_radius = 15;
	//Player
	player->pl_width = 25;
	player->pl_height = 120;
	player->pl_x = SCREEN_WIDTH - player->pl_width - 15;
	player->pl_y = SCREEN_HEIGHT / 2 - player->pl_height / 2;
	player->pl_speed = 7;
	//Opponent
	opponent->pl_width = 25;
	opponent->pl_height = 120;
	opponent->pl_x = 15;
	opponent->pl_y = SCREEN_HEIGHT / 2 - opponent->pl_height / 2;
	opponent->pl_speed = 7;
	//Load
	Music music = LoadMusicStream("GameMusic.mp3");
	FX = LoadSound("Beat_It.wav");
	BallTex = LoadTexture("Ball.png");
	//Function for opponent
	OpponentFunc UpdateOp = Config.isPlayWithBot == 1 ? Update_Opponent_Bot : Update_Opponent_Player;

	PlayMusicStream(music);
	while (WindowShouldClose() == 0)
	{
		sourse = (Rectangle){ 0, 0, ball->ball_radius * 2, ball->ball_radius * 2 };
		dest = (Rectangle){ (float)ball->ball_x, (float)ball->ball_y, sourse.width, sourse.height };
		if (Config.isWithMusic == 1)
			UpdateMusicStream(music);
		if (!IsQuit) {
			//Updating
			Update_Ball(ball);
			Update_Player(player);
			UpdateOp(opponent, *ball);

			//Check collision
			if (CheckCollisionCircleRec((Vector2) { (float)ball->ball_x, (float)ball->ball_y }, ball->ball_radius, (Rectangle) { (float)player->pl_x, (float)player->pl_y, (float)player->pl_width, (float)player->pl_height })) {
				PlaySound(FX);
				ball->ball_speed_x *= -1;
			}
			if (CheckCollisionCircleRec((Vector2) { (float)ball->ball_x, (float)ball->ball_y }, ball->ball_radius, (Rectangle) { (float)opponent->pl_x, (float)opponent->pl_y, (float)opponent->pl_width, (float)opponent->pl_height })) {
				PlaySound(FX);
				ball->ball_speed_x *= -1;
			}
		}
		//Drawing
		BeginDrawing();
		ClearBackground(BLACK);

		DrawForms(ball, player, opponent);

		//Check
		if ((Opponent_Score >= 5 || Player_Score >= 5) && IsKeyDown(KEY_Q) == 0) {
			SpeedRotation = 0;
			if (Opponent_Score == 5)
				DrawText("Red Win", SCREEN_WIDTH / 2 - MeasureText("Red Win", 45), SCREEN_HEIGHT / 4 - MeasureText("Red Win", 20), 80, RAYWHITE);
			if (Player_Score == 5)
				DrawText("Blue Win", SCREEN_WIDTH / 2 - MeasureText("Blue Win", 45), SCREEN_HEIGHT / 4 - MeasureText("Blue Win", 20), 80, RAYWHITE);
			DrawText("Press 'Q' to exit", SCREEN_WIDTH / 2 - MeasureText("Press 'Q' to exit", 45)+20, SCREEN_HEIGHT / 3 - 50, 80, RAYWHITE);
			IsQuit = 1;
		}
		else if ((Opponent_Score == 5 || Player_Score == 5) && IsKeyDown(KEY_Q) == 1) {
			StopMusicStream(music);
			return;
		}
		EndDrawing();
		
	}
}

void SettingsMenu(Music mus) {
	Button PlayWithBot = { 0 };
	Button TwoPlayers = { 0 };
	Button WithMusic = { 0 };
	Button WOMusic = { 0 };
	Button WithTexture = { 0 };
	Button WOTexture = { 0 };
	Button QuitSet = { 0 };
	//Button for playing with bot
	PlayWithBot.Form = (Rectangle) { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 5, 300, 180 };
	PlayWithBot.Message = "Play\n\n\n\nWith\n\n\n\nBot";
	PlayWithBot.Action = 0;
	PlayWithBot.color = DARKGREEN;
	//Button for two players
	TwoPlayers.Form = (Rectangle){ SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 30, 300, 180 };
	TwoPlayers.Message = "  Two\n\n\nPlayers";
	TwoPlayers.Action = 0;
	TwoPlayers.color = DARKGREEN;
	//Button for play with music
	WithMusic.Form = (Rectangle){100, 160, 300, 180};
	WithMusic.Message = "Play\n\n\n\nWith\n\n\n\nMusic";
	WithMusic.Action = 0;
	WithMusic.color = DARKGREEN;
	//Button for play without music
	WOMusic.Form = (Rectangle){100, 160+30+180, 300, 180};
	WOMusic.Message = "Play\n\n\n\nWithout\n\n\n\nMusic";
	WOMusic.Action = 0;
	WOMusic.color = DARKGREEN;
	//Button for play with texture
	WithTexture.Form = (Rectangle){SCREEN_WIDTH/2+240, 160,300 , 180};
	WithTexture.Message = "Play With\n\n\n\nTextures";
	WithTexture.Action = 0;
	WithTexture.color = DARKGREEN;
	//Button for play without texture
	WOTexture.Form = (Rectangle){ SCREEN_WIDTH/2+240, 160+210,300 , 180 };
	WOTexture.Message = "\t\t No\n\n\n\nTextures";
	WOTexture.Action = 0;
	WOTexture.color = DARKGREEN;
	//Quit button
	QuitSet.Form = (Rectangle){ SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 220, 300, 180 };
	QuitSet.Message = "  Quit\n\n\nSettings";
	QuitSet.Action = 0;
	QuitSet.color = DARKGREEN;

	BackGround = LoadTexture("BG.png");
	while (WindowShouldClose() == 0) {
		if (Config.isWithMusic == 1)
			UpdateMusicStream(mus);

		CheckMousePosition(&PlayWithBot);
		CheckMousePosition(&TwoPlayers);
		CheckMousePosition(&WithMusic);
		CheckMousePosition(&WOMusic);
		CheckMousePosition(&WithTexture);
		CheckMousePosition(&WOTexture);
		CheckMousePosition(&QuitSet);

		//Draw
		BeginDrawing();
		ClearBackground(BLACK);
		if (Config.isWithTexture == 1)
			DrawTexture(BackGround, 0, 0, WHITE);
		DrawText("Settings", SCREEN_WIDTH / 2 - MeasureText("Settings", 40), 50, 80, WHITE);

		DrawRectangle((int)PlayWithBot.Form.x, (int)PlayWithBot.Form.y, (int)PlayWithBot.Form.width, (int)PlayWithBot.Form.height, PlayWithBot.color);
		DrawRectangleLines((int)PlayWithBot.Form.x, (int)PlayWithBot.Form.y, (int)PlayWithBot.Form.width, (int)PlayWithBot.Form.height, GRAY);
		DrawText(PlayWithBot.Message, (int)PlayWithBot.Form.x+100, (int)PlayWithBot.Form.y+5, 50, WHITE);

		DrawRectangle((int)TwoPlayers.Form.x, (int)TwoPlayers.Form.y, (int)TwoPlayers.Form.width, (int)TwoPlayers.Form.height, TwoPlayers.color);
		DrawRectangleLines((int)TwoPlayers.Form.x, (int)TwoPlayers.Form.y, (int)TwoPlayers.Form.width, (int)TwoPlayers.Form.height, GRAY);
		DrawText(TwoPlayers.Message, (int)TwoPlayers.Form.x + 60, (int)TwoPlayers.Form.y + 40, 50, WHITE);

		DrawRectangle((int)WithMusic.Form.x, (int)WithMusic.Form.y, (int)WithMusic.Form.width, (int)WithMusic.Form.height, WithMusic.color);
		DrawRectangleLines((int)WithMusic.Form.x, (int)WithMusic.Form.y, (int)WithMusic.Form.width, (int)WithMusic.Form.height, GRAY);
		DrawText(WithMusic.Message, (int)WithMusic.Form.x+90, (int)WithMusic.Form.y+10, 50, WHITE);

		DrawRectangle((int)WOMusic.Form.x, (int)WOMusic.Form.y, (int)WOMusic.Form.width, (int)WOMusic.Form.height, WOMusic.color);
		DrawRectangleLines((int)WOMusic.Form.x, (int)WOMusic.Form.y, (int)WOMusic.Form.width, (int)WOMusic.Form.height, GRAY);
		DrawText(WOMusic.Message, (int)WOMusic.Form.x+90, (int)WOMusic.Form.y+10, 50, WHITE);
		//
		DrawRectangle((int)WithTexture.Form.x, (int)WithTexture.Form.y, (int)WithTexture.Form.width, (int)WithTexture.Form.height, WithTexture.color);
		DrawRectangleLines((int)WithTexture.Form.x, (int)WithTexture.Form.y, (int)WithTexture.Form.width, (int)WithTexture.Form.height, GRAY);
		DrawText(WithTexture.Message, (int)WithTexture.Form.x+30, (int)WithTexture.Form.y+35, 50, WHITE);

		DrawRectangle((int)WOTexture.Form.x, (int)WOTexture.Form.y, (int)WOTexture.Form.width, (int)WOTexture.Form.height, WOTexture.color);
		DrawRectangleLines((int)WOTexture.Form.x, (int)WOTexture.Form.y, (int)WOTexture.Form.width, (int)WOTexture.Form.height, GRAY);
		DrawText(WOTexture.Message, (int)WOTexture.Form.x+25, (int)WOTexture.Form.y+25, 50, WHITE);

		DrawRectangle((int)QuitSet.Form.x, (int)QuitSet.Form.y, (int)QuitSet.Form.width, (int)QuitSet.Form.height, QuitSet.color);
		DrawRectangleLines((int)QuitSet.Form.x, (int)QuitSet.Form.y, (int)QuitSet.Form.width, (int)QuitSet.Form.height, GRAY);
		DrawText(QuitSet.Message, (int)QuitSet.Form.x + 55, (int)QuitSet.Form.y + 45, 50, WHITE);

		EndDrawing();

		//Check actions of buttons
		if (PlayWithBot.Action) {
			Config.isPlayWithBot = 1;
			printf("You playing with bot\n");
			return;
		}
		if (TwoPlayers.Action) {
			Config.isPlayWithBot = 0;
			printf("You playing with anouther player\n");
			return;
		}
		if (WithMusic.Action) {
			Config.isWithMusic = 1;
			printf("You playing with music\n");
			return;
		}
		if (WOMusic.Action) {
			Config.isWithMusic = 0;
			printf("You playing without music\n");
			return;
		}
		if (WithTexture.Action) {
			Config.isWithTexture = 1;
			printf("You playing with texture\n");
			return;
		}
		if (WOTexture.Action) {
			Config.isWithTexture = 0;
			printf("You playing without texture\n");
			return;
		}
		if (QuitSet.Action)
			return;
	}
}

void MainMenu(Ball* ball, Player* player, Player* opponent) {
	Button Start = { 0 };
	Button Settings = { 0 };
	Button Quit = { 0 };
	ClickFX = LoadSound("ClickSound.wav");
	//Start button
	Start.Form = (Rectangle){SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/5, 300, 180};
	Start.Message = "Start Game";
	Start.Action = 0;
	Start.color = DARKGREEN;
	//Quit button
	Quit.Form = (Rectangle){SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT-220, 300, 180};
	Quit.Message = "Quit";
	Quit.Action = 0;
	Quit.color = DARKGREEN;
	//Settings button
	Settings.Form = (Rectangle){SCREEN_WIDTH/2-150, SCREEN_HEIGHT/2-30, 300, 180};
	Settings.Message = "Settings";
	Settings.Action = 0;
	Settings.color = DARKGREEN;

	Vector2 mousePos = {0, 0};
	Music menu = LoadMusicStream("MenuMusic.mp3");

	if (Config.isWithTexture == 1)
		BackGround = LoadTexture("BG.png");
	
	while (WindowShouldClose() == 0) {
		if (Config.isWithMusic == 1) {
			PlayMusicStream(menu);
			UpdateMusicStream(menu);
		}
		CheckMousePosition(&Start);
		CheckMousePosition(&Settings);
		CheckMousePosition(&Quit);

		Player_Score = 0;
		Opponent_Score = 0;
		SpeedRotation = 5;

		//Draw
		BeginDrawing();
		ClearBackground(BLACK);
		if (Config.isWithTexture == 1)
			DrawTexture(BackGround, 0, 0, WHITE);
		DrawText("Ping Pong", SCREEN_WIDTH / 2 - MeasureText("Ping Pong", 40), 50, 80, WHITE);

		DrawRectangle((int)Start.Form.x, (int)Start.Form.y, (int)Start.Form.width, (int)Start.Form.height, Start.color);
		DrawRectangleLines((int)Start.Form.x, (int)Start.Form.y, (int)Start.Form.width, (int)Start.Form.height, GRAY);
		DrawText(Start.Message, (int)Start.Form.x + 7, (int)Start.Form.y + MeasureText(Start.Message, 12), 50, WHITE);

		DrawRectangle((int)Settings.Form.x, (int)Settings.Form.y, (int)Settings.Form.width, (int)Settings.Form.height, Settings.color);
		DrawRectangleLines((int)Settings.Form.x, (int)Settings.Form.y, (int)Settings.Form.width, (int)Settings.Form.height, GRAY);
		DrawText(Settings.Message, (int)Settings.Form.x+45, (int)Settings.Form.y+ MeasureText(Settings.Message, 17), 50, WHITE);

		DrawRectangle((int)Quit.Form.x, (int)Quit.Form.y, (int)Quit.Form.width, (int)Quit.Form.height, Quit.color);
		DrawRectangleLines((int)Quit.Form.x, (int)Quit.Form.y, (int)Quit.Form.width, (int)Quit.Form.height, GRAY);
		DrawText(Quit.Message, (int)Quit.Form.x + 100, (int)Quit.Form.y + MeasureText(Quit.Message, 30), 50, WHITE);
		EndDrawing();

		//Check actions of buttons
		if (Start.Action) {
			StopMusicStream(menu);
			Game_Start(ball, player, opponent);
			Start.Action = 0;
		}
		if (Settings.Action) {
			SettingsMenu(menu);
			Settings.Action = 0;
		}
		if (Quit.Action)
			return;
	}
}

errno_t LoadConfig(const char* configPath) {
	errno_t code = 0;
	FILE* pConfigFile = NULL;
	code = fopen_s(&pConfigFile, configPath, "r");
	if (code != 0 || pConfigFile == NULL) {
		printf("Error open config file with code: %d\n", code);
		return code;
	}

	unsigned int BotTmp;
	int ret = fscanf_s(pConfigFile, "With_Bot = %u\n", &BotTmp);
	if (ret != 1) {
		printf("Error load config: read id\n");
		fclose(pConfigFile);
		return ENODATA;
	}
	unsigned int MusicTmp;
	ret = fscanf_s(pConfigFile, "With_Music = %u\n", &MusicTmp);
	if (ret != 1) {
		printf("Error load config: read id\n");
		fclose(pConfigFile);
		return ENODATA;
	}
	unsigned int TextureTmp;
	ret = fscanf_s(pConfigFile, "With_Texture = %u", &TextureTmp);
	if (ret != 1) {
		printf("Error load config: read id\n");
		fclose(pConfigFile);
		return ENODATA;
	}

	Config.isPlayWithBot = BotTmp;
	Config.isWithMusic = MusicTmp;
	Config.isWithTexture = TextureTmp;
	fclose(pConfigFile);
	printf("Config is load\n");

	return code;
}

errno_t StoreConfig(const char* configPath) {
	errno_t code = 0;

	FILE* pConfigFile = NULL;
	code = fopen_s(&pConfigFile, configPath, "w");
	if (code != 0) {
		printf("Error open config file with code: %d\n", code);
		return code;
	}
	int ret = fprintf_s(pConfigFile, "With_Bot = %u\nWith_Music = %u\nWith_Texture = %u", Config.isPlayWithBot, Config.isWithMusic, Config.isWithTexture);
	fclose(pConfigFile);
	printf("Config unload\n");

	return code;
}