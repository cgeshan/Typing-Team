// Charlotte Avra
// 24-780 - Engineering Computation 
// Project - Minigame 1: Rockets
// November 22, 2022

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"

class Rockets
{
public:
	YsRawPngDecoder png[3];

	double x1, y1, x2, y2;
	int vel1, vel2; 
	int state1, state2;

	void Initialize(void);
	void drawBackground();
	void drawRocket(void);
	void moveRocket1(void);
	void moveRocket2(void);
	void speedRocket1(void);
	void speedRocket2(void);
	int checkRockets(void);
};

void Rockets::Initialize()
{
	x1 = 150;
	x2 = 450;
	y1 = 600; // rockets both start at the bottom of the screen
	y2 = 900; 

	vel1 = 5; // initial velocities for rockets  
	vel2 = 5; 

	state1 = 0; // state becomes one when word is typed correctly 
	state2 = 0; 

	// image data
	png[0].Decode("space.png");	png[0].Flip();
	if (0 == png[0].wid || 0 == png[0].hei) { printf("Failed to load space.png.\n"); }

	png[1].Decode("Rocket1.png");	png[1].Flip();
	if (0 == png[1].wid || 0 == png[1].hei) { printf("Failed to load Rocket1.png.\n"); }

	png[2].Decode("Rocket2.png");	png[2].Flip();
	if (0 == png[2].wid || 0 == png[2].hei) { printf("Failed to load Rocket2.png.\n"); }
}

void Rockets::drawBackground()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(0, 600 - 1);
	glDrawPixels(png[0].wid, png[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);
	glDisable(GL_BLEND);
}

void Rockets::drawRocket()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glRasterPos2i(x1, y1);
	glDrawPixels(png[1].wid, png[1].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[1].rgba);
	glRasterPos2i(x2, y2);
	glDrawPixels(png[2].wid, png[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);

	glDisable(GL_BLEND);
}

void Rockets::moveRocket1()
{
	y1 -= vel1;
}

void Rockets::moveRocket2()
{
	y2 -= vel2;
}

void Rockets::speedRocket1()
{
	vel1 += 4; 

	if (y1 < -10)
	{
		vel1 = 5; // return to original velocity
		state1 = 0; 
		y1 = 800; // reset y
		x1 = (rand() % 601) + 100; // random value for x between 100 and 700
	}
}

void Rockets::speedRocket2()
{
	vel2 += 4; 

	if (y2 < 0)
	{
		vel2 = 5; // return to original velocity
		state2 = 0; 
		y2 = 800; // reset y
		x2 = (rand() % 601) + 100; // random value for x between 100 and 700
	}
}

int Rockets::checkRockets()
{
	if ((y1 < 0 && state1 != 1) || (y2 < 0 && state2 != 1))
	{
		return 1; 
	}
	else
	{
		return 0; 
	}
}

int main(void)
{
	// initialize class variables for Mars minigame 
	Rockets rockets;
	rockets.Initialize();

	FsOpenWindow(0, 0, 800, 600, 1);


	// initialize time variables 
	int time_init, time_final = 0;
	time_init = time(NULL); // time how long the player lasts

	int terminate = 0;
	while (terminate == 0) // while the rover has not hit an obstacle
	{
		FsPollDevice();
		int key = FsInkey();

		switch (key)
		{
		case FSKEY_ESC:
			terminate = 1;
			break;

		case FSKEY_ENTER: // this should change to if user clicks enter and the word is correct, then do stuff in if statemtent 

			if (rockets.state1 == 0) // if rocket is not speeding **********and word is typed correctly**********
			{
				rockets.state1 = 1;
			}
			else
			{
				rockets.state2 = 1; 
			}
			break;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		rockets.drawBackground();
		rockets.drawRocket();
		rockets.moveRocket1();
		rockets.moveRocket2();

		if (rockets.state1 == 1)
		{
			rockets.speedRocket1();
		}
		if (rockets.state2 == 1)
		{
			rockets.speedRocket2();
		}
		if (rockets.checkRockets() == 1)
		{
			terminate = 1;
			time_final = time(NULL); // final time 
			break;
		}
		
		FsSwapBuffers();
		FsSleep(25); // 25 milliseconds
	}
	return 0; 
}