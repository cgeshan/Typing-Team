#ifndef TUTORIAL_IS_INCLUDED
#define TUTORIAL_IS_INCLUDED
/*{*/

#include "textinput.h"
#include "yspng.h"

class Tutorial{
public:

    TextInput textInput;
  	TextString inputStr;
    YsRawPngDecoder bkgd;

    std::string wordBank[5] = {"cow", "apple", "space", "rover", "astronauts"};
	  int wordCount = 0;
    int state = 0;
    bool terminate = false;
    
    void Run(void);
    void Initialize(void);
    void RunOneStep(void);
    void Draw(void);
    void PlayInstructions(void);
    void ReturnToMenu(void);
    void drawTargetWord(char letters[]);
    void drawResult(bool result);
	
};

/*}*/
#endif