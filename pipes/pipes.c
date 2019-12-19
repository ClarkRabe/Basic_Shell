#include "pipes.h"
int containsPipe(char *s)
{

	const char * pipe = "|";
	int count = 0, i;
 	char * num = strchr(s, *pipe);

	for(i = 0; i < strlen(s); i++)
	{
        if(s[i] == *pipe)
        	count++;
    }

	if(count == 0)
	{
		//printf("Pipe count is zero\n");
		return 0;
	}
	else
	{
        //printf("Pipe count is %d\n", count);
        return count;
	}
}


char ** parsePrePipe(char *s, int * preCount)
{

	char** argv = NULL;
	char copy[100];
	strcpy(copy, s);
	char* token = strtok(copy, "|");
	char* tokentwo = strtok(NULL, "");
	int total = makeargs(token, &argv);
	*preCount = total;

	return argv;
}


char** parseMidPipe(char* s, int* midCount)
{

	char** argv = NULL;
	char copy[100];
	strcpy(copy, s);
	char* token = strtok(copy, "|");
	char* tokentwo = strtok(NULL, "|");
	int total = makeargs(token, &argv);
	*midCount = total;

		return argv;

}

char ** parsePostPipe(char *s, int * postCount)
{

	char** argv = NULL;
	char copy[100];
	strcpy(copy, s);
	char* token = strtok(copy, "|");
	char* tokenII;

	while(token != NULL)
	{
		tokenII = token;
		token = strtok(NULL,"|");
	}


	int total = makeargs(tokenII, &argv);
	*postCount = total;

	return argv;
}


void pipeIt(char ** prePipe, char ** postPipe)
{

	int status = 0;
	pid_t pid = fork();

	if(pid != 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		int fd[2];
		int res = pipe(fd);

		if(res != 0)
		{
			perror("didn't work\n");
			exit(res);
		}

		pid = fork();

		if(pid != 0)//if not child, execute 2nd part of pipe
		{
			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			res = execvpe(postPipe[0], postPipe, NULL);

			if(res == -1)
			{
				perror("didn't work2\n");
				exit(res);
			}
		} 
		else//if child execute the first part of the pipe
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			res = execvpe(prePipe[0], prePipe, NULL);

			if(res == -1)
			{
				perror("didn't work3\n");
				exit(res);
			}

		}

	}


}

void pipeItx2(char** prePipe, char** midPipe, char** postPipe)
{

		int status = 0;
		pid_t pid = fork();

		if(pid != 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			int fd[2];
			int res = pipe(fd);

			if(res != 0)
			{
				perror("didn't work\n");
				exit(res);
			}

			pid_t pid1 = fork();

			if(pid != 0)//if not child, execute 2nd part of pipe
			{
				close(fd[1]);
				close(0);
				dup(fd[0]);
				close(fd[0]);
				res = execvpe(postPipe[0], postPipe, NULL);

				if(res == -1)
				{
					perror("didn't work2\n");
					exit(res);
				}
			}
			else//if child execute the first part of the pipe
			{

				int fd0[2];
				int res0 = pipe(fd0);

				if(res0 != 0)
				{
					perror("2nd pipe didn't work\n");
					exit(res0);
				}

				pid_t pid2 = fork();

				if(pid2 != 0)
				{
					close(fd[0]);
					close(1);
					dup(fd[1]);
					close(fd[1]);

					close(fd0[1]);
					close(0);
					dup(fd0[0]);
					close(fd0[0]);

					res = execvpe(midPipe[0], midPipe, NULL);

					if(res0 == -1)
					{
						perror("didn't work3\n");
						exit(res0);
					}
				}

				else
				{
					close(fd0[0]);
					close(1);
					dup(fd0[1]);
					close(fd0[1]);
					res = execvpe(prePipe[0], prePipe, NULL);

					if(res0 == -1)
					{
						perror("didn't work4\n");
						exit(res0);
					}

				}

			}

		}
}



