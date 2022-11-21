#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"

/*
Pictures:
0: BG, 1: Idle, 2: WalkA, 3: WalkB, 4:Jump

Think I need to draw a minigame "Portal"
*/

GLuint texId[10];

class ImageData
{
public:
	bool firstRenderingPass;
	YsRawPngDecoder png[10];
};

class GameData
{
public:
	ImageData imgdat;

	//Reset
	void ResetScreen();
	int screencount = 0;

	//BG
	void DrawBG();
	void DrawFadeOut(int alphacount);
	int alphacount = 0;

	//Platform 
	void DrawPlatforms();
	void GeneratePlatforms();
	void CheckCollision();
	int platx1, platx2, platx3, platy1, platy2, platy3;
	
	//Player Movement
	void DrawPlayer();
	void MovePlayer();
	void Gravity();
	double px = 0;
	double py = 0;
	double vy = 20;
	int facestate = 1;
	int jumpstate = 0;
	int walktimer = 0;

	//Minigame Door Spawn
	void DrawPortal();

	//Collectibles

	//GameState
	int gameState = 0;
};

//BG Items
void GameData::DrawBG()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId[0]);

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
		gameState = 0;
	}

	else if (alphacount <= -250 && gameState == 0)
	{
		px = 0;
		py = 400;
		alphacount = 0;
		gameState = 1;
	}

	if (screencount == 2)
	{
		gameState = 3;
	}
}
void GameData::DrawPlatforms()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId[5]);

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


	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);

	//glColor4d(1.0, 1.0, 1.0, 1.0);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texId[6]);

	//glBegin(GL_QUADS);

	//glTexCoord2d(0.0, 0.0);
	//glVertex2i(0 + platx2, 0 + platy2);

	//glTexCoord2d(0.0, 1.0);
	//glVertex2i(0 + platx2, 120 + platy2);

	//glTexCoord2d(1.0, 1.0);
	//glVertex2i(260 + platx2, 120 + platy2);

	//glTexCoord2d(1.0, 0.0);
	//glVertex2i(260 + platx2, 0 + platy2);

	//glEnd();

	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
}
void GameData::GeneratePlatforms()
{
	platx1 = rand() % 800;
	//platx2 = rand() % 800;
	//platx3 = rand() % 800;

	platy1 = rand() % 400 + 100;
	//platy2 = rand() % 400;
	//platy3 = rand() % 400;
}

//Player
void GameData::DrawPlayer(void)
{
	//Left and Right
	if((FsGetKeyState(FSKEY_RIGHT) || FsGetKeyState(FSKEY_LEFT)) && jumpstate == 0)
	{
		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		if(walktimer > 15)
		{
			glBindTexture(GL_TEXTURE_2D, texId[2]);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, texId[3]);

		}

		glBegin(GL_QUADS);

		if(FsGetKeyState(FSKEY_RIGHT))
		{
			glTexCoord2d(0.0, 0.0);
			glVertex2i(0 + px, 0 + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(0 + px, imgdat.png[2].hei + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(imgdat.png[2].wid + px, imgdat.png[2].hei + py);

			glTexCoord2d(1.0, 0.0);
			glVertex2i(imgdat.png[2].wid + px, 0 + py);

			glEnd();
		}
		else
		{
			glTexCoord2d(1.0, 0.0);
			glVertex2i(0 + px, 0 + py);

			glTexCoord2d(1.0, 1.0);
			glVertex2i(0 + px, imgdat.png[2].hei + py);

			glTexCoord2d(0.0, 1.0);
			glVertex2i(imgdat.png[2].wid + px, imgdat.png[2].hei + py);

			glTexCoord2d(0.0, 0.0);
			glVertex2i(imgdat.png[2].wid + px, 0 + py);

			glEnd();
		}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	//Jump
	else if (jumpstate == 1)
	{
		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texId[4]);

		glBegin(GL_QUADS);

		if(facestate == 1)
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
		glBindTexture(GL_TEXTURE_2D, texId[1]);

		glBegin(GL_QUADS);

		if(facestate == 1)
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
	if (FsInkey() == FSKEY_UP && py > -140)
	{
		walktimer = 0;
		jumpstate = 1;
	}

	//jump
	if (jumpstate == 1)
	{
		walktimer = 0;
		Gravity();
	}
	if (px >= 800 && gameState == 1)
	{
		gameState = 2;
	}

	//check collision
	CheckCollision();
}

//Collision
void GameData::Gravity()
{
	py -= vy;
	vy -= 0.1 * 9.81;

	if (py >= 399)
	{
		py = 400;
		vy = 20;
		jumpstate = 0;
	}
}
void GameData::CheckCollision()
{
	if ((px > platx1 - 100 && px < platx1 + 200 ) && (py < platy1 - 120 && py > platy1 - 125))
	{
		vy = 0;
	}
}

//Portal
void GameData::DrawPortal()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId[7]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0 + 700, 0 + 400);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0 + 700, imgdat.png[7].hei + 400);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[7].wid + 700, imgdat.png[7].hei + 400);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[7].wid + 700, 0 + 400);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Render(void* incoming)
{
	GameData& game = *(GameData*)incoming;
	ImageData imgdat;

	if (true == game.imgdat.firstRenderingPass)  // Do it only once.
	{
		game.imgdat.firstRenderingPass = false; // And, don't do it again.

		for (int i = 0; i < 10 ;++i)
		{
			glGenTextures(1, &texId[i]);  // Reserve one texture identifier
			glBindTexture(GL_TEXTURE_2D, texId[i]);  // Making the texture identifier current (or bring it to the deck)

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

	//Play game
	switch (game.gameState)
	{
	case 0: //fade in
		game.DrawPlayer();
		game.ResetScreen();
		game.GeneratePlatforms();
		break;

	case 1: //game play
		game.DrawPlatforms();
		game.DrawPlayer();
		game.MovePlayer();
		break;

	case 2: //fade out
		game.ResetScreen();
		//game.DrawPlatforms();
		break;

	case 3: //spawn minigame
		game.DrawPortal();
		game.DrawPlayer();
		game.MovePlayer();
		break;
	}

	FsSwapBuffers();
}
int main(void)
{
	FsChangeToProgramDir();
	srand(time(NULL));

	ImageData imgdat;
	GameData game;

	//inital player positon
	game.px = 0;
	game.py = 400;

	game.imgdat.firstRenderingPass = true;

	//Images
	game.imgdat.png[0].Decode("BG.png");
	game.imgdat.png[1].Decode("Idle_Lineart.png");
	game.imgdat.png[2].Decode("WalkA_Lineart.png");
	game.imgdat.png[3].Decode("WalkB_Lineart.png");
	game.imgdat.png[4].Decode("Jump_Lineart.png");
	game.imgdat.png[5].Decode("Platform.png");
	game.imgdat.png[6].Decode("Platform.png");
	game.imgdat.png[7].Decode("Portal.png");

	FsOpenWindow(0, 0, 800, 600, 1);
	FsRegisterOnPaintCallBack(Render, &game);

	for (;;)
	{
		FsPollDevice();
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			//go to cliffs code 
			break;
		}
		FsPushOnPaintEvent();
		FsSleep(25);
	}
	return 0;
}