//Frank Kepler 1/11/2014 CSCD340 HW1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileUtil.h"

const int MAX = 100;

char * getFileName()
{
    char temp[MAX];
	printf("\nPlease enter the name of the file you wish to use: ");
	scanf("%s", temp);
	char * fn = (char*)calloc(strlen(temp)+1, sizeof(char));
	strcpy(fn,temp);
	return fn;
}

FILE * openUnknownFile(char * mode)
{

	FILE * fin = NULL;
	int count = 0;
	char temp[MAX], fn[MAX];

	getFileName(fn);

	fin = fopen(fn, mode);
	if(!fin)
	{
		printf("File could not open.");
		exit(-1);
	}
	while(!feof(fin))
	{
		fscanf(fin,"%s", temp);
		count++;
	}
	if(count == 0)
	{
		perror("Empty File");
		exit(-1);
	}
	rewind(fin);
	return fin;
}

FILE * openKnownFile(char * fn, char * mode)
{

	FILE * fin = NULL;
	int count = 0;
	char temp[MAX];

	fin = fopen(fn, mode);
	if(!fin)
	{
		printf("File could not open.");
		exit(-1);
	}
	while(!feof(fin) && (strcmp(mode, "w") != 0))
	{
		fscanf(fin,"%s", temp);
		count++;
	}
	if(count == 0 && (strcmp(mode, "r") == 0))
	{
		perror("Empty File");
		exit(-1);
	}
	rewind(fin);
	return fin;
}

void stripRN(char * word)
{
    int i = 0;
    for(i = 0; i < strlen(word); i++)
        if(word[i] == '\r' || word[i] == '\n')
            word[i] = '\0';
}
