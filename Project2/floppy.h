/* Dean Choi
 * Floppy Disk functions header file
*/

#ifndef FLOPPY_H_
#define FLOPPY_H_

char imageName[50];

//floppy disk variables
int fd;
int mounted;
unsigned int bytes_per_sector;
unsigned int sectors_per_cluster;
unsigned int reserved_sectors;
unsigned int num_of_fats;
unsigned int max_root_dirs;
unsigned int total_sectors;
unsigned int sectors_per_fat;

unsigned int sectors_per_track;
unsigned int num_of_heads;
unsigned int volume_id;
unsigned char volume_label[11];


//struct of a FAT12 directory entry
struct dirEntry {
    unsigned char filename[8];
    unsigned char extension[3];
    unsigned char attributes[1];
    unsigned char reserved[2];
    unsigned short creation_time;
    unsigned short creation_date;
    unsigned short last_access_date;
    unsigned short last_write_time;
    unsigned short last_write_date;
    unsigned short first_cluster;
    unsigned short file_size;
    unsigned char fullpath[128];
};

//node structure for a Singly-Linked List for directory entries
struct mynode {
    struct dirEntry entry;
    struct mynode *next;
};


//floppy disk methods

void mount(char *filename);
void unmount();

void structure();

void traverse(int l);

struct mynode* addDirPath(struct mynode* node);


void showSector(int sector);

void showFat();

void setBootVariables();
void resetBootVariables();



#endif //_FLOPPY_H_
