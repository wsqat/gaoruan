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

int main(int argc,char* argv[])
{
    MenuConfig("version","XXX1.0(Menu program v7.0 inside)",NULL);
    MenuConfig("quit","Quit from XXX",Quit);
    MenuConfig("directory","Show the work path",Directory);
    MenuConfig("date","Show the date",Date);

    ExecuteMenu();
}