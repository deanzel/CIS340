/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 1 - Define the function mergeSort and printList
*/

//In C compiler, can get rid of these preprocessor lines
#include <stdio.h>
#include "node.h"

//Prints out a Doubly Linked List in the forward direction
void printList(struct mynode* head) {

    struct mynode *current = head;

    while (current != NULL) {
        if (current->next != NULL) {
            printf("%d, ", current->value);

        } else {
            printf("%d\n", current->value);
        }

        current = current->next;
    };
};

struct mynode* mergeSort(struct mynode* head){
    //Case if list is null to begin with and the final determining step of the recurrent relationship where the list is
    // broken down to a single node
    if (head == NULL || head->next == NULL) {
        return head;
    };
    //List is split and head of second list is assigned to *head2
    struct mynode *head2 = split(head);

    //Recurrent mergesort on the two split linked lists
    head = mergeSort(head);
    head2 = mergeSort(head2);

    //Merge the two sorted halves of the DLL
    return merge(head, head2);

};

//Merging TWO SORTED Linked lists and returning the pointer to the lowest determined value
struct mynode* merge(struct mynode* a, struct mynode* b) {
    //Case if first linked list starting from a is empty
    if (a == NULL){
        return b;
    }
    //Case if second linked list starting from b is empty
    if (b == NULL){
        return a;
    }
    //If a.value is smaller than b.value
    if (a->value < b->value){
        //We perform a merge function between the next node after a and the original b (recursive call) and assign that
        // as the next node for the original a (which is the smallest sorted value here)
        a->next = merge(a->next, b);
        //Whichever node reference is returned, we change its prev pointer to the lowest value a
        a->next->prev = a;
        //Since a is the lowest, we make its prev pointer NULL
        a->prev = NULL;
        //Return the processed node of a which is the lowest
        return a;
    }
    //If b.value is smaller than a.value
    else {
        //We perform a merge function between the next node after b and the original a (recursive call) and assign that
        //as the next node for the original b (which is the smallest sorted value here)
        b->next = merge(a, b->next);
        //Whichever node reference is returned, we change its prev pointer to the lowest value b
        b->next->prev = b;
        //Since b is the lowest, we make its prev pointer NULL
        b->prev = NULL;
        //Return the processed node of b which is the lowest
        return b;

    }
};

//Splits a DLL into 2 DLLs of half sizes and returns pointer to starting head of second DLL
struct mynode* split(struct mynode* head) {
    //create a fast node which advances two links per iteration and a slow node which advances one link per iteration
    struct mynode *fast = head->next;
    struct mynode *slow = head;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    //This will return the head of the second linked list and NULL the .next reference between the two adjacent lists
    struct mynode *head2 = slow->next;
    slow->next = NULL;
    return head2;
};