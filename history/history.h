
#ifndef HISTORY_HISTORY_H_
#define HISTORY_HISTORY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../utils/myUtils.h"
#include "../linkedList/LinkedList.h"
#include "../listUtils/listUtils.h"

#define MAX 100

struct history
{
	char* data;
};
typedef struct history History;

int HISTCOUNT;
int HISTFILECOUNT;
LinkedList* HISTORYLL;

void printHistoryHelper(History* h);
void printHistory();
void cleanHistoryHelper(History* h);
void cleanHistory();
void historyAdd(char* addMe);
int getHistorySize();
char* extractHistory(int num);
char* getLastHistory();
void writeHistoryToFile();

#endif
