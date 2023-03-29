#ifndef GENERICCHARARRAY_IS_INCLUDED
#define GENERICCHARARRAY_IS_INCLUDED
/*{*/

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

/*}*/
#endif



