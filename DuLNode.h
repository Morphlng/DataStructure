#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int DLinkType;

typedef struct DLinkNode {	//双向链表定义
	DLinkType data;
	struct DLinkNode* _next;
	struct DLinkNode* _prior;

}DLinkNode;



typedef struct DLinkList {
	DLinkNode* head;	//头指针
	DLinkNode* tail;	//尾指针
	int size;
}DLinkList;

//创建一个结点
DLinkNode* CreatNewNode(DLinkType value) {
	DLinkNode* Node = (DLinkNode*)malloc(sizeof(DLinkNode));
	if (!Node)
	{
		printf("ERROR\n");
		exit(0);
	}
	if (Node != NULL) {
		Node->data = value;
		Node->_next = NULL;
		Node->_prior = NULL;
	}
	return Node;
}

//释放一个结点
void DestoryNode(DLinkNode** node) {
	if (node == NULL) {

		printf("ERROR\n");
		exit(0);
	}

	if (*node == NULL) {

		printf("ERROR\n");
		exit(0);
	}
	free(*node);
	*node = NULL;
}



//初始化双向链表

DLinkList* InitDLinkList() {
	DLinkList* plist = (DLinkList*)malloc(sizeof(DLinkList));
	plist->head = CreatNewNode('0');
	if (plist != NULL) {
		if (plist->head != NULL) {
			plist->head = plist->head;
			plist->tail = plist->head;
			plist->size = 0;
		}
		else {
			return NULL;
		}
	}
	return plist;
}



//判断链表是否为空

bool DLinkListEmpty(DLinkList* plist) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	if (plist->tail == plist->head && plist->size == 0) {
		return true;
	}
	return false;
}

//尾插一个元素
DLinkNode* DLinkListPushBack(DLinkList* plist, DLinkType value) {
	if (plist->head == NULL) {
		printf("ERROR\n");
		exit(0);
	}
	DLinkNode* InsertNode = CreatNewNode(value);
	DLinkNode* cur = plist->head;
	//遍历链表，cur到最后尾指针位置
	while (cur != plist->tail) {
		cur = cur->_next;
	}
	cur->_next = InsertNode;
	InsertNode->_prior = cur;
	plist->tail = InsertNode;
	plist->size++;
	return InsertNode;
}



//打印整个链表

void PrintChar(DLinkList* plist, char* msg) {
	if (plist == NULL) {
		return;
	}
	printf("%s\n", msg);
	DLinkNode* cur1 = plist->head->_next;
	DLinkNode* cur2 = plist->tail;
	if (cur1 == NULL || cur2->_prior == plist->head) {
		//空链表
		printf("\n\n[head]<-[tail]\n\n");
		return;
	}
	
	//正着打印
	printf("\n\n\n[head]->");
	for (; cur1 != plist->tail; cur1 = cur1->_next) {
		printf("[%c]->", cur1->data);
	}

	printf("[%c]<-[tail]", cur1->data);
	
	//反着打印
	printf("\n\n\n[tail]->");

	for (; cur2 != plist->head; cur2 = cur2->_prior) {
		printf("[%c]->", cur2->data);
	}

	printf("[head]\n\n\n");
}



//尾删一个元素

void DLinkListPopBack(DLinkList* plist) {

	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur->_next != plist->tail) {
		cur = cur->_next;
	}

	DLinkNode* Delete = cur->_next;

	plist->tail = cur;

	Delete->_prior = NULL;

	cur->_next = NULL;

	plist->size--;

	DestoryNode(&Delete);
}



//头插一个元素

void DLinkListPushFront(DLinkList* plist, DLinkType value) {

	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}
	DLinkNode* node = CreatNewNode(value);

	DLinkNode* cur = plist->head->_next;

	plist->head->_next = node;

	node->_prior = plist->head;

	node->_next = cur;

	cur->_prior = node;

	plist->size++;
}



//头删一个元素

void DLinkListPopFront(DLinkList* plist) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	//保存要删除的元素

	DLinkNode* Delete = plist->head->_next;

	DLinkNode* cur = plist->head->_next->_next;

	plist->head->_next = cur;

	cur->_prior = plist->head;

	plist->size--;

	DestoryNode(&Delete);
}



//查找某个元素

DLinkNode* DLinkListFind(DLinkList* plist, DLinkType to_find) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur != plist->tail) {

		cur = cur->_next;

		if (cur->data == to_find) {
			//如果找到第一个值相等的元素，就返回cur
			return cur;
		}

	}

	//如果查找失败了，记得释放结点

	DLinkNode* error = CreatNewNode('-1');

	printf("链表里未保存此元素");

	return error;
}



//往指定位置之前插入一个元素

void DLinkListInsert(DLinkList* plist, DLinkNode* pos, DLinkType value) {
	if (pos == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = CreatNewNode(pos->data);

	DLinkNode* pos_next = pos->_next;

	//判断pos是否是最后一个元素

	if (pos_next == NULL) {
		pos->_next = cur;

		cur->_prior = pos;

		pos->data = value;

		plist->tail = cur;

		plist->size++;
	}

	else {

		pos->_next = cur;

		cur->_prior = pos;

		cur->_next = pos_next;

		pos_next->_prior = cur;

		pos->data = value;

		plist->size++;
	}
}



//往指定位置之后插入一个元素

void DLinkListInsertAfter(DLinkList* plist, DLinkNode* pos, DLinkType value) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	//创建新结点

	DLinkNode* insert = CreatNewNode(value);

	DLinkNode* pos_next = pos->_next;

	if (pos_next == NULL) {

		//当前结点是最后一个结点

		pos->_next = insert;

		insert->_prior = pos;

		//更新尾指针和链表长度size

		plist->size++;

		plist->tail = insert;

	}

	else {

		//交换

		pos->_next = insert;

		insert->_prior = pos;

		insert->_next = pos_next;

		pos_next->_prior = insert;

		//更新链表长度size

		plist->size++;
	}

}



//删除指定位置的元素

void DLinkListErase(DLinkList* plist, DLinkNode* pos) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur->_next != pos) {

		cur = cur->_next;

		if (cur->_next == NULL) {

			printf("pos位置传入错误");

			return;

		}
	}

	DLinkNode* Delete = pos;

	DLinkNode* pos_next = pos->_next;

	if (pos_next == NULL) {

		//pos为最后一个元素

		cur->_next = NULL;

		//更新链表size，释放删除的结点的空间

		plist->tail = cur;

		plist->size--;

		DestoryNode(&pos);
	}

	else {
		//开始拆除结点

		cur->_next = pos_next;

		pos_next->_prior = cur;

		plist->size--;

		DestoryNode(&pos);

	}
}



//删除指定值的元素

void DLinkListRemove(DLinkList* plist, DLinkType to_delete) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	DLinkNode* cur = plist->head;

	while (cur->_next->data != to_delete) {
		cur = cur->_next;

		if (cur->_next == NULL) {

			printf("链表中查不到此元素\n");

			return;

		}
	}

	DLinkNode* del_next = cur->_next->_next;

	DLinkNode* Delete = cur->_next;

	if (del_next == NULL) {

		//假如要删除的元素位于链表的最后一位，那么de_next一定为空指针

		cur->_next = NULL;

		//更新尾指针，size，并且释放删除的结点

		plist->tail = cur;

		plist->size--;

		DestoryNode(&Delete);
	}

	else {
		//拆除结点

		cur->_next = del_next;

		del_next->_prior = cur;

		plist->size--;

		DestoryNode(&Delete);

	}
}



//删除所有指定值的元素

void DLinkListRemoveAll(DLinkList* plist, DLinkType to_delete) {
	if (plist == NULL) {
		printf("ERROR\n");
		exit(0);
	}

	int sz = plist->size;

	while (sz--) {
		//删除所有指定值的元素
		DLinkListRemove(plist, to_delete);
	}
}



//删除一个链表的所有元素

void DLinkListClear(DLinkList* plist) {
	if (plist == NULL) {

		return;

	}

	DLinkNode* cur = plist->head->_next;

	DLinkNode* to_free = plist->head->_next;

	plist->tail = plist->head;

	while (cur->_next != NULL) {
		cur = cur->_next;

		DestoryNode(&to_free);

		to_free = cur;
	}

	DestoryNode(&to_free);

	plist->head->_next = NULL;
}
