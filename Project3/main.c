/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 3 - A Customized Shell
 * Goal - Implement a customized shell that supports Linux shell commands in addition to internal commands.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
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


    while (1) {
        char input[4096];
        char inputCopy[4096];
        int pipeCount = 0;

        printPrompt();


        fgets(input, 4096, stdin);
        input[strcspn(input, "\n")] = 0;    //gets rid of newline at end of input
        //strcpy(input, "ls -l | grep -i txt | wc -c | grep 13 | grep 132");
        //strcpy(input, "ls -l | grep -i txt | wc -c");
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
            //char **argv = calloc((size_t) (pipeCount + 1), sizeof(char *));
            //char **argv[pipeCount + 1];

            char ***argv = malloc((pipeCount + 1) * sizeof(char**));

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
                int **fd = calloc((size_t) pipeCount, sizeof(int *));
                int j;
                for (j = 0; j < pipeCount; j++) {
                    fd[j] = calloc(2, sizeof(int));
                }

                executePipe(argv, fd, pipeCount);

                for (j = 0; j < pipeCount; j++){
                    free(fd[j]);
                }
                free(fd);
                free(argv);
            }
        }

        else if ((ret = strstr(inputCopy, " < ")) != NULL) {      //input redirection from a file exists w/ no pipes
            //get the number of " < " and parse the cmd lines; split replace the '<' with \a (bell escape character which is non-printing)
            //we can only have one input redirection here, so if there are somehow 2 or more, " < " occurrences, we'll return an error
            int irCount = 0;
            while (ret != NULL) {
                irCount++;
                ret[1] = '\a';

                ret = strstr(inputCopy, " < ");
            }
            if (irCount > 1) {      //incorrect command error
                printf("\nThat is an invalid command...\n");

            } else {
                //split into 2 char pointer arrays of the long input strings delimited by the now '\a' char
                int inputStrIndex = 0;
                char initialInput[1024];
                char inputFile[1024];

                char *token, *save_ptr;
                token = strtok_r(inputCopy, "\a", &save_ptr);

                //split on '\a' and we'll have extra white spaces, but that will be taken care of in next set of parsing; should only bring back 2 strings tokens
                while (token != NULL) {
                    if (inputStrIndex == 0) {
                        strcpy(initialInput, token);
                    } else {
                        strcpy(inputFile, token);
                    }

                    token = strtok_r(NULL, "\a", &save_ptr);
                    inputStrIndex++;
                }

                //parse filename string, should only be one argument...
                char **filename;
                filename = malloc((3) * sizeof(char *));
                int fileCount = 0;

                //Using strtok_r, we will split on blank spaces as long as they are not within two surrounding double quotes
                //tokenize an input string while not splitting on a space within two surrounding double quotes
                char *pch1, *pch2, *save_ptr1, *save_ptr2;
                int inQuotes = 0;   //boolean for if the token is currently within a pair of double quotes

                //split first on the \" (quote) because that is the main thing to look for
                pch1 = strtok_r(inputFile, "\"", &save_ptr1);

                while (pch1 != NULL) {
                    //if the first surrounding double quote as been found and delimited...
                    if (inQuotes) {
                        filename[fileCount] = malloc((maxArgLen + 1) * sizeof(char));
                        strcpy(filename[fileCount], pch1);
                        pch1 = strtok_r(NULL, "\"", &save_ptr1);
                        inQuotes = 0;
                        fileCount++;
                        continue;
                    }
                    //else process/delimit the blank spaces normally within the second token pointer
                    pch2 = strtok_r(pch1, " ", &save_ptr2);
                    while (pch2 != NULL) {
                        filename[fileCount] = malloc((maxArgLen + 1) * sizeof(char));
                        strcpy(filename[fileCount], pch2);
                        pch2 = strtok_r(NULL, " ", &save_ptr2);
                        fileCount++;
                    }
                    //if a double quote is encountered, set inQuote to true, delimit at that double quote, and use the first token pointer
                    pch1 = strtok_r(NULL, "\"", &save_ptr1);
                    inQuotes = 1;

                }
                filename[fileCount] = 0;

                if (fileCount == 1) {   //proper filename so parse the initial set of commands
                    char **argv;
                    argv = malloc((maxArgs + 1) * sizeof(char *));
                    int argCount = 0;
                    inQuotes = 0;   //boolean for if the token is currently within a pair of double quotes

                    //split first on the \" because that is the main thing to look for
                    pch1 = strtok_r(initialInput, "\"", &save_ptr1);

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

                    //We will run the command arguments and the filename in the input redirection method

                    inputRedirect(argv, filename[0]);

                    free(argv);

                } else {
                    printf("\nThat is an invalid set of arguments for the filename for output redirection...\n");
                }
            }
        }

        else if ((ret = strstr(inputCopy, " > ")) != NULL) {      //output redirection from a file exists w/ no pipes
            //get the number of " > " and parse the cmd lines; split replace the '>' with \a (bell escape character which is non-printing)
            //we can only have one output redirection here, so if there are somehow 2 or more, " > " occurrences, we'll return an error
            int orCount = 0;
            while (ret != NULL) {
                orCount++;
                ret[1] = '\a';

                ret = strstr(inputCopy, " > ");
            }
            if (orCount > 1) {      //incorrect command error
                printf("\nThat is an invalid command...\n");

            } else {
                //split into 2 char pointer arrays of the long input strings delimited by the now '\a' char
                int inputStrIndex = 0;
                char initialInput[1024];
                char outputFile[1024];

                char *token, *save_ptr;
                token = strtok_r(inputCopy, "\a", &save_ptr);

                //split on '\a' and we'll have extra white spaces, but that will be taken care of in next set of parsing; should only bring back 2 strings tokens
                while (token != NULL) {
                    if (inputStrIndex == 0) {
                        strcpy(initialInput, token);
                    } else {
                        strcpy(outputFile, token);
                    }

                    token = strtok_r(NULL, "\a", &save_ptr);
                    inputStrIndex++;
                }

                //parse filename string, should only be one argument...
                char **filename;
                filename = malloc((3) * sizeof(char *));
                int fileCount = 0;

                //Using strtok_r, we will split on blank spaces as long as they are not within two surrounding double quotes
                //tokenize an input string while not splitting on a space within two surrounding double quotes
                char *pch1, *pch2, *save_ptr1, *save_ptr2;
                int inQuotes = 0;   //boolean for if the token is currently within a pair of double quotes

                //split first on the \" (quote) because that is the main thing to look for
                pch1 = strtok_r(outputFile, "\"", &save_ptr1);

                while (pch1 != NULL) {
                    //if the first surrounding double quote as been found and delimited...
                    if (inQuotes) {
                        filename[fileCount] = malloc((maxArgLen + 1) * sizeof(char));
                        strcpy(filename[fileCount], pch1);
                        pch1 = strtok_r(NULL, "\"", &save_ptr1);
                        inQuotes = 0;
                        fileCount++;
                        continue;
                    }
                    //else process/delimit the blank spaces normally within the second token pointer
                    pch2 = strtok_r(pch1, " ", &save_ptr2);
                    while (pch2 != NULL) {
                        filename[fileCount] = malloc((maxArgLen + 1) * sizeof(char));
                        strcpy(filename[fileCount], pch2);
                        pch2 = strtok_r(NULL, " ", &save_ptr2);
                        fileCount++;
                    }
                    //if a double quote is encountered, set inQuote to true, delimit at that double quote, and use the first token pointer
                    pch1 = strtok_r(NULL, "\"", &save_ptr1);
                    inQuotes = 1;

                }
                filename[fileCount] = 0;

                if (fileCount == 1) {   //proper filename so parse the initial set of commands
                    char **argv;
                    argv = malloc((maxArgs + 1) * sizeof(char *));
                    int argCount = 0;
                    inQuotes = 0;   //boolean for if the token is currently within a pair of double quotes

                    //split first on the \" because that is the main thing to look for
                    pch1 = strtok_r(initialInput, "\"", &save_ptr1);

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

                    //We will run the command arguments and the filename in the output redirection method
                    outputRedirect(argv, filename[0]);

                    free(argv);

                } else {
                    printf("\nThat is an invalid set of arguments for the filename for output redirection...\n");
                }

            }

        }

        else {    //no pipes exist in the input, no input/output redirection, so just one set of command arguments

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

            free(argv);

        }
    }

    return 0;

}



