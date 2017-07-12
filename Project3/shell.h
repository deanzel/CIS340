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


void execute();

#endif //End SHELL_H
