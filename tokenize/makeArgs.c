#include "makeArgs.h"

void clean(int argc, char **argv)
{

	int x = 0;
	for(x = 0; x < argc; x++)
	{
		free(argv[x]);
		argv[x] = NULL;
	}

	free(argv);
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	char copy[MAX];
	char* save = NULL;
	int count = 0;
	strcpy(copy, s);


	char* token = strtok_r(copy," ",&save);

	int x;
	while(token != NULL)
	{
		token = strtok_r(NULL," ", &save);
		count++;
	}

	if(count < 1)
	{
		return -1;
	}
	else
	{
		save = NULL;
		(*argv) = (char**)calloc(count+1, sizeof(char*));
		char* tok1 = strtok_r(s, " ", &save);
		(*argv)[0] = (char*)calloc(strlen(tok1)+1, sizeof(char));
		strcpy((*argv)[0], tok1);

		for(x = 1; x < count; x++)
		{
			tok1 = strtok_r(NULL, " ",&save);
			(*argv)[x] = (char*)calloc(strlen(tok1) +1, sizeof(char));
			strcpy((*argv)[x], tok1);
		}

		return count;


	}
}// end makeArgs
