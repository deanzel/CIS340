/* Dean Choi
 * Floppy Disk commands/functions: structure, traverse, showsector, showfat
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "floppy.h"


//save the file information and then opens the file
void mount(char *filename) {
    //must first check to see if an image is already mounted, if it is then unmount it

    if ((fd = open(filename, O_RDONLY)) >= 0) {
        //functions to load the boot disk info into memory
        printf("%s has been succesfully  mounted.\n", filename);

    } else {
        printf("The floppy disk could not be mounted. Please check the filename and location.");
    }



}

void unmount();