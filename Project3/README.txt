Dean Choi
CSU# 2690159
CIS 340 - Project 3 - A Customized Shell

============================================================================
*Project Description:
This C console program allows acts as a customized shell that supports Linux shell commands in addition to the internal commands based upon our own determined PATH environment variable.

============================================================================
*Compiling Instructions:
The source code of this program consists of 3 files: 2 source code files of “main.c” & “shell.c” along with 1 header file of “shell.h”.

This C source code comes with an accompanying Makefile in the project folder. To compile the “myexec” executable binary, just type in the “make” command at the Terminal. Run the binary by typing in ./myexec

If the Makefile is not present, you can compile the executable via gcc in Terminal with the following command:

	gcc main.c shell.c sort.c -o myexec

============================================================================
*Instructions on how to use the internal commands of the Shell program:
1). cd (without arguments)  :  is a command to change to your current working directory to the furthest allowable root directory.

2). cd </full_folder_path>  :  is a command to change your current working directory to the specified full folder path (if it exists and you have permission). The cd command is flexible in that you can start or end with/without a ‘/‘ character.
	*Special note: If your target folder path includes a ‘blank space’ somewhere, I have implemented a method to allow for the parsing. You just need to enclose the argument in two surrounding quotation marks (\”). The shell will only parse the blank spaces outside of surrounding quotes. For example, “cd “/Users/deanchoi/Happy Birthday/Pictures” is a valid command that works.

3). cd <relative_folder_path>  :  us a command to change your current working directory to the specified relative folder path from your current working directory. For example, “cd ..” will change the current working directory of the shell to its immediate parent directory. The cd command is flexible in that you can start or end with/without a ‘/‘ character.
	*Special note: If your target folder path includes a ‘blank space’ somewhere, I have implemented a method to allow for the parsing. You just need to enclose the argument in two surrounding quotation marks (\”). The shell will only parse the blank spaces outside of surrounding quotes. For example, “cd “/Users/deanchoi/Happy Birthday/Pictures” is a valid command that works.

4). path (without arguments)  :  displays the pathnames currently set when searching for binaries outside of the current working directory. It is initialized to a blank string at startup, so you must add your own pathnames manually via the next 2 methods. For example, the “path” command can return a string like this once setup, “/bin:/sbin:/usr/bin”, with the ‘:’ character serving as the delimiter between each full path folder.

5). path + </full_path_name>  :  appends the single full path name to the “pathnames” variable. The </full path name> argument must be in the form of “/abc/def” where it begins with a ‘/‘, doesn’t end with a ‘/‘, and doesn’t contain any ‘:’ characters. The pathname is appended to the path variable whether it exists or not, so be careful when entering it.

6). path - </full_path_name>  :  removes the specified pathname from the path variable, only if it exists exactly as so in the current path variable. The </full path name> argument must be in the form of “/abc/def” where it begins with a ‘/‘, doesn’t end with a ‘/‘, and doesn’t contain any ‘:’ characters. The case of the characters must match exactly as printed in the path variable.

7). quit  :  This command will exit/quit the shell program.

8). cmd1 | cmd2  :  pipes the two commands together and provides the appropriate I/O redirection. For example, “ls -l | grep txt”.

9). cmd1 | cmd2 | cmd3 | …. | cmdn  :  pipes together a series of n commands with the appropriate I/O redirection. Support for “infinite” pipes has been implemented only limited by the input char restriction of 4096 characters. For example, “ls -l | grep txt | wc - c”.

10). cmd1 > filename  :  Output redirection where the output of cmd1 is saved to the text file of filename.txt. For example, “ls -l > DeanText” saves the output of “ls -l” in the current directory to a text file named “DeanText.txt” in the same current directory.

11). cmd1 < myfile  :  Input redirection where the text data in the myfile.txt text file is redirected into the input of cmd1. For example, “grep txt < DeanText” will input the previously saved “ls -l” text output into the “grep txt” string search command.


**Instructions on how to use other Linux commands:
1). Full Linux commands are supported beyond the above internal commands. You just need to specify the proper pathname in the path variable beforehand.
2). To run a binary in the current working directory, you must type in the format of “./binaryname”.
3). Internal commands are searched first before defaulting to searching for the individual Linux commands in each pathname directory.


============================================================================
*Sample Test Run:

dechoi@vangogh:~/dechoi/Project3$ ./myexec

Welcome to Dean Choi's customized Linux shell.

Project3$ path

The current path environment is empty. Please add at least one path folder...

Project3$ path + /usr/local/sbin

/usr/local/sbin

Project3$ path + /usr/local/bin

/usr/local/sbin:/usr/local/bin

Project3$ path

/usr/local/sbin:/usr/local/bin

Project3$ cd

$ pwd

/

$  cd /home

home$ pwd

/home

home$ cd student/dechoi

dechoi$ pwd

/home/student/dechoi

dechoi$ ls -l

total 3900
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 CIS 265 HW
drwxr-xr-x 4 dechoi users    4096 Jul  7  2016 cuda-workspace
drwxr-xr-x 5 dechoi users    4096 Jul 13 08:42 dechoi
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Desktop
-rw-r--r-- 1 dechoi users  181202 Jul 12 19:33 device.pdf
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Documents
drwxr-xr-x 2 dechoi users    4096 Jan 26 18:22 Downloads
-rw-r--r-- 1 dechoi users    8980 Jul  5  2016 examples.desktop
-rw-r--r-- 1 dechoi users 3457732 Jun 16 16:14 fat12.pdf
-rw-r--r-- 1 dechoi users  111003 Jul 21  2016 jul20.jpg
-rw-r--r-- 1 dechoi users  103278 Jul 21  2016 july18.jpg
-rw-r--r-- 1 dechoi users   54047 Jul 21  2016 july19.jpg
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Music
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Pictures
-rw-r--r-- 1 dechoi users   11573 Jun 16 12:20 project2.html
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Public
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Templates
drwxr-xr-x 2 dechoi users    4096 Jul  7  2016 Videos

dechoi$ ls -l | grep pdf

-rw-r--r-- 1 dechoi users  181202 Jul 12 19:33 device.pdf
-rw-r--r-- 1 dechoi users 3457732 Jun 16 16:14 fat12.pdf

dechoi$ ls -l > DeanText

dechoi$ ls

CIS 265 HW      Desktop     examples.desktop  july19.jpg     Public
cuda-workspace  device.pdf  fat12.pdf         Music          Templates
DeanText.txt    Documents   jul20.jpg         Pictures       Videos
dechoi          Downloads   july18.jpg        project2.html

dechoi$ grep txt < DeanText
-rw-r--r-- 1 dechoi users       0 Jul 13 08:49 DeanText.txt

dechoi$ quit

Quitting the shell program...


============================================================================
*Existing Bugs:
1). You cannot have a argument or string sequence of “ | “ outside of your pipe declarations. However, with the parsing/splitting method implemented, you are allowed to have the ‘|’ character in any of your arguments.
2). Input is limited to 4096 characters.
3). Current maximum number of arguments within a single command (within a pipe) is set at 15 with each having a maximum length of 99. However, this is hardcoded in and dynamically allocated, so it is very easy to change.
4). Current pipe commands beyond 1 total pipe has a bug at the moment. I created an method that can parse and process an “infinite” number of pipes, but there seems to be a tiny bug somewhere in the piping/wiring somewhere. Almost have it finished.
5). Input and Output redirection has been completed and implemented individually and in addition to pipe system calls. You can see the output samples above.
