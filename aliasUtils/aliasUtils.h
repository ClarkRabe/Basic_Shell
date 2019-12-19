
#ifndef ALIASUTILS_ALIASUTILS_H_
#define ALIASUTILS_ALIASUTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/myUtils.h"
#include "../listUtils/listUtils.h"
#include "../linkedList/LinkedList.h"

struct alias
{
	char* name;
	char* exe;
};
typedef struct alias Alias;

LinkedList* ALIAS;

void storeAlias(Alias* alias);
void buildAlias(char* name, char* exe);
void isAlias(char* alias);
void runAlias(Alias* alias);
char* getAliasName(char* alias);
char* getAliasExe(char* alias);
void removeAlias(LinkedList* ll, Alias* a);
int compareAlias(Alias* p1, Alias* p2);

#endif
