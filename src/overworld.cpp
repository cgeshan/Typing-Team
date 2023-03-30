#include "overworld.h"
#include "ysglfontdata.h"

GLuint OverworldTextureId[12];

//Point Call (wip)
std::tuple <int, int> GameData::GetData(int level, int points)
{
	GameData gd;
	std::ifstream infile;
	infile.open("media/game.txt", std::ifstream::in);
	if (infile.good()) {
		infile >> gd.level >> gd.points;
	}

	std::cout << "level -> " << gd.level << "\npoints -> " << gd.points << std::endl;

	return std::make_tuple(gd.level, gd.points);

}

void GameData::SaveGame(int level, int points) {
	FILE* fp = fopen("media/game.txt", "w");

	if (nullptr != fp) {
		FILE* File;
		File = fopen("media/game.txt", "w+");
		fprintf(File, "%i %i", level, points);
		fclose(File);
	}
}

//BG Items
void GameData::DrawBG()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, OverworldTextureId[0]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0, 0);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, 600);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(800, 600);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(800, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void GameData::DrawFadeOut(int alphacount)
{
	glColor4ub(0, 0, 0, alphacount);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	glVertex2d(0, 0);
	glVertex2d(800, 0);
	glVertex2d(800, 600);
	glVertex2d(0, 600);

	glEnd();
	glDisable(GL_BLEND);
}
void GameData::ResetScreen()
{
	if (gameState == 2)
	{
		alphacount += 10;

		DrawFadeOut(alphacount);
	}

	else if (gameState == 0)
	{
		alphacount -= 10;
		DrawFadeOut(alphacount);
	}

	if (alphacount >= 250 && gameState == 2)
	{
		px = 0;
		py = 400;
		++screencount;
		alphacount = 0;
		platstate = 0;
		coinvisState = 0;
		gameState = 0;
	}

	else if (alphacount <= -250 && gameState == 0)
	{
		px = 0;
		py = 400;
		alphacount = 0;
		gameState = 1;
	}

	if (screencount == 2 && gameState != 3)
	{
		screencount = 3;
		alphacount = 0;
		platstate = 0;
		coinvisState = 0;
		gameState = 3;
	}

	if (gameState == 3)
	{
		px = 0;
		py = 400;
		alphacount -= 10;
		DrawFadeOut(alphacount);
	}

	if (alphacount <= -250 && gameState == 3)
	{
		px = 0;
		py = 400;
		alphacount = 0;
		platstate = 0;
		coinvisState = 0;
		gameState = 4;
	}
}
void GameData::DrawPlatforms()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, OverworldTextureId[7]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0 + platx3, 0 + platy3);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0 + platx3, 120 + platy3);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(260 + platx3, 120 + platy3);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(260 + platx3, 0 + platy3);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, OverworldTextureId[6]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0 + platx2, 0 + platy2);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0 + platx2, 120 + platy2);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(260 + platx2, 120 + platy2);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(260 + platx2, 0 + platy2);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, OverworldTextureId[5]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0 + platx1, 0 + platy1);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0 + platx1, 120 + platy1);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(260 + platx1, 120 + platy1);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(260 + platx1, 0 + platy1);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void GameData::GeneratePlatforms()
{
	if (platstate == 0)
	{
		platx1 = rand() % 600;
		platx2 = rand() % 600;
		platx3 = rand() % 600;

		platy1 = rand() % 100 + 300;
		platy2 = rand() % 100 + 200;
		platy3 = rand() % 100 + 100;

		platstate = 1;
	}
}

//Coins
void GameData::DrawCoins()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (coinstate1 == 1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, OverworldTextureId[9]);

		glBegin(GL_QUADS);

		glTexCoord2d(0.0, 0.0);
		glVertex2i(coinx1, coiny1);

		glTexCoord2d(0.0, 1.0);
		glVertex2i(coinx1, coiny1 + imgdat.png[9].hei);

		glTexCoord2d(1.0, 1.0);
		glVertex2i(coinx1 + imgdat.png[9].wid, coiny1 + imgdat.png[9].hei);

		glTexCoord2d(1.0, 0.0);
		glVertex2i(coinx1 + imgdat.png[9].wid, coiny1);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	if (coinstate2 == 1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, OverworldTextureId[10]);

		glBegin(GL_QUADS);

		glTexCoord2d(0.0, 0.0);
		glVertex2i(coinx2, coiny2);

		glTexCoord2d(0.0, 1.0);
		glVertex2i(coinx2, coiny2 + imgdat.png[10].hei);

		glTexCoord2d(1.0, 1.0);
		glVertex2i(coinx2 + imgdat.png[10].wid, coiny2 + imgdat.png[10].hei);

		glTexCoord2d(1.0, 0.0);
		glVertex2i(coinx2 + imgdat.png[10].wid, coiny2);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	if (coinstate3 == 1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, OverworldTextureId[11]);

		glBegin(GL_QUADS);

		glTexCoord2d(0.0, 0.0);
		glVertex2i(coinx3, coiny3);

		glTexCoord2d(0.0, 1.0);
		glVertex2i(coinx3, coiny3 + imgdat.png[11].hei);

		glTexCoord2d(1.0, 1.0);
		glVertex2i(coinx3 + imgdat.png[11].wid, coiny3 + imgdat.png[11].hei);

		glTexCoord2d(1.0, 0.0);
		glVertex2i(coinx3 + imgdat.png[11].wid, coiny3);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void GameData::GenerateCoins()
{
	if (coinvisState == 0)
	{
		coinx1 = platx1 + 100;
		coinx2 = platx2 + 100;
		coinx3 = platx3 + 100;

		coiny1 = platy1 - 70;
		coiny2 = platy2 - 70;
		coiny3 = platy3 - 70;

		coinstate1 = 1;
		coinstate2 = 1;
		coinstate3 = 1;

		coinvisState = 1;
	}
}

//Increase Point, Remove Coin Image
void GameData::PointCount()
{
	if (px > coinx1 - 80 && px < coinx1 + 20 && py > coiny1 - 100 && py < coiny1)
	{
		if (coinstate1 == 1)
		{
			points += 10;
		}
		coinstate1 = 0;
	}

	if (px > coinx2 - 80 && px < coinx2 + 20 && py > coiny2 - 100 && py < coiny2)
	{
		if (coinstate2 == 1)
		{
			points += 10;
		}
		coinstate2 = 0;
	}

	if (px > coinx3 - 80 && px < coinx3 + 20 && py > coiny3 - 100 && py < coiny3)
	{
		if (coinstate3 == 1)
		{
			points += 10;
		}
		coinstate3 = 0;
	}
}
void GameData::DrawPointCount()
{
	glRasterPos2i(600, 30);
	char pointstxt[256];
	std::sprintf(pointstxt, "%d", points);
	YsGlDrawFontBitmap16x20("Points: ");

	glRasterPos2i(720, 30);
	YsGlDrawFontBitmap16x20(pointstxt);
}

//Player
void GameData::DrawPlayer(void)
{
	//Left and Right
	if ((FsGetKeyState(FSKEY_RIGHT) || FsGetKeyState(FSKEY_LEFT)) && jumpdrawingstate == 0 && vy >= 0)
	{
		int bounceAnim = 0;

		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		if (walktimer > 15)
		{
			glBindTexture(GL_TEXTURE_2D, OverworldTextureId[2]);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, OverworldTextureId[3]);

		}
		//walk animations
		if ((walktimer >= 0 && walktimer < 3) || (walktimer >= 15 && walktimer < 18))
		{
			bounceAnim = 5;
		}
		else if ((walktimer >= 3 && walktimer < 5) || (walktimer >= 18 && walktimer < 20) || (walktimer >= 28 && walktimer < 30) || (walktimer >= 13 && walktimer < 15))
		{
			bounceAnim = 2;
		}
		else if ((walktimer == 5) || (walktimer == 20) || (walktimer == 27) || (walktimer == 12))
		{
			bounceAnim = 1;
		}
		else
		{
			bounceAnim = 0;
		}

		glBegin(GL_QUADS);

		if (FsGetKeyState(FSKEY_RIGHT))
		{
			glTexCoord2d(0.0, 0.0);
			glVertex2i(0 + px - bounceAnim, 0 + py + bounceAnim);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(0 + px - bounceAnim, imgdat.png[2].hei + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(imgdat.png[2].wid + px + bounceAnim, imgdat.png[2].hei + py);

			glTexCoord2d(1.0, 0.0);
			glVertex2i(imgdat.png[2].wid + px + bounceAnim, 0 + py + bounceAnim);

			glEnd();
		}
		else
		{
			glTexCoord2d(1.0, 0.0);
			glVertex2i(0 + px - bounceAnim, 0 + py + bounceAnim);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(0 + px - bounceAnim, imgdat.png[2].hei + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(imgdat.png[2].wid + px + bounceAnim, imgdat.png[2].hei + py);

			glTexCoord2d(0.0, 0.0);
			glVertex2i(imgdat.png[2].wid + px + bounceAnim, 0 + py + bounceAnim);

			glEnd();
		}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	//Jump
	else if (jumpdrawingstate == 1 || vy < 0)
	{
		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, OverworldTextureId[4]);

		glBegin(GL_QUADS);

		if (facestate == 1)
		{
			glTexCoord2d(0.0, 0.0);
			glVertex2i(0 + px, 0 + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(0 + px, imgdat.png[4].hei + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(imgdat.png[4].wid + px, imgdat.png[4].hei + py);

			glTexCoord2d(1.0, 0.0);
			glVertex2i(imgdat.png[4].wid + px, 0 + py);
		}
		else if (facestate == 2)
		{
			glTexCoord2d(1.0, 0.0);
			glVertex2i(0 + px, 0 + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(0 + px, imgdat.png[4].hei + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(imgdat.png[4].wid + px, imgdat.png[4].hei + py);

			glTexCoord2d(0.0, 0.0);
			glVertex2i(imgdat.png[4].wid + px, 0 + py);
		}

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	//Idle
	else
	{
		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, OverworldTextureId[1]);

		glBegin(GL_QUADS);

		if (facestate == 1)
		{
			glTexCoord2d(0.0, 0.0);
			glVertex2i(0 + px, 0 + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(0 + px, imgdat.png[1].hei + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(imgdat.png[1].wid + px, imgdat.png[1].hei + py);

			glTexCoord2d(1.0, 0.0);
			glVertex2i(imgdat.png[1].wid + px, 0 + py);
		}
		else if (facestate == 2)
		{
			glTexCoord2d(1.0, 0.0);
			glVertex2i(0 + px, 0 + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(0 + px, imgdat.png[1].hei + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(imgdat.png[1].wid + px, imgdat.png[1].hei + py);

			glTexCoord2d(0.0, 0.0);
			glVertex2i(imgdat.png[1].wid + px, 0 + py);
		}

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
}
void GameData::MovePlayer()
{
	//key control
	if (FsGetKeyState(FSKEY_RIGHT))
	{
		facestate = 1;
		++walktimer;
		px += 5;
		if (walktimer >= 30)
		{
			walktimer = 0;
		}
	}
	if (FsGetKeyState(FSKEY_LEFT) && px > 0)
	{
		facestate = 2;
		++walktimer;
		if (walktimer >= 30)
		{
			walktimer = 0;
		}
		px -= 5;
	}
	if (FsGetKeyState(FSKEY_UP) && py > -140 && vy == 0)
	{
		vy = 20;
		jumpstate = 1;
		jumpdrawingstate = 1;
	}
	//jump
	if (jumpstate == 1)
	{
		Gravity();
	}

	if (px >= 800 && gameState == 1)
	{
		gameState = 2;
	}
	CheckCollision();
}

//Collision
void GameData::Gravity()
{
	py -= vy;
	vy -= 0.1 * 9.81;
}
void GameData::CheckCollision()
{
	if (((px > platx1 - 80 && px < platx1 + 220) && (py < platy1 - 100 && py > platy1 - 130)) && vy < 0)
	{
		vy = 0;
		jumpdrawingstate = 0;
	}

	if (((px > platx2 - 80 && px < platx2 + 220) && (py < platy2 - 100 && py > platy2 - 130)) && vy < 0)
	{
		vy = 0;
		jumpdrawingstate = 0;
	}

	if (((px > platx3 - 80 && px < platx3 + 220) && (py < platy3 - 100 && py > platy3 - 130)) && vy < 0)
	{
		vy = 0;
		jumpdrawingstate = 0;
	}

	else if (py > 400)
	{
		vy = 0;
		jumpstate = 0;
		py = 400;
		jumpdrawingstate = 0;
	}
}

//Portal
void GameData::DrawPortal()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, OverworldTextureId[8]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0 + 700, 0 + 400);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0 + 700, imgdat.png[8].hei + 400);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[8].wid + 700, imgdat.png[8].hei + 400);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[8].wid + 700, 0 + 400);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

//Sound
int GameData::playMusic()
{
	if (YSOK != wav.LoadWav("media/overworld_music.wav"))
	{
		printf("failed to load music");
		return 1;
	}
	player.Start();
	player.PlayOneShot(wav);
	return 0;
}

//Render
void RenderOverworld(void* incoming)
{
	GameData& game = *(GameData*)incoming;
	OverworldImageData imgdat;

	if (true == game.imgdat.firstRenderingPass)  // Do it only once.
	{
		game.imgdat.firstRenderingPass = false; // And, don't do it again.

		for (int i = 0; i < 13;++i)
		{
			glGenTextures(1, &OverworldTextureId[i]);  // Reserve one texture identifier
			glBindTexture(GL_TEXTURE_2D, OverworldTextureId[i]);  // Making the texture identifier current (or bring it to the deck)

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D
			(GL_TEXTURE_2D,
				0,    // Level of detail
				GL_RGBA,
				game.imgdat.png[i].wid,
				game.imgdat.png[i].hei,
				0,    // Border width, but not supported and needs to be 0.
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				game.imgdat.png[i].rgba);
		}
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//setup
	game.DrawBG();
	game.PointCount();

	game.DrawPlatforms();
	game.DrawCoins();
	game.DrawPointCount();

	//Play game
	switch (game.gameState)
	{
	case 0: //fade in
		game.DrawPlayer();
		game.GeneratePlatforms();
		game.GenerateCoins();
		game.ResetScreen();
		break;

	case 1: //game play
		game.DrawPlayer();
		game.MovePlayer();
		break;

	case 2: //fade out
		game.GeneratePlatforms();
		game.GenerateCoins();
		game.ResetScreen();
		break;

	case 3: //fade out to last screen + generate portal
		game.GeneratePlatforms();
		game.GenerateCoins();
		game.DrawPortal();
		game.DrawPlayer();
		game.ResetScreen();
		break;

	case 4: //spawn minigame
		game.DrawPortal();
		game.DrawPlayer();
		game.MovePlayer();
		break;
	}

	FsPollDevice();
	FsSwapBuffers();
}

void GameData::Initialize(void) {

	//inital player positon
	px = 0;
	py = 400;

	imgdat.firstRenderingPass = true;

	//Images
	imgdat.png[0].Decode("media/BG.png");
	imgdat.png[1].Decode("media/Idle.png");
	imgdat.png[2].Decode("media/WalkA.png");
	imgdat.png[3].Decode("media/WalkB.png");
	imgdat.png[4].Decode("media/Jump.png");
	imgdat.png[5].Decode("media/Platform.png");
	imgdat.png[6].Decode("media/Platform.png");
	imgdat.png[7].Decode("media/Platform.png");
	imgdat.png[8].Decode("media/Portal.png");
	imgdat.png[9].Decode("media/moon_coin.png");
	imgdat.png[10].Decode("media/moon_coin.png");
	imgdat.png[11].Decode("media/moon_coin.png");

	vy = 0.0;
	facestate = 1;
	jumpstate = 0;
	jumpdrawingstate = 0;
	platstate = 0;
	coinvisState = 0;

	//coin exists or not
	coinstate1 = 1;
	coinstate2 = 1;
	coinstate3 = 1;

	//point total
	level = 0;
	points = 0;

	//1, 2,3
	walktimer = 0;

	gameState = 0;
	terminate = false;

}

void GameData::Run(void) {

	srand(time(NULL));

	// OverworldImageData imgdat;
	GameData game;
	game.Initialize();
	game.playMusic();
	FsRegisterOnPaintCallBack(RenderOverworld, &game);
	std::tie(game.level, game.points) = game.GetData(game.level, game.points);

	for (;;)
	{
		FsPollDevice();
		auto key = FsInkey();

		if (FsGetKeyState(FSKEY_ESC))
		{
			// game.SaveGame(game.level, game.points);
			std::cout << "\npressed esc" << std::endl;
			terminate = true;
			break;
		}

		if (game.gameState == 4 && game.px >= 650 && game.py >= 400) {
			game.SaveGame(game.level, game.points);
			std::cout << "At portal, now leaving overworld." << std::endl;
			terminate = true;
			break;
		}
		FsPushOnPaintEvent();
		FsSleep(15);
	}
}