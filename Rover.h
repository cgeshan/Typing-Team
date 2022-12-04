#ifndef ROVER_IS_INCLUDED
#define ROVER_IS_INCLUDED
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


class RoverImageData
{
public:
	bool firstRenderingPass;
	YsRawPngDecoder png[10];
};

class Rover
{
public:
	int wordState, locationW, locationS, locationF1, locationF2, locationR, velS, velW, count, numLives, wordCount=0;
	bool changeWords = false;
	RoverImageData imgdat;

    TextInput textInput;
  	TextString inputStr;

    std::string wordBank[5] = {"cow", "apple", "space", "rover", "astronauts"};

    bool terminate = false;

	void Initialize();
	void drawBackground();
	void drawWords(char word[], int arraySize);
	void wordInput();
	void moveForground();
	void drawRover2();
	void moveRover1();
    void Run();
	void drawYouLost();
	void drawYouWon();
	void drawRemainingLives();
	void ReturnToMenu();
	void drawInput(TextInput in, TextString str);

};

/*}*/
#endif