typedef struct DataNode
{
    char *cmd;
    char *desc;
    int (*handler)();
    struct DataNode *next;
}tDataNode;

/* Find a command in the linklist and return the pointer */
tDataNode* FindCmd(tDataNode *head, char *cmd);

/* Show all commands */
int ShowAllCmd(tDataNode *head);

/* Show local time */
int ShowLocalTime();
