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
extern int maxArgLen;
static pid_t pidFinal;
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


//special execute method we run for any of the pipe processes; almost same as execute() except we don't call fork() in the method and pass in the pid
void executeP(char *argv[], pid_t pid) {

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
            printf("\nThe binary of './%s' does not exist in the current working directory...\n", editedArg);
            exit(1);
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

    } else {    //parent won't run execute anything
        //sleep for 100 milliseconds
        usleep(100000);
        printf("\nThat is an invalid command...\n");
    }
};



//new method, will actually not need to be recursive at all; form all pipes from the parent in the beginning and then fork the children
//within every child, close all the unneeded pipes; then close all the pipes in the parent; then execute each statement one-by-one in each child
void executePipe(char ***argv, int* fd[], int pipeCount) {
    pid_t pid, pid1, pid2;
    //static pid_t pidFinal;
    //locally handle any SIGPIPE errors
    signal(SIGPIPE, SIG_IGN);

    //set it up for one pipe at first; so only fd[0][2], pipeCount = 1, and *argv[2][]

    //for the very first cmd set, keep stdin at 0 but redirect output to pipe
    //case if we only have 1 pipe, then don't need recursive call
    if (pipeCount == 1) {
        //fd[0] = malloc (2 * sizeof(int));
        //create the first pipe
        if (pipe(fd[0]) != 0) {
            printf("\nPipe cannot be opened...\n");
            exit(1);
        }
        if ((pid1 = fork()) == 0) {     //child1
            //save the stdout as a new file descriptor in order to restore later if error.
            int saved_stdout = dup(1);
            close(1);
            dup2(fd[0][1], 1);
            close(fd[0][1]);
            close(fd[0][0]);
            executeP(argv[0], pid1);
            //only reach if there is an error in the command
            dup2(saved_stdout, 1);
            close(saved_stdout);

            //the stdout is re-established to the monitor
            printf("\nInvalid command in Process 1.\n");
            exit(1);

        } else if ((pid2 = fork()) == 0) {  //child2
            close(0);
            dup2(fd[0][0], 0);
            close(fd[0][0]);
            close(fd[0][1]);
            //waitpid((pid1 - 1), NULL, 0);
            executeP(argv[1], pid2);
            //only reach if there is an error in the command; don't need to redirect back to stdout as the error is already printed from executeP() method
            close(1);

        } else {    //parent execution closes the pipe
            close(fd[0][0]);
            close(fd[0][1]);
            waitpid((pid1 - 1), NULL, 0);
            waitpid((pid2 - 1), NULL, 0);
        }

    }  else {   //when number of pipes is greater than 1
        int saved_stdout[pipeCount];

        int i;
        //create all necessary pipes
        for (i = 0; i < pipeCount; i++){
            //fd[i] = malloc (2 * sizeof(int));
            if (pipe(fd[i]) < 0) {
                printf("\nPipe cannot be opened...\n");
                exit(1);
            }
        }

        for (i = 0; i < (pipeCount + 1); i++) {
            if ((pid = fork()) == 0) {      //child coding
                if (i == 0) {   //child1
                    //save stdout of each child in case of error later on when we execute
                    saved_stdout[i] = dup(1);
                    close(1);
                    dup2(fd[0][1], 1);
                    close(fd[0][1]);
                    close(fd[0][0]);

                    //now close all other pipe connections
                    int j;
                    for (j = 0; j < pipeCount; j++) {
                        if (j != i) {
                            close(fd[j][0]);
                            close(fd[j][1]);
                        }
                    }

                } else if (0 < i < pipeCount) {     //all middle children processes; not the end
                    saved_stdout[i] = dup(1);
                    close(0);
                    //reroute input of child to read end of previous pipe[i - 1]
                    dup2(fd[i - 1][0], 0);
                    close(fd[i - 1][0]);
                    close(fd[i - 1][1]);
                    //close stdout
                    close(1);
                    //reroute output of child to write end of next pipe[index]
                    dup2(fd[i][1], 1);
                    close(fd[i][1]);
                    close(fd[i][0]);

                    //now close all other pipe connections
                    int j;
                    for (j = 0; j < pipeCount; j++) {
                        if ((j < (i - 1)) || (j > i)) {
                            close(fd[j][0]);
                            close(fd[j][1]);
                        }
                    }

                } else {    //last child process when i = pipeCount
                    pidFinal = getpid();
                    //dont need to save stdout because it remains tied to the monitor
                    close(0);
                    //reroute stdin input of final child to read end of last pipe[i - 1]
                    dup2(fd[pipeCount - 1][0], 0);
                    close(fd[pipeCount - 1][0]);
                    close(fd[pipeCount - 1][1]);

                    //now close all other pipe connections
                    int j;
                    for (j = 0; j < (pipeCount - 1); j++) {
                            close(fd[j][0]);
                            close(fd[j][1]);
                    }

                }

                executeP(argv[i], pid);
                //this is reached if there is an error running the command
                dup2(saved_stdout[i], 1);
                close(saved_stdout[i]);
                //the stdout is re-established to the monitor
                printf("\nInvalid command in Process %d.\n", i + 1);
                exit(1);

            } else {    //parent process
                //close all pipes
                int k;
                for (k = 0; k < pipeCount; k++) {
                    close(fd[k][0]);
                    close(fd[k][1]);
                }
                usleep(500000);
                //waitpid(pidFinal, NULL, 0);
            }
        }
    }

};

