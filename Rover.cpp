#include "Rover.h"

GLuint RoverTextureId[10];

void Rover::Initialize()
{
	wordState = 2;
	locationW = 895;
	locationS = 800;
	locationF1 = 800;
	locationF2 = 400;
	locationR = 100;
	count = 0;
	numLives = 3;
    terminate = false;
	changeWords = false;

    imgdat.firstRenderingPass = true;
    imgdat.png[0].Decode("BG.png");
    imgdat.png[1].Decode("Sign.png");
    imgdat.png[2].Decode("Rock1.png");
    imgdat.png[3].Decode("Rock2.png");
    imgdat.png[4].Decode("EnemyCar.png");
    imgdat.png[5].Decode("PlayerCar.png");
}

void Rover::drawBackground()
{
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
	if (wordState == 0)
	{
		wordState = 2;
	}
	
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
	
	if (locationW <= 0)
	{
		locationW = 895;
		locationS = 800;
		wordState = 0;
		count = 0;
	}

	if (wordState == 2)
	{
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

		locationS = locationS - 1;

		glColor3f(0, 0, 1);
		glRasterPos3f(locationW, 375, 0.2);
		YsGlDrawFontBitmap32x48(word);
		locationW = locationW - 1;
	}
	else if (wordState == 1)
	{
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

		locationS = locationS - 1;

		glColor3f(1, 0, 0);
		glRasterPos3f(locationW, 375, 0.2);
		YsGlDrawFontBitmap32x48(word);
		locationW = locationW - 1;
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

	locationF1 = locationF1 - 1;

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

	locationF2 = locationF2 - 1;

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
	glVertex2i(0, 475);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, imgdat.png[5].hei + 325);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[5].wid - 150, imgdat.png[5].hei + 325);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[5].wid - 150, 475);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	if (wordState == 0)
	{
		locationR = locationR + 50;
	}
}

void Rover::drawYouLost(){
	for(int i = 0; i < 150; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		drawBackground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Sorry, you ran out of lives...");

		glRasterPos2i(92, 92);
		YsGlDrawFontBitmap16x24(":-(");

		FsSwapBuffers();
		FsSleep(20);
	}

	for(int i = 0; i < 150; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		drawBackground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Rover::drawYouWon(){
	for(int i = 0; i < 150; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		drawBackground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Congratulations! You Won.");

		glRasterPos2i(92, 92);
		YsGlDrawFontBitmap16x24("Now unlocking next level...  :-)");

		FsSwapBuffers();
		FsSleep(20);
	}

	for(int i = 0; i < 150; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		drawBackground();

		glRasterPos2i(62, 62);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Rover::ReturnToMenu(void){
	for(int i = 0; i < 50; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		drawBackground();
		
		glColor3f(1, 1, 1);
		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24("Returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Rover::drawRemainingLives(){

	std::string strNum = std::to_string(numLives);
	std::string strLives = "Remaining Lives: " + strNum;
	char livesDisplay[256];
	strcpy(livesDisplay, strLives.c_str()); 

	glRasterPos2i(500, 62);
	YsGlDrawFontBitmap12x16(livesDisplay);

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

	//setup
	game.drawBackground();

	if(game.wordCount < sizeof(game.wordBank)/sizeof(game.wordBank[0])){
		std::string targetWord = game.wordBank[game.wordCount];
		auto len = targetWord.size();
		char letters[256];
		strcpy(letters, targetWord.c_str());
		
		game.drawWords(letters, len);
	}

	game.drawRover2();
	game.moveRover1();
	game.moveForground();
	game.drawRemainingLives();

	game.textInput.Draw();

	FsSwapBuffers();
}

void Rover::Run(void){
    Rover r;
    r.Initialize();
    FsRegisterOnPaintCallBack(RenderRover, &r);

    for (;;)
	{
        FsPollDevice();
        auto key = FsInkey();
        auto c=FsInkeyChar();    
        inputStr = textInput.str.GetPointer();

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        textInput.RunOneStep(key,c);
		r.textInput.RunOneStep(key,c);

        std::string targetWord = r.wordBank[r.wordCount];

		if (FSKEY_ESC == key)
		{
			ReturnToMenu();
			terminate = true;
			break;
		}

        if(FSKEY_ENTER == key){

            if (inputStr.GetPointer() == targetWord) 
            {
                changeWords = true;
				// r.wordCount++;
                auto completeTime = FsPassedTime();
                std::cout << "Completion time: " << completeTime*0.001 << " seconds." << std::endl;
            }
            if(r.wordCount >= sizeof(r.wordBank)/sizeof(r.wordBank[0])){
				drawYouWon();
                terminate = true;
                break;
            }
            textInput.str.CleanUp();
            inputStr.CleanUp();

			r.textInput.str.CleanUp();
            r.inputStr.CleanUp();
	    }

		if(r.numLives == 0){
			drawYouLost();
			terminate = true;
			break;
		}

		if(r.locationS <= 0 && changeWords == true){
			r.wordCount++;
			changeWords = false;
		}

        if (r.locationR >= 600)
			{
				terminate = true; // Go to Overworld
				break;
			}

		FsPushOnPaintEvent();
		// FsSleep(25);
	}
}