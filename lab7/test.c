#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "menu.h"

void Quit(int argc, char *argv[]);
void Version(int argc, char *argv[]);


void Quit(int argc, char *argv[])
{
    exit(0);
}

void Version(int argc, char *argv[])
{
    printf("version7.0\n");
}

void Directory(int argc, char *argv[])
{
	char buf[80];
	getcwd(buf,sizeof(buf));
	printf("current working directory: %s\n",buf);    
}

void Date(int argc, char *argv[])
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p=gmtime(&timep);
	printf("%d\\",1900+p->tm_year);
	printf("%d\\",1+p->tm_mon);
	printf("%d\n",p->tm_mday);
}

int Add(int argc, char* argv[])
{
    int i,r;
    if(argc !=3)
    {
        printf("warning input 2 numbers\n");
        return 0;
    }
    r=atoi(argv[1])+atoi(argv[2]);
    printf("result is %d\n",r);
    return 0;
}

int Sub(int argc, char* argv[])
{
    int i,r;
    if(argc !=3)
    {
        printf("warning input 2 numbers\n");
        return 0;
    }
    r=atoi(argv[1])-atoi(argv[2]);
    printf("result is %d\n",r);
    return 0;
}

int Mul(int argc, char* argv[])
{
    int i,r;
    if(argc !=3)
    {
        printf("warning input 2 numbers\n");
        return 0;
    }
    r=atoi(argv[1])*atoi(argv[2]);
    printf("result is %d\n",r);
    return 0;
}

int Divi(int argc, char* argv[])
{
    int i;
    float r;
    if(argc !=3)
    {
        printf("warning input 2 numbers\n");
        return 0;
    }
    r=((float)atoi(argv[1]))/atoi(argv[2]);
    printf("result is %.2f\n",r);
    return 0;
}

int main(int argc,char* argv[])
{
    MenuConfig("version","XXX1.0(Menu program v7.0 inside)",NULL);
    MenuConfig("quit","Quit from XXX",Quit);
    MenuConfig("directory","Show the work path",Directory);
    MenuConfig("date","Show the date",Date);
    MenuConfig("add","printf all you input in the terminal", Add);
    MenuConfig("sub","printf all you input in the terminal", Sub);
    MenuConfig("mul","printf all you input in the terminal", Mul);
    MenuConfig("divi","printf all you input in the terminal", Divi);

    ExecuteMenu();
}