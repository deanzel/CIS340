Dean Choi
CSU# 2690159
CIS 340 - Assignment 1

Project Description:
This C program creates a Doubly Linked List (DLL) of integer values based upon the user’s keyboard input or if a “samplevalues.txt” file is present in the same directory with accompanying integer values separated by “new lines”. The program first will create individual nodes of the integer values and append them to the DLL as long as the integer value input is not ‘0’. If the user (or the file) enters ‘0’, the creation of the DLL is stopped and the program proceeds on to the next stage.

If you want to ensure that user inputs the node integer values directly, please rename or delete the "samplevalues.txt" file within the folder.

The next part of the program will display the non-sorted order of the integer values in the original DLL. After that, the program will perform a MergeSort on the DLL and then print the integer values of the sorted nodes below. This concludes the program.


Compiling Instructions:
The source code of this program consists of 3 files: main.c, node.c, and node.h.

This C source code comes with an accompanying Makefile in the project folder. To compile the “myexec” executable binary, just type in the “make” command at the Terminal.

If the Makefile is not present, you can compile the executable via gcc in Terminal with the following command:

	gcc main.c node.c -o myexec


Sample Output:
wlan-172-20-40-122:~ deanchoi$ /Users/deanchoi/Documents/CIS340/Project1/myexec
Type in an integer value to add to the list. A value of 0 will end the input:
30
20
50
70
10
0

This is the original unsorted Linked List:
30, 20, 50, 70, 10

This is the Linked List after merge sorting:
10, 20, 30, 50, 70


Existing Bugs: No known bugs at the moment. All requirements were fulfilled.
