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
    printf("\nWelcome to Dean Choi's customized Linux shell.\n");

    getcwd(cwd, 1024);
    pathEnv[0] = 0;

    addPath("/bin");
    addPath("/sbin");
    addPath("/usr/bin");
    cd("/Users/deanchoi");

    //int *fd[2];
    /*char *argv[2][3];
    argv[0][0] = "ls";
    argv[0][1] = "-l";
    argv[0][2] = 0;
    argv[1][0] = "grep";
    argv[1][1] = "txt";
    argv[1][2] = 0;*/

    /*char argv[3][3][maxArgLen] = {
            {"ls", "-l", 0},
            {"grep", "txt", 0},
            {"grep", "my", 0}

    };

    executePipe(argv, fd, 0, 1);*/



    while (1) {
        char input[4096];
        char inputCopy[4096];
        int pipeCount = 0;


        printPrompt();


        //fgets(input, 4096, stdin);
        //input[strcspn(input, "\n")] = 0;    //gets rid of newline at end of input
        strcpy(input, "ls -l | grep txt | grep my");
        strcpy(inputCopy, input);

        char *ret;

        if ((ret = strstr(inputCopy, " | ")) != NULL) {  //pipes exist!! in the large total input

            //manage the number of pipes and parse the cmd lines; split pipes and replace the '|' with \a (bell escape character which is non-printing)
            //get the total count of pipes and replace the '|' char within a " | " pattern with '\a'
            while (ret != NULL) {
                pipeCount++;
                ret[1] = '\a';

                ret = strstr(inputCopy, " | ");
            }
            //split into arrays of long input strings delimited by the now '\a' char
            int inputStrIndex = 0;
            char **inputStr;
            //1 pipe = 2 cmd lines; 2 pipes = 3 cmd lines; 3 pipes = 4 cmd lines...
            inputStr = malloc((pipeCount + 1) * sizeof(char *));

            char *token, *save_ptr;
            token = strtok_r(inputCopy, "\a", &save_ptr);

            //split on '\a' and we'll have extra white spaces, but that will be taken care of in next set of parsing
            while (token != NULL) {
                inputStr[inputStrIndex] = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(inputStr[inputStrIndex], token);

                token = strtok_r(NULL, "\a", &save_ptr);
                inputStrIndex++;
            }
            //Now, we will parse each input cmd line (that is its own pipe cmd) into individual argv[]
            //not sure what data type of argv will work until we test it later
            char **argv[pipeCount + 1];
            //char ***argv;
            //argv = malloc((pipeCount + 1) * sizeof(int *));

            //for each input string we have separated, create into argv[i][]
            int i;
            for (i = 0; i < pipeCount + 1; i++) {
                argv[i] = malloc((maxArgs + 1) * sizeof(char *));
                int argCount = 0;

                //Use same strtok_r parsing method from below that will split on blank spaces unless they are enclosed in two surround double quotes
                char *pch1, *pch2, *save_ptr1, *save_ptr2;
                int inQuotes = 0;

                pch1 = strtok_r(inputStr[i], "\"", &save_ptr1);

                while (pch1 != NULL) {
                    if (inQuotes) {
                        argv[i][argCount] = malloc((maxArgLen + 1) * sizeof(char));
                        strcpy(argv[i][argCount], pch1);
                        pch1 = strtok_r(NULL, "\"", &save_ptr1);
                        inQuotes = 0;
                        argCount++;
                        continue;
                    }
                    pch2 = strtok_r(pch1, " ", &save_ptr2);
                    while (pch2 != NULL) {
                        argv[i][argCount] = malloc((maxArgLen + 1) * sizeof(char));
                        strcpy(argv[i][argCount], pch2);
                        pch2 = strtok_r(NULL, " ", &save_ptr2);
                        argCount++;
                    }
                    pch1 = strtok_r(NULL, "\"", &save_ptr1);
                    inQuotes = 1;

                }
                argv[i][argCount] = 0;

            }

            //the char *argv[pipeCount + 1][argCount] has been fully processed and we can send it into the pipe execute method along with the pipeCount
            //and we'll statically allocate the memory for the filedescriptor 2d array
            if (pipeCount > 0) {
                int fd[pipeCount][2];
                //int fd[2][2] = {0};
                //memset(fd, 0, sizeof(fd));

                //executePipe(argv, (int**) fd, 0, pipeCount);
                executePipe(argv, fd, 0, pipeCount);
            }


        } else {    //no pipes exist in the input, so just one set of command arguments

            //limitation: we can only handle up to 15 arguments in each command line (could manually increase though since we use malloc)
            //and each argument size has a limit of 99 characters (this can be manually increased as well in the global variables)

            //dynamically declare char *argv[] in order to minimize some resources
            char **argv;
            argv = malloc((maxArgs + 1) * sizeof(char *));
            int argCount = 0;

            //Using strtok_r, we will split on blank spaces as long as they are not within two surrounding double quotes
            //tokenize an input string while not splitting on a space within two surrounding double quotes
            char *pch1, *pch2, *save_ptr1, *save_ptr2;
            int inQuotes = 0;   //boolean for if the token is currently within a pair of double quotes

            //split first on the \" because that is the main thing to look for
            pch1 = strtok_r(inputCopy, "\"", &save_ptr1);

            while (pch1 != NULL) {
                //if the first surrounding double quote as been found and delimited...
                if (inQuotes) {
                    argv[argCount] = malloc((maxArgLen + 1) * sizeof(char));
                    strcpy(argv[argCount], pch1);
                    pch1 = strtok_r(NULL, "\"", &save_ptr1);
                    inQuotes = 0;
                    argCount++;
                    continue;
                }
                //else process/delimit the blank spaces normally within the second token pointer
                pch2 = strtok_r(pch1, " ", &save_ptr2);
                while (pch2 != NULL) {
                    argv[argCount] = malloc((maxArgLen + 1) * sizeof(char));
                    strcpy(argv[argCount], pch2);
                    pch2 = strtok_r(NULL, " ", &save_ptr2);
                    argCount++;
                }
                //if a double quote is encountered, set inQuote to true, delimit at that double quote, and use the first token pointer
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



