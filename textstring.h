#ifndef TEXTSTRING_IS_INCLUDED
#define TEXTSTRING_IS_INCLUDED
/*{*/

#include "genericchararray.h"

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

/*}*/
#endif