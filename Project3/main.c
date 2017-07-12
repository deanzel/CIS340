/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 3 - A Customized Shell
 * Goal - Implement a customized shell that supports Linux shell commands in addition to internal commands.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"

char cwd[1024];
char pathEnv[1024];

int main() {
    printf("\nWeclome to Dean Choi's customized Linux shell.\n");


    getcwd(cwd, 1024);
    pathEnv[0] = 0;
    //execvp("ls", 0);

    //addPath("/Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug");
    //execute();

    addPath("/bin");
    addPath("/sbin");
    //remPath("/Users");
    //path();
    char *argv[] = {"ls", "-l", 0};
    execute(argv);


    while (1) {
        char input[4096];
        char inputCopy[4096];
        char *token;
        int count = 0;
        int pipeCount = 0;



        char command[100], arg[5][400];


        printPrompt();


        fgets(input, 4096, stdin);
        strcpy(inputCopy, input);

        if (strstr(inputCopy, " | ") != NULL){  //pipes exist in the large input
            //manage the number of pipes and parse them
            //split pipes and replace the | with \a (bell escape character which is non-printing)


            while (strstr(inputCopy, " | ") != NULL) {
                //inputCopy[3] = (char) 28;

               // char *delimeter[] = {(char) 28, 0};
                //can replace middle char of '|' with \a for alert bell (non-printed char)
                //then when we run it,



            }




        } else {
            //no pipes exist in the input, so just one "command"

            //tokenize multiple strings at once for possibility of double quotes enclosed string with a space
            token = strtok(inputCopy, " \t\v\n");

            while (count < 5 && token != NULL) {
                if (count == 0) {
                    strcpy(command, token);
                    count++;
                } else {
                    strcpy(arg[count - 1], token);
                    count++;
                }

                token = strtok(NULL, " \t\n\v");
            };

            //Single Argument commands
            if (count == 1) {
                if (!strcmp("quit", command)) {
                    printf("\nQuitting the shell program...\n");
                    break;
                } else if (!strcmp("path", command)) {
                    printPath();
                } else if (!strcmp("cd", command)) {
                    cd("/");
                } else if (!strcmp("ls", command)){
                    //execute();
                }
                else {
                    printf("\nError. Invalid command.\n");
                }
            }
                //Two Argument commands
            else if (count == 2) {
                if (!strcmp("cd", command)) {
                    cd(arg[0]);
                } else {
                    printf("\nError. Invalid command.\n");
                }
            } else if (count == 3) {
                if (!strcmp("path", command) && !strcmp("+", arg[0])) {
                    addPath(arg[1]);
                } else if (!strcmp("path", command) && !strcmp("-", arg[0])) {
                    remPath(arg[1]);
                }
            } else {
                printf("\nError. Invalid command.\n");
            }


        }
        }






    return 0;

}



