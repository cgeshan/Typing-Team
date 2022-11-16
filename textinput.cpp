#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"


class GenericCharArray{
private:
	int len=0;
	char *data=nullptr;

    GenericCharArray(const GenericCharArray &copyFrom);
    const GenericCharArray &operator=(const GenericCharArray &copyFrom);
public:
	GenericCharArray(){
	}
	~GenericCharArray(){
		CleanUp();
	}
	void CleanUp(void){
		len=0;
		if(nullptr!=data){
			delete [] data;
			data=nullptr;
		}
	}

	void Resize(int newLen){
		auto newData=new char [newLen];
		for(int i=0; i<len && i<newLen; ++i){
			newData[i]=data[i];
		}
		CleanUp();
		len=newLen;
		data=newData;
	}
	int GetSize(void) const{
		return len;
	}
protected:
	char *GetData(void){
		return data;
	}
	const char *GetData(void) const{
		return data;
	}
};




class TextString : public GenericCharArray{
public:
	TextString();
	TextString(const char from[]);
	TextString(const TextString &str);
	const TextString &operator=(const TextString &from);

	void Set(const char from[]);
	void Add(const char from[]);
	void Add(const char c);
	const int Strlen(void) const;
	const char *GetPointer(void) const;
	void BackSpace(void);
	const char *Fgets(FILE *fp);

	void Print(void) const;
};

TextString::TextString(){
}
TextString::TextString(const char from[]){
	Set(from);
}
TextString::TextString(const TextString &from){
	Set(from.GetData());
}

void TextString::Set(const char from[]){
	if(from!=GetData()){
		CleanUp();
		if(nullptr!=from){
			auto len=strlen(from);
			GenericCharArray::Resize(len+1);
			strcpy(GetData(),from);
		}
	}
}

void TextString::Add(const char from[]){
	if(nullptr!=from){
		for(int i=0; 0!=from[i]; ++i){
			Add(from[i]);
		}
	}
}
void TextString::Add(const char c){
	if(0==Strlen()){
		char s[2]={c,0};
		Set(s);
		return;
	}
	auto len=strlen(GetData());
	Resize(len+1+1);
	auto newStr=GetData();
	newStr[len  ]=c;
	newStr[len+1]=0;
}

const int TextString::Strlen(void) const{
	auto str=GetData();
	if(nullptr==str){
		return 0;
	}
	return strlen(str);
}

void TextString::BackSpace(void){
	auto len=Strlen();
	if(0<len){
		--len;
		GetData()[len]=0;
		GenericCharArray::Resize(len+1);
	}
}

const char *TextString::GetPointer(void) const{
	auto str=GetData();
	if(nullptr==str){
		return "";
	}
	return str;
}

const char *TextString::Fgets(FILE *fp){
	CleanUp();

	const int bufferLen=16;
	char str[bufferLen+1];
	bool eof=true;
	while(nullptr!=fgets(str,bufferLen,fp)){
		eof=false;
		for(int i=0; 0!=str[i]; ++i){
			if('\n'==str[i]){
				return GetPointer();
			}
			Add(str[i]);
		}
	}
	return (true==eof ? nullptr : GetPointer());
}

const TextString &TextString::operator=(const TextString &from){
	Set(from.GetPointer());
	return *this;
}

void TextString::Print(void) const{
	printf("%s\n",GetPointer());
}




class TextInput{
public:
	TextString str;
	bool terminate=false;

	void BeginInput(void);
	void RunOneStep(int key,int c);
	void Draw(void) const;
};

void TextInput::BeginInput(void){
	str.CleanUp();
	terminate=false;
}

void TextInput::RunOneStep(int key,int c){
	if(FSKEY_ENTER==key){
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
	glRasterPos2i(32,32);

	auto copy=str;
	if(0==time(nullptr)%2){
		copy.Add('|');
	}
	else{
		copy.Add('_');
	}
	YsGlDrawFontBitmap12x16(copy.GetPointer());
}

int main(void){
	FsOpenWindow(16,16,800,600,1);

	TextInput textInput;

	textInput.BeginInput();
	while(true!=textInput.terminate){
		FsPollDevice();
		auto key=FsInkey();
		auto c=FsInkeyChar();

		textInput.RunOneStep(key,c);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		textInput.Draw();

		FsSwapBuffers();
		FsSleep(25);
	}

	textInput.str.Print();

	return 0;
}

