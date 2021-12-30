#include <stdio.h>
#include <malloc.h>

typedef struct _Node
{
	int data;
	struct Node* link;
}Node;

typedef struct _LinkedList
{
	Node* head;
	Node* current;
}List;

void InitF(List* fList)
{
	fList->head = NULL;
	fList->current = NULL;
}

List* InsertF(List* fList, int data)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	if (fList->head == NULL)
	{
		fList->head = new_node;
		new_node->link = fList->head;
	}
	else
	{
		fList->current = fList->head;
		while (fList->current->link != fList->head)
		{
			fList->current = fList->current->link;
		}
		new_node->link = fList->head;
		fList->current->link = new_node;
	}
	return fList;
}

List* InsertL(List* fList, int data)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	if (fList->head == NULL)
	{
		fList->head = new_node;
		new_node->link = fList->head;
	}
	else
	{
		new_node->link = fList->head->link;
		fList->head->link = new_node;
	}
	return fList;
}

void Display(List* fList)
{
	fList->current = fList->head;
	do 
	{
		printf("%d -> ", fList->current->data);
		if (fList->current->link == NULL)
		{
			break;
		}
		fList->current = fList->current->link;
	} while (fList->current->link != fList->head);
	printf("%d -> ", fList->current->data);
	printf("\n");
}

int main()
{
	int loop=1, data;
	List* fList = (List*)malloc(sizeof(List));
	InitF(fList);
	do
	{
		printf("First loop data : ");
		scanf_s("%d %d", &loop, &data);
		fList = InsertF(fList, data);
		Display(fList);
	} while (loop != 0);
	do
	{
		printf("Last loop data : ");
		scanf_s("%d %d", &loop, &data);
		fList = InsertL(fList, data);
		Display(fList);
	} while (loop != 0);
}