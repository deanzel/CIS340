/* Dean Choi
 * Shell header
*/

#ifndef SHELL_H
#define SHELL_H




void printPrompt();

void printPath();

void cd(char *path);

void addPath(char *path);

void remPath(char *path);

void execute(char *argv[]);

void executeP(char *argv[], pid_t pid);

void executePipe(char ***argv, int *fd[], int pipeCount);

void outputRedirect();

void inputRedirect();


#endif //End SHELL_H
