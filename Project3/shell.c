/* Dean Choi
 * Shell functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"


//global variable of pathname from main.c
extern char cwd[1024];

//Print the shell prompt which includes the current folder name followed by '$'
void printPrompt(){

    //pointer to last occurrence of '/' in cwd

    char *folder = strrchr(cwd, '/');

    printf("\n%s$ ", &folder[1]);

};


//print current working directory
void path(){

    printf("\n%s\n", cwd);

};


void cd(char *path) {

    if (chdir(path) == -1) {
        printf("\nThe path of '%s' does not exist...\n", path);
    } else {
        getcwd(cwd, 1024);
    }

};


void addPath(char *path) {

    char *newPath = strcat(cwd, "/");
    strcat(newPath, path);

    if (chdir(newPath) == -1) {
        printf("\n'%s' cannot be added to the current path...\n", path);
    } else {
        getcwd(cwd, 1024);
    }

};

