#ifndef MINIGAME_ROCKET_IS_INCLUDED
#define MINIGAME_ROCKET_IS_INCLUDED
/*{*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tuple>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include "textinput.h"

class Rockets
{
public:
	YsRawPngDecoder png[3];

	YsSoundPlayer rocketsPlayer;
	YsSoundPlayer::SoundData rocketsWav;

	//Music
	int playMusic();
	TextInput textInput;
	TextString inputStr;

	std::string wordBank[66] = { "asteroid",
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
	int wordCount, randWord;
	bool terminate = false;

	int level;
	int points;
	void DrawPointCount();
	void SaveGame(int level, int points);
	std::tuple <int, int> GetData(int level, int points);


	double x1, y1, x2, y2;
	int vel1, vel2, numLives, prevCheck;
	int vis1, vis2, state1, state2;

	void Initialize(void);
	void drawBackground();
	void drawRocket(char str[], int arraySize);
	void moveRocket1(void);
	void moveRocket2(void);
	void speedRocket1(void);
	void speedRocket2(void);
	int checkRockets(void);
	void RunOneStep(void);
	void drawYouLost();
	void drawYouWon();
	void ReturnToMenu();
	void drawRemainingLives();
};

/*}*/
#endif