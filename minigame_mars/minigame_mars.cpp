// Charlotte Avra
// 24-780 - Engineering Computation 
// Project - Minigame 1: Mars
// November 22, 2022

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"

class Mars
{
public:
	YsRawPngDecoder png[4];

	// player variables
	double angle;
	int rover, start_x, start_y; 
	double rover_x, rover_y;
	double vel, vel_x, vel_y, dt;

	// obstacle variables
	double x1, y1, x2, y2; // each obstacle is a png with upper left corner coordineates (x, y)
	int speed, height;
	int seed[20]; // empty array of 20 values 
	int index;
	int initiate_jump;

	void Initialize(void);
	void drawBackground();
	void drawForeground();
	void drawRover(void);
	void drawObstacles(char str[]);
	void moveObstacle1(void);
	void moveObstacle2(void);
	void jumpRover(void); 
	int checkObstacle(void);
};

void Mars::Initialize(void)
{
	// scene variables
	const double YS_PI = 3.14115927;
	angle = (YS_PI / 10.0); // angle of the mountain
	
	// rover variables
	rover = 0; // rover is not jumping
	start_x = 100, start_y = 430; // starting position of rover and where to return after jump
	rover_x = start_x;
	rover_y = start_y;
	vel = 300; // initial velocity of rover 
	vel_x = vel * sin(angle);
	vel_y = -1 * vel * cos(angle);
	dt = 0.1; 

	// obstacle variables
	srand(time(NULL)); // set seed for the random-number generator
	x1 = 800 + rand() % 201; // move obstacle off screen to a random variable x between 800 and 1,000 
	x2 = x1 + 400; // second obstacle is always 300 pixels to the right of the first obstacle  
	y1 = 435 + (tan(angle) * x1); // y=b+mx based on angle of the mountain
	y2 = 435 + (tan(angle) * x1); // y=b+mx based on angle of the mountain
	speed = 5; 
	height = 130;
	initiate_jump = 0; // 0: Enter has not been selected or word typed incorrectly 1: jump initiated, waiting to jump till obstacle is close enough

	// image data
	png[0].Decode("mars_background.png");	png[0].Flip();
	if (0 == png[0].wid || 0 == png[0].hei) {printf("Failed to load mars_background.png.\n");}

	png[1].Decode("mars_rover_rotated.png");	png[1].Flip();
	if (0 == png[1].wid || 0 == png[1].hei) { printf("Failed to load mars_rover_rotated.png.\n");}

	png[2].Decode("rock1_rotated.png");	png[2].Flip();
	if (0 == png[2].wid || 0 == png[2].hei) { printf("Failed to load rock1_rotated.png.\n");}

	png[3].Decode("rock2_rotated.png");	png[3].Flip();
	if (0 == png[3].wid || 0 == png[3].hei) { printf("Failed to load rock2_rotated.png.\n");}
}

void Mars::drawBackground(void)
{
	glShadeModel(GL_SMOOTH); // gradient background 
	glBegin(GL_QUADS);

	glColor3ub(255, 235, 198);
	glVertex2i(0, 0);

	glColor3ub(255, 235, 198);
	glVertex2i(800, 0);

	glColor3ub(255, 248, 235);
	glVertex2i(800, 400);

	glColor3ub(255, 248, 235);
	glVertex2i(0, 400);

	glEnd();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
	glRasterPos2i(0, 600 - 1); 
	glDrawPixels(png[0].wid, png[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);
	glDisable(GL_BLEND); 
}

void Mars::drawForeground()
{
	glBegin(GL_TRIANGLES);
	glColor3ub(236, 157, 117);
	glVertex2i(0, 370);
	glVertex2i(0, 600);
	glVertex2i((600 - 370) / tan(angle), 600);
	glEnd();
}

void Mars::drawRover()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(rover_x, rover_y);
	glDrawPixels(png[1].wid, png[1].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[1].rgba);
	glDisable(GL_BLEND);
}

void Mars::drawObstacles(char str[])
{
	// draw rocks
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glRasterPos2i(x1, y1);
	glDrawPixels(png[2].wid, png[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);

	glRasterPos2i(x2, y2);
	glDrawPixels(png[3].wid, png[3].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[3].rgba);

	glDisable(GL_BLEND);

	// text on rocks
	glColor3ub(255, 255, 255);
	glRasterPos2d(x1 + 50, y1 - 50);
	YsGlDrawFontBitmap20x32(str);
	glFlush();

	glColor3ub(255, 255, 255);
	glRasterPos2d(x2 + 50, y2 - 50);
	YsGlDrawFontBitmap20x32(str);
	glFlush();
}

void Mars::moveObstacle1()
{
	if (x1 < -100)
	{
		srand(time(NULL)); // set seed for the random-number generator
		x1 = 800 + rand() % 201; // move obstacle off screen to a random variable x between 800 and 1,000
	}

	else
	{
		x1 -= speed * cos(angle);
	}

	// update y values   
	y1 = 435 + (tan(angle) * x1); // y=b+mx based on angle of the mountain
}

void Mars::moveObstacle2()
{
	if (x2 < -100)
	{
		srand(time(NULL)); // set seed for the random-number generator
		x2 = 800 + rand() % 201; // move obstacle off screen to a random variable x between 800 and 1,000 
	}

	else
	{
		x2 -= speed * cos(angle);
	}

	// update y values   
	y2 = 435 + (tan(angle) * x2); // y=b+mx based on angle of the mountain
}

void Mars::jumpRover()
{
	if (rover_y > start_y) // if rover goes below starting position, reset initial positions to integer values  
	{
		rover_x = start_x;
		rover_y = start_y;
		rover = 0; // update state to 'not jumping'
	}
	
	else
	{
		rover_x += vel_x * dt;
		rover_y += vel_y * dt;

		double accel_x = -1 * 98 * sin(angle); // need player to return to same x value after jump so gravity is in both x and y directions
		double accel_y = 98 * cos(angle); // assuming 10 pixels per meter, gravity should be 98 pixels/s^2 

		vel_x += dt * accel_x;
		vel_y += dt * accel_y;
	}
}

int Mars::checkObstacle()
{
	if (rover_x - 200 > x1 && rover_y > y1 || rover_x - 200 > x2 && rover_y > y2)
	{
		return 1;
	}
	return 0;
}

int main(void)
{
	// initialize class variables for Mars minigame 
	Mars mars;
	mars.Initialize();

	char str[] = { 'c', 'o', 'w' }; // test string

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

			if (mars.rover == 0) // if rover is not jumping  **********and word is typed correctly********** 
			{
				//mars.vel_x = mars.vel * sin(mars.angle);
				//mars.vel_y = -1 * mars.vel * cos(mars.angle);
				//mars.rover = 1;
				mars.initiate_jump = 1; 
			}
			break;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mars.drawBackground();
		mars.drawForeground();
		mars.drawRover(); 
		mars.drawObstacles(str); 
		mars.moveObstacle1();
		mars.moveObstacle2();

		if (mars.initiate_jump == 1) // jump initiated meaning word was typed correctly and user selected 'Enter' 
		{
			if ((mars.x1 - mars.rover_x < 80) || (mars.x2 - mars.rover_x < 80)) // rover is close enough to an obstacle
			{
				mars.vel_x = mars.vel * sin(mars.angle); // initial velocity of jump
				mars.vel_y = -1 * mars.vel * cos(mars.angle);
				mars.rover = 1; // set rover to jumping
				mars.initiate_jump = 0; // return to no jump initiated to wait for next correctly typed word
			}
		}
		
		if (mars.rover == 1) // if rover is jumping
		{
			mars.jumpRover(); // continue trajectory
		}

		FsSwapBuffers();
		FsSleep(25); // 25 milliseconds

		// check if rover has hit an obstacle
		if (mars.checkObstacle() == 1)
		{
			terminate = 1;
			time_final = time(NULL); // final time 
			break;
		}
	}

	return 0;
}