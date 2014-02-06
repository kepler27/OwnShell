//Frank Kepler 1/11/2014 CSCD340 HW1
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include<stdio.h>

struct node
{
    void * data;
    struct node * next;
};


typedef struct node Node;

void addFirst(void * data, Node ** head);
void addLast(void * data, Node ** head);
void printListToFile(Node * head, FILE * fout);
//void addOrdered(void * data, Node ** head);
void addIndexed(void * data, Node ** head, int index);
void removeIndex(Node ** head, int index);
void removeFirst(Node ** head);
void removeLast(Node ** head);
void removeNode(Node ** head, char * keyIn); //fName & lName should be changed for future lists.
void * findNode(Node* head, char * keyIn);
void clearList(Node ** head);
void printList(Node * head);
int getListCount(Node ** head);
void printFromIndex(Node ** head, int index);
void printToFileFromIndex(Node ** head, int index, FILE * fout);
void freeNode(Node * cur);
Node * createNode(void* data);

//Node * sortList (Node *n, int flag);
//Node * mergeLists(Node *a, Node *b, int flag);
//Node * divList (Node *n, int flag);
//void sortByInt(Node ** head);
//void sortByChar(Node ** head);

#endif // LINKEDLIST_H_INCLUDED
