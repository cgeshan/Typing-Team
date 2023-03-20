#ifndef GALAGA_IS_INCLUDED
#define GALAGA_IS_INCLUDED
/*{*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <tuple>
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
	int enemyState, wordState, laserX, laserY, numHit, numLives, randWord, wordCount = 0;
	double locationE, locationW, velE, velW;
	GalagaImageData imgdat;

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

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

	bool terminate = false;

	int level;
	int points;
	void DrawPointCount();
	void SaveGame(int level, int points);
	std::tuple <int, int> GetData(int level, int points);

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

	void drawRemainingLives();
	void ReturnToMenu();
	void drawInput(TextInput in, TextString str);

};

/*}*/
#endif
