//Frank Kepler 1/11/2014 CSCD340 HW1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "linkedList.h"
#include "keyVal.h"

void addFirst(void * data, Node ** head)
{
    Node * newNode = createNode(data);
    if(*head == NULL)
        *head = newNode;
    else
    {
        newNode -> next = *head;
        *head = newNode;
    }
}

void addLast(void * data, Node ** head)
{

    Node * newNode = createNode(data);
    if(*head == NULL)
        *head = newNode;
    else
    {
        Node * cur = *head;

        while(cur -> next != NULL)
            cur = cur -> next;

        cur -> next = newNode;
    }
}

int getListCount(Node ** head)
{
    int count = 1;

    if(*head == NULL)
        return 0;

    Node * cur = *head;

    while(cur -> next != NULL)
    {
        cur = cur -> next;
        count++;
    }

    return count;
}
/*
void addOrdered(void * data, Node ** head)      //MUST BE CHANGED OUT FOR DIFFERING STRUCTS
{
    if(*head == NULL)
        addFirst(data,head);

    else if((*head)->next == NULL)
    {
        Node * newNode = createNode(data);

        if(strcmp(((Player*)((*head)->data))->lastName, ((Player*)(newNode->data))->lastName) < 0)
            (*head)->next = newNode;
        else
        {
            newNode->next = *head;
            *head = newNode;
        }
    }
    else
    {
        Node * newNode = createNode(data);
        Node * cur;
        cur = (*head);
        while(cur->next != NULL && strcmp(((Player*)(cur->next->data))->lastName, ((Player*)(newNode->data))->lastName) < 0)
            cur = cur->next;
        newNode->next = cur->next;
        cur->next = newNode;
    }
}
*/
void addIndexed(void * data, Node ** head, int index)
{

    Node * cur, * prev, * temp;

    if(index == 0)
        addFirst(data, head);
    else
    {

        cur = *head;
        while(index != 0)
        {
            if(cur->next == NULL)
            {
                printf("Index out of Bounds");
                break;
            }
            else
            {
                prev = cur;
                cur = cur->next;
                index--;
            }
        }
        if(index == 0)
        {
            Node * newNode = createNode(data);
            temp = cur;
            prev->next = newNode;
            newNode->next = temp;
        }
    }
}
void printFromIndex(Node ** head, int index)
{

    Node * cur, * prev;

    if(index == 0)
        printList(*head);
    else
    {

        cur = *head;
        while(index != 0)
        {
            if(cur->next == NULL)
            {
                printf("Index out of Bounds");
                break;
            }
            else
            {
                prev = cur;
                cur = cur->next;
                index--;
            }
        }
        if(index == 0)
        {
            printList(cur);
        }
    }
}

void printToFileFromIndex(Node ** head, int index, FILE * fout)
{

    Node * cur, * prev;

    if(index == 0)
        printListToFile(*head, fout);
    else
    {
        cur = *head;
        while(index != 0)
        {
            if(cur->next == NULL)
            {
                printf("Index out of Bounds");
                break;
            }
            else
            {
                prev = cur;
                cur = cur->next;
                index--;
            }
        }
        if(index == 0)
        {
            printListToFile(cur, fout);
        }
    }
}

void removeFirst(Node ** head)
{
    if(*head != NULL)
    {
        Node * cur = *head;

        *head = (*head) -> next;
        freeNode(cur);
    }
}

void removeLast(Node ** head)
{
    Node * cur = *head;
    if(cur == NULL)
        printf("Empty List");
    else if(cur->next == NULL)
    {
        freeNode(cur);
    }
    else
    {
        while(cur->next->next != NULL)
            cur = cur->next;
        freeNode(cur->next);
        cur->next = NULL;

    }

}

void removeIndex(Node ** head, int index)
{
    Node * cur, * prev, * temp;

    if(index == 0)
        removeFirst(head);
    else if(index < 0)
    {
        printf("Index out of Bounds");
    }
    else
    {
        cur = *head;
        while(index != 0)
        {
            if(cur->next == NULL)
            {
                printf("Index out of Bounds");
                break;
            }
            else
            {
                prev = cur;
                cur = cur->next;
                index--;
            }
        }
        if(index == 0)
        {
            temp = cur;
            prev->next = cur->next;
            freeNode(temp);
        }
    }
}

void clearList(Node ** head)
{
    if(*head != NULL)
    {
        Node * cur = *head;

        while(cur != NULL)
        {
            *head = (*head) -> next;
            freeNode(cur);
			cur = *head;
		}
	}
}

void printList(Node * head)//MUST BE CHANGED OUT FOR DIFFERING STRUCTS
{
    if(head == NULL)
        printf("List is Empty!\n");
    else
    {
        Node * cur = head;
        printf("--------------\n%-10s|%-10s\n", "Key","Value");
        while(cur != NULL)
        {
            KeyVal * curKeyVal = ((KeyVal*)cur->data);
            printf("-------------\n%-10s|%-10s\n", curKeyVal->key, curKeyVal->value);
            cur = cur -> next;
        }
        printf("---------------\n");
    }
}

void printListToFile(Node* head, FILE * fout)//MUST BE CHANGED OUT FOR DIFFERING STRUCTS
{
    if(head == NULL);
    else
    {
        Node * cur = head;
//        fprintf(fout,"--------------\n%%-10s\n","Value");
        while(cur != NULL)
        {
            KeyVal * curKeyVal = ((KeyVal*)cur->data);
            fprintf(fout,"%s\n", curKeyVal->value);
            cur = cur -> next;
        }
    }
}

void freeNode(Node * cur)//MUST BE CHANGED OUT FOR DIFFERING STRUCTS
{
    if( ((KeyVal*)(cur->data))-> key != NULL)
    {
        free(((KeyVal*)(cur->data))->key);
        ((KeyVal*)(cur->data))->key = NULL;
    }
    if( ((KeyVal*)(cur->data))->value != NULL)
    {
        free(((KeyVal*)(cur->data))->value);
        ((KeyVal*)(cur->data))->value = NULL;
    }
    if(cur->data != NULL)
    {
        free(cur -> data);
        cur -> data = NULL;
    }
    if(cur != NULL)
    {
        free(cur);
        cur = NULL;
    }
}

Node * createNode(void* data)//MUST BE CHANGED OUT FOR DIFFERING STRUCTS
{
    Node * newNode = (Node *)calloc(1, sizeof(Node)); //was Node, changed to Node * haven't tested.

    newNode -> data = (KeyVal*)data;

    return newNode;
}

void removeNode(Node ** head, char * keyIn)
{
    Node * cur, * prev, * temp;

    if(head == NULL)
        printf("List is Empty!");
    else if((strcasecmp(keyIn, ((KeyVal*)((*head)->data))->key)) == 0)
        removeFirst(head);
    else
    {
        cur = *head;
        while( (strcasecmp(keyIn, ((KeyVal*)(cur->data))->key)) != 0)
        {
            if(cur->next == NULL)
            {
                printf("The item to be removed was not located.");
                break;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
        if((strcasecmp(keyIn,((KeyVal*)(cur->data))->key)) == 0)
        {
            if(cur->next == NULL)
            {
                freeNode(cur);
                prev->next = NULL;
            }
            else
            {
                temp = cur;
                prev->next = cur->next;
                freeNode(temp);
            }
        }
    }
}

void* findNode(Node* head, char * keyIn)//MUST BE CHANGED OUT FOR DIFFERING STRUCTS
{
    if(head == NULL);
    else
    {
        Node * cur = head;
        while(cur != NULL)
        {
            KeyVal * curKeyVal = ((KeyVal*)cur->data);
            if ((strcasecmp(keyIn,curKeyVal->key)) == 0)
                return curKeyVal;
            else

                cur = cur -> next;

        }
    }
    return NULL;
}

Node * divList (Node *n, int flag)
{
    int i = 0;
    if (n)
    {
        Node *tail, *n2 = n;
        while (1)
        {
            n2 = n2->next;
            if (!n2) break;
            if (i++ & 1) n = n->next;
        }
        tail = n->next;
        n->next = NULL;
        return tail;
    }
    return NULL;
}
/*
Node * mergeLists(Node *a, Node *b, int flag)
{
    Node *n;
    Node **last = &n;
    if (!a) return b;
    if (!b) return a;

    while (1)
    {
        if(flag == 1)
        {

            if(strcasecmp(((Player*)(a->data))->teamName,((Player*)(b->data))->teamName) > 0)   //CHANGE BASED ON SORTING PARAM
            {
                *last = b;
                last = &b->next;
                b = b->next;
                if (!b)
                {
                    *last = a;
                    break;
                }
            }
            else
            {
                *last = a;
                last = &a->next;
                a = a->next;
                if (!a)
                {
                    *last = b;
                    break;
                }
            }
        }
        else
        {
            if(((Player*)(a->data))->gamesPlayed < ((Player*)(b->data))->gamesPlayed)   //CHANGE BASED ON SORTING PARAM
            {
                *last = b;
                last = &b->next;
                b = b->next;
                if (!b)
                {
                    *last = a;
                    break;
                }
            }
            else
            {
                *last = a;
                last = &a->next;
                a = a->next;
                if (!a)
                {
                    *last = b;
                    break;
                }
            }
        }
    }
    return n;
}

Node * sortList (Node *n, int flag)
{
    Node *tail = divList(n, flag);
    if (!tail) return n;
    return mergeLists(sortList(n,flag), sortList(tail,flag),flag);
}

void sortByChar(Node ** head)
{
    Node * cur, * prev, * find;
    for(cur = *head; cur->next != NULL; cur = cur->next)
    {
        prev =cur;
        for(find = cur->next; find != NULL;find = find->next)
        {
            if(strcasecmp(((Player*)(prev->data))->teamName, ((Player*)(find->data))->teamName) > 0)
                prev = find;
            else if(strcasecmp(((Player*)(prev->data))->teamName, ((Player*)(find->data))->teamName) == 0)
            {
                if(strcasecmp(((Player*)(prev->data))->lastName, ((Player*)(find->data))->lastName) > 0)
                prev = find;
            }
        }
        Player * temp = cur->data;
        cur->data = prev->data;
        prev->data = temp;
    }
}

void sortByInt(Node ** head)
{
    Node * cur, * prev, * find;
    for(cur = *head; cur->next != NULL; cur = cur->next)
    {
        prev =cur;
        for(find = cur->next; find != NULL; find = find->next)
        {
            if(((Player*)(prev->data))->gamesPlayed < ((Player*)(find->data))->gamesPlayed)
                prev = find;
            else if(((Player*)(prev->data))->gamesPlayed == ((Player*)(find->data))->gamesPlayed)
            {
                if(strcasecmp(((Player*)(prev->data))->lastName, ((Player*)(find->data))->lastName) > 0)
                prev = find;
            }
        }
        Player * temp = cur->data;
        cur->data = prev->data;
        prev->data = temp;
    }
}
*/
