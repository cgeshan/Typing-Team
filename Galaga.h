#ifndef GALAGA_IS_INCLUDED
#define GALAGA_IS_INCLUDED
/*{*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "textinput.h"


class GalagaImageData
{
public:
	bool firstRenderingPass;
	YsRawPngDecoder png[10];
};

class Galaga
{
public:
	int enemyState, wordState, laserX, laserY, numHit, numLives, wordCount=0;
	double locationE, locationW, velE, velW;
	GalagaImageData imgdat;

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;
	
	//Music
	int playMusic();

    TextInput textInput;
  	TextString inputStr;

    std::string wordBank[5] = {"cow", "apple", "space", "rover", "astronauts"};

    bool terminate = false;

	void Initialize();
	void drawBackground();
	void drawPlayer();
	void drawWords(char word[], int arraySize);
	void wordInput();
	void drawEnemy();
	void shootEnemy();
    void Run(void);
	void drawYouLost();
	void drawYouWon();
	int GetData(void);
	void SaveGame(int level, int points);
	void drawRemainingLives();
	void ReturnToMenu();
	void drawInput(TextInput in, TextString str);

};

/*}*/
#endif

