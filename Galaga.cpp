#include "Galaga.h"

GLuint GalagaTextureId[10];

void Galaga::Initialize()
{
	enemyState = 1;
	wordState = 2;
	locationE = 10.0;
	velE = 0.5;
	locationW = 0.0;
	velW = 0.5;
	laserX = -1000;
	laserY = -1000;
	numHit = 0;
	numLives = 3;
    terminate = false;

    imgdat.firstRenderingPass = true;
	imgdat.png[0].Decode("Player_Ship.png");
	imgdat.png[1].Decode("Enemy_Ship.png");
}

void Galaga::drawBackground()
{
	glClearColor(0, 0, 0, 0);

	glBegin(GL_POINTS);
	for (int star = 0; star < 100; star++)
	{
		unsigned int starred = rand() % 256;
		unsigned int stargreen = rand() % 256;
		unsigned int starblue = rand() % 256;

		glColor3ub(starred, stargreen, starblue);

		glVertex2i(rand() % 800, rand() % 600);
	}
	glEnd();
}

void Galaga::drawPlayer()
{
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GalagaTextureId[0]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(300, 450);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(300, imgdat.png[0].hei + 400);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imgdat.png[0].wid + 300, imgdat.png[0].hei + 400);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(imgdat.png[0].wid + 300, 450);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Galaga::drawWords(char word[], int arraySize)
{
	int start = 315;

	if (arraySize > 4)
	{
		start = start - (17.5 * (arraySize - 4));
	}
	else if (arraySize < 4)
	{
		start = start + (17.5 * (4 - arraySize));
	}
	
	if (locationW >= 340.0)
	{
		locationW = 0.0;
	}

	if (wordState == 2)
	{
		glColor3f(1, 1, 1);
		glRasterPos3f(start, locationW, 0.2);
		YsGlDrawFontBitmap32x48(word);
		locationW = locationW + velW;
	}
	else
	{
		locationW = 0.0;
	}

	// if (wordState == 0)
	// {
	// 	wordState = 2;
	// }
}

void Galaga::drawEnemy()
{
	if (locationE >= 350.0)
	{
		enemyState = 0;
		numLives--;
	}

	if (enemyState == 1)
	{
		glColor4d(1.0, 1.0, 1.0, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, GalagaTextureId[1]);

		glBegin(GL_QUADS);

		glTexCoord2d(0.0, 0.0);
		glVertex2i(315, locationE);

		glTexCoord2d(0.0, 1.0);
		glVertex2i(315, imgdat.png[1].hei + locationE);

		glTexCoord2d(1.0, 1.0);
		glVertex2i(imgdat.png[1].wid + 315, imgdat.png[1].hei + locationE);

		glTexCoord2d(1.0, 0.0);
		glVertex2i(imgdat.png[1].wid + 315, locationE);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		locationE = locationE + velE;
	}
	else
	{
		locationE = 10.0;
	}

	if (enemyState == 0)
	{
		enemyState = 1;
	}
}

void Galaga::shootEnemy()
{
	if (wordState == 0)
	{
		laserX = 400;
		laserY = 500;
	}

	while(laserY > locationW){
		laserY = laserY - 2;
		glColor3ub(255, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(laserX, laserY);
		glVertex2i(laserX, laserY - 25);
		glEnd();
	}
	numHit++;
	wordState = 2;


	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glDisable(GL_BLEND);

	

	if (laserY < locationE)
	{
		enemyState = 0;
		laserX = -1000;
		laserY = -1000;
		// numHit++;
		// wordState = 2;
	}
}

void Galaga::drawYouLost(){
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
		YsGlDrawFontBitmap16x24("Now returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Galaga::drawYouWon(){
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
		YsGlDrawFontBitmap16x24("Now returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Galaga::ReturnToMenu(void){
	for(int i = 0; i < 50; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		drawBackground();
		
		glColor3f(1, 1, 1);
		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24("Now returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(20);
	}
}

void Galaga::drawRemainingLives(){

	std::string strNum = std::to_string(numLives);
	std::string strLives = "Remaining Lives: " + strNum;
	char livesDisplay[256];
	strcpy(livesDisplay, strLives.c_str()); 

	glRasterPos2i(500, 62);
	YsGlDrawFontBitmap12x16(livesDisplay);

}

void Galaga::drawInput(TextInput in, TextString str) {
	glRasterPos2i(100,62);
	
	auto copy=str;
	if(0==time(nullptr)%2){
		copy.Add('|');
	}
	else{
		copy.Add('_');
	}
	YsGlDrawFontBitmap16x24(copy.GetPointer());
}

void RenderGalaga(void* incoming)
{
	Galaga& game = *(Galaga*)incoming;
	GalagaImageData imgdat;

	if (true == game.imgdat.firstRenderingPass)  // Do it only once.
	{
		game.imgdat.firstRenderingPass = false; // And, don't do it again.

		for (int i = 0; i < 10; ++i)
		{
			glGenTextures(1, &GalagaTextureId[i]);  // Reserve one texture identifier
			glBindTexture(GL_TEXTURE_2D, GalagaTextureId[i]);  // Making the texture identifier current (or bring it to the deck)

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
	if(game.wordCount < sizeof(game.wordBank)/sizeof(game.wordBank[0])){
		std::string targetWord = game.wordBank[game.wordCount];
		auto len = targetWord.size();
		char letters[256];
		strcpy(letters, targetWord.c_str());

		game.drawBackground();
		game.drawPlayer();
		game.drawWords(letters, len);
		game.drawEnemy();
		game.drawRemainingLives();

		// game.drawInput(game.textInput, game.inputStr);
		game.textInput.Draw();
		
	}

	// std::cout << game.wordState << std::endl;
	if(game.wordState == 0){
		game.shootEnemy();
		// std::cout << "Shots fired!" << std::endl;

	}

	FsSwapBuffers();
}

void Galaga::Run(void){
    Galaga g;

    g.Initialize();

    FsRegisterOnPaintCallBack(RenderGalaga, &g);

    	
	for (;;)
	{
		FsPollDevice();
        auto key = FsInkey();
        auto c=FsInkeyChar();    
        inputStr = textInput.str.GetPointer();

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        textInput.RunOneStep(key,c);

        // textInput.Draw();
        // std::cout << inputStr.GetPointer() << std::endl;

		if (FSKEY_ESC == key)
		{
			ReturnToMenu();
			terminate = true;
			break;
		}

		// std::cout << g.numHit << std::endl;
		if(g.numLives == 0){
		//You Lost animation
			drawYouLost();
			terminate = true;
			break;
		}

        if (g.numHit >= sizeof(g.wordBank)/sizeof(g.wordBank[0]) || g.wordCount >= sizeof(g.wordBank)/sizeof(g.wordBank[0]))
        {
            drawYouWon();
			terminate = true; // Go to Overworld
			break;
        }
		
		std::string targetWord = g.wordBank[g.wordCount];
		if(FSKEY_ENTER == key){

            if (inputStr.GetPointer() == targetWord) 
            {
				g.wordState = 0;
				g.locationW = 0.0;
				g.enemyState = 0;
				g.wordCount++;
                auto completeTime = FsPassedTime();
                std::cout << "Completion time: " << completeTime*0.001 << " seconds." << std::endl;
				g.velE += 0.1;
				g.velW += 0.1;
				
            }
            // if(g.wordCount >= sizeof(g.wordBank)/sizeof(g.wordBank[0])){
            //     terminate = true;
            //     break;
            // }
            textInput.str.CleanUp();
            inputStr.CleanUp();
			// g.wordState = 2;
	    }
		FsPushOnPaintEvent();
		// FsSleep(25);
	}
}
