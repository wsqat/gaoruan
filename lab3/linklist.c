#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linklist.h"

tDataNode* FindCmd(tDataNode *head, char *cmd)
{
    if (head == NULL || cmd == NULL)
    {
        return NULL;
    }
    tDataNode *p = head;
    while (p != NULL)
    {
        if (!strcmp(p -> cmd, cmd))
        {
            return p;
        }
        p = p -> next;
    }

    return NULL;
}

int ShowAllCmd(tDataNode *head)
{
    printf("Menu List:\n");
    tDataNode *p = head;
    while (p != NULL)
    {
        printf("%s - %s\n", p -> cmd, p -> desc);
        p = p -> next;
    }

    return 0;
}

int ShowLocalTime()
{
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    //printf("Local time is: %d:%d:%d\n", local -> tm_hour, local -> tm_min, local -> tm_sec);
    printf("The current date/time is: %s", asctime(local));

    return 0;
}
