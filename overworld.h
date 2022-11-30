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
	YsRawPngDecoder png[10];
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

	//Collectibles

	//GameState
	int gameState;
	bool terminate = false;

	void Initialize(void);
	void Run(void);
};

/*}*/
#endif

