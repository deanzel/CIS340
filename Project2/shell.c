/* Dean Choi
 * Shell commands - help, quit, fmount, fumount
*/

#include <stdio.h>
#include "shell.h"



void printPrompt(){
    printf("\nflop: ");
};

void printHelp() {

    printf("\n================ FLOPPY DISK HELP =================\n");
    printf("             <required> - [optional]\n\n");
    printf("  help:                      Displays a list and description of all available commands.\n");
    printf("  quit:                      Quits the floppy disk shell program.\n");
    printf("  fmount <img_file>:         Mounts a local floppy disk image.\n");
    printf("  fumount:                   Unmounts the mounted floppy disk image.\n");
    printf("  structure:                 Lists the structure of the floppy disk image.\n");
    printf("  traverse [-l]:             Lists the contents of the root directory. Optional -l flag lists more file details.\n");
    printf("  showfat:                   Shows the content of the FAT Table.\n");
    printf("  showsector <sector_num>:   Shows the contents of the specific sector.\n");
    printf("\n================ FLOPPY DISK HELP =================\n");
};