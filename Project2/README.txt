Dean Choi
CSU# 2690159
CIS 340 - Assignment 2

*Project Description:
This C console program allows a user to mount and access the data/information on a FAT12 floppy disk image. The various command operations available to the user are: help, quit, fmount, fumount, structure, traverse [-l], showsector, showfat, and quit. The user can enter the ‘help’ command at anytime to get a quick summary of these functions and how to use them.


*Compiling Instructions:
The source code of this program consists of 7 files: 4 source code files of “floppy.c”, “main.c”, “shell.c” & “sort.c” along with 3 header files of “floppy.h”, “shell.h” & “sort.h”.

This C source code comes with an accompanying Makefile in the project folder. To compile the “myexec” executable binary, just type in the “make” command at the Terminal. Run the binary by typing in ./myexec

If the Makefile is not present, you can compile the executable via gcc in Terminal with the following command:

	gcc main.c floppy.c shell.c sort.c -o myexec



*Sample Test Run:


Deans-MBP-2:Project2 deanchoi$ ./myexec

Welcome to the Floppy Disk Shell program. Please enter a command after the prompt to get started. 
For help with a list of the available commands, enter "help". To quit the program, enter "quit".

flop: help

================ FLOPPY DISK HELP =================
             <required> - [optional]

  help:                      Displays a list and description of all available commands.
  quit:                      Quits the floppy disk shell program.
  fmount <img_file>:         Mounts a local floppy disk image.
  fumount:                   Unmounts the mounted floppy disk image.
  structure:                 Lists the structure of the floppy disk image.
  traverse [-l]:             Lists the contents of the root directory. Optional -l flag lists more file details.
  showfat:                   Shows the content of the FAT Table.
  showsector <sector_num>:   Shows the contents of the specific sector.

================ FLOPPY DISK HELP =================

flop: fmount imagefile.img

'imagefile.img' has been successfully mounted.

flop: structure

Structure of Floppy Disk 'imagefile.img':
    number of FAT:                      2
    number of sectors used by FAT:      9
    number of sectors per cluster:      1
    number of ROOT Entries:             224
    number of bytes per sector:         512
    ---Sector #---     ---Sector Types---
          0                   BOOT
       01 -- 09               FAT1
       10 -- 18               FAT2
       19 -- 32               ROOT DIRECTORY

flop: traverse

/A.CLA                             
/ALOOP1.CLA                        
/ALOOP1.JAV                        
/ALOOP2.CLA                        
/ALOOP2.JAV                        
/ALOOP3.CLA                        
/ALOOP3.JAV                        
/B.CLA                             
/CONDIT.CLA                        
/CONDIT.JAV                        
/D.CLA                             
/DEMO.CLA                          
/DEMO.JAV                          
/DIR1                              <DIR>
/DIR1/.                            <DIR>
/DIR1/..                           <DIR>
/DIR1/C.CLA                        
/DIR1/DIR2                         <DIR>
/DIR1/DIR2/.                       <DIR>
/DIR1/DIR2/..                      <DIR>
/FSEVEN~1                          <DIR>
/FSEVEN~1/.                        <DIR>
/FSEVEN~1/..                       <DIR>
/FSEVEN~1/FSEVEN~1                 
/POLYTEST.CLA                      
/POLYTEST.JAV                      

flop: traverse -l

    *****************************
    ** FILE ATTRIBUTE NOTATION **
    **                         **
    ** R ------ READ ONLY FILE **
    ** S ------ SYSTEM FILE    **
    ** H ------ HIDDEN FILE    **
    ** A ------ ARCHIVE FILE   **
    *****************************

-A---	10/27/2014 13:13:05			     670	/A.CLA                             	3
-A---	10/27/2014 13:13:05			     763	/ALOOP1.CLA                        	5
-A---	10/27/2014 13:13:05			     333	/ALOOP1.JAV                        	7
-A---	10/27/2014 13:13:05			     786	/ALOOP2.CLA                        	8
-A---	10/27/2014 13:13:05			     404	/ALOOP2.JAV                        	10
-A---	10/27/2014 13:13:05			     786	/ALOOP3.CLA                        	11
-A---	10/27/2014 13:13:05			     408	/ALOOP3.JAV                        	13
-A---	10/27/2014 13:13:05			     358	/B.CLA                             	14
-A---	10/27/2014 13:13:05			    1067	/CONDIT.CLA                        	15
-A---	10/27/2014 13:13:05			     444	/CONDIT.JAV                        	18
-A---	10/27/2014 13:13:05			     508	/D.CLA                             	19
-A---	10/27/2014 13:13:05			     967	/DEMO.CLA                          	20
-A---	10/27/2014 13:13:05			     648	/DEMO.JAV                          	22
-----	10/27/2014 13:13:05		<DIR>			/DIR1                              	24
-----	10/27/2014 13:13:05		<DIR>			/DIR1/.                            	24
-----	10/27/2014 13:13:05		<DIR>			/DIR1/..                           	0
-A---	10/27/2014 13:13:05			     427	/DIR1/C.CLA                        	27
-----	10/27/2014 13:13:05		<DIR>			/DIR1/DIR2                         	25
-----	10/27/2014 13:13:05		<DIR>			/DIR1/DIR2/.                       	25
-----	10/27/2014 13:13:05		<DIR>			/DIR1/DIR2/..                      	24
---H-	06/19/2017 12:55:09		<DIR>			/FSEVEN~1                          	2
-A-H-	07/02/2017 01:34:04		<DIR>			/FSEVEN~1/.                        	2
-----	06/19/2017 12:55:09		<DIR>			/FSEVEN~1/..                       	0
-A---	07/02/2017 01:34:03			      36	/FSEVEN~1/FSEVEN~1                 	34
-A---	10/27/2014 13:13:05			     630	/POLYTEST.CLA                      	28
-A---	10/27/2014 13:13:05			    1063	/POLYTEST.JAV                      	30

flop: showfat

FAT table content in 'imagefile.img' (starting from Sector 1):

        0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    f

   0            fff    4  fff    6  fff  fff    9  fff  fff    c  fff  fff  fff   10
  10   11  fff  fff  fff   15  fff   17  fff  fff  fff  fff  fff   1d  fff   1f   20
  20  fff  fff  fff FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  30 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  40 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  50 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  60 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  70 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  80 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  90 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  a0 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  b0 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  c0 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  d0 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  e0 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
  f0 FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE FREE
................ (many more lines omitted here)


flop: showsector 10

Hex Dump of Sector 10 in 'imagefile.img':

        0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f

   0   F0   FF   FF   FF   4F    0   FF   6F    0   FF   FF   FF    9   F0   FF   FF
  10   CF    0   FF   FF   FF   FF    F    1   11   F0   FF   FF   FF   FF   15   F0
  20   FF   17   F0   FF   FF   FF   FF   FF   FF   FF   1D   F0   FF   1F    0    2
  30   FF   FF   FF   FF    F    0    0    0    0    0    0    0    0    0    0    0
  40    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  50    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  60    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  70    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  80    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  90    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  A0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  B0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  C0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  D0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  E0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
  F0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 100    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 110    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 120    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 130    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 140    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 150    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 160    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 170    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 180    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 190    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 1A0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 1B0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 1C0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 1D0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 1E0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
 1F0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

flop: fumount

The floppy disk of imagefile.img has been successfully unmounted.

flop: quit

Quitting the floppy disk shell program...


*Existing Bugs: No bugs at the moment. Project was fully tested and vetted to make sure it worked for all different floppy images, FAT12 variances, various user input, and outlier data.
