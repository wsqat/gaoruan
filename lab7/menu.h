#ifndef _MENU_H
#define _MENU_H

int MenuConfig(char * cmd, char * desc, void (*handler)(int argc, char *argv[]));

int ExecuteMenu();

#endif