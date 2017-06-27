/* Dean Choi

*/

#ifndef _FLOPPY_H_
#define _FLOPPY_H_

//floppy disk variables
int fd;
int mounted = 0;
unsigned int bytes_per_sector;
unsigned int sectors_per_cluster;
unsigned int reserved_sectors;
unsigned int num_of_fats;
unsigned int max_root_dirs;
unsigned int total_sectors;
unsigned int sectors_per_fat;

unsigned int sectors_per_track;
unsigned int num_of_heads;


//floppy disk methods


void mount(char *filename);
void unmount();

void setBootVariables();

#endif //_FLOPPY_H_
