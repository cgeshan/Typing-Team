#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include "textstring.h"

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