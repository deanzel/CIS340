/* Dean Choi
 * Sorting directory entry functions
*/

#include <stdio.h>
#include <string.h>
#include "sort.h"
#include "floppy.h"


//mergesort the array of directory entries by filename
struct mynode* mergeSort(struct mynode* head) {
    //Case if list is null to begin with and the final determining step of the recurrent relationship where the list is
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
    return merge(head, head2);

};


//merging two sorted linked lists and returning the pointer to lowest determined value
struct mynode* merge(struct mynode* a, struct mynode* b) {

    //Case if first linked list starting from a is empty
    if (a == NULL){
        return b;
    }
    //Case if second linked list starting from b is empty
    if (b == NULL){
        return a;
    }
    //If a's full pathname is smaller than b's full pathname
    if (strcmp(a->entry.fullpath, b->entry.fullpath) < 0) {
        //We perform a merge function between the next node after a and the original b (recursive call) and assign that
        // as the next node for the original a (which is the smallest sorted value here)
        a->next = merge(a->next, b);
        //Return the processed node of a which is the smallest fullpath value
        return a;
    }
    //If a's full pathname is greater than b's full pathname
    else if (strcmp(a->entry.fullpath, b->entry.fullpath) > 0) {
        //We perform a merge function between the next node after b and the original a (recursive call) and assign that
        //as the next node for the original b (which is the smallest sorted value here)
        b->next = merge(a, b->next);
        //Return the processed node of b which is the smallest fullpath value
        return b;
    }
    //If somehow a and b have the same fullpath name (this should never be reached though)
    else {
        return b;
    }

};



//Splitting a linked list into 2 and returning the pointer of the head of the second linked list
struct mynode* split(struct mynode* head) {
    //create a fast node which advances two links per iteration and a slow node which advances one link per iteration
    struct mynode *fast = head->next;
    struct mynode *slow = head;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    //This will return the head of the second linked list and NULL the .next reference between the two adjacent lists
    //which acts as splitting the list
    struct mynode *head2 = slow->next;
    slow->next = NULL;
    return head2;

};