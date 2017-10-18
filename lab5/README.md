# 实验五：用callback增强链表模块来实现命令行菜单小程序V2.8

> 学号：SA17225363 姓名：王世卿

## 一、实验要求

- 给lab5-1.tar.gz的代码找quit函数无法执行的bug

- 利用callback函数参数使Linktable的查询接口更加通用

- 注意接口的信息隐藏


## 二、实验过程
### 1、拉代码
> git clone https://github.com/wsqat/gaoruan.git

![clone.png](http://upload-images.jianshu.io/upload_images/688387-6d39d456a9c40fb0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2、创建文件
> mkdir lab5 并解压文件lab5-1.tar.gz到lab5/目录下

![lab5.png](http://upload-images.jianshu.io/upload_images/688387-372984627c854670.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3、找quit函数无法执行的bug
> gcc linktable.c menu.c -o menu       

输入'quit'指令，发现执行quit命令无法退出程序

![quit.png](http://upload-images.jianshu.io/upload_images/688387-28ff6eda01766445.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> *查看代码，发现linktable.c中的SearchLinkTableNode函数存在问题.while循环条件while(pNode != pLinkTable -> pTail)使得函数在找到链表最后一个节点时即退出循环,因此无法访问最后一个节点.将while(pNode != pLinkTable -> pTail)改为while(pNode != NULL)即可*

- **定位bug**
![bug.png](http://upload-images.jianshu.io/upload_images/688387-386ae26a974a792d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- **修改bug**
![modify-bug.png](http://upload-images.jianshu.io/upload_images/688387-68fedb3465930fcd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- **测试通过**
![pass.png](http://upload-images.jianshu.io/upload_images/688387-578b5d59850d03a7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 4、使用Callback编写linktable.h
linktable.h代码如下:
```
/********************************************************************/
/* Copyright (C) SSE-USTC, 2012-2013                                */
/*                                                                  */
/*  FILE NAME             :  linktabe.h                             */
/*  PRINCIPAL AUTHOR      :  Wang Shiqing                           */
/*  SUBSYSTEM NAME        :  LinkTable                              */
/*  MODULE NAME           :  LinkTable                              */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2017/10/18                             */
/*  DESCRIPTION           :  interface of Link Table                */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by Wang Shiqing,2017/10/18
 *
 */

#ifndef _LINK_TABLE_H_
#define _LINK_TABLE_H_
#include <pthread.h>
#define SUCCESS 0
#define FAILURE (-1)
/*
 * LinkTable Node Type
 */
typedef struct LinkTableNode
{
    struct LinkTableNode *pNext;
}tLinkTableNode;
/*
 * LinkTable Type
 */
typedef struct LinkTable tLinkTable;
/*
 * Create a LinkTable
 */
tLinkTable * CreateLinkTable();
/*
 * Delete a LinkTable
 */
int DeleteLinkTable(tLinkTable *pLinkTable);
/*
 * Add a LinkTableNode to LinkTable
 */
int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
/*
 * Delete a LinkTableNode from LinkTable
 */
int DelLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
/*
 * Search a LinkTableNode from LinkTable
 * int Conditon(tLinkTableNode * pNode);
 */
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode,void * args),void *args);
/*
 * get LinkTableHead
 */
tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable);
/*
 * get next LinkTableNode
 */
tLinkTableNode * GetNextLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
#endif /* _LINK_TABLE_H_ */

```

### 5、使用Callback编写linktable.c
linktable.c代码如下:
```
#include<stdio.h>
#include<stdlib.h>
#include"linktable.h"
struct LinkTable
{
    tLinkTableNode *pHead;
    tLinkTableNode *pTail;
    int         SumOfNode;
    pthread_mutex_t mutex;
};
/*
 * Create a LinkTable
 */
tLinkTable * CreateLinkTable()
{
    tLinkTable * pLinkTable = (tLinkTable *)malloc(sizeof(tLinkTable));
    if(pLinkTable == NULL)
    {
        return NULL;
    }
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    pthread_mutex_init(&(pLinkTable->mutex), NULL);
    return pLinkTable;
}
/*
 * Delete a LinkTable
 */
int DeleteLinkTable(tLinkTable *pLinkTable)
{
    if(pLinkTable == NULL)
    {
        return FAILURE;
    }
    while(pLinkTable->pHead != NULL)
    {
        tLinkTableNode * p = pLinkTable->pHead;
        pthread_mutex_lock(&(pLinkTable->mutex));
        pLinkTable->pHead = pLinkTable->pHead->pNext;
        pLinkTable->SumOfNode -= 1 ;
        pthread_mutex_unlock(&(pLinkTable->mutex));
        free(p);
    }
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    pthread_mutex_destroy(&(pLinkTable->mutex));
    free(pLinkTable);
    return SUCCESS;
}
/*
 * Add a LinkTableNode to LinkTable
 */
int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
        return FAILURE;
    }
    pNode->pNext = NULL;
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->pHead == NULL)
    {
        pLinkTable->pHead = pNode;
    }
    if(pLinkTable->pTail == NULL)
    {
        pLinkTable->pTail = pNode;
    }
    else
    {
        pLinkTable->pTail->pNext = pNode;
        pLinkTable->pTail = pNode;
    }
    pLinkTable->SumOfNode += 1 ;
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return SUCCESS;
}
/*
 * Delete a LinkTableNode from LinkTable
 */
int DelLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
        return FAILURE;
    }
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->pHead == pNode)
    {
        pLinkTable->pHead = pLinkTable->pHead->pNext;
        pLinkTable->SumOfNode -= 1 ;
        if(pLinkTable->SumOfNode == 0)
        {
            pLinkTable->pTail = NULL;
        }
        pthread_mutex_unlock(&(pLinkTable->mutex));
        return SUCCESS;
    }
    tLinkTableNode * pTempNode = pLinkTable->pHead;
    while(pTempNode != NULL)
    {
        if(pTempNode->pNext == pNode)
        {
            pTempNode->pNext = pTempNode->pNext->pNext;
            pLinkTable->SumOfNode -= 1 ;
            if(pLinkTable->SumOfNode == 0)
            {
                pLinkTable->pTail = NULL;
            }
            pthread_mutex_unlock(&(pLinkTable->mutex));
            return SUCCESS;
        }
        pTempNode = pTempNode->pNext;
    }
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return FAILURE;
}
/*
 * Search a LinkTableNode from LinkTable
 * int Conditon(tLinkTableNode * pNode);
 */
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode,void * args), void * args)
{
    if(pLinkTable == NULL || Conditon == NULL)
    {
        return NULL;
    }
    tLinkTableNode * pNode = pLinkTable->pHead;
    while(pNode != NULL)
    {
        if(Conditon(pNode,args) == SUCCESS)
        {
            return pNode;
        }
        pNode = pNode->pNext;
    }
    return NULL;
}
/*
 * get LinkTableHead
 */
tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable)
{
    if(pLinkTable == NULL)
    {
        return NULL;
    }
    return pLinkTable->pHead;
}
/*
 * get next LinkTableNode
 */
tLinkTableNode * GetNextLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
    {
        return NULL;
    }
    tLinkTableNode * pTempNode = pLinkTable->pHead;
    while(pTempNode != NULL)
    {
        if(pTempNode == pNode)
        {
            return pTempNode->pNext;
        }
        pTempNode = pTempNode->pNext;
    }
    return NULL;
}
```

### 6、使用Callback编写menu.c
menu.c代码如下:
```
#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10

void help();
void add();
void sub();
void max();
void min();
void ls();
void quit();

/* data struct and its operations */
typedef struct DataNode
{
    tLinkTableNode* pNext;
    char*   cmd;
    char*   desc;
    int     (*handler)();
} tDataNode;
int SearchCondition(tLinkTableNode* pLinkTableNode, void* args)
{
    char *cmd = (char*)args;
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;           
}
/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(tLinkTable* head, char* cmd)
{
    return  (tDataNode*)SearchLinkTableNode(head, SearchCondition, (void*)cmd);
}
/* show all cmd in listlist */
int ShowAllCmd(tLinkTable* head)
{
    tDataNode* pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    return 0;
}
int InitMenuData(tLinkTable** ppLinktable)
{
    *ppLinktable = CreateLinkTable();
    tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "help!";
    pNode->handler = help;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "add";
    pNode->desc = "addition";
    pNode->handler = add; 
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "sub";
    pNode->desc = "sub";
    pNode->handler = sub; 
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "ls";
    pNode->desc = "list";
    pNode->handler = ls; 
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "max";
    pNode->desc = "max";
    pNode->handler = max; 
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "min";
    pNode->desc = "min";
    pNode->handler = min; 
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "Quit from Menu Program V2.8";
    pNode->handler = quit; 
    AddLinkTableNode(*ppLinktable, (tLinkTableNode*)pNode);

    return 0; 
}
/* menu program */
tLinkTable* head = NULL;
int main()
{
    InitMenuData(&head); 
   /* cmd line begins */
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("please input a cmd >\n");
        scanf("%s", cmd);
        tDataNode* p = FindCmd(head, cmd);
        if( p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc); 
        if(p->handler != NULL) 
        { 
            p->handler();
        }

    }
}

void help()
{
    ShowAllCmd(head);
}

void add()
{
    double num1;
    double num2;
    double result;

    printf("Addition!Please input two numbers!\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%lf%lf", &num1, &num2);
    result=num1+num2;
    printf("%.2lf\n", result);
}

void sub()
{    
    double minuend;
    double meiosis;
    double result;

    printf("subtraction!Please input two numbers!\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%lf%lf", &minuend, &meiosis);
    result=minuend-meiosis;
    printf("%.2lf\n", result);
}

void mul()
{    
    double num1;
    double num2;
    double result;

    printf("Multiplication!Please input two numbers!\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%lf%lf", &num1, &num2);
    result=num1*num2;
    printf("%.2lf\n", result);
}

 void divi()
{   
    double dividend;
    double divisor;
    double result;

    printf("Divition!Please input two numbers!\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%lf%lf", &dividend, &divisor);
    if(divisor==0)
    {
        printf("Error!Dividor can not be zero!\n");
    }
    result=dividend / divisor;
    printf("%.2lf\n", result);

 }

void max()
{
    int a,b;
    int max;
    printf("please enter two integers:\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%d",&a);
    scanf("%d",&b);
    if(a>b)
        max=a;
    else
        max=b;
    printf("the maximum of %d and %d is %d\n",a,b,max);
}

void min()
{
    int a,b;
    int min;
    printf("please enter two integers:\n");
    scanf("%d",&a);
    scanf("%d",&b);
    if(a<b)
         min=a;
    else
        min=b;
    printf("the minimum of %d and %d is %d\n",a,b,min);
}

void ls()
{
    system("ls");
}

void Error()
{ 
    printf("Command not found!\n");
}

void quit()
{
    exit(0);
}
```

### 7、测试程序

![display1.png](http://upload-images.jianshu.io/upload_images/688387-6a0e60805e88b883.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![display2.png](http://upload-images.jianshu.io/upload_images/688387-d191bbb4699d40fc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



## 三、上传代码
```
git add .
git commit -m "add lab5/"
git push
```
![push.png](http://upload-images.jianshu.io/upload_images/688387-22c9fce67f783948.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 四、实验总结

- 回调函数是把函数的指针作为参数传递给另一个函数，回调函数不是由该函数的实现方直接调用，而是在特定的事件或条件发生时由另外的一方调用的，用于对该事件或条件进行响应。

- 回调函数可以允许用户把需要调用的函数的指针作为参数传递给一个函数，以便该函数在处理相似事件的时候可以灵活的使用不同的方法。

- callback函数的使用提高了代码的重用性，实现了更松的耦合。同时将一些内部结构接口隐藏，简化了用户接口，更保证了使用安全，减少误操作。
