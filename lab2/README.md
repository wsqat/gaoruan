#实验二：命令行菜单小程序V1.0，具体要求参见视频

> 学号：SA17225363 姓名：王世卿


## 一、实验要求

### 1、代码风格规范：
代码风格的原则：简明、易读、无二义性；
缩进、命名、注释等代码编排的风格规范；

### 2、具体要求（参照视频中的具体实验过程）：
 - 实现一个命令行的菜单小程序，执行某个命令时调用一个特定的函数作为执行动作，实现的命令个数不少于8个；

- 类似ftp的help目录或者bash的help目录；

- 程序循环、接收用户的命令，如help、others等命令；

- 可以广泛通用的命令行菜单子系统组件，可方便地定制而嵌入到其他系统；



## 二、实验过程
### 1、拉取代码
```
git clone https://github.com/wsqat/gaoruan.git
```

![clone.png](http://upload-images.jianshu.io/upload_images/688387-ad6ea573dfc29024.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 2、更改~/.vimrc的值

```
#"Tab键宽度为4个空格"    
set tabstop=4
#"使用C语言对齐方式"    
set cindent
#"搜索时关键字高亮"    
set hlsearch  
```
![~/.vimrc.png](http://upload-images.jianshu.io/upload_images/688387-d7bbe329b298ac53.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 3、编码过程
完整代码如下：
```
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

void Help();
void Max();
void Min();
void Add();
void Sub();

int main()
{
    char cmd[128];
    Help();
    while (1)
    {
        printf("Menu->");
        scanf("%s", cmd);
        if (strcmp(cmd, "help") == 0)
        {
            Help();    
        }
        else if (strcmp(cmd, "ls") == 0)
        {                            
            system(cmd);
        }
        else if (strcmp(cmd, "pwd") == 0)
        {
            system(cmd);
        }
        else if (strcmp(cmd, "max") == 0)
        {
            Max();
        }
        else if (strcmp(cmd, "min") == 0)
        {
            Min();
        }
        else if (strcmp(cmd, "add") == 0)
        {
            Add();
        }
        else if (strcmp(cmd, "sub") == 0)
        {
            Sub();
        }
        else if (strcmp(cmd, "quit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Error: unsupported command, you can use 'help' to list the available commands\n");
        }
    }
}

void Help()
{
    printf("*----------*--------Help-------------------   *\n");
    printf("*   name   *      description                *\n");
    printf("*----------*----------------------- -------  *\n");
    printf("*   help   *      cmd tips                   *\n");
    printf("*   ls     *      list files                 *\n");
    printf("*   pwd    *    print working directory      *\n");
    printf("*   max    *    find the maximum             *\n");
    printf("*   min    *    find the minimum             *\n");
    printf("*   add    *    addition of two numbers      *\n");
    printf("*   sub    *    subtraction of two numbers   *\n");
    printf("*   quit   *      exit cmd                   *\n");
}

/*
* @Description: Find the maximum
*/
void Max()
{
    int a,b;
    int max;
    printf("please enter two integers , such as:12 23:\n");
    scanf("%d",&a);
    scanf("%d",&b);

    if(a > b)
        max=a;
    else
        max=b;

    printf("the maximum of %d and %d is %d\n",a,b,max);
}

/*
* @Description: Find the minimum
*/
void Min()
{
    int a,b;
    int min;
    printf("please enter two integers , such as:12 6:\n");
    scanf("%d",&a);
    scanf("%d",&b);

    if (a < b)
        min=a; 
    else
        min=b;

    printf("the minimum of %d and %d is %d\n",a,b,min);
}

/*
* @Description: Addition of two numbers
*/
void Add()
{
    double num1;
    double num2;
    double result;

    printf("------*--------*------*-------*------\n");
    printf("Addition!Please input two numbers! Such as:1 2 \n");
    scanf("%lf%lf", &num1, &num2);
    result=num1+num2;
    printf("%.2lf\n", result);
    printf("------*--------*------*-------*------\n");
}

/*
* @Description: subtraction of two numbers
*/
void Sub()
{    
    double minuend;
    double meiosis;
    double result;

    printf("------*--------*------*-------*------\n");
    printf("subtraction!Please input two numbers! Such as:1 2 \n");
    scanf("%lf%lf", &minuend, &meiosis);
    result=minuend-meiosis;
    printf("%.2lf\n", result);
    printf("------*--------*------*-------*------\n");
}
```
### 4、运行截图
```
gcc menu.c -o menu
ls
./menu
```
![menu.png](http://upload-images.jianshu.io/upload_images/688387-28ac006607cd77dc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![help.png](http://upload-images.jianshu.io/upload_images/688387-f9ed94cd056efabe.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![ls、pwd、max、min等指令.png](http://upload-images.jianshu.io/upload_images/688387-dbfa9c2ccd7af60f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 5、上传代码
```
git add .
git commit -m "add lab2/"
git push
```
![push.png](http://upload-images.jianshu.io/upload_images/688387-c3ed9b0741fc9364.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


## 四、总结

    代码风格的原则：简明、易读、无二义性

- 缩进：4个空格
- 行宽：<100个字符
- 复杂表达式中用（）清晰表达逻辑优先级
- 所有{和}都独占一行且成对对齐
- 不要把多条语句和多个变量定义放在同一行
- 注释使用英文，不要用中文，保持源代码是ASCII字符格式文件



