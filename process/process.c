#include "process.h"

void forkIt(char ** argv)
{
	pid_t pid = fork();
	int status;

	if(pid != 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		int res = execvp(argv[0], argv);
		exit(res);
	}


}
