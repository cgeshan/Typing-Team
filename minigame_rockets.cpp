// Charlotte Avra
// 24-780 - Engineering Computation 
// Project - Minigame 1: Rockets
// November 22, 2022

#include <string>
#include "yssimplesound.h"
#include "minigame_rockets.h"
#include "textinput.h"

//Point Call (wip)
std::tuple <int, int> Rockets::GetData(int level, int points)
{
	Rockets r;
	std::ifstream infile;
	infile.open("game.txt", std::ifstream::in);
	if (infile.good()) {
		infile >> r.level >> r.points;
	}

	std::cout << "level -> " << r.level << "\npoints -> " << r.points << std::endl;

	return std::make_tuple(r.level, r.points);

}

void Rockets::SaveGame(int level, int points) {
	FILE* fp = fopen("game.txt", "w");

	if (nullptr != fp) {
		FILE* File;
		File = fopen("game.txt", "w+");
		fprintf(File, "%i %i", level, points);
		fclose(File);
	}
}

void Rockets::Initialize()
{
	x1 = 150;
	x2 = 450;
	y1 = 600; // rockets both start at the bottom of the screen
	y2 = 600;

	vel1 = 4; // initial velocities for rockets  
	vel2 = 4;

	vis1 = 1; // visability state, 1: rocket is on the screen, 0: rocket is not on the screen
	vis2 = 0;

	state1 = 0; // state becomes one when word is typed correctly (rocket speeds to top) 
	state2 = 0;

	numLives = 3;
	prevCheck = 0;

	wordCount = 0;
	randWord = (rand() % (65));
	std::tie(level, points) = GetData(level, points);
	bool terminate = false;

	// image data
	png[0].Decode("space.png");	png[0].Flip();
	if (0 == png[0].wid || 0 == png[0].hei) { printf("Failed to load space.png.\n"); }

	png[1].Decode("Rocket1.png");	png[1].Flip();
	if (0 == png[1].wid || 0 == png[1].hei) { printf("Failed to load Rocket1.png.\n"); }

	png[2].Decode("Rocket2.png");	png[2].Flip();
	if (0 == png[2].wid || 0 == png[2].hei) { printf("Failed to load Rocket2.png.\n"); }

	playMusic();
}

void Rockets::drawBackground()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(0, 600 - 1);
	glDrawPixels(png[0].wid, png[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);
	glDisable(GL_BLEND);
}

void Rockets::drawRocket(char str[], int arraySize)
{
	int start = 0;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (vis1 == 1)
	{
		glRasterPos2i(x1, y1);
		glDrawPixels(png[1].wid, png[1].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[1].rgba);
		glDisable(GL_BLEND);

		glColor3ub(255, 255, 255);
		if (arraySize > 4)
		{
			start = (x1 + 50) - (17.5 * (arraySize - 4));
		}
		else if (arraySize < 4)
		{
			start = (x1 + 50) + (17.5 * (4 - arraySize));
		}
		else
		{
			start = (x1 + 50) + (17.5 * (5 - arraySize));
		}

		glRasterPos2d(start, y1 + 50);
		YsGlDrawFontBitmap20x32(str);
		glFlush();
	}
	if (vis2 == 1)
	{
		glRasterPos2i(x2, y2);
		glDrawPixels(png[2].wid, png[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);

		glColor3ub(255, 255, 255);

		if (arraySize > 4)
		{
			start = (x2 + 90) - (17.5 * (arraySize - 4));
		}
		else if (arraySize < 4)
		{
			start = (x2 + 90) + (17.5 * (4 - arraySize));
		}

		glRasterPos2d(start, y2 + 50);
		YsGlDrawFontBitmap20x32(str);
		glFlush();
	}

}

void Rockets::moveRocket1()
{
	if (vis1 == 1) // only move rocket if it's visable
	{
		y1 -= vel1;
	}

}

void Rockets::moveRocket2()
{
	if (vis2 == 1) // only move rocket if it's visable
	{
		y2 -= vel2;
	}
}

void Rockets::speedRocket1()
{
	vel1 += 4;

	if (y1 < -100)
	{
		vel1 = 5; // return to original velocity
		state1 = 0;
		y1 = 600; // reset y
		x1 = (rand() % 601) + 100; // random value for x between 100 and 700
		vis1 = 0; // rocket is no longer visable
		vis2 = 1; // set other rocket to visable (switch)
		wordCount++;
		randWord = (rand() % (65));
	}

}

void Rockets::speedRocket2()
{
	vel2 += 4;

	if (y2 < -100)
	{
		vel2 = 5; // return to original velocity
		state2 = 0;
		y2 = 600; // reset y
		x2 = (rand() % 601) + 100; // random value for x between 100 and 700
		vis2 = 0; // rocket is no longer visable 
		vis1 = 1; // set other rocket to visable (switch)
		wordCount++;
		randWord = (rand() % (65));
	}

}

int Rockets::checkRockets()
{
	if ((y1 < 0 && vis1 && state1 != 1) || (y2 < 0 && vis2 && state2 != 1))
	{
		y1 = 600;
		y2 = 600;
		return 1;
	}
	else
	{
		return 0;
	}
}

void Rockets::drawRemainingLives() {

	std::string strNum = std::to_string(numLives);
	std::string strLives = "Remaining Lives: " + strNum;
	char livesDisplay[256];
	strcpy(livesDisplay, strLives.c_str());

	glRasterPos2i(500, 62);
	YsGlDrawFontBitmap12x16(livesDisplay);

}

void Rockets::drawYouLost() {
	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();

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

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Rockets::drawYouWon() {
	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();

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

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Rockets::ReturnToMenu(void) {
	for (int i = 0; i < 50; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawBackground();

		glColor3ub(236, 157, 117);
		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

int Rockets::playMusic()
{
	if (YSOK != wav.LoadWav("rockets_music.wav"))
	{
		printf("failed to load music");
		return 1;
	}
	player.Start();
	player.PlayOneShot(wav);
	player.SetVolume(wav, 0.8);
	return 0;
}

void Rockets::DrawPointCount()
{
	glRasterPos2i(600, 30);
	char pointstxt[256];
	std::sprintf(pointstxt, "%d", points);
	YsGlDrawFontBitmap16x20("Points: ");

	glRasterPos2i(720, 30);
	YsGlDrawFontBitmap16x20(pointstxt);
}

void Rockets::RunOneStep(void) {

	FsPollDevice();
	auto key = FsInkey();
	auto c = FsInkeyChar();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	srand(time(NULL));


	std::string targetWord = wordBank[randWord];
	auto len = targetWord.size();
	char letters[256];
	strcpy(letters, targetWord.c_str());

	inputStr = textInput.str.GetPointer();

	textInput.RunOneStep(key, c);

	drawBackground();

	drawRocket(letters, len);
	moveRocket1();
	moveRocket2();
	textInput.Draw();
	drawRemainingLives();
	DrawPointCount();

	// initialize time variables 
	int time_init, time_final = 0;
	time_init = time(NULL); // time how long the player lasts

	if (FsGetKeyState(FSKEY_ESC)) {
		ReturnToMenu();
		terminate = true;
	}

	if (FSKEY_ENTER == key) {
		if (inputStr.GetPointer() != targetWord) {
			points -= 10;
		}
		if (inputStr.GetPointer() == targetWord) // if rocket is not speeding **********and word is typed correctly**********
		{
			points += 20;
			if (vis1 == 1 && state1 == 0) // if rocket is visable, not speeding, **********and word is typed correctly**********
			{
				state1 = 1;
			}
			if (vis2 == 1 && state2 == 0)
			{
				state2 = 1;
			}


			auto completeTime = FsPassedTime();
			std::cout << "Completion time: " << completeTime * 0.001 << " seconds." << std::endl;
		}

		textInput.str.CleanUp();
		inputStr.CleanUp();
	}

	if (vis1 == 1 && state1 == 1)
	{
		speedRocket1();

	}
	if (vis2 == 1 && state2 == 1)
	{
		speedRocket2();

	}
	// std::cout << prevCheck << std::endl;
	if (prevCheck == 0 && checkRockets() == 1)
	{
		numLives--;
		points -= 5;
		if (vis1 == 1) {
			vis1 = 0;
			vis2 = 1;
		}
		else if (vis2 == 1) {
			vis2 = 0;
			vis1 = 1;
		}
		time_final = time(NULL); // final time 
	}
	prevCheck = checkRockets();

	if (numLives == 0) {
		//You Lost animation
		drawYouLost();
		if (level == 3) {
			SaveGame(3, points);
		}
		else if (level == 4) {
			SaveGame(4, points);
		}
		terminate = true;
	}

	if (wordCount >= 10) {
		//Winning animation
		drawYouWon();
		std::cout << "level = " << level << std::endl;
		if (level <= 3) {
			SaveGame(3, points);
		}
		terminate = true;
	}
	FsSwapBuffers();
	// FsSleep(25); // 25 milliseconds

}