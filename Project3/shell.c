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
extern char pathEnv[1024];

int pid;

//Print the shell prompt which includes the current folder name followed by '$'
void printPrompt(){

    //pointer to last occurrence of '/' in cwd

    char *folder = strrchr(cwd, '/');

    printf("\n%s$ ", &folder[1]);

};



//change directory command; what if path has a space somewhere in it? Process it if the path comes wrapped in quotes
void cd(char *path) {

    if (chdir(path) == -1) {
        printf("\nThe path of '%s' does not exist...\n", path);
    } else {
        getcwd(cwd, 1024);
    }

};


//print current pathEnv variable
void printPath(){

    if (strcmp(pathEnv, "") == 0) {
        printf("\nThe current path environment is empty. Please add at least one path folder...\n");
    } else {
        printf("\n%s\n", pathEnv);
    }

};


//append a folder to the current path; must start with "/", not end with "/", and not contain ":"
void addPath(char *path) {

    if ((path[0] == '/') && (path[strlen(path) - 1] != '/') && (strchr(path, ':') == NULL)){

        if (strlen(pathEnv) != 0) {
            strcat(pathEnv, ":");
        }
        strcat(pathEnv, path);

        printPath();
    } else if (strchr(path, ':') != NULL) {
        printf("\n'%s' cannot be added to the current PATH env. Remove all ':' and enter one folder at a time.\n", path);
    }
    else {
        printf("\n'%s' cannot be added to the current PATH env. Please use the format of '/abc/def' to enter a new path folder.\n", path);
    }

};


//remove a folder from the current path; in order to successfully remove, start with "/" and have the matching case as well
void remPath(char *path) {
    char *token;
    int match = 0;
    char newPath[1024];
    char pathCopy[1024];

    strcpy(pathCopy, pathEnv);
    newPath[0] = 0;

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
        if (strlen(newPath) > 0) {
            newPath[strlen(newPath) - 1] = 0;
        }
        strcpy(pathEnv, newPath);
        newPath[0] = 0;
        pathCopy[0] = 0;
        printPath();
    } else {
        printf("\n'%s' cannot be removed from the current PATH env. Please use the format of '/abc/def' with proper casing to remove an existing path folder.\n", path);
        newPath[0] = 0;
        pathCopy[0] = 0;
    }



};




// int execv(const char *path, char *const argv[]);
/*int execv(const char *path, char *const argv[]);
int execve(const char *filename, char *const argv[], char *const envp[]);*/

//execute function that takes in the the char* arg[][] pointer, statement number (starting from 0), number of pipes (0 to num)
//make it recursive
//fork within the parent and setup all the piping first; then use the execve call at the end of setting up all the wiring.

void execute(char *argv[]) {
    pid = fork();

    if (pid == 0) { //child
        char pathString[1024];
        char *token;
        char buffer[1024];

        strcpy(pathString, pathEnv);

        token = strtok(pathString, ":");
        while (token != NULL) {
            strcpy(buffer, token);
            strcat(buffer, "/");
            strcat(buffer, argv[0]);

            //execv will not return and execute the binary if it exists in that path folder; else it will continue
            execv(buffer, argv);
            token = strtok(NULL, ":");
            buffer[0] = 0;
        }

        printf("\nThat is an incorrect command...\n");

    } else {    //parent
        //sleep for 100 milliseconds
        usleep(100000);
    }

};


