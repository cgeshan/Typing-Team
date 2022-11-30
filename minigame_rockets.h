#ifndef MINIGAME_ROCKET_IS_INCLUDED
#define MINIGAME_ROCKET_IS_INCLUDED
/*{*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include "textinput.h"

class Rockets
{
public:
	YsRawPngDecoder png[3];
    TextInput textInput;
  	TextString inputStr;

    std::string wordBank[5] = {"cow", "apple", "space", "rover", "astronauts"};

	double x1, y1, x2, y2;
	int vel1, vel2; 
	int state1, state2;
    int wordCount;
    bool terminate = false;

	void Initialize(void);
	void drawBackground();
	void drawRocket(void);
	void moveRocket1(void);
	void moveRocket2(void);
	void speedRocket1(void);
	void speedRocket2(void);
	int checkRockets(void);
    void RunOneStep(void);
    void drawTargetWord(char letters[]);
};

/*}*/
#endif