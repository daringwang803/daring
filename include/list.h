/*
 * @Description: 
 * @Author: daringwang
 * @Date: 2021-07-10 08:14:07
 * @LastEditTime: 2021-07-10 14:06:43
 * @LastEditors: daringwang
 * @Reference: All rights reserved by Daring Wang.
 */


#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include "public.h"

typedef struct ListNode {
	int listLen;
	int val;
	struct ListNode* next;

}List;






/********************
*函数声明
********************/
List* list_twoExchange(List* beforeC, List* head);
List* list_createList(int *pValue, int valNum);
void list_deleteList(List* head);
void list_printList(List* head);
void list_insertHeadList(List* head, List *newNode);
struct ListNode* list_reverseList(struct ListNode* head) ;
struct ListNode* list_exchange(struct ListNode* head) ;

VOID daring_listTest();
VOID daring_listReverseTest();

#endif
