#include "files.h"
#include <stdio.h>

#if defined(_MSC_VER) && defined(_WIN32) && !defined(snprintf)
#define snprintf _snprintf
#endif

void ReadString(FILE *fp, std::string &buffer, int fixedLength)
{
	char c;

	if (fixedLength > 0)
	{
		char *temp = new char[fixedLength];
		fread(temp, 1, fixedLength, fp);

		for (int i = 0; i < fixedLength; ++i)
		{
			c = temp[i];

			if (c != '\0')
				buffer += c;
			else
				break;
		}
	}
	else
	{
		do
		{
			fread(&c, 1, 1, fp);
			if (c != '\0')
				buffer += c;
		} while (c != '\0');
	}
}
