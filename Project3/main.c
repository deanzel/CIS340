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
int maxArgs = 15;   //maximum number of Arguments per
int maxArgLen = 100;

int main() {
    printf("\nWeclome to Dean Choi's customized Linux shell.\n");

    getcwd(cwd, 1024);
    pathEnv[0] = 0;

    addPath("/bin");
    addPath("/sbin");



    while (1) {
        char input[4096];
        char inputCopy[4096];
        char *token;
        int count = 0;
        int pipeCount = 0;





        printPrompt();


        fgets(input, 4096, stdin);
        input[strcspn(input, "\n")] = 0;    //gets rid of newline at end of input
        strcpy(inputCopy, input);

        if (strstr(inputCopy, " | ") != NULL) {  //pipes exist in the large input
            //manage the number of pipes and parse them; figure this out later
            //split pipes and replace the | with \a (bell escape character which is non-printing)


            while (strstr(inputCopy, " | ") != NULL) {
                //inputCopy[3] = (char) 28;

                // char *delimeter[] = {(char) 28, 0};
                //can replace middle char of '|' with \a for alert bell (non-printed char)
                //then when we run it,



            }


        } else {
            //no pipes exist in the input, so just one set of command arguments
            //limitation: we can only handle up to 15 arguments in each command line (could increase though since we use malloc)

            //tokenize multiple strings at once for possibility of double quotes enclosed string with a space
            //for now just statically declare argv[]
            //char argv[15][100];
            char **argv;

            argv = malloc(maxArgs * sizeof(char *));
            int argCount = 0;

            //tokenize an input string while not splitting on a space within two double quotes
            char *pch1, *pch2, *save_ptr1, *save_ptr2;
            //use inputCopy
            int inQuotes = 0;

            pch1 = strtok_r(inputCopy, "\"", &save_ptr1);

            while (pch1 != NULL) {
                if (inQuotes) {
                    argv[argCount] = malloc((maxArgLen + 1) * sizeof(char));
                    strcpy(argv[argCount], pch1);
                    pch1 = strtok_r(NULL, "\"", &save_ptr1);
                    inQuotes = 0;
                    argCount++;
                    continue;
                }
                pch2 = strtok_r(pch1, " ", &save_ptr2);
                while (pch2 != NULL) {
                    argv[argCount] = malloc((maxArgLen + 1) * sizeof(char));
                    strcpy(argv[argCount], pch2);
                    pch2 = strtok_r(NULL, " ", &save_ptr2);
                    argCount++;
                }
                pch1 = strtok_r(NULL, "\"", &save_ptr1);
                inQuotes = 1;

            }
            argv[argCount] = 0;




            //Single Argument commands; search internal commands first
            if (argCount == 1) {
                if (!strcmp("quit", argv[0])) {
                    printf("\nQuitting the shell program...\n");
                    break;
                } else if (!strcmp("path", argv[0])) {
                    printPath();
                } else if (!strcmp("cd", argv[0])) {    //cd with nothing after will default to cd(root);
                    cd("/");
                } else {
                    execute(argv);
                }
            } else if (argCount == 2) {  //Two Argument commands; search internals first
                if (!strcmp("cd", argv[0])) {
                    cd(argv[1]);
                } else {
                    execute(argv);
                }
            } else if (argCount == 3) { //3 Argument commands; only internals possible are path + or -
                if (!strcmp("path", argv[0]) && !strcmp("+", argv[1])) {
                    addPath(argv[2]);
                } else if (!strcmp("path", argv[0]) && !strcmp("-", argv[1])) {
                    remPath(argv[2]);
                } else {
                    execute(argv);
                }
            } else {
                execute(argv);
            }

            free(argv);     //deallocate argv[]

        }
    }



    return 0;

}



