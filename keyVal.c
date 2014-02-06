//Frank Kepler 1/11/2014 CSCD340 HW1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "keyVal.h"

extern int MAX;

KeyVal * createKeyVal(char * keyIn, char * valueIn)
{
    KeyVal * newKeyVal = (KeyVal *) calloc(1, sizeof(KeyVal));
    newKeyVal->key = (char*) calloc(strlen(keyIn)+1, sizeof(char));
    strcpy(newKeyVal->key, keyIn);
    newKeyVal->value = (char*) calloc(strlen(valueIn)+1, sizeof(char));
    strcpy(newKeyVal->value, valueIn);

    return newKeyVal;
}

/*
char * getPosition(char * fileName)
{
    char * position = (char*)calloc(2, sizeof(char*));
    strncpy(position, fileName+7, 2);
    if(strcmp(position, "K.") == 0)
        strcpy(position,"K");
    return position;
}

void getKeyValName(char ** fName, char ** lName)
{
    char tempF[MAX], tempL[MAX];
    while ( getchar() != '\n' );
    printf("Please enter the FIRST name of the KeyVal you would like to remove: ");
    fgets(tempF,MAX,stdin);
    printf("Please enter the LAST name of the KeyVal you would like to remove: ");
    fgets(tempL,MAX,stdin);
    *fName = (char*)calloc(strlen(tempF)+1, sizeof(char));
    *lName = (char*)calloc(strlen(tempL)+1, sizeof(char));
    stripRN(tempF);
    stripRN(tempL);
    strcpy(*fName,tempF);
    strcpy(*lName,tempL);
}
void getPositionUser(char ** position)
{
    char temp[MAX];
    while ( getchar() != '\n' );
    printf("What position: ");
    fgets(temp,MAX,stdin);
    *position = (char*)calloc(strlen(temp)+1, sizeof(char));
    stripRN(temp);
    strcpy(*position,temp);

}

void printSpecificKeyVals(Node *head, char * position)
{
    if(head == NULL)
        printf("List is Empty!");
    else
    {
        Node * cur = head;
        printf("----------------------------------------------------------------------------------------\n%-20s|%-20s|%-10s|%-20s|%-13s|\n", "Last Name","First Name","Position","Team Name","Games Played");
        while(cur != NULL)
        {
          if(strcasecmp(((KeyVal*)(cur->data))->position, position) == 0)
            {
                KeyVal * curPlay = ((KeyVal*)cur->data);
                printf("----------------------------------------------------------------------------------------\n%-20s|%-20s|%-10s|%-20s|%-13d|\n", curPlay->value, curPlay->key, curPlay->position, curPlay->teamName, curPlay->gamesPlayed);
            }
            cur = cur->next;
        }
        printf("----------------------------------------------------------------------------------------\n");
    }
}
*/
