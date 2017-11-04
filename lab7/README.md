# 实验七：将menu设计为可重用的子系统

> 学号：SA17225363 姓名：王世卿

## 一、实验要求

- 为menu子系统设计接口，并写用户范例代码来实现原来的功能；
- 使用make和make clean来编译程序和清理自动生成的文件；
- 使menu子系统支持带参数的复杂命令，并在用户范例代码中自定义一个带参数的复杂命令；
- 可以使用getopt函数获取命令行参数。


## 二、实验过程
### 1、拉代码
> git clone https://github.com/wsqat/gaoruan.git

![clone.png](http://upload-images.jianshu.io/upload_images/688387-5234cec829deec5e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2、创建文件
> mkdir lab7

![lab7.png](http://upload-images.jianshu.io/upload_images/688387-4ae533289e4c0449.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 三、实验代码
### 1、linktable.h代码如下:
```
#ifndef _LINK_TABLE_H_
#define _LINK_TABLE_H_
#include <pthread.h>
#define SUCCESS 0
#define FAILURE (-1)
/*
 * LinkTable Node Type
 */
typedef struct LinkTableNode tLinkTableNode;
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
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void * args), void * args);
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

### 2、linktable.c代码如下:
```
#include<stdio.h>
#include<stdlib.h>
#include"linktable.h"
typedef struct LinkTableNode
{
    struct LinkTableNode * pNext;
}tLinkTableNode;
typedef struct LinkTable{
    tLinkTableNode *pHead;
    tLinkTableNode *pTail;
    int            SumOfNode;
    pthread_mutex_t mutex;
}tLinkTable;
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
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void * args), void * args)
{
    if(pLinkTable == NULL || Conditon == NULL)
    {
        return NULL;
    }
    tLinkTableNode * pNode = pLinkTable->pHead;
    while(pNode != NULL)
    {    
        if(Conditon(pNode, args) == SUCCESS)
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


### 3、menu.h代码如下:
```
#ifndef _MENU_H
#define _MENU_H

int MenuConfig(char * cmd, char * desc, void (*handler)(int argc, char *argv[]));

int ExecuteMenu();

#endif
```

### 4、menu.c代码如下:
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linktable.h"
#include "menu.h"
#define CMD_MAX_LEN 128
#define CMD_MAX_ARGV_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10


tLinkTable * head = NULL;
void Help(int argc, char *argv[]);



/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char*   cmd;
    char*   desc;
    void     (*handler)(int argc, char *argv[]);
} tDataNode;

int SearchCondition(tLinkTableNode * pLinkTableNode, void * args)
{
    char * cmd = (char*) args;
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;           
}

/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(tLinkTable * head, char * cmd)
{
    return  (tDataNode*)SearchLinkTableNode(head, SearchCondition, (void *)cmd);
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable * head)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode *)pNode);
    }
    return 0;
}

int MenuConfig(char * cmd, char * desc, void (*handler)(int argc, char *argv[]))
{
    tDataNode* pNode = NULL;
    if (head == NULL)
    {
        head = CreateLinkTable();
        pNode = (tDataNode*)malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "Menu List:";
        pNode->handler = Help;
        AddLinkTableNode(head, (tLinkTableNode *)pNode);
    }
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = cmd;
    pNode->desc = desc;
    pNode->handler = handler;
    AddLinkTableNode(head, (tLinkTableNode *)pNode);
}

int ExecuteMenu()
{
    while(1)
    {
        int argc = 0;
        char *argv[CMD_MAX_ARGV_LEN];
        char cmd[CMD_MAX_LEN];
        char *pcmd = NULL;
        printf("Input a cmd number > ");
        pcmd = fgets(cmd, CMD_MAX_LEN, stdin);
        if (pcmd == NULL)
        {
            continue;
        }
        pcmd = strtok(pcmd, " ");
        while (pcmd != NULL && argc < CMD_MAX_ARGV_LEN)
        {
            argv[argc] = pcmd;
            argc++;
            pcmd = strtok(NULL, " ");
        }
        if (argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len - 1) = '\0';
        }

        tDataNode *p = FindCmd(head, argv[0]);
        if( p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc); 
        if(p->handler != NULL) 
        { 
            p->handler(argc, argv);
        }

    }
}

void Help(int argc, char *argv[])
{
    ShowAllCmd(head);
}
```

### 5、test.c代码如下:
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "menu.h"

void Quit(int argc, char *argv[]);
void Version(int argc, char *argv[]);


void Quit(int argc, char *argv[])
{
    exit(0);
}

void Version(int argc, char *argv[])
{
    printf("version7.0\n");
}

void Directory(int argc, char *argv[])
{
	char buf[80];
	getcwd(buf,sizeof(buf));
	printf("current working directory: %s\n",buf);    
}

void Date(int argc, char *argv[])
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p=gmtime(&timep);
	printf("%d\\",1900+p->tm_year);
	printf("%d\\",1+p->tm_mon);
	printf("%d\n",p->tm_mday);
}

int main(int argc,char* argv[])
{
    MenuConfig("version","XXX1.0(Menu program v7.0 inside)",NULL);
    MenuConfig("quit","Quit from XXX",Quit);
    MenuConfig("directory","Show the work path",Directory);
    MenuConfig("date","Show the date",Date);

    ExecuteMenu();
}
```

### 6、Makefile代码如下:
```
CC_PTHREAD_FLAGS   =-lpthread
CC_FLAGS           =-c
CC_OUTPUT_FLAGS    =-o
CC                 =gcc
RM                 =rm
RM_FLAGS           =-f
TARGET=test
OBJS=linktable.o menu.o test.o
all: $(OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) $<

clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGET) *.bak
```

### 7、实验结果截图

![make.png](http://upload-images.jianshu.io/upload_images/688387-24e2f2bd79fb52bd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![menu.png](http://upload-images.jianshu.io/upload_images/688387-a752272c449fe925.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 四、上传代码
```
git add .
git commit -m "add lab7/"
git push
```
![push.png](http://upload-images.jianshu.io/upload_images/688387-1dec173af81cd3b2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 五、实验总结

- Makefile方法能够减轻执行程序时繁琐的指令输入过程，尤其是在Makefile文件中，代码必须以**Tab**键规范格式，不可以用四个空格键。
- gets()方法有缓冲区溢出的问题，为了防止缓冲区溢出攻击的危险，使用fgets()方法更好。
- shell将命令j解析成argc 和 argv传递给执行程序，可以使用getopt函数获取命令行参数。
- 修改menu之后，能够扩展功能，支持对新功能的添加。

