#include"redirect.h"


int containsRedirect(char* s)
{
	const char* red0 = ">";
	const char* red1 = "<";
	int count = 0, i;
	char* test0 = strchr(s, *red0);
	char* test1 = strchr(s, *red1);

	for(i = 0; i < strlen(s); i++)
	{
	    if(s[i] == *red0 || s[i] == *red1)
	    count++;
	}

	if(count == 0)
	{
		printf("Redirect count is zero\n");
		return 0;
	}
	else
	{
	    printf("Pipe count is %d\n", count);
	    return count;
	}
}
