#include <stdio.h>
#include <malloc.h>

typedef struct _Node
{
	int data;
	struct Node* link;
}Node;

typedef struct _LinkedList
{
	Node* current;
	Node* head;
}List;

void Init(List* pList)
{
	pList->current = NULL;
	pList->head = NULL;
}

void LinkedInsert(List* pList, int count, int data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->link = NULL;
	if (pList->head == NULL)
	{
		pList->head = temp;
	}
	else
	{
		if (count == 0)
		{
			temp->link = pList->head;
			pList->head = temp;
		}
		else
		{
			pList->current = pList->head;
			for (int i = 0; i < count-1; i++)
			{
				if (pList->current->link == NULL)
				{
					break;
				}
				pList->current = pList->current->link;
			}
			temp->link = pList->current->link;
			pList->current->link = temp;
		}
	}
}

void display(List* pList)
{
	pList->current = pList->head;
	while (pList->current != NULL)
	{
		printf("%d -> ", pList->current->data);
		if (pList->current->link == NULL)
		{
			break;
		}
		pList->current = pList->current->link;
	}
	printf("\n");
}

int main()
{
	List* pList = (List*)malloc(sizeof(List));
	Init(pList);
	int num;
	printf("노드의 개수를 입력하시오 : ");
	scanf_s("%d", &num);
	int data, count;
	for (int i = 0; i < num; i++)
	{
		printf("위치, 데이터 : ");
		scanf_s("%d %d", &count, &data);
		LinkedInsert(pList, count, data);
		display(pList);
	}
}