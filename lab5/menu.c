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