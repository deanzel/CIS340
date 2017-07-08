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
        int outOfRange = 0;

        char command[50], arg[50];

        printPrompt();

        //printf(cwd);

        fgets(input, 500, stdin);
        token = strtok(input, " \t\n\v");

        while (count < 2 && !outOfRange) {
            if (token != NULL) {
                if (count == 0) {
                    strcpy(command, token);
                    count++;
                } else if (count == 1) {
                    strcpy(arg, token);
                    count++;
                } else {
                    outOfRange = 1;
                    count++;
                }
                token = strtok(NULL, " \t\n\v");
            } else {
                break;
            }
        }

        if (outOfRange) {
            printf("\nThat is an incorrect input of more than two arguments.\n");
        }
            //Single Argument commands
        else if (count == 1) {
            if (!strcmp("quit", command)) {
                printf("\nQuitting the floppy disk shell program...\n");
                break;
/*            } else if (!strcmp("help", command)) {
                printHelp();
            } else if (!strcmp("structure", command)) {
                structure();
            } else if (!strcmp("fumount", command)) {
                unmount();
            } else if (!strcmp("showfat", command)) {
                showFat();
            } else if (!strcmp("traverse", command)) {
                traverse(0);        //short traverse*/
            } else {
                printf("\nError. Invalid command.\n");
            }
        }
            //Two Argument commands
        else if (count == 2) {
/*            if (!strcmp("fmount", command)) {
                mount(arg);
            } else if ((!strcmp("traverse", command)) && (!strcmp("-l", arg))) {
                traverse(1);        //long traverse
            } else if ((!strcmp("showsector", command)) && ((atoi(arg) != 0) || !strcmp("0", arg))){

                showSector(atoi(arg));
            } else {
                printf("\nError. Invalid command.\n");
            }*/
        } else {
            printf("\nError. Invalid command.\n");
        }


        return 0;

    }

}





