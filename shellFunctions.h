#ifndef SHELLFUNCTIONS_H_INCLUDED
#define SHELLFUNCTIONS_H_INCLUDED

#include "linkedList.h"
#define MAX 100

extern int histFileSize;
extern int histSize;
extern int hasAmper;

void forkIt(char ** argv);
int getCount(char ** argv);
void clean(int argc, char **argv);
void printargs(int argc, char **argv);
char ** makeArgs(char *s, int * argc);
int parseSides(char *s, char ***leftSide, char *** rightSide, char * token);
void pipeIt(char **prePipe, char **postPipe);
void redirection(char **pre, char **post, int inOrOut);
void createAlias(char * s, Node ** aliasHead);
void removeAlias(char * s, Node ** aliasHead);
void aliasSwap(char ** argv, int argc, Node * aliasHead);
int hasSpace(char * word);
char * finalString(char * words, Node * aliasHead);
void addToHist(char * s, Node ** histHead);
void setPath(char * s, char * path, int replace);
char * removeChar(char *str, char * token);
void doWork(char * s, char ** prevCommand, char ** path, char ** directory, Node ** aliasHead, Node ** histHead, int fromFile);
void freeCharPP(char ** argv);
#endif // SHELLFUNCTIONS_H_INCLUDED
