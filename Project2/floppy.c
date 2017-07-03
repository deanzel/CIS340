/* Dean Choi
 * Floppy Disk commands/functions: structure, traverse, showsector, showfat
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include "floppy.h"
#include "sort.h"

int mounted = 0;


//save the file information and then opens the file
void mount(char *filename) {
    //must first check to see if an image is already mounted, if it is then unmount it
    if (mounted == 1) {
        printf("\nThere is already a floppy disk image mounted. Please unmount the image first "
                       "before loading a new one.\n");
    }
    else if ((fd = open(filename, O_RDONLY)) >= 0) {
        //functions to load the sector boot disk info into memory
        setBootVariables();
        mounted = 1;
        strcpy(imageName, filename);

        printf("\n'%s' has been successfully mounted.\n", filename);

    } else {
        printf("\nThe floppy disk could not be mounted. Please check the filename and location.\n");
    }

}

//unmount a floppy disk image
void unmount(){
    if (mounted == 0) {
        printf("\nThere is no floppy disk mounted at the moment...\n");
    }
    else {
               printf("\nThe floppy disk of %s has been successfully unmounted.\n", imageName);
        resetBootVariables();
        mounted = 0;
    }

};


//Prints out the structure of the mounted floppy disk image
void structure(){
    if (mounted == 1){

        printf("\nStructure of Floppy Disk '%s':\n", imageName);

        printf("\tnumber of FAT: \t\t\t\t\t\t%d\n", num_of_fats);
        printf("\tnumber of sectors used by FAT: \t\t%d\n", sectors_per_fat);
        printf("\tnumber of sectors per cluster: \t\t%d\n", sectors_per_cluster);
        printf("\tnumber of ROOT Entries: \t\t\t%d\n", max_root_dirs);
        printf("\tnumber of bytes per sector: \t\t%d\n", bytes_per_sector);

        int sector = 0;         //sector count variable to calculate sector ranges of Major Disk sections
        printf("\t---Sector #---     ---Sector Types---\n");
        printf("\t      %d                   BOOT\n", sector);
        for (int i=0; i < num_of_fats; i++){
            printf("\t   %02d -- %02d               FAT%d\n", sector += 1, sector += sectors_per_fat - 1, i+1);
        }
        printf("\t   %02d -- %02d               ROOT DIRECTORY\n", sector += 1, sector + (max_root_dirs/16 - 1));

    }
    else {
        printf("\nThere currently is no mounted floppy disk image...\n");
    }
};


//Load the Boot sector info of the floppy disk image to the specific variables
void setBootVariables(){
    lseek(fd, 11, SEEK_SET);
    read(fd, &bytes_per_sector, 2);
    read(fd, &sectors_per_cluster, 1);
    read(fd, &reserved_sectors, 2);
    read(fd, &num_of_fats, 1);
    read(fd, &max_root_dirs, 2);
    read(fd, &total_sectors, 2);

    lseek(fd, 1, SEEK_CUR);
    read(fd, &sectors_per_fat, 2);
    read(fd, &sectors_per_track, 2);
    read(fd, &num_of_heads, 2);

    lseek(fd, 11, SEEK_CUR);
    read(fd, &volume_id, 4);
    read(fd, &volume_label, 11);
};


//Reset the Boot sector info of the floppy disk image to 0 values
void resetBootVariables(){

    bytes_per_sector = 0;
    sectors_per_cluster = 0;
    reserved_sectors = 0;
    num_of_fats = 0;
    max_root_dirs = 0;
    total_sectors = 0;
    sectors_per_fat = 0;
    sectors_per_track = 0;
    num_of_heads = 0;
    volume_id = 0;
};



//Traverse : list the content in the root directory. '-l' option will activate long method which also includes file
// attribution (and beginning key), last modified time, the size, the full pathname, and the starting cluster id.
void traverse(int l){

    if (mounted == 1){

        //initialize dirEntry array in order to insert directory elements
        //struct dirEntry directory[max_root_dirs];

        //Create a Singly-Linked List
        struct mynode *head = (struct mynode*) malloc(sizeof(struct mynode));
        head->next = NULL;
        struct mynode *current = head;

        //move to beginning of Root directory
        lseek(fd, (num_of_fats * sectors_per_fat + 1) * bytes_per_sector, SEEK_SET);

        for (int i = 0; i < max_root_dirs; i++) {

            read(fd, current->entry.filename, 8);
            read(fd, current->entry.extension, 3);
            read(fd, current->entry.attributes, 1);
            read(fd, current->entry.reserved, 2);
            read(fd, &current->entry.creation_time, 2);
            read(fd, &current->entry.creation_date, 2 );
            read(fd, &current->entry.last_access_date, 2);

            lseek(fd, 2, SEEK_CUR);
            read(fd, &current->entry.last_write_time, 2);
            read(fd, &current->entry.last_write_date, 2);
            read(fd, &current->entry.first_cluster, 2);
            read(fd, &current->entry.file_size, 4);


            //If the Attributes byte is 0x0F, then this directory entry is part of a long file name and can
            //be ignored for purposes of this assignment.
            if (current->entry.attributes[0] == 0x0f)
                continue;

            //If the first byte of the Filename field is 0xE5, then the directory entry is free (i.e., currently
            //unused), and hence there is no file or subdirectory associated with the directory entry.
            if (current->entry.filename[0] == 0xE5)
                continue;


            //If the first byte of the Filename field is 0x00, then this directory entry is free and all the
            //remaining directory entries in this directory are also free.
            if (current->entry.filename[0] == 0x00)
                break;


            //build fullpath name including directories
            char path[128] = "/";
            char filename[9];
            char ext[4];


            for (int j = 0; j < 8; j++) {
                if (!isspace(current->entry.filename[j])) {
                   filename[j] = current->entry.filename[j];
                    if (j == 7) {
                        filename[8] = '\0';
                    }
                } else {
                    filename[j] = '\0';
                    break;
                }
            }

            if (!isspace(filename[0])) {
                strcat(path, filename);
            }

            if (!isspace(current->entry.extension[0])) {
                strcat(path, ".");
                for (int j = 0; j < 3; j++) {
                    if (!isspace(current->entry.extension[j])) {
                        ext[j] = current->entry.extension[j];
                        if (j == 2){
                            ext[3] = '\0';
                        }
                    } else {
                        ext[j] = '\0';
                        break;
                    }
                }
                strcat(path, ext);
            }

            strcpy(current->entry.fullpath, path);


            //if current file is a subdirectory, go into addDir method
            if (current->entry.attributes[0] & 0x10) {

                //save current file position
                long position = lseek(fd, 0, SEEK_CUR);
                //add subdirectory files
                struct mynode *new = addDirPath(current);
                current = new;
                //reset back to original position
                lseek(fd, position, SEEK_SET);
            }

            struct mynode *temp = (struct mynode*) malloc(sizeof(struct mynode));
            current->next = temp;
            current = temp;
        }


        //Print out Filenames, extensions, attributes, filesize, firstcluster
        current = head;

        while (current->next != NULL){

            printf("\npath: %s", current->entry.fullpath);
            printf("\tfilename: %s", current->entry.filename);
            printf("\text: %s", current->entry.extension);
            printf("\tattribute: %X", current->entry.attributes[0]);
            printf("\tfilesize: %d", current->entry.file_size);
            printf("\tfirstcluster: %d\n", current->entry.first_cluster);

            current = current->next;
        }

        //Mergesort the directory entries in the root directory by filename
        //mergeSort(head);




        //if '-l' is entered ('l' is true/1) then enter long traverse
        if (l) {
            printf("\n\n    *****************************\n");
            printf("    ** FILE ATTRIBUTE NOTATION **\n");
            printf("    **                         **\n");
            printf("    ** R ------ READ ONLY FILE **\n");
            printf("    ** S ------ SYSTEM FILE    **\n");
            printf("    ** H ------ HIDDEN FILE    **\n");
            printf("    ** A ------ ARCHIVE FILE   **\n");
            printf("    *****************************\n");
            printf("\n");






        }

        //Shorter regular traverse
        else {








        }





    }
    else {


        printf("\nThere currently is no mounted floppy disk image...\n");
    }


};

//Print the directory folder and further explore the directory; *path is the current full path name constructed so far
struct mynode* addDirPath(struct mynode* node) {
    char path[128];
    //only run on subdirectory files

    if (node->entry.attributes[0] & 0x10) {
        //seek to subdirectory entry via physical sector number = 33 + FAT entry num - 2
        lseek(fd, ((num_of_fats * sectors_per_fat + (max_root_dirs / 16) + 1) + node->entry.first_cluster - 2) *
                  bytes_per_sector
                  * sectors_per_cluster, SEEK_SET);


        //create a new node
        struct mynode *current = (struct mynode *) malloc(sizeof(struct mynode));
        strcpy(path, node->entry.fullpath);
        node->next = current;
        current->next = NULL;

        struct mynode *previous = node;


        for (int i = 0; i < max_root_dirs; i++) {

            //somehow save previous node

            read(fd, current->entry.filename, 8);
            read(fd, current->entry.extension, 3);
            read(fd, current->entry.attributes, 1);
            read(fd, current->entry.reserved, 2);
            read(fd, &current->entry.creation_time, 2);
            read(fd, &current->entry.creation_date, 2);
            read(fd, &current->entry.last_access_date, 2);

            lseek(fd, 2, SEEK_CUR);
            read(fd, &current->entry.last_write_time, 2);
            read(fd, &current->entry.last_write_date, 2);
            read(fd, &current->entry.first_cluster, 2);
            read(fd, &current->entry.file_size, 4);


            //If the Attributes byte is 0x0F, then this directory entry is part of a long file name and can
            //be ignored for purposes of this assignment.
            if (current->entry.attributes[0] == 0x0f)
                continue;

            //If the first byte of the Filename field is 0xE5, then the directory entry is free (i.e., currently
            //unused), and hence there is no file or subdirectory associated with the directory entry.
            if (current->entry.filename[0] == 0xE5)
                continue;

            //If the first byte of the Filename field is 0x00, then this directory entry is free and all the
            //remaining directory entries in this directory are also free.

            //problem here when we break, we don't want to return the current but actually set it back
            if (current->entry.filename[0] == 0x00)
                break;


            char newPath[128] = "/";
            char rootPath[128];
            char filename[9];
            char ext[4];

            strcpy(rootPath, path);

            for (int j = 0; j < 8; j++) {
                if (!isspace(current->entry.filename[j])) {
                    filename[j] = current->entry.filename[j];
                    if (j == 7) {
                        filename[8] = '\0';
                    }
                } else {
                    filename[j] = '\0';
                    break;
                }
            }

            if (!isspace(filename[0])) {
                strcat(newPath, filename);
            }

            if (!isspace(current->entry.extension[0])) {
                strcat(newPath, ".");
                for (int j = 0; j < 3; j++) {
                    if (!isspace(current->entry.extension[j])) {
                        ext[j] = current->entry.extension[j];
                        if (j == 2) {
                            ext[3] = '\0';
                        }
                    } else {
                        ext[j] = '\0';
                        break;
                    }
                }
                strcat(newPath, ext);
            }

            strcat(rootPath, newPath);
            strcpy(current->entry.fullpath, rootPath);

            //if new file is another subdirectory, recursive call
            if ((strncmp(filename, ".", 1) == 0) || (strncmp(filename, "..", 2) == 0)) {
                struct mynode *temp = (struct mynode *) malloc(sizeof(struct mynode));
                previous = current;
                current->next = temp;
                current = temp;
            } else if (current->entry.attributes[0] & 0x10) {

                //save current file position
                long position = lseek(fd, 0, SEEK_CUR);
                //add subdirectory files
                struct mynode *new = addDirPath(current);
                current = new;

                //reset back to original position
                lseek(fd, position, SEEK_SET);

            } else {
                struct mynode *temp = (struct mynode *) malloc(sizeof(struct mynode));
                previous = current;
                current->next = temp;
                current = temp;
            }

        }
        if (current->entry.filename[0] != 0x00) {
            return current;
        } else {
            return previous;
        }
    }
    else {
        return node;
    }
}






//show the contents (in hex dump) of the specified sector number
void showSector(int sector){
    unsigned short value;

    if (mounted == 1 && sector <= total_sectors){
        printf("\nHex Dump of Sector %d in '%s':\n", sector, imageName);

        printf("\n\t\t 0 \t 1 \t 2 \t 3 \t 4 \t 5 \t 6 \t 7 \t 8 \t 9 \t A \t B \t C \t D \t E \t F\n");

        lseek(fd, sector*512, SEEK_SET);

        for (int i = 0; i < bytes_per_sector; i++){
            if (i % 16 == 0) {
                printf("\n%4X", i);
            }

            read(fd, &value, 1);
            printf("\t%.2X", value);

        }

        printf("\n");

    }

    else if (mounted == 1){
        printf("\nThat sector # is out of range. Please try again...\n");
    }
    else {
        printf("\nThere currently is no mounted floppy disk image...\n");
    }
};



//show the content of FAT table starting from Sector 1
void showFat(){
    int entry;
    unsigned int low;
    unsigned int high;
    unsigned int value;

    if (mounted == 1){
        printf("\nFAT table content in '%s' (starting from Sector 1):\n", imageName);

        printf("\n        0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    f\n");

        printf("\n   0          ");     //first two FAT entries are reserved

        //Go through each FAT entry one-by-one and properly reset the SEEK each time
        for (entry = 2; entry < sectors_per_fat*512*2/3; entry++){
            if (entry % 16 == 0) {
                printf("\n%4x", entry);
            }

            lseek(fd, ((entry*3)/2) + bytes_per_sector, SEEK_SET);
            read(fd, &low, 1);
            read(fd, &high, 1);
            if (entry % 2) {        //odd entry; take upper 4 bits of low and put at end of 8 bits of high
                value = ((high << 4) & 0x0ff0) + ((low >> 4) & 0x00f);

            } else {        //even entry; take lower 4 bits of high and put in front of 8 bits of low
                value = ((high << 8) & 0x0f00) + (low & 0x00ff);
            }

            if (value == 0) {
                printf(" FREE");
            }
            else {
                printf("  %3x", value);
            }

        }

        printf("\n");

    }
    else {
        printf("\nThere currently is no mounted floppy disk image...\n");
    }

};

