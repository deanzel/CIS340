/* Dean Choi
 * Shell functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"

//extern char **environ;
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
void path(){

    printf("\n%s\n", pathEnv);
    //printf("\n%s\n", getenv("PATH"));

};


//append a folder to the current path; going to use setenv with overwrite set to 1; must start with "/"
void addPath(char *path) {

    if ((path[0] == '/') && (path[strlen(path) - 1] != '/') && (strchr(path, ':') == NULL)){
        //char newPath[1024];
        //strcpy(newPath, getenv("PATH"));
        //strcat(newPath, ":");
        //strcat(newPath, path);
        if (strlen(pathEnv) != 0) {
            strcat(pathEnv, ":");
        }
        strcat(pathEnv, path);

        //setenv("PATH", newPath, 1);
        //newPath[0] = 0;
        printf("\n%s\n", pathEnv);
    } else if (strchr(path, ':') != NULL) {
        printf("\n'%s' cannot be added to the current PATH env. Remove all ':' and enter one folder at a time.\n", path);
    }
    else {
        printf("\n'%s' cannot be added to the current PATH env. Please use the format of '/abc/def' to enter a new path folder.\n", path);
    }

};


//remove a folder from the current path; going to use setenv with overwrite set to 1
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
        //setenv("PATH", newPath, 1);
        newPath[0] = 0;
        pathCopy[0] = 0;
        printf("\n%s\n", pathEnv);
    } else {
        printf("\n'%s' cannot be removed from the current PATH env. Please use the format of '/abc/def' with proper casing to remove an existing path folder.\n", path);
        newPath[0] = 0;
        pathCopy[0] = 0;
    }



};



//int execl (const char *path, const char *arg, ...);
// int execv(const char *path, char *const argv[]);
//execve passing in environ variable
//test if path environment searching works with a hello.c code example
/*int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg,
..., char * const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],*/

//execute function that takes in the the char* arg[][] pointer, statement number (starting from 0), number of pipes (0 to num)
//make it recursive
//fork within the parent and setup all the piping first; then use the execve call at the end of setting up all the wiring.

void execute(){
    pid = fork();

    //char *argv[] = {"ls", "-l", 0};
    char *argv[] = {"hello", 0};

    if (pid == 0) {
        execvp(argv[0], argv);
        printf("\nThat is an incorrect command...\n");

    }



};


