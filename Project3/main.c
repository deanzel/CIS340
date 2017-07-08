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

int main() {
    printf("\nWeclome to Dean Choi's customized Linux shell.\n");


    getcwd(cwd, 1024);



    while (1) {
        char input[500];
        char *token;
        int count = 0;
        //int outOfRange = 0;

        char command[100], arg[5][400];


        //path();

        printPrompt();

        //printf(cwd);

        fgets(input, 500, stdin);
        token = strtok(input, " \t\v\n");

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
                path();
            } else if (!strcmp("cd", command)) {
                cd("/");
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

    return 0;

}





