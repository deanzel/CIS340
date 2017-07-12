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



//change directory command
void cd(char *path) {

    if (chdir(path) == -1) {
        printf("\nThe path of '%s' does not exist...\n", path);
    } else {
        getcwd(cwd, 1024);
    }

};


//print current "PATH" environment variable
void path(){

    printf("\n%s\n", getenv("PATH"));

};


//append a folder to the current path; going to use setenv with overwrite set to 1; must start with "/"
void addPath(char *path) {

    if (path[0] == '/' && path[strlen(path)] != '/'){
        char newPath[1024];
        strcpy(newPath, getenv("PATH"));
        strcat(newPath, ":");
        strcat(newPath, path);

        setenv("PATH", newPath, 1);
        newPath[0] = 0;
        printf("\n%s\n", getenv("PATH"));
    } else {
        printf("\n'%s' cannot be added to the current PATH env. Please use the format of '/abc/def' to enter a new path folder.\n", path);
    }

};


//remove a folder from the current path; going to use setenv with overwrite set to 1
void remPath(char *path) {
    char *token;
    int match = 0;
    char newPath[1024];
    char pathCopy[1024];

    strcpy(pathCopy, getenv("PATH"));

    token = strtok(pathCopy, ":");
    while (token != NULL) {
        if (strcmp(path, token) != 0){
            strcat(newPath, token);
            strcat(newPath, ":");
            token = strtok(NULL, ":");
        } else {
            match = 1;
            token = strtok(NULL, ":");
        }
    }

    if (match) {
        newPath[strlen(newPath) - 1] = 0;
        setenv("PATH", newPath, 1);
        newPath[0] = 0;
        pathCopy[0] = 0;
        printf("\n%s\n", getenv("PATH"));
    } else {
        printf("\n'%s' cannot be removed from the current PATH env. Please use the format of '/abc/def' to remove an existing path folder.\n", path);
        newPath[0] = 0;
        pathCopy[0] = 0;
    }



};



//int execl (const char *path, const char *arg, ...);
// int execv(const char *path, char *const argv[]);
void execute(){

};
