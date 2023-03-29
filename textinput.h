#ifndef TEXTINPUT_IS_INCLUDED
#define TEXTINPUT_IS_INCLUDED
/*{*/

#include "textstring.h"

class TextInput{
public:
	TextString str;
	bool terminate=false;

	void BeginInput(void);
	void RunOneStep(int key,int c);
	void Draw(void) const;
};

/*}*/
#endif