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
	int wordState, locationW, locationS, locationF1, locationF2, locationR, velS, velW, count, numLives, randWord, wordCount=0;
	bool changeWords = false;
	RoverImageData imgdat;

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;
	
	//Music
	int playMusic();

    TextInput textInput;
  	TextString inputStr;

    std::string wordBank[66] = {"asteroid",
								"astronaut",
								"astronomer",
								"astronomy",
								"axial tilt",
								"black hole",
								"comet",
								"cosmonaut",
								"cosmos",
								"crater",
								"day",
								"deep space",
								"density",
								"dust",
								"dwarf star",
								"Earth",
								"eclipse",
								"ecliptic",
								"equinox",
								"full moon",
								"galaxy",
								"gravity",
								"half moon",
								"inertia",
								"Jupiter",
								"lens",
								"light-year",
								"lunar",
								"magnitude",
								"Mars",
								"mass",
								"Mercury",
								"meteor",
								"meteorite",
								"meteoroid",
								"Milky Way",
								"moon",
								"nebula",
								"Neptune",
								"new moon",
								"orbit",
								"penumbra",
								"phase",
								"planet",
								"Pluto",
								"rings",
								"rocket",
								"satellite",
								"Saturn",
								"sky",
								"solar",
								"solar wind",
								"solstice",
								"Space",
								"space",
								"star",
								"starlight",
								"sun",
								"telescope",
								"umbra",
								"universe",
								"Uranus",
								"Venus",
								"waning",
								"waxing",
								"zodiac"
								};

    bool terminate = false;

	void Initialize();
	void drawBackground();
	void drawWords(char word[], int arraySize);
	void wordInput();
	void moveForground();
	void drawRover2();
	void moveRover1();
	int GetData(void);
	void SaveGame(int level, int points);
    void Run();
	void drawYouLost();
	void drawYouWon();
	void drawRemainingLives();
	void ReturnToMenu();
	void drawInput(TextInput in, TextString str);

};

/*}*/
#endif