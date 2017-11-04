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