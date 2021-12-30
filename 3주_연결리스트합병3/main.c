#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* link;
}Node;

typedef struct linkedList
{
	Node* head;
}List;

void Init(List* plist)
{
	plist->head = NULL;
}

void LinkedInsert(List* plist, int data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));

	newnode->data = data;

	newnode->link = plist->head;
	plist->head = newnode;
}

List* Merge(Node* a, Node* b)
{
	Node* c, * temp;
	temp = NULL;
	c = NULL;
	while (a != NULL && b != NULL)
	{
		if (c == NULL)
		{
			if (a->data <= b->data)
			{
				c = a;
				a = a->link;
				c->link = NULL;
			}
			else if (a->data > b->data)
			{
				c = b;
				b = b->link;
				c->link = NULL;
			}
			temp = c;
		}
		else
		{
			if (a->data <= b->data)
			{
				temp->link = a;
				temp = a;
				a = a->link;
			}
			else if (a->data > b->data)
			{
				temp->link = b;
				temp = b;
				b = b->link;
			}
			temp->link = NULL;
		}

		if (a != NULL) {
			temp->link = a;
		}
		else if (b != NULL) {
			temp->link = b;
		}
	}
	return c;
}

void display(Node* head)
{

	while (head != NULL)
	{
		printf("%d -> ", head->data);
		head = head->link;
	}
	printf("\n");
}

int main()
{
	List* alist = (List*)malloc(sizeof(List));
	List* blist = (List*)malloc(sizeof(List));
	List* clist = (List*)malloc(sizeof(List));
	Init(alist);
	Init(blist);
	Init(clist);
	LinkedInsert(alist, 4);
	LinkedInsert(alist, 3);
	LinkedInsert(alist, 1);

	LinkedInsert(blist, 5);
	LinkedInsert(blist, 2);
	LinkedInsert(blist, 1);
	printf("합병 전 리스트 a\n");
	display(alist->head);
	printf("합병 전 리스트 b\n");
	display(blist->head);
	printf("\n");
	clist->head = Merge(alist->head, blist->head);
	printf("합병 후 리스트\n");
	display(clist->head);
}