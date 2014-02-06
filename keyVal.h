//Frank Kepler 1/11/2014 CSCD340 HW1
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

struct keyVal
{
    char * key;
    char * value;
};

typedef struct keyVal KeyVal;

KeyVal* createKeyVal(char * key, char * value);
//char * getPosition(char * fileName);
//void getPositionUser(char ** position);
//void getPlayerName(char ** fName, char ** lName);
//void printSpecificPlayers(Node *head, char * position);
#endif // PLAYER_H_INCLUDED
