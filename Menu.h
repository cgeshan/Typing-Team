#ifndef MENU_IS_INCLUDED
#define MENU_IS_INCLUDED
/*{*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "yspng.h"

class Menu
{
public:
	YsRawPngDecoder png[15]; //Change to 16 if add remainder of images

	double x, y, dt,tx1, tx2, titly1, titly2, bobv;
	int move, move2, bob;
	int level;

	void Initialize(void);
	void drawRover(void);
	void drawBackground(void);
	void drawTitle(void);
	void drawOverworldButton(int, int);
	void drawResetButton(int, int);
	void drawTutorialButton(int, int);
	void drawLevel1(int,int, bool, bool);
	void drawLevel2(int, int, bool, bool);
	void drawLevel3(int, int, bool, bool);
	void drawLevel4(int, int, bool, bool);

};

/*}*/
#endif

