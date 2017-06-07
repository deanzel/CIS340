/* Dean Choi
 * CSU# 2690159
 * CIS 340 - Project 1 - Node Header file for declarations and macro definitions
*/

#ifndef NODE_H
#define NODE_H

struct mynode {
    int const value;
    struct mynode *next;
    struct mynode *prev;
};

void printList(struct mynode* head);

struct mynode* mergeSort(struct mynode* head);

struct mynode* merge(struct mynode* a, struct mynode* b);

struct mynode* split(struct mynode* head);

#endif //NODE_H
