#include "fileUtils.h"

int isFile(char* fin)
{
	FILE* lol = fopen(fin, "r");

	if(lol == NULL)
		return 0;
	else
		return 1;
}
