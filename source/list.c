#include <stdio.h>
#include "list.h"
#include <malloc.h>

/*节点currunt和afterC相邻，互换位置,beforeC是currunt的前一个节点
如果beforeC是null，只交换链头两个节点*/
List* list_twoExchange(List* beforeC, List* head)
{
	List* currunt = NULL;
	List* afterC = NULL;
	if (NULL == beforeC && NULL == head)
	{
		printf("error!\n");
		return NULL;
	}
	/*只交换链头两个节点*/
	if (NULL != head && NULL != head->next)
	{
		currunt = head;
		afterC = head->next;

		currunt->next = afterC->next;
		afterC->next = currunt;
		head = afterC;
		return head;
	}
	else if(NULL != beforeC &&
		NULL != beforeC->next &&
		NULL != beforeC->next->next)
	{
		currunt = beforeC->next;
		afterC = beforeC->next->next;

		beforeC->next = afterC;

		currunt->next = afterC->next;
		afterC->next = currunt;
	}
	
	
	return beforeC;
}

List* list_createList(int *pValue, int valNum)
{
	int index = 0;
	List* head = (List* )malloc(sizeof(List));
	List* temp = head;
	List* node = NULL;

	if (NULL == pValue || 0 == valNum)
	{
		printf("error");
		return NULL;
	}
	head->val = pValue[index];
	head->next = NULL;
	index++;
	while (index != valNum)
	{
		node = (List*)malloc(sizeof(List));
		node->val = pValue[index];
		node->next = NULL;

		temp->next = node;
		temp = temp->next;
		index++;
	} 

	return head;

}

void list_deleteList(List* head)
{
	//int index = 0;
	List* temp = head;
	List* node = head;

	do
	{
		if (NULL != node)
		{
			free(node);
		}
		node = temp->next;
		temp = temp->next;
	} while (NULL != temp);

	return;

}

void list_printList(List* head)
{
	int index = 0;
	List* temp = head;
	if (NULL == head)
	{
		printf("error\n");
		return;
	}
	do
	{
		printf("value %u: %u\n",index, temp->val);
		temp = temp->next;
		index++;
	} while (NULL != temp);

	return;
}

void list_insertHeadList(List* head, List *newNode)
{
	if (NULL == head || NULL == newNode)
	{
		return;
	}

	newNode->next = head->next;
	head->next = newNode;
	
	return;
}

/*
* 从头节点循环遍历原链表，把原链表每个结点指向后继的指针，改为执行结点的前驱.
* 注意的是，最后返回反转后链表的头节点时，应该是prev，而不是current，
* 因为最终退出循环时，current保存的是原链表的最后一个结点，其next指针为NULL，而prev才是反转后链表的头节点.
*/
struct ListNode* list_reverseList(struct ListNode* head) {
	struct ListNode* prev = NULL;
	struct ListNode* current = head;

	while (current) {
		struct ListNode* node = current->next;
		current->next = prev;
		prev = current;
		current = node;
	}

	return prev;
}

/*两两交换*/
struct ListNode* list_exchange(struct ListNode* head) 
{
	//int index = 0;
	int num = 0;/*链长*/
	struct ListNode* pTemp = head;
	struct ListNode* node = head;

	while (NULL != node)
	{
		num++;
		node = node->next;

	}
	printf("list length is %u\n",num);
	if (0 == num || 1 == num)
	{
		return head;
	}

	head = list_twoExchange(NULL, head);/*前两个节点互换导致head变化*/
	node = head;
	while (NULL != pTemp)
	{
		pTemp = node->next;
		pTemp = list_twoExchange(pTemp, NULL);
		node->next = pTemp;

		pTemp = pTemp->next;
		if (NULL ==pTemp || NULL == pTemp->next || NULL == pTemp->next->next)
		{
			break;
		}	
	} 

	return head;
}


/*****************
 * 单链中不应该有内容重复的节点
 * **************/

/*********************************************************************************
 * function : 前插
 * input    : pHead  : 链表头节点
 * input    : newVal : 待插入的节点内容
 * input    : val    : newVal插在val之前
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listHeadInsertNode(List *pHead, int val, int newVal)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	List *pNode = pHead->next;
	List *pNewNode = (List *)malloc(sizeof(List));
	pNewNode->val = newVal;
	pNewNode->next = NULL;
	int index = 0;
	int locate = 0;
	List *pBefore= pHead->next; /*待插入节点的前一个节点*/

	while(NULL != pNode && val != pNode->val)
	{
		pNode = pNode->next;
		index++;
	}
	if(0 == index)
	{
		/*往第一个节点前插入*/
		pNewNode->next = pNode;
		pHead->next = pNewNode;
		goto sizebig;
	}
	for(locate=0;locate<index-1; locate++)
	{
		pBefore = pBefore->next;
	}

	pNewNode->next = pBefore->next;
	pBefore->next = pNewNode;
sizebig:
	pHead->listLen += 1;

	return true;
}

/*********************************************************************************
 * function : 尾插，根据元素内容找到插入点
 * input    : pHead  : 链表头节点
 * input    : newVal : 待插入的节点内容
 * input    : val    : newVal插在val之后
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listTailInsertNode(List *pHead, int val, int newVal)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	List *pNode = pHead->next;
	List *pNewNode = (List *)malloc(sizeof(List));
	pNewNode->val = newVal;
	pNewNode->next = NULL;

	while(NULL != pNode && val != pNode->val)
	{
		pNode = pNode->next;
	}
	pNewNode->next = pNode->next;
	pNode->next = pNewNode;
	pHead->listLen += 1;

	return true;
}

/*********************************************************************************
 * function : 
 * input    : pHead  : 链表头节点
 * input    : val    : 待删的节点内容
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listDeleteNode(List *pHead, int val)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	int index = 0;
	int locate = 0;
	List *pNode = pHead->next;  /*待删节点*/
	List *pBefore= pHead->next; /*待删节点的前一个节点*/

	while(NULL != pNode && val != pNode->val)
	{
		pNode = pNode->next;
		index ++;
	}
	if(0 == index)
	{
		/*删除第一个节点*/
		pHead->next = pNode->next;
		goto nodeFree;
	}
	for(locate=0;locate<index-1; locate++)
	{
		pBefore = pBefore->next;
	}

	pBefore->next = pNode->next;
nodeFree:
	free(pNode);
	pHead->listLen -= 1;

	return true;
}

List *daring_listCreate(int *pInitData, int size)
{
	DARING_CHECK_INPUT_OUTPUT(pInitData, NULL);
	int *pData = pInitData;
	int index = 0;
	List *pNew = NULL;
	List *pHeadTemp = NULL;

	List *pHead = (List *)malloc(sizeof(List));
	memset(pHead, 0, sizeof(List));
	pHead->next = NULL;
	pHead->listLen = size;/*头节点仅仅存储链长*/
	pHeadTemp = pHead;

	for(index= 0; index< size; index++)
	{
		pNew = (List *)malloc(sizeof(List));
		memset(pNew, 0, sizeof(List));
		pNew->val = *pData;
		pData++;
		pHeadTemp->next = pNew; /*尾插法*/
		pHeadTemp = pHeadTemp->next;	
	}
	pHeadTemp->next = NULL;	

	return pHead;
}

/*********************************************************************************
 * function : 将链清空
 * input    : pHead  : 链表头节点
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listDelete(List *pHead)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	List *pNode = pHead->next;  
	List *pDelete= pHead->next; 

	while(NULL != pNode)
	{
		pDelete = pNode;
		free(pDelete);	
		pNode = pNode->next;
	}

	return true;
}

VOID daring_listPrint(List *pHead)
{
	List *pNode = pHead->next;
	int index = 0;
	printf("size of list is %u\n", pHead->listLen);
	while(NULL != pNode)
	{
		printf("element %-2u:%u\n", index, pNode->val);
		index++;
		pNode = pNode->next;
	}
	return;
}

VOID daring_listTest()
{
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
    int dataNum = 10;
    List *pHead = NULL;

    printf("\n---Now test list functions(start)---\n");
    pHead = daring_listCreate((int *)data, dataNum);
    if(NULL == pHead)
    {
        printf("create list failed!\n");
        return;
    }
    daring_listPrint(pHead);

    daring_listTailInsertNode(pHead, 2, 30);/*在元素2后插30*/
    daring_listHeadInsertNode(pHead, 10,100);/*在元素10前插100*/
    daring_listDeleteNode(pHead, 1);/*删除元素1*/
    daring_listDeleteNode(pHead, 8);/*删除元素8*/
    daring_listPrint(pHead);

    daring_listDelete(pHead);
    printf("\n---Now test list functions(end)---\n");

	return;
}





/*********************************************************************************
 * function : 尾插，直接给出插入点，插入的节点已经封装好
 * input    : pHead  : 链表头节点
 * input    : newVal : 待插入的节点内容
 * input    : val    : newVal插在val之后
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listTailInsertNode2(List *pHead, int pos, List **ppNewNode)
{
	DARING_CHECK_INPUT_OUTPUT(ppNewNode, false);
	DARING_CHECK_INPUT_OUTPUT(*ppNewNode, false);
	List *pNode = pHead->next;
	int index = 0;
	/*if(0 == pos)
	{
		(*ppNewNode)->next = pHead->next,
		pHead->next = *ppNewNode;
		goto addnum;
	}*/

	while(NULL != pNode && pos != index)
	{
		pNode = pNode->next;
		index++;
	}
	(*ppNewNode)->next = pNode->next;
	pNode->next = *ppNewNode;
addnum:
	pHead->listLen += 1;

	return true;
}

/*********************************************************************************
 * function :  删除的节点不释放内存
 * input    : pHead  : 链表头节点
 * input    : val    : 待删的节点内容
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listDeleteNode2(List *pHead, List *pDeleteNode)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	int index = 0;
	int locate = 0;
	List *pNode = pHead->next;  /*待删节点*/
	List *pBefore= pHead->next; /*待删节点的前一个节点*/

	while(NULL != pNode && pDeleteNode->val != pNode->val)
	{
		pNode = pNode->next;
		index ++;
	}
	if(0 == index)
	{
		/*删除第一个节点*/
		pHead->next = pDeleteNode->next;
		goto nodeFree;
	}
	for(locate=0;locate<index-1; locate++)
	{
		pBefore = pBefore->next;
	}

	pBefore->next = pDeleteNode->next;
nodeFree:
	pHead->listLen -= 1;

	return true;
}

/*********************************************************************************
 * function : 两个节点内容互换
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listNodeExchang(List *pHead, int pos1, int pos2)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	int index = 0;
	List *pNode = pHead->next;
	List *pNode2 = pHead->next;
	int tempVal = 0;

	while(NULL != pNode && pos1 != index)
	{
		pNode = pNode->next;
		index++;
	}
	index = 0;

	while(NULL != pNode2 && pos2 != index)
	{
		pNode2 = pNode2->next;
		index++;
	}
	tempVal = pNode->val;
	pNode->val = pNode2->val;
	pNode2->val = tempVal;

	return true;
}

/*********************************************************************************
 * function : 两个节点内存互换
 * output   : 无
 * comment  : pos1 <= pos2
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
bool daring_listNodeExchang2(List *pHead, int pos1, int pos2)
{
	DARING_CHECK_INPUT_OUTPUT(pHead, false);
	int index1 = 0;
	int index2 = 0;
	List *pNode1 = pHead->next;
	List *pNode2 = pHead->next;
	//int tempIndex = 0;

	while(NULL != pNode1 && pos1 != index1)
	{
		pNode1 = pNode1->next;
		index1++;
	}

	while(NULL != pNode2 && pos2 != index2)
	{
		pNode2 = pNode2->next;
		index2++;
	}
	daring_listDeleteNode2(pHead, pNode1);
	daring_listDeleteNode2(pHead, pNode2);

	//tempIndex = (index1 == 0? 0 : index1-1);
	daring_listTailInsertNode2(pHead, index1, &pNode2);
	daring_listTailInsertNode2(pHead, index2-1, &pNode1);

	return true;
}
/*********************************************************************************
 * function : 链表反转
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.27
 * *********************************************************************************/
VOID daring_listReverse(List *pHead, int plan)
{
	DARING_CHECK_INPUT_NO_OUTPUT(pHead);
	int index1 = 0;
		
	for(index1= 0; index1< (pHead->listLen/2); index1++)
	{
		switch(plan)
		{
		case 0:
			/*内容反转，内存不变*/
			daring_listNodeExchang(pHead, index1, pHead->listLen-1-index1);
			break;
		case 1:
			/*节点反转*/
			daring_listNodeExchang2(pHead, index1, pHead->listLen-1-index1);
			break;
		default:break;
		}
	}

	return;
}

VOID daring_listReverseTest()
{
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
    int dataNum = 10;
    List *pHead = NULL;

    printf("\n---Now test list reverse functions(start)---\n");
    pHead = daring_listCreate((int *)data, dataNum);
    if(NULL == pHead)
    {
        printf("create list failed!\n");
        return;
    }
    daring_listPrint(pHead);

	daring_listReverse(pHead, 0);
	daring_listPrint(pHead);

	daring_listReverse(pHead, 1);
    daring_listPrint(pHead);

    daring_listDelete(pHead);
    printf("\n---Now test list reverse functions(end)---\n");

	return;
}

