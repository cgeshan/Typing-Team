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

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;
	
	//Music
	int playMusic();
	
    TextInput textInput;
  	TextString inputStr;

    std::string wordBank[5] = {"cow", "apple", "space", "rover", "astronauts"};
	int wordCount;

	// player variables
	double angle;
	int rover, start_x, start_y, numLives; 
	double rover_x, rover_y;
	double vel, vel_x, vel_y, dt;

	// obstacle variables
	double x1, y1, speed; // each obstacle is a png with upper left corner coordineates (x, y)
	int height;
	int seed[20]; // empty array of 20 values 
	int index;
	int initiate_jump, prevCheck;
    bool term = false;
	bool changeWord = false;

	void Initialize(void);
	void drawBackground();
	void drawForeground();
	void drawRover(void);
	void drawObstacles(char str[]);
	void moveObstacle1(void);
	int GetData(void);
	void SaveGame(int level, int points);
	void jumpRover(void); 
	int checkObstacle(void);
    void RunOneStep(void);
    void drawTargetWord(char letters[]);
	void drawYouLost();
	void drawYouWon();
	void ReturnToMenu();
	void drawRemainingLives();

};

/*}*/
#endif