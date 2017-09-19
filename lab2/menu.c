/*
*@FileName: menu.c
*@Author: sagewang
*@Time: 2017-09-19
*@Descriptions: Small Menu Program
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// some cmd functions
void Help();
void ShowTime();
void Max();
void Min();
void Add();
void Sub();
void Mul();
void Divi();
void Pows();
void Error();

int main()
{
    char cmd[256];
    while(1)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "help")==0)
            Help();
        else if (strcmp(cmd, "quit")==0)
            exit(0);        
        else if (strcmp(cmd, "time")==0)
            ShowTime();
        else if (strcmp(cmd, "max")==0)
            Max();
        else if (strcmp(cmd, "min")==0)
            Min();
        else if (strcmp(cmd, "add")==0)
            Add();
        else if (strcmp(cmd, "sub")==0)
            Sub();
        else if (strcmp(cmd, "mul")==0)
            Mul();
        else if (strcmp(cmd, "div")==0)
            Divi();
        else if (strcmp(cmd, "pow")==0) 
            Pows();
        else
            Error();
    }    
    return 0;
}

void Help()
{
    printf("*----------*------------------------------   *\n");
    printf("*   name   *      description                *\n");
    printf("*----------*----------------------- -------  *\n");
    printf("*   help   *      cmd tips                   *\n");
    printf("*   quit   *      exit cmd                   *\n");
    printf("*   time   *      show time                  *\n");
    printf("*   max    *    find the maximum             *\n");
    printf("*   min    *    find the minimum             *\n");
    printf("*   add    *    addition of two numbers      *\n");
    printf("*   sub    * subtraction of two numbers      *\n");
    printf("*   mul    * multiplication of two numbers   *\n");
    printf("*   div    * division of two numbers         *\n");
}

/*
* @Description: Displays the current time
*/
void ShowTime()
{
    time_t timep;  
    char s[30];  
    time(&timep);  
    strcpy(s,ctime(&timep));
    printf("------*--------*------*--------*------\n");  
    printf("%s\n", s); 
    printf("------*--------*------*--------*------\n");
}

/*
* @Description: Find the maximum
*/
void Max()
{
    int a,b;
    int max;
    printf("please enter two integers:\n");
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
    printf("please enter two integers:\n");
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
    printf("Addition!Please input two numbers!\n");
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
    printf("subtraction!Please input two numbers!\n");
    scanf("%lf%lf", &minuend, &meiosis);
    result=minuend-meiosis;
    printf("%.2lf\n", result);
    printf("------*--------*------*-------*------\n");
}

/*
* @Description: Multiplication of two numbers
*/
void Mul()
{    
    double num1;
    double num2;
    double result;

    printf("------*--------*------*-------*------\n");
    printf("Multiplication!Please input two numbers!\n");
    scanf("%lf%lf", &num1, &num2);
    result=num1*num2;
    printf("%.2lf\n", result);
    printf("------*--------*------*-------*------\n");
}

/*
* @Description: Multiplication of two numbers
*/
void Divi()
{   
    double dividend;
    double divisor;
    double result;

    printf("------*--------*------*-------*------\n");
    printf("Divition!Please input two numbers!\n");
    scanf("%lf%lf", &dividend, &divisor);

    if (divisor == 0)
    {
        printf("Error!Dividor can not be zero!\n");
    }

    result=dividend / divisor;
    printf("%.2lf\n", result);
    printf("------*--------*------*-------*------\n");
 }

/*
* @Description: Exponentiation of two numbers
*/
void Pows()
{   
    double num1;
    double num2;
    double result;

    printf("------*--------*------*-------*------\n");
    printf("Exponentiation!Please input two numbers!\n");
    scanf("%lf%lf", &num1, &num2);
    result=(double)pow(num1, num2);
    printf("%lf\n", result);
    printf("------*--------*------*-------*------\n");
}

void Error()
{ 
    printf("Command not found!\n");
}
