#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./history/history.h"
#include "./listUtils/listUtils.h"
#include "./fileUtils/fileUtils.h"
#include "./linkedList/LinkedList.h"
#include "./aliasUtils/aliasUtils.h"
#include "./redirect/redirect.h"


int main()
{
  int argc, pipeCount;
  char **argv = NULL, s[MAX];
  char * tok;
  char copy[MAX];
  int preCount = 0, postCount = 0;
  int midCount = 0;
  char ** prePipe = NULL, ** postPipe = NULL, **midPipe = NULL;
  HISTORYLL = linkedList();
  char path[MAX];

  FILE* file = fopen(".msshrc", "r");

  if(file != NULL)
  {

	  while(!feof(file))
	  {

		  fgets(s, MAX, file);
		  strip(s);

		  if(strcmp(s, "HISTCOUNT=") == 0)
		  {

			  int i, j;
			  for(i = 10; i < strlen(s)-1; i++)
			  {
				  sscanf(&s[i], "%d", &j);
			  }

			  HISTCOUNT = j;

		  }
		  else if(strcmp(s, "HISTFILECOUNT=") == 0)
		  {

			  int i, j;
			  for(i = 10; i < strlen(s)-1; i++)
			  {
			  		sscanf(&s[i], "%d", &j);
			  }

			  HISTFILECOUNT = j;

		  }
		  else if(strcmp(s, "PATH=") ==0)
		  {

			  char* nPath = parse(s, "=");
			  setenv("PATH",nPath, 1);

		  }

		  else if(strcmp(s, "alias ") == 0)
		  {

			  char* name = getAliasName(s);
			  char* exe = getAliasExe(s);
			  buildAlias(name, exe);

		  }
	  }

	  fclose(file);


  }

  else
  {
	  char* path = getenv("PATH");
	  setenv("PATH", path, 1);
	  HISTCOUNT = 100;
	  HISTFILECOUNT = 1000;
  }

  printf("command?: ");
  fgets(s, MAX, stdin);
  strip(s);


  while(strcmp(s, "exit") != 0)
  {

	  historyAdd(s);
	  //isAlias(s);
	  strcpy(copy, s);
	  tok = strtok(copy, " ");
	  if(strcmp(s, "HISCOUNT=") == 0)
	  {

	  	int i, j;
	  	for(i = 10; i < strlen(s)-1; i++)
	  	{
	  		sscanf(&(s[i]), "%d", &j);
	  	}

	  	HISTCOUNT = j;

	  }
	  else if(strcmp(s, "HISTFILECOUNT=") == 0)
	  {

	    int i, j;
	  	for(i = 10; i < strlen(s)-1; i++)
	  	{
	  		sscanf(&(s[i]), "%d", &j);
	  	}

	  	HISTFILECOUNT = j;

	  }
	  else if(strcmp(s, "PATH=") ==0)
	  {

	  	char* nPath = strtok(s, "=");
	  	nPath = strtok(NULL, "=");
	  	setenv("PATH",nPath, 1);

	  }

	  else if(strcmp(s, "alias ") == 0)
	  {

	  	char* name = getAliasName(s);
	  	char* exe = getAliasExe(s);
	  	buildAlias(name, exe);

	  }
	  else if(strcmp(s, "history") == 0)
	  {
		  if(getHistorySize(HISTORYLL) == 0)
		  {
			  printf("No history to be displayed...\n");
		  }
		  else
		  {
			  printHistory();
		  }


	  }
	  else if(strcmp(tok, "cd") == 0)
	  {
		  tok = strtok(NULL, "");
		  int res = chdir(tok);
		  if(res != 0)
		  {
			  printf("Unable to change dir");
		  }
		  else
		  {
			  getcwd(path, sizeof(path));
			  printf("Dir changed to: %s\n", path);
		  }

	  }
	  else if(strncmp(s, "!", 1) == 0)
	  {

		  if(strcmp(s, "!!") == 0)
		  {
			  if(getHistorySize() != 0)
			  {

				  printf("%s", getLastHistory);

			  }
			  else
			  {
				  printf("history is empty...\n");
			  }
		  }
		  else
		  {

			  int x = sscanf(&(s[1]), "%d", &x);
			  int z = getHistorySize();

			  if(x < z)
			  {
				  printf("%s\n", extractHistory(x));

			  }
			  else
			  {
				  printf("number specified is bigger than history count...\n");
			  }

		  }
	  }



	pipeCount = containsPipe(s);

	if(pipeCount != 0)
	{
		if(pipeCount == 1)
		{
			prePipe = parsePrePipe(s, &preCount);
			postPipe = parsePostPipe(s, &postCount);

			pipeIt(prePipe, postPipe);

			clean(preCount, prePipe);
			clean(postCount, postPipe);

		}
		else
		{

			prePipe = parsePrePipe(s, &preCount);
			midPipe = parseMidPipe(s, &midCount);
			postPipe = parsePostPipe(s, &postCount);

			pipeItx2(prePipe, midPipe,postPipe);

			clean(preCount, prePipe);
			clean(midCount, midPipe);
			clean(postCount, postPipe);
		}
	}
	else
	{
		argc = makeargs(s, &argv);

		if(argc != -1)
			forkIt(argv);

		clean(argc, argv);
		argv = NULL;

	}

	printf("command?: ");

	fgets(s, MAX, stdin);
    strip(s);
    //historyAdd(HISTORYLL, s);

  }// end while

  writeHistoryToFile();
  cleanHistory();


  return 0;

}// end main




