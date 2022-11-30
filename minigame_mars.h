#ifndef MINIGAME_MARS_IS_INCLUDED
#define MINIGAME_MARS_IS_INCLUDED
/*{*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "yspng.h"
#include "textinput.h"

class Mars
{
public:
	YsRawPngDecoder png[4];
    TextInput textInput;
  	TextString inputStr;

    std::string wordBank[5] = {"cow", "apple", "space", "rover", "astronauts"};

	// player variables
	double angle;
	int rover, start_x, start_y, wordCount; 
	double rover_x, rover_y;
	double vel, vel_x, vel_y, dt;

	// obstacle variables
	double x1, y1, x2, y2; // each obstacle is a png with upper left corner coordineates (x, y)
	int speed, height;
	int seed[20]; // empty array of 20 values 
	int index;
    bool term = false;

	void Initialize(void);
	void drawBackground();
	void drawForeground();
	void drawRover(void);
	void drawObstacles(void);
	void moveObstacle1(void);
	void moveObstacle2(void);
	void jumpRover(void); 
	int checkObstacle(void);
    void RunOneStep(void);
    void drawTargetWord(char letters[]);
};

/*}*/
#endif