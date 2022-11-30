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
	int enemyState, wordState, locationE, locationW, laserX, laserY, numHit, wordCount=0;
	GalagaImageData imgdat;

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

};

/*}*/
#endif

