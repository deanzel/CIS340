/* Dean Choi
 * Shell functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"

//global variable of cwd and pathEnv from main.c
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
//execute function that takes in the the char* arg[] pointer array; only for 0 pipes

void execute(char *argv[]) {
    pid = fork();

    if (pid == 0) { //child
        char pathString[1024];
        char *token;
        char buffer[1024];

        //if the first argument starts with ./ then run in current working directory first
        if (!strncmp(argv[0], "./", 2)) {
            char editedArg[100];
            char fullCwd[1024];
            strcpy(editedArg, &argv[0][2]);
            strcpy(argv[0], editedArg);

            strcpy(fullCwd, cwd);
            strcat(fullCwd, "/");
            strcat(fullCwd, editedArg);

            execv(fullCwd, argv);
            printf("\nbitching\n");
        } else {    //all other cases, then try to run binary in all the various path folders

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
        }

        printf("\nThat is an invalid command...\n");
        exit(1);

    } else {    //parent
        //sleep for 100 milliseconds
        usleep(100000);
    }

};


// statement number (starting from 0), number of pipes (0 to num), make it recursive,
// fork within the parent and setup all the piping first; then use the execve call at the end of setting up all the wiring.
//should take in the triple string array of all the inputs, filedescriptor 2d array for each of the created pipes fd[i][2], index of which pipe/statement we are at, total number of pipes
// recursive call if index < pipeCount; we have a universal filedescriptor 2d array; also each process will wait for the previous to terminate before executing its set of commands

void executePipe(char **argv[], int *fd[], int index, int pipeCount) {
    pid_t pid1, pid2;

    //set it up for one pipe at first; so only fd[0][2], pipeCount = 1, and *argv[2][]

    //for the very first cmd set, keep stdin at 0 but redirect output to pipe
    if (index == 0) {
        //create the first pipe
        if (pipe(fd[0]) != 0) {
            perror("Pipe cannot be opened...");
            exit(1);
        }
        if ((pid1 = fork()) == 0) {     //child
            close(1);
            dup(fd[0][1]);
            close(fd[0][1]);
            close(fd[0][0]);
            executePipe(***argv, **fd, index + 1, pipeCount);
        }
        //else would be a parent execution

    } else if (index < pipeCount) {    //next
        //create next needed pipe
        if (pipe(fd[index]) != 0) {
            perror("Pipe cannot be opened...");
            exit(1);
        }

        if ((pid1 = fork()) == 0) {     //child
            //close stdin
            close(0);
            //reroute input of child to write end of previous pipe[index - 1]
            dup(fd[index - 1][1]);
            close(fd[index - 1][1]);
            //close stdout
            close(1);
            //reroute output of child to read of newly created pipe[index]
            dup(fd[index][0]);
            close(fd[index][0]);
            executePipe(***argv, **fd, index + 1, pipeCount);

        }//else here would be parent execution

    } else {    //index = pipeCount; so last process; don't create pipe and no need to reroute its output, just need to connect its input
        if ((pid1 = fork()) == 0) {     //child
            close(0);
            dup(fd[index - 1][0]);
            close(fd[index - 1][0]);
            close(fd[index - 1][1]);

        }


    }



};




