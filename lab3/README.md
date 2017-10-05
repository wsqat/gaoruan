# 实验三：内部模块化的命令行菜单小程序V2.0
> 学号：SA17225363 姓名：王世卿

## 一、实验要求
实现内部模块化的命令行菜单小程序V2.0

注意代码的业务逻辑和数据存储之间的分离，即将系统抽象为两个层级：菜单业务逻辑和菜单数据存储

要求:
  1. 遵守代码风格规范，参考借鉴代码设计规范的一些方法；  
  2. 代码的业务逻辑和数据存储使用不同的源文件实现，即应该有2个.c和一个.h作为接口文件。

## 二、实验过程
### 1、拉代码
> git clone https://github.com/wsqat/gaoruan.git

![gaoruan.png](http://upload-images.jianshu.io/upload_images/688387-69dcb64ee1c43ae9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 2、创建文件
> mkdir lab3

![lab3.png](http://upload-images.jianshu.io/upload_images/688387-57b6452d8f481c44.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 3、编写linklist.h
**linklist.h代码如下：**

```
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
```
![linklist.h.png](http://upload-images.jianshu.io/upload_images/688387-c61fc8229d8a62d2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 4、编写linklist.c
**linklist.c代码如下：**

```
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
```
![linklist.c.png](http://upload-images.jianshu.io/upload_images/688387-b084ef2127b53df4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 5、编写menu.c
**menu.c代码如下：**
```
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
```

![menu.c.png](http://upload-images.jianshu.io/upload_images/688387-98ac84e266ee0e27.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 6、编译 & 运行截图
> gcc menu.c linklist.c -o menu   
> ls
> ./menu

![help.png](http://upload-images.jianshu.io/upload_images/688387-fdf2afe693143da0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![cmd.png](http://upload-images.jianshu.io/upload_images/688387-03cee351aa61a0ac.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![quit.png](http://upload-images.jianshu.io/upload_images/688387-89d9fbfb388e6354.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 三、上传代码
```
git add .
git commit -m "add lab3/"
git push
```
![push.png](http://upload-images.jianshu.io/upload_images/688387-22c9fce67f783948.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 四、实验总结
### 1、编码收获
- 学习了模块化的编程思想  
- 提高了menu程序的重用性  
- 掌握学习了c程序的编译调试方法

### 2、代码设计中的一些常见方法:
- KISS(keep   it simple & stupid)
- using   design to frame the code(matching design with implementation)
- including   pseuducode
- 不要和陌生人说话原则
- 合理利用Control   Structures、Data Structures来简化代码
- 一定要有错误处理
