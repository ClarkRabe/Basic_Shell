#include"LinkedList.h"

LinkedList * linkedList()
{
	LinkedList* temp = (LinkedList*)calloc(1, sizeof(LinkedList));
	temp->head = (Node*)calloc(1, sizeof(Node));
	temp->head->next = NULL;
	temp->head->prev = NULL;
	temp->size = 0;
	return temp;

}

void addLast(LinkedList * theList, Node * nn)
{

	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}

	if(nn == NULL)
	{
		perror("The node to be added is Null");
		exit(-99);
	}


	if(theList->size == 0)
	{
		addFirst(theList, nn);

	}
	else
	{
		Node * walker = theList->head;

		while(walker->next != NULL)
		{
			walker = walker->next;
		}

		walker->next = nn;
		nn->next = NULL;
		nn->prev = walker;
		theList->size = theList-> size +1;
	}

}

void addFirst(LinkedList * theList, Node * nn)
{
	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}

	if(nn == NULL)
	{
		perror("The node to be added is Null");
		exit(-99);
	}


	if(theList->size == 0)
	{
		theList->head->next = nn;
		nn->prev = theList->head;
		theList->size = theList->size +1;
	}
	else
	{
		nn->next = theList->head->next;
		theList->head->next = nn;
		nn->prev = theList->head;
		theList->size = theList->size +1;
	}
}

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}

	if(theList-> size == 0)
	{
		printf("Unable to remove the first Node as the LinkedList is empty\n");

	}
	else
	{
		Node* rnode = theList->head->next;
		theList->head->next = rnode->next;
		rnode->next->prev = theList->head;
		removeData(rnode);
		rnode = NULL;
		theList->size = theList->size -1;
	}


}

void removeLast(LinkedList * theList, void (*removeData)(void *))
{

	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}

	if(theList-> size <= 1)
	{
		printf("Unable to remove the last Node as the LinkedList is empty or has one element\n");
		return;

	}

		Node* rnode = theList->head;
		Node* pnode;

		while(rnode->next != NULL)
		{
			pnode = rnode;
			rnode = rnode->next;
		}

		removeData(rnode->data);
		pnode->next = NULL;
		theList->size = theList->size - 1;

}

void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}

	if(nn == NULL)
	{
		perror("The node to be removed is Null");
		exit(-99);
	}

	Node * cnode = theList->head->next;
	Node * pnode = theList->head;

	while(cnode != NULL)
	{
		if(compare(cnode->data, nn->data) == 0)
		{
			if(cnode->next == NULL)
			{
				pnode->next = NULL;
				removeData(cnode->data);
				free(cnode);
				cnode = NULL;
				theList->size = theList->size -1;
			}
			else
			{
				pnode->next = cnode->next;
				cnode->next->prev = pnode;
				removeData(cnode->data);
				free(cnode);
				cnode = NULL;
				theList->size = theList->size - 1;
			}
		}

		if(cnode != NULL)
		{
			pnode = cnode;
			cnode = cnode->next;
		}

	}

}

void clearList(LinkedList * theList, void (*removeData)(void *))
{

	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}


	Node* rnode = theList->head->next;

	if(theList->size > 0)
	{
		Node* rnode = theList->head->next;
		Node* pnode = rnode->next;

		while(pnode != NULL)
		{
			removeData(rnode->data);
			free(rnode);
			rnode = NULL;
			rnode = pnode;
			pnode = pnode->next;
		}

		free(theList->head);
		theList->head = NULL;
		theList->size = 0;
	}

}


void printList(const LinkedList * theList, void (*convertData)(void *))
{

	if(theList == NULL)
	{
		printf("Empty List");

	}
	else
	{
		Node* nn = theList->head;

		while(nn->next != NULL)
		{
			nn = nn->next;
			convertData(nn->data);
		}

		printf("\n");
	}
}

