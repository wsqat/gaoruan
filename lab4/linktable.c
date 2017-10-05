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
