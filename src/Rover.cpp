#include "Rover.h"
#include "textinput.h"
#include "textstring.h"


GLuint RoverTextureId[10];

//Point Call (wip)
std::tuple <int, int> Rover::GetData(int level, int points)
{
	Rover r;
	std::ifstream infile;
	infile.open("media/game.txt", std::ifstream::in);
	if (infile.good()) {
		infile >> r.level >> r.points;
	}

	std::cout << "level -> " << r.level << "\npoints -> " << r.points << std::endl;

	return std::make_tuple(r.level, r.points);

}

void Rover::SaveGame(int level, int points) {
	FILE* fp = fopen("media/game.txt", "w");

	if (nullptr != fp) {
		FILE* File;
		File = fopen("media/game.txt", "w+");
		fprintf(File, "%i %i", level, points);
		fclose(File);
	}
}

void Rover::Initialize()
{
	randWord = (rand() % (65));
	level = 0;
	points = 0;
	std::tie(level, points) = GetData(level, points);

	wordState = 2;
	locationW = 895;
	locationS = 800;
	locationF1 = 800;
	locationF2 = 400;
	locationR = 0;
	velS = 4;
	velW = 4;
	count = 0;
	numLives = 3;
	terminate = false;
	changeWords = false;

	imgdat.firstRenderingPass = true;
	imgdat.png[0].Decode("media/RacingBG_moonGround.png");
	imgdat.png[1].Decode("media/Sign.png");
	imgdat.png[2].Decode("media/Rock1Gray.png");
	imgdat.png[3].Decode("media/Rock2Gray.png");
	imgdat.png[4].Decode("media/EnemyCar.png");
	imgdat.png[5].Decode("media/PlayerCar.png");
	//imgdat.png[6].Decode("Stars.png");

	for (int i = 0; i < 50; i++)
	{
		starx[i] = rand() % 800;
		stary[i] = rand() % 450;

		starred[i] = rand() % 256;
		stargreen[i] = rand() % 256;
		starblue[i] = rand() % 256;
	}
}

void Rover::drawBackground()
{
	glClearColor(0, 0, 0, 0);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, RoverTextureId[6]);

	//glBegin(GL_QUADS);

	//glTexCoord2d(0.0, 0.0);
	//glVertex2i(0, 0);

	//glTexCoord2d(0.0, 1.0);
	//glVertex2i(0, 600);

	//glTexCoord2d(1.0, 1.0);
	//glVertex2i(800, 600);

	//glTexCoord2d(1.0, 0.0);
	//glVertex2i(800, 0);

	//glEnd();

	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);

	for (int star = 0; star < 50; star++)
	{
		glBegin(GL_QUADS);
		glColor3ub(starred[star], stargreen[star], starblue[star]);

		glVertex2i(starx[star] + 1, stary[star] + 1);
		glVertex2i(starx[star] - 1, stary[star] + 1);
		glVertex2i(starx[star] - 1, stary[star] - 1);
		glVertex2i(starx[star] + 1, stary[star] - 1);

		starx[star] = starx[star] - velS;

		if (starx[star] < 0)
		{
			starx[star] = 800;
		}

		glEnd();
	}

	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RoverTextureId[0]);

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

void Rover::drawWords(char word[], int arraySize)
{
	if (count == 0)
	{
		if (arraySize > 4)
		{
			locationW = locationW - (17.5 * (arraySize - 4));
		}
		else if (arraySize < 4)
		{
			locationW = locationW + (17.5 * (4 - arraySize));
		}
		count++;
	}

	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RoverTextureId[1]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(locationS, 300);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(locationS, imgdat.png[1].hei + 200);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[1].wid + locationS, imgdat.png[1].hei + 200);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[1].wid + locationS, 300);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	locationS = locationS - velS;

	if (wordState == 2)
	{
		glColor3f(0, 0, 1);
		glRasterPos3f(locationW, 375, 0.2);
		YsGlDrawFontBitmap32x48(word);
		locationW = locationW - velW;
	}

	if (locationW <= 0)
	{
		locationW = 895;
		locationS = 800;
		count = 0;
		numLives--;
		points -= 5;
	}

	if (locationS <= -125 && wordState == 0)
	{
		locationW = 895;
		locationS = 800;
		wordState = 2;
		count = 0;
		velS = velS + 0.5;
		velW = velW + 0.5;
	}
}

void Rover::moveForground()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RoverTextureId[2]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(locationF1, 550);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(locationF1, imgdat.png[2].hei + 600);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[2].wid + locationF1, imgdat.png[2].hei + 600);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[2].wid + locationF1, 550);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	locationF1 = locationF1 - 5;

	if (locationF1 <= -150)
	{
		locationF1 = 850;
	}

	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RoverTextureId[3]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(locationF2, 550);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(locationF2, imgdat.png[3].hei + 600);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[3].wid + locationF2, imgdat.png[3].hei + 600);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[3].wid + locationF2, 550);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	locationF2 = locationF2 - 5;

	if (locationF2 <= -150)
	{
		locationF2 = 850;
	}
}

void Rover::drawRover2()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RoverTextureId[4]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(600, 475);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(600, imgdat.png[4].hei + 325);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[4].wid + 400, imgdat.png[4].hei + 325);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[4].wid + 400, 475);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Rover::moveRover1()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, RoverTextureId[5]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(locationR, 475);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(locationR, imgdat.png[5].hei + 325);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[5].wid - 200 + locationR, imgdat.png[5].hei + 325);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[5].wid - 200 + locationR, 475);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Rover::drawYouLost() {
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

void Rover::drawYouWon() {
	for (int i = 0; i < 150; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBackground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Congratulations! You Won.");

		glRasterPos2i(92, 92);
		YsGlDrawFontBitmap16x24("You have now unlocked all levels");

		glRasterPos2i(92, 122);
		YsGlDrawFontBitmap16x24("Feel free to replay any levels...  :-)");

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

void Rover::ReturnToMenu(void) {
	for (int i = 0; i < 50; i++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawBackground();

		glColor3f(1, 1, 1);
		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Rover::drawRemainingLives() {

	std::string strNum = std::to_string(numLives);
	std::string strLives = "Remaining Lives: " + strNum;
	char livesDisplay[256];
	strcpy(livesDisplay, strLives.c_str());

	glRasterPos2i(500, 62);
	YsGlDrawFontBitmap12x16(livesDisplay);

}

void Rover::drawInput(TextInput in, TextString str) {
	glRasterPos2i(100, 62);

	auto copy = str;
	if (0 == time(nullptr) % 2) {
		copy.Add('|');
	}
	else {
		copy.Add('_');
	}
	YsGlDrawFontBitmap16x24(copy.GetPointer());
}

void Rover::DrawPointCount()
{
	glRasterPos2i(600, 30);
	char pointstxt[256];
	std::sprintf(pointstxt, "%d", points);
	YsGlDrawFontBitmap16x20("Points: ");

	glRasterPos2i(720, 30);
	YsGlDrawFontBitmap16x20(pointstxt);
}

//Sound
int Rover::playMusic()
{
	if (YSOK != roverWav.LoadWav("media/rover_music.wav"))
	{
		printf("failed to load music");
		return 1;
	}
	roverPlayer.Start();
	roverPlayer.PlayOneShot(roverWav);
	roverPlayer.SetVolume(roverWav, 0.8);
	return 0;
}

void RenderRover(void* incoming)
{
	Rover& game = *(Rover*)incoming;
	RoverImageData imgdat;

	if (true == game.imgdat.firstRenderingPass)  // Do it only once.
	{
		game.imgdat.firstRenderingPass = false; // And, don't do it again.

		for (int i = 0; i < 10; ++i)
		{
			glGenTextures(1, &RoverTextureId[i]);  // Reserve one texture identifier
			glBindTexture(GL_TEXTURE_2D, RoverTextureId[i]);  // Making the texture identifier current (or bring it to the deck)

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

	if (game.wordCount < 10)
	{
		std::string targetWord = game.wordBank[game.randWord];
		auto len = targetWord.size();
		char letters[256];
		strcpy(letters, targetWord.c_str());

		game.drawBackground();
		game.drawWords(letters, len);
		game.drawRover2();
		game.moveRover1();
		game.moveForground();
		game.drawRemainingLives();
		game.DrawPointCount();
		game.textInput.Draw();
	}


	FsSwapBuffers();
}

void Rover::Run(void) {
	Rover r;
	r.Initialize();
	FsRegisterOnPaintCallBack(RenderRover, &r);
	r.playMusic();

	std::string targetWord;
	srand(time(NULL));
	r.randWord = (rand() % (65));

	for (;;)
	{
// 		std::cout << targetWord.length() << std::endl;
		if(targetWord.length() > 7){
			r.randWord = (rand() % (65));
			targetWord = r.wordBank[randWord];
		}
		
		FsPollDevice();
		auto key = FsInkey();
		auto c = FsInkeyChar();
		inputStr = textInput.str.GetPointer();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		textInput.RunOneStep(key, c);
		r.textInput.RunOneStep(key, c);

		// drawTargetWord(letters);
		textInput.Draw();

		if (FsGetKeyState(FSKEY_ESC))
		{
			ReturnToMenu();
			terminate = true;
			break;
		}

		if (r.numLives == 0) {
			drawYouLost();
			if (level == 4) {
				r.SaveGame(4, r.points);
			}

			terminate = true;
			break;
		}

		if (r.locationR >= 600 || r.wordCount >= 10) {
			drawYouWon();
			r.SaveGame(4, r.points);
			terminate = true;
			break;
		}

		if (r.locationS <= 0 && changeWords == true) {
			r.wordCount++;
			r.randWord = (rand() % (65));
			targetWord = r.wordBank[randWord];
			changeWords = false;
		}

		if (r.wordCount < 10)
		{
			targetWord = r.wordBank[r.randWord];
		}

		if (FSKEY_ENTER == key)
		{
			if (inputStr.GetPointer() != targetWord) {
				r.points -= 10;
			}
			if (inputStr.GetPointer() == targetWord)
			{
				r.wordState = 0;
				r.locationR = r.locationR + 60;
				r.points += 20;
				changeWords = true;
				// r.wordCount++;
				auto completeTime = FsPassedTime();
				std::cout << "Completion time: " << completeTime * 0.001 << " seconds." << std::endl;
			}

			textInput.str.CleanUp();
			inputStr.CleanUp();

			r.textInput.str.CleanUp();
			r.inputStr.CleanUp();
		}

		FsPushOnPaintEvent();
		FsSleep(20);
	}
}
