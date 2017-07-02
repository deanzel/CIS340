/* Dean Choi
 * Sorting directory entry header file
*/

#ifndef SORT_H
#define SORT_H


//Merge sort functions for the Singly-Linked List
struct mynode* mergeSort(struct mynode*);
struct mynode* merge(struct mynode* a, struct mynode* b);
struct mynode* split(struct mynode* head);


#endif //SORT_H
