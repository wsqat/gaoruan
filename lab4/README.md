# 实验四：用可重用的链表模块来实现命令行菜单小程序V2.5

> 学号：SA17225363 姓名：王世卿

## 一、实验要求
用可重用的链表模块来实现命令行菜单小程序V2.5

- 用可重用的链表模块来实现命令行菜单小程序，执行某个命令时调用一个特定的函数作为执行动作

- 链表模块的接口设计要足够通用，命令行菜单小程序的功能保持不变

- 可以将通用的Linktable模块集成到我们的menu程序中

- 接口规范

## 二、实验过程
### 1、拉代码
> git clone https://github.com/wsqat/gaoruan.git

![gaoruan.png](http://upload-images.jianshu.io/upload_images/688387-de3ecb37a50ad926.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2、创建文件
> mkdir lab4

![lab4.png](http://upload-images.jianshu.io/upload_images/688387-7cf32f0f34561c82.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 3、编写linktable.h
linktable.h代码如下:
```
/*
 * Created by sagewang on 2017/10/05
 */
#ifndef _LINK_TABLE_H_
#define _LINK_TABLE_H_
#include <pthread.h>
#define  SUCCESS 0
#define  FAILURE (-1)

/*
 * LinkTableNode Node Type
 */
typedef struct LinkTableNode
{
    struct LinkTableNode *pNext;
}tLinkTableNode;

/*
 * LinkTableNode Type
 */
typedef struct LinkTable
{
    tLinkTableNode * pHead;
    tLinkTableNode * pTail;
    int            SumOfNode;
    //pthread_mutex_t_mutex ;
}tLinkTable;

tLinkTable * CreateLinkTable();
int DelLinkTable(tLinkTable* pLinkTable);
int AddLinkTable(tLinkTable* pLinkTable,tLinkTableNode *pNode);
int DelLinkTableNode(tLinkTable* pLinkTable,tLinkTableNode *pNode);
tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable);
tLinkTableNode * GetNextLinkTableNode(tLinkTable* pLinkTable,tLinkTableNode *pNode);
#endif
```

### 4、编写linktable.c
linktable.c代码如下:
```
/*
 * Created by sagewang on 2017/10/05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linktable.h"

tLinkTable * CreateLinkTable()
{
    tLinkTable *pLinkTable=(tLinkTable*)malloc(sizeof(tLinkTable));
    if (pLinkTable == NULL)
    {
        return NULL;
        printf("create linktable failure! ");
    }
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    return pLinkTable;
}

int DelLinkTable(tLinkTable* pLinkTable)
{
    if(pLinkTable == NULL)
        return FAILURE;
    
    while(pLinkTable->pHead != NULL)
    {
        tLinkTableNode *p = pLinkTable->pHead;
        pLinkTable->pHead = p->pNext;
        free(p);
    }
    
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;
    free(pLinkTable);
    return SUCCESS;
}

int AddLinkTable(tLinkTable* pLinkTable,tLinkTableNode *pNode)
{ 
    if(pLinkTable == NULL || pNode == NULL)
        return FAILURE;
    if(pLinkTable->pHead == NULL && pLinkTable->pTail == NULL)
    {
        pLinkTable->pHead = pNode;
        pLinkTable->pTail = pNode;
        pLinkTable->pTail = NULL;
        pLinkTable->SumOfNode = 1;
    }
    else
    {
        pLinkTable->pTail->pNext = pNode;
        pLinkTable->pTail = pNode;
        pLinkTable->pTail->pNext = NULL;
        pLinkTable->SumOfNode ++;
    }
    return SUCCESS;
}

int DelLinkTableNode(tLinkTable* pLinkTable,tLinkTableNode *pNode)
{
    if (pLinkTable == NULL)
        return FAILURE;
    tLinkTableNode *pWork = pLinkTable->pHead;
    tLinkTableNode *pre = pWork;
    
    if (pLinkTable->pHead == pNode)
    {
        pLinkTable->pHead = pWork->pNext;
        free(pWork);
        return SUCCESS;
    }

    while (pWork != NULL)
    {
        if(pWork == pNode)
        {
            pre->pNext = pWork->pNext;
            free(pWork);
            return SUCCESS;
        }
        pre = pWork;
        pWork = pWork->pNext;
    }

    return FAILURE;
}

tLinkTableNode * GetLinkTableHead(tLinkTable *pLinkTable)
{
    if (pLinkTable->pHead == NULL)
    {
        printf("LinkTable is empty\n");
        return NULL;
    }
    return pLinkTable->pHead;
}

tLinkTableNode * GetNextLinkTableNode(tLinkTable* pLinkTable,tLinkTableNode *pNode)
{
    if (pLinkTable == NULL || pNode == NULL)
    {
        printf("LinkTable is empty\n");
        return NULL;
    }
    
    tLinkTableNode *pWork = pLinkTable->pHead;
    
    while(pWork != NULL)
    {
        if(pWork == pNode)
            return pWork->pNext;
        pWork = pWork->pNext;
    }

    return NULL;
}
```

### 5、编写menu.c
menu.c代码如下:
```
/*
 * Created by sagewang on 2017/10/05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "linktable.h"

#define CMD_MAX_LEN 128
#define DESC_LEN 1024
#define CMD_NUM 10

int Help();
int Add();
int Sub();
int Multi();
int Divide();
int Time();
int Power();
int Quit();

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char* cmd;
    char* desc;
    int (*handler)();
}tDataNode;

tDataNode * FindCmd(tLinkTable *head, char *cmd)
{
    tDataNode *pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        if(strcmp(pNode->cmd, cmd) == 0)
        {
            return pNode;
        }
        pNode = (tDataNode*)GetNextLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    return NULL;
}

int ShowAllCmd(tLinkTable *head)
{
    tDataNode *pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf("%s ---- %s\n", pNode->cmd, pNode->desc);
        pNode= (tDataNode*)GetNextLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    return 0;
}

static tDataNode menu[] =
{
        {(tLinkTableNode*)&menu[1],"version", "menu program v2.5",NULL},
        {(tLinkTableNode*)&menu[2],"help", "this is help cmd!", Help},
        {(tLinkTableNode*)&menu[3],"add", "this is add cmd!", Add},
        {(tLinkTableNode*)&menu[4],"sub", "this is sub cmd!", Sub},
        {(tLinkTableNode*)&menu[5],"mul", "this is multi cmd!", Multi},
        {(tLinkTableNode*)&menu[6],"div", "this is divide cmd!", Divide},
        {(tLinkTableNode*)&menu[7],"pow", "this is power cmd!", Power},
        {(tLinkTableNode*)&menu[8],"time", "this is time cmd!", Time},
        {(tLinkTableNode*)NULL,"quit", "this is quit cmd", Quit}
};

int InitMenuData(tLinkTable **ppLinkTable)
{
    *ppLinkTable = CreateLinkTable();
    (*ppLinkTable)->pHead = (tLinkTableNode*)&menu[0];
    (*ppLinkTable)->pTail = (tLinkTableNode*)&menu[8];
    (*ppLinkTable)->SumOfNode = 9;
}

tLinkTable *head = NULL;

int main()
{
    InitMenuData(&head);
    printf("Welcome!Use 'help' to get how to use this system.\n");
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("input a cmd >");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        printf("%d\n", head->SumOfNode);
        if(p == NULL)
        {
            printf("Wrong cmd!Use 'help' to get how to use this system.\n");
            continue;
        }
        printf("%s ---- %s\n", p->cmd, p->desc);
        if(p->handler != NULL)
        {
            p->handler();
        }
    }
}

int Help()
{
    ShowAllCmd(head);
}

int Add()
{
    int a,b;
    printf("Please input two integer numbers:\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%d %d", &a, &b);
    int c = a + b;
    printf("The result of add cmd is:\n");
    printf("%d+%d=%d\n", a,b,c);
    return 0;
}

int Sub()
{
    int a,b;
    printf("Please input two integer numbers:\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%d %d", &a, &b);
    int c = a - b;
    printf("The result of sub cmd is:\n");
    printf("%d-%d=%d\n", a,b,c);
    return 0;
}

int Multi()
{
    int a,b;
    printf("Please input two integer numbers:\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%d %d", &a, &b);
    int c = a * b;
    printf("The result of mul cmd is:\n");
    printf("%d*%d=%d\n", a,b,c);
    return 0;
}

int Divide()
{
    int a,b;
    printf("Please input two integer numbers:\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%d %d", &a, &b);
    int c = a / b;
    printf("The result of div cmd is:\n");
    printf("%d/%d=%d\n", a,b,c);
    return 0;
}

int Power()
{
    double a,b;
    printf("Please input two double numbers:\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%lf %lf", &a, &b);
    double c = pow(a, b);
    printf("The result of pow cmd is: \n");
    printf("%.6f^%.6f=%.6f\n", a,b,c);
    return 0;
}

int Time()
{
    time_t t = time(0);
    char temp[64];
    strftime(temp, sizeof(temp), "%Y/%m/%d %X %A", localtime(&t));
    puts(temp);
    return 0;
}

int Quit()
{
    exit(0);
}
```

### 6、编译程序
> gcc menu.c linktable.c -o menu -lm

![menu.png](http://upload-images.jianshu.io/upload_images/688387-b310d50d1d0a4cf3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 7、测试程序

![display.png](http://upload-images.jianshu.io/upload_images/688387-4fd25753db154f6b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![display.png](http://upload-images.jianshu.io/upload_images/688387-dda996f77867df66.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



## 三、上传代码
```
git add .
git commit -m "add lab4/"
git push
```
![push.png](http://upload-images.jianshu.io/upload_images/688387-22c9fce67f783948.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 四、实验总结
### 1、编码收获
- 体会到接口使代码开发效率更高
- 提高了menu程序的重用性  
- 掌握学习了c程序的编译调试方法

### 2、代码设计中的一些常见方法:
- 用表达式作为判断条件，不要用布尔变量做比较
- 代码风格的原则：简明、易读、无二异性

