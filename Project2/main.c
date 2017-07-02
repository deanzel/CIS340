/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 2 - A Floppy Disk Console
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"
#include "floppy.h"



int main() {

    char input[50];


    printf("Welcome to the Floppy Disk Console program. Please enter a command after the prompt to get started. "
                   "For help with a list of the commands, type \"help\". To quit the program, type \"quit\".\n");


    while (1){
        printPrompt();

        //scanf("%s", input);

/*        fd = open("imagefile.img", O_RDONLY);

        printf("%d\n", fd);*/


        mount("imagefile.img");


        structure();

        showSector(55);

        traverse(1);

        showSector(10);

        showFat();

        scanf("%s", input);

        if (strcmp(input, "quit") == 0){
            break;
        }





    }


    return 0;

}