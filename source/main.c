#include <stdio.h>
#include <string.h>
#include "list.h"
#include "ipv6.h"
#include "array.h"
#include "sort.h"
#include "leetcode.h"

void f(int b[4][5])
{
	printf("b[0][0]=%d\n",b[0][0]);
	return;
}

int  sub(char x,char y)
{
	int z;
	z = x % y;
	return z;
}

/******************************
* 
*******************************/
int findMaxForm(char** strs, int strsSize, int m, int n)
{
	int index = 0;
	int index2 = 0;
	int num = 0;
	int mm = 0;/*表示0的个数*/
	int nn = 0;/*表示1的个数*/
	char** ptr = NULL;
	//int s = 0;

	if (NULL == strs || NULL == *strs)
	{
		return 0;
	}
	ptr = strs;

	for (index = 0; index < strsSize; index++)
	{
		for (index2 = 0; index2 < strlen(ptr[index]); index2++)
		{
			if ('0' == *(ptr[index] + index2))
			{
				mm++;
			}
			if ('1' == *(ptr[index]+ index2))
			{
				nn++;
			}
		}
		if ((mm < m) && (nn < n))/*满足子集条件*/
		{
			num++;
		}
		mm = 0;
		nn = 0;
	}
	return num;

}

#define SIZE 10
int main()
{
	/*int x = 1, a = 0, b = 0;;
	switch (x)
	{
	case 0:
		b++;

	case 1:
		a++;
	case 2:
		a++;
		b++;
		//break;
	case 3:
		a++;
		b++;
	}
	printf("a=%d,b=%d\n",a,b);*/

	/*int x = 0, y = 1, z = 0;
	if (x = z = y)
		x = 3;
	printf("%d,%d\n",x,z);*/
	
	/*char ch;
	ch = getchar();
	switch (ch)
	{
		{case 'H':
			printf("Hello!\n");
		case 'G':
			printf("Good morning!\n");
		default:
			printf("Bye-bye!\n"); }
	}*/

	/*printf("*\40*\n");  //'\40'表示空格
	*/

	/*int x = 010;
	printf("x=%u\n");*/

	/*int x = 1,y = 2;
	printf("%d",(x,y));*/

	/*int x = 1;
	x = 10, x + 10, x++;
	printf("x=%d\n", x);*/

	/*int b[][5] = {2,3,4,5,6};

	f(b);*/

	/*int g = 5, h = 3, k;
	k = sub(g,h);
	printf("%d\n",k);*/

	//int a[3][] = { {1,2}, {1,2,3}, {1,2,3,4} };

	/*int n;
	scanf_s("%d",&n);
	int a[SIZE];
	int aa[n];*/

	/*char s1[5] = { 0 }, s2[7] = {0};
	scanf_s("%s",s1);
	scanf_s("%s", s2);
	printf("s1=%s,s2=%s\n",s1,s2);*/

	/*char str[5][7] = {0};
	memcpy((char *)str[0], "10" , 3);
	memcpy((char *)str[1], "1" , 2);
	memcpy((char *)str[2], "0" , 2);
	memcpy((char*)str[3], "0001", 5);
	memcpy((char*)str[4], "111001", 7);
	char* p = str[0];

	//{ "10", "0001", "111001", "1", "0" };
	int i = findMaxForm(&p, 3, 1, 1);
	printf("i = %u\n",i);*/

	/*int stt[] = {1,2,3,4,5};
	List* head = list_createList(stt, sizeof(stt)/sizeof(int));
	list_printList(head);
	
	printf("list has two two exchanged!\n");
	head = list_exchange(head);
	list_printList(head);
	//list_deleteList(head);
	//free(head);*/

	/*int stt[] = { 1,2,3,4,5 };
	List* head = list_createList(stt, sizeof(stt) / sizeof(int));
	list_printList(head);
	
	printf("after revert:\n");
	head = list_reverseList(head);
	list_printList(head);*/

	/*char ch[4] = {0x31, 0x32,0x33, 0x34};
	int t = 0;
	memcpy(&t, &ch, 4);
	printf("sizeof(int)=%u\n",sizeof(int));
	printf("t=%x\n",t);*/

	daring_test_ipv6RangeAdd();

	daring_test_array();

	daring_listTest();

	daring_listReverseTest();

	daring_test_sort_bubble();

	daring_test_sort_quick();

	daring_leetcode1();
	
	daring_leetcode2();

	daring_leetcode3();
	
	return 0;

}
