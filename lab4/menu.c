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
