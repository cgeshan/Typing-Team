#include "textinput.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"


void TextInput::BeginInput(void){
	str.CleanUp();
	terminate=false;
}

void TextInput::RunOneStep(int key,int c){
	if(FSKEY_ESC==key){
		terminate=true;
	}
	if(FSKEY_BS==key){
		str.BackSpace();
	}
	if(' '<=c){
		str.Add(c);
	}
}

void TextInput::Draw(void) const{
	glRasterPos2i(100,62);

	auto copy=str;
	if(0==time(nullptr)%2){
		copy.Add('|');
	}
	else{
		copy.Add('_');
	}

	YsGlDrawFontBitmap16x24(copy.GetPointer());
}

