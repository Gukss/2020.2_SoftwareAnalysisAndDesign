#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* link;
}pNode;

typedef struct linkedList
{
	pNode* head;
}List;

void Init(List* plist)
{
	plist->head = NULL;
}

void LinkedInsert(List* plist, int data)
{
	pNode* newnode = (pNode*)malloc(sizeof(pNode));

	newnode->data = data;

	newnode->link = plist->head;
	plist->head = newnode;
}

List* Merge(pNode* alist, pNode* blist)
{
	if (alist == NULL) return blist;
	if (blist == NULL) return alist;
	pNode* clist = (pNode*)malloc(sizeof(pNode));
	if (alist->data <= blist->data)
	{
		clist = alist;
		alist->link = Merge(alist->link, blist);
	}
	else
	{
		clist = blist;
		alist->link = Merge(alist, blist->link);
	}
	return clist;
}

int main()
{
	List* alist = (List*)malloc(sizeof(List));
	List* blist = (List*)malloc(sizeof(List));
	List* clist = (List*)malloc(sizeof(List));
	Init(alist);
	Init(blist);
	LinkedInsert(alist, 4);
	LinkedInsert(alist, 3);
	LinkedInsert(alist, 1);
	
	LinkedInsert(blist, 5);
	LinkedInsert(blist, 2);
	LinkedInsert(blist, 1);

	clist->head = Merge(alist->head, blist->head);
}