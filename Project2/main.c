/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 2 - A Floppy Disk Console
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"
#include "floppy.h"

int main() {

    printf("\nWelcome to the Floppy Disk Shell program. Please enter a command after the prompt to get started. "
                   "\nFor help with a list of the available commands, enter \"help\". To quit the program, enter \"quit\".\n");

    while (1) {
        char input[100];
        char *token;
        int count = 0;
        int outOfRange = 0;

        char command[50], arg[50];

        printPrompt();
        fgets(input, 100, stdin);
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
            }
            else {
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
            } else if (!strcmp("help", command)) {
                printHelp();
            } else if (!strcmp("structure", command)) {
                structure();
            } else if (!strcmp("fumount", command)) {
                unmount();
            } else if (!strcmp("showfat", command)) {
                showFat();
            } else if (!strcmp("traverse", command)) {
                traverse(0);        //short traverse
            } else {
                printf("\nError. Invalid command.\n");
            }
        }
            //Two Argument commands
        else if (count == 2) {
            if (!strcmp("fmount", command)) {
                mount(arg);
            } else if ((!strcmp("traverse", command)) && (!strcmp("-l", arg))) {
                traverse(1);        //long traverse
            } else if ((!strcmp("showsector", command)) && ((atoi(arg) != 0) || !strcmp("0", arg))){

                showSector(atoi(arg));
            } else {
                printf("\nError. Invalid command.\n");
            }
        } else {
            printf("\nError. Invalid command.\n");
        }

    }

    return 0;
}