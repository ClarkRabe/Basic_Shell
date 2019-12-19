#include"listUtils.h"


Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) )
{

	Node* nn = (Node*)calloc(1, sizeof(Node));
	nn->data = buildData(fin);
	return nn;
}

Node * buildNode_Type(void * passedIn)
{
	Node* nn = (Node*)calloc(1, sizeof(Node));
	nn->data = passedIn;
	return nn;

}


void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{

	if(theList == NULL)
	{
		perror("The linkedlist is Null");
		exit(-99);
	}

	if(theList->size == 0 || theList->size == 1)
	{
		return;
	}
	else
	{
		Node* start, *search, *min;
		void* temp;
		for(start = theList->head->next; start != NULL; start = start->next)
		{
			min = start;

			for(search = start->next; search != NULL; search = search->next)
			{

				if(compare(search->data, min->data) < 0)
				{
					min = search;
				}
			}

			temp = (void*)min->data;
			min->data = start->data;
			start->data = (void*)(temp);

		}

	}

}


void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in))
{

	if(myList == NULL)
	{
		perror("List is NULL");
		exit(-99);
	}

	if(total <= 0)
	{
		perror("Number of items is less than or equal to zero...\n");
		exit(-99);
	}

	int x;
	Node* nn;
	for(x = 0; x < total; x++)
	{
		nn = buildNode(fin,buildData);
		addLast(myList, nn);

	}



}

