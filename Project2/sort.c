/* Dean Choi
 * Sorting directory entry functions
*/

#include <stdio.h>
#include <string.h>
#include "sort.h"




//mergesort the array of directory entries by filename
struct mynode* mergeSort(struct mynode* head) {
/*    //Case if list is null to begin with and the final determining step of the recurrent relationship where the list is
    // broken down to a single node
    if (head == NULL || head->next == NULL) {
        return head;
    };
    //List is split and head of second list is assigned to *head2
    struct mynode *head2 = split(head);

    //Recursive mergesort on the two split linked lists
    head = mergeSort(head);
    head2 = mergeSort(head2);

    //Merge the two sorted halves of the DLL
    return merge(head, head2);*/

};


//merging two sorted linked lists and returning the pointer to lowest determined value
struct mynode* merge(struct mynode* a, struct mynode* b) {
/*

    //Case if first linked list starting from a is empty
    if (a == NULL){
        return b;
    }
    //Case if second linked list starting from b is empty
    if (b == NULL){
        return a;
    }
    //If a's filename is smaller than b's filename
    if (strcmp(a->entry.filename, b->entry.filename) < 0) {
        //We perform a merge function between the next node after a and the original b (recursive call) and assign that
        // as the next node for the original a (which is the smallest sorted value here)
        a->next = merge(a->next, b);
        //Whichever node reference is returned, we change its prev pointer to the lowest value a

        //Since a is the lowest, we make its prev pointer NULL

        //Return the processed node of a which is the lowest
        return a;
    }

    else if (strcmp(a->entry.filename, b->entry.filename) > 0) {
        //We perform a merge function between the next node after b and the original a (recursive call) and assign that
        //as the next node for the original b (which is the smallest sorted value here)
        b->next = merge(a, b->next);
        //Whichever node reference is returned, we change its prev pointer to the lowest value b

        //Since b is the lowest, we make its prev pointer NULL

        //Return the processed node of b which is the lowest
        return b;

    }

    else {


        return b;

    }
*/



};






//Splitting a linked list into 2 and returning the pointer of the head of the second linked list
struct mynode* split(struct mynode* head) {







};






