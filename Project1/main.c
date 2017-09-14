/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 1 - Doubly Linked List
*/

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main() {

    char *filename = "samplevalues.txt";

    //Check to see is the samplevalues.txt file exists and if it does, change the stdin to read from keyboard to the file
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        fclose(stdin);
        stdin = f;
    };

    printf("\nType in an integer value to add to the list. A value of 0 will end the input:\n");

    //Allocate memory space for a struct mynode which won't initialize the int const value but just set aside memory space
    //for it. Const cannot be changed once initialized. We can then use scanf to assign it a value via the pointer.
    struct mynode *head = (struct mynode*) malloc(sizeof(struct mynode));

    scanf("%d", (int *) &head->value);
    head->next = NULL;
    head->prev = NULL;

    struct mynode *current = head;

    //Read from stdin integer input and assign to a temp node that we create. If the int value is not 0, it will append
    //the node to our Doubly Linked List and repeat the loop.
    while (current->value != 0) {
        struct mynode *temp = (struct mynode*) malloc(sizeof(struct mynode));
        temp->next = NULL;
        temp->prev = NULL;

        scanf("%d", (int *) &temp->value);
        if (temp->value != 0) {
            current->next = temp;
            temp->prev = current;
            current = temp;
        } else {
            break;
        }
    };

    printf("\nThis is the original unsorted Linked List:\n");
    printList(head);

    printf("\nThis is the Linked List after merge sorting:\n");
    printList(mergeSort(head));

    return 0;

}