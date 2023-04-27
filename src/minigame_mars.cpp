// Charlotte Avra
// 24-780 - Engineering Computation 
// Project - Minigame 1: Mars
// November 22, 2022

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include "minigame_mars.h"
#include "textinput.h"
#include "textstring.h"
#include "tutorial.h"

//Point Call (wip)
std::tuple <int, int> Mars::GetData(int level, int points)
{
	Mars m;
	std::ifstream infile;
	infile.open("media/game.txt", std::ifstream::in);
	if (infile.good()) {
		infile >> m.level >> m.points;
	}

	std::cout << "level -> " << m.level << "\npoints -> " << m.points << std::endl;

	return std::make_tuple(m.level, m.points);

}

void Mars::SaveGame(int level, int points) {
	FILE* fp = fopen("media/game.txt", "w");

	if (nullptr != fp) {
		FILE* File;
		File = fopen("media/game.txt", "w+");
		fprintf(File, "%i %i", level, points);
		fclose(File);
	}
}

void Mars::Initialize(void)
{
	term = false;
	wordCount = 0;
	randWord = (rand() % (65));
	changeWord = false;
	std::tie(level, points) = GetData(level, points);

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
	// x2 = x1 + 800; // second obstacle is always 300 pixels to the right of the first obstacle  
	y1 = 435 + (tan(angle) * x1); // y=b+mx based on angle of the mountain
	// y2 = 435 + (tan(angle) * x1); // y=b+mx based on angle of the mountain
	speed = 5.0;
	height = 130;
	numLives = 3;
	prevCheck = 0;
	initiate_jump = 0; // 0: Enter has not been selected or word typed incorrectly 1: jump initiated, waiting to jump till obstacle is close enough

	// image data
	png[0].Decode("media/mars_background.png");	png[0].Flip();
	if (0 == png[0].wid || 0 == png[0].hei) { printf("Failed to load mars_background.png.\n"); }

	png[1].Decode("media/mars_rover_rotated.png");	png[1].Flip();
	if (0 == png[1].wid || 0 == png[1].hei) { printf("Failed to load mars_rover_rotated.png.\n"); }

	png[2].Decode("media/rock1_rotated.png");	png[2].Flip();
	if (0 == png[2].wid || 0 == png[2].hei) { printf("Failed to load rock1_rotated.png.\n"); }

	png[3].Decode("media/rock2_rotated.png");	png[3].Flip();
	if (0 == png[3].wid || 0 == png[3].hei) { printf("Failed to load rock2_rotated.png.\n"); }

	playMusic();
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(0, 600 - 1);
	glDrawPixels(png[0].wid, png[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);
	glDisable(GL_BLEND);
}

void Mars::drawRemainingLives() {

	std::string strNum = std::to_string(numLives);
	std::string strLives = "Remaining Lives: " + strNum;
	char livesDisplay[256];
	strcpy(livesDisplay, strLives.c_str());

	glRasterPos2i(500, 62);
	YsGlDrawFontBitmap16x20(livesDisplay);

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glRasterPos2i(x1, y1);
	glDrawPixels(png[2].wid, png[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);
	// glRasterPos2i(x2, y2);
	// glDrawPixels(png[3].wid, png[3].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[3].rgba);

	glDisable(GL_BLEND);
	// text on rocks
	if (changeWord == false) {
		glColor3ub(255, 255, 255);
		glRasterPos2d(x1 + 50, y1 - 50);
		YsGlDrawFontBitmap20x32(str);
	}

	glFlush();

	// glColor3ub(255, 255, 255);
	// glRasterPos2d(x2 + 50, y2 - 50);
	// YsGlDrawFontBitmap20x32(str);
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
	// if (rover_x > x1 && rover_y > y1 || rover_x > x2 && rover_y > y2)
	if (rover_x > x1 && rover_y > y1)
	{
		return 1;
	}
	return 0;
}

void Mars::drawTargetWord(char letters[]) {
	glRasterPos2i(100, 32);
	YsGlDrawFontBitmap16x24(letters);
}

void Mars::drawYouLost() {
	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();
		drawForeground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Sorry, you ran out of lives...");

		glRasterPos2i(92, 92);
		YsGlDrawFontBitmap16x24(":-(");

		FsSwapBuffers();
		FsSleep(20);
	}

	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();
		drawForeground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Mars::drawYouWon() {
	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();
		drawForeground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Congratulations! You Won.");

		glRasterPos2i(92, 92);
		YsGlDrawFontBitmap16x24("Now unlocking next level...  :-)");

		FsSwapBuffers();
		FsSleep(20);
	}

	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();
		drawForeground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Mars::ReturnToMenu(void) {
	for (int i = 0; i < 50; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawBackground();
		drawForeground();

		glColor3ub(236, 157, 117);
		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Mars::DrawPointCount()
{
	glRasterPos2i(600, 30);
	char pointstxt[256];
	std::sprintf(pointstxt, "%d", points);
	YsGlDrawFontBitmap16x20("Points: ");

	glRasterPos2i(720, 30);
	YsGlDrawFontBitmap16x20(pointstxt);
}

//Sound
int Mars::playMusic()
{
	if (YSOK != marsWav.LoadWav("media/mars_music.wav"))
	{
		printf("failed to load music");
		return 1;
	}
	marsPlayer.Start();
	marsPlayer.PlayOneShot(marsWav);
	marsPlayer.SetVolume(marsWav, 0.8);
	return 0;
}

void Mars::RunOneStep(void) {

	FsPollDevice();
	auto key = FsInkey();
	auto c = FsInkeyChar();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::string targetWord = wordBank[randWord];
	auto len = targetWord.size();
	char letters[256];
	strcpy(letters, targetWord.c_str());

	inputStr = textInput.str.GetPointer();
	textInput.RunOneStep(key, c);

	drawBackground();
	drawForeground();
	drawRover();

	drawObstacles(letters);
	moveObstacle1();

	glColor3ub(236, 157, 117);
	drawRemainingLives();
	DrawPointCount();
	textInput.Draw();

	// initialize time variables 
	int time_init, time_final = 0;
	time_init = time(NULL); // time how long the player lasts

	if (FsGetKeyState(FSKEY_ESC)) {
		ReturnToMenu();
		term = true;
	}

	if (FSKEY_ENTER == key) {
		if (inputStr.GetPointer() != targetWord) {
			points -= 10;
		}
		if (inputStr.GetPointer() == targetWord && rover == 0) {

			points += 20;
			initiate_jump = 1;

			auto completeTime = FsPassedTime();
			std::cout << "Completion time: " << completeTime * 0.001 << " seconds." << std::endl;

		}
		textInput.str.CleanUp();
		inputStr.CleanUp();
	}

	if (initiate_jump == 1) // jump initiated meaning word was typed correctly and user selected 'Enter' 
	{
		changeWord = true;
		// if ((x1 - rover_x < 80) || (x2 - rover_x < 80)) // rover is close enough to an obstacle
		if ((x1 - rover_x < 80))
		{
			vel_x = vel * sin(angle); // initial velocity of jump
			vel_y = -1 * vel * cos(angle);
			rover = 1; // set rover to jumping
			initiate_jump = 0; // return to no jump initiated to wait for next correctly typed word

			speed += 0.05;

		}
	}

	if (rover == 1) // if rover is jumping
	{
		jumpRover();
	}

	// check if rover has hit an obstacle
	if (prevCheck == 0 && checkObstacle() == 1 && initiate_jump == 0)
	{
		// std::cout << "Collision" << std::endl;
		time_final = time(NULL); // final time 
		numLives--;
		points -= 5;
	}

	prevCheck = checkObstacle();

	if (numLives == 0) {
		//You Lost animation
		drawYouLost();
		if (level == 1) {
			SaveGame(1, points);
		}
		else if (level == 2) {
			SaveGame(2, points);
		}
		else if (level == 3) {
			SaveGame(3, points);
		}
		else if (level == 4) {
			SaveGame(4, points);
		}
		term = true;
	}

	if (x1 + png[2].wid <= 100.0 && changeWord == true) {
		if (wordCount < 10) {
			wordCount++;
			randWord = (rand() % (65));
			changeWord = false;
		}
	}

	if (wordCount >= 10) {
		//Winning animation
		drawYouWon();
		std::cout << "level = " << level << std::endl;
		if (level <= 1) {
			SaveGame(1, points);
		}
		term = true;
	}

	FsSwapBuffers();
	// FsSleep(25); // 25 milliseconds
}

