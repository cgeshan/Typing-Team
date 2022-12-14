#ifndef MENU_IS_INCLUDED
#define MENU_IS_INCLUDED
/*{*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <tuple>
#include "yspng.h"

class Menu
{
public:
	YsRawPngDecoder png[16]; //Change to 16 if add remainder of images

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

	double x, y, dt, tx1, tx2, titly1, titly2, bobv;
	int move, move2, bob;

	int level;
	int points;
	void SaveGame(int level, int points);
	std::tuple <int, int> GetData(int level, int points);
	void DrawPointCount();

	void Initialize(void);
	int playMusic(void);
	void drawRover(void);
	void drawBackground(int bgnum);
	void drawTitle(void);
	void drawOverworldButton(int, int);
	void drawResetButton(int, int);
	void drawTutorialButton(int, int);
	void drawLevel1(int, int, bool, bool);
	void drawLevel2(int, int, bool, bool);
	void drawLevel3(int, int, bool, bool);
	void drawLevel4(int, int, bool, bool);
	void LoadingGame(int level);
	void ResetGame(bool& l1, bool& l2, bool& l3, bool& l4);

};

/*}*/
#endif
