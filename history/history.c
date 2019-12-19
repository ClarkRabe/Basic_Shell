#include "history.h"

void printHistoryHelper(History* h)
{
	printf("%s", h->data);

}

void printHistory()
{

	Node* n = HISTORYLL->head->next;


	while(n->next != NULL)
	{

		printHistoryHelper(n->data);
		n = n->next;
		printf("\n");

	}


}

History* makeHistory(FILE* file)
{
	History* h =(History*)calloc(1, sizeof(History));
	char c[MAX];
	char* save;

	fgets(c, MAX, file);
	strtok_r(c, " ", &save);
	h->data = (char*)calloc(strlen(save) +1, sizeof(char));
	strcpy(h->data, save);

	return h;


}

void cleanHistoryHelper(History* h)
{

	if(h == NULL)
	{

	}
	else
	{
		free(h->data);
		h->data = NULL;
		free(h);
		h = NULL;


	}
}


void cleanHistory()
{

	clearList(HISTORYLL, cleanHistoryHelper);
	free(HISTORYLL);
	HISTORYLL = NULL;

}
void historyAdd(char* addMe)
{

	History* h = (History*)calloc(1, sizeof(History));

	h->data = (char*)calloc(strlen(addMe) + 1, sizeof(char));
	strcpy(h->data, addMe);
	Node* n = buildNode_Type(h);
	addLast(HISTORYLL, n);


}

int getHistorySize()
{

	return HISTORYLL->size;

}

char* extractHistory(int num)
{

	if(num >= HISTORYLL->size || num < 0)
	{
		perror("The history you requested does not exist...\n");
		return 0;

	}
	else
	{
		Node* curr = HISTORYLL->head->next;
		int i;
		for(i = 0; i < num; i++)
		{
			if(curr->next != NULL)
			{
				curr = curr->next;
			}

		}
		History* ret = (History*)curr->data;
		return ret->data;
	}

}

char* getLastHistory()
{
	Node* n;
	if(HISTORYLL->size == 0)
	{
		printf("Empty History\n");
		return 0;
	}
	else if(HISTORYLL->size ==1)
	{
		Node* n = HISTORYLL->head->next;
		History* h = (History*)n->data;
		return h->data;


	}
	else
	{

		while(n->next != NULL)
		{
			n = n->next;
		}

		History* h = (History*)n->data;
		return h->data;
	}

}


void writeHistoryToFile()
{
	if(HISTORYLL == NULL)
	{
		return;
	}
	else
	{
		FILE* file = fopen(".msshrc_history", "w");
		printHistory();
		fclose(file);

	}


}
