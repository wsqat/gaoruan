#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "linklist.h"

int Help();
int Addition();
int Fact();
int SleepCmd();
int EchoCmd();
int TimeCmd();
int Quit();

#define CMD_MAX_LEN 128
#define DESC_LEN 1024
#define CMD_NUM 10

static tDataNode head[] = 
{
    {"help", "This is a help cmd.", Help, &head[1]}, 
    {"version", "Menu program v1.0.", NULL, &head[2]},
    {"add", "Addition for two integer.", Addition, &head[3]},
    {"author", "The author of this program is a good person.", NULL, &head[4]},
    {"fact", "Factorial for one integer.", Fact, &head[5]},
    {"sleep", "Sleep several seconds by input value.", SleepCmd, &head[6]},
    {"echo", "Show what you input in the command line.", EchoCmd, &head[7]},
    {"time", "Show the system time.", TimeCmd, &head[8]},
    {"quit", "Quit from menu.", Quit, NULL}
};

int main()
{
    char cmd[CMD_MAX_LEN];

    Help();
    printf("\n");
    while (1)
    {
        printf("Please input a cmd: \n>");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        if (p == NULL)
        {
            printf("You have entered a wrong cmd.\n");
            printf("Please use 'help' to get the help!\n\n");
            continue;
        }
        printf("%s - %s\n", p -> cmd, p -> desc);
        if (p -> handler != NULL)
            p -> handler();
        printf("\n");
    }
    return 0;
}

/* Call ShowAllCmd() in module linklist to implement Help(). */
int Help()
{
    ShowAllCmd(head);

    return 0;
}

/* Ask the user to input two integers and compute its addition results where no error detection. */
int Addition()
{
    int addnum1, addnum2;

    printf("Please input two numbers.\n");
    printf("Use 'Blank' or 'Enter' to divide the two numbers.\n");
    scanf("%d", &addnum1);
    scanf("%d", &addnum2);
    printf("The answer of these two numbers is %d.\n", addnum1 + addnum2);

    return 0;
}

int Fact()
{
    int factnum, factans;

    factans = 1;
    printf("Please input a number you want to compute factorial(less than 31).\n");
    scanf("%d", &factnum);

    //Use iteration to compute factorial
    if (factnum < 0)
        printf("Wrong input, abort!\n");
    else
    {
        while (factnum >= 1)
        {
            factans *= factnum;
            --factnum;
        }
    }            
    printf("The answer is %d.\n", factans);

    return 0;
}

/* Ask the user how many seconds they want to sleep and notice the user every second. */
int SleepCmd()
{
    int i, sleeptime;

    printf("Please input the time you want to sleep(better smaller one):\n");
    scanf("%d", &sleeptime);
    for (i = 0; i < sleeptime; ++i)
    {
        printf("I have slept %d seconds.\n", i);
        sleep(1);
    }
    printf("Time to wake up.\n");

    return 0;
}

/* Output what the user input before the user input EOF. */
int EchoCmd()
{
    char ch;

    printf("Please end your input with 'CTRL' + 'D'(means EOF in UNIX/LINUX).\n");
    while ((ch = getchar()) != EOF)
        printf("%c", ch);
    printf("\n");

    return 0;
}

/* Call ShowLocalTime() in module linklist to implement TimeCmd(). */
int TimeCmd()
{
    ShowLocalTime();

    return 0;
}

int Quit()
{
    printf("Bye, see you!\n");
    exit(0);
}
