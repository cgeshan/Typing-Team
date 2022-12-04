#ifndef OVERWORLD_IS_INCLUDED
#define OVERWORLD_IS_INCLUDED
/*{*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"


class OverworldImageData
{
public:
	bool firstRenderingPass;
	YsRawPngDecoder png[12];
};

class GameData
{
public:
	OverworldImageData imgdat;

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
	double px;
	double py;
	double vy = 0;
	int facestate, jumpstate, jumpdrawingstate, platstate;
	//1, 2,3
	int walktimer;

	//Minigame Door Spawn
	void DrawPortal();

	//Coins
	void DrawCoins();
	void GenerateCoins();

	int coinx1, coinx2, coinx3, coiny1, coiny2, coiny3;
	int coinstate1, coinstate2, coinstate3;
	int coinvisState;

	//Points
	void PointCount();
	void DrawPointCount();
	int points;

	//GameState
	int gameState;
	bool gameEnd = false;
	bool terminate = false;

	void Initialize(void);
	void Run(void);
};

/*}*/
#endif

