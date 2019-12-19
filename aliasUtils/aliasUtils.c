#include "aliasUtils.h"

//stores alias into a LL

void storeAlias(Alias* alias)
{

	Node* nn = buildNode_Type(alias);
	addLast(ALIAS, nn);

}

//builds the alias by setting name && exe by the parameters passed in

void buildAlias(char* name, char* exe)
{
	ALIAS = linkedList();
	Alias* na = (Alias*)calloc(1, sizeof(Alias));
	na->name = name;
	na->exe = exe;
	storeAlias(na);
}

//checks if the command passed in is an alias already

void isAlias(char* alias)
{
	if(ALIAS->size == 0)
	{



	}
	else
	{
		Alias* a = (Alias*)calloc(1,sizeof(Alias));
		a->name = (char*)calloc(strlen(alias)+1, sizeof(char));
		strcpy(a->name, alias);

		Node* n = ALIAS->head->next;

		while(n->next != NULL)
		{
			Alias* a2 = (Alias*)n->data;

			if(compareAlias(a, a2) == 0)
			{
				runAlias(a);
			}
			else
			{
				n = n->next;
			}
		}
		free(a->name);
		a->name =NULL;
		free(a);
		a =NULL;

	}

}


//runs the alias command

void runAlias(Alias* alias)
{
	char* exe = alias->exe;
	char* command[strlen(exe)];
	int i = 0;

	command[i] = strtok(exe, " ");

	while(command[i] != NULL)
	{

		command[++i] = strtok(NULL, " ");

	}

	if(command[0] == NULL)
		return;
	else
		execvpe(command[0], command, NULL);

}



char* getAliasName(char* alias)
{
	char copy[100];
	strcpy(copy, alias);
	char* name = strtok(copy, " ");
	name = strtok(NULL, "=");
	return name;


}



char* getAliasExe(char* alias)
{
	char copy[100];
	char word[100];
	char* exe;
	int i = 0;
	int j = 0;
	strcpy(copy, alias);

	for(i = 0; i< strlen(copy)-1;i++)
	{
		if(copy[i] == '"')
		{
			i++;
			while(copy[i] != '"')
			{
				word[j] = copy[i];
				i++;
				j++;
			}
		}


	}
	strcpy(exe, word);
	return exe;

}


//removes specified alias

void removeAlias(LinkedList* ll, Alias* a)
{

		if(ll == NULL)
		{
			perror("The Alias list is Null");
			exit(-99);
		}

		if(a == NULL)
		{
			perror("The alias passed in is Null");
			exit(-99);
		}

		Node * cnode = ll->head->next;
		Node * pnode = ll->head;

		while(cnode != NULL)
		{
			Alias* a0 = cnode->data;
			if(compareAlias(a0, a) == 0)
			{
				if(cnode->next == NULL)
				{
					pnode->next = NULL;
					free(cnode->data);
					free(cnode);
					cnode->data = NULL;
					cnode = NULL;
					ll->size = ll->size -1;
				}
				else
				{
					pnode->next = cnode->next;
					cnode->next->prev = pnode;
					free(cnode->data);
					free(cnode);
					cnode->data = NULL;
					cnode = NULL;
					ll->size = ll->size - 1;
				}
			}

			if(cnode != NULL)
			{
				pnode = cnode;
				cnode = cnode->next;
			}

		}
}


int compareAlias(Alias* p1, Alias* p2)
{

	if(p1 == NULL || p2 == NULL)
	{
		perror("One or both of the values are NULL\n");
		exit(-99);

	}

	return p1->name - p2->name;
}


