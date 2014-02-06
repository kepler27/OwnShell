#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellFunctions.h"
#include "linkedList.h"
#include "FileUtil.h"


#include <unistd.h>

int histSize = 0;
int histFileSize = 0;
int hasAmper = 0;

int main()
{
	char s[MAX], *prevCommand = NULL, *path = NULL,  *directory= NULL;
    //int argc;

    Node * aliasHead = NULL;
    Node * histHead = NULL;
    FILE * myshrc = fopen(".myshrc", "r");
    FILE * myshrc_history = fopen(".myshrc_history", "r");
    FILE * profile = fopen(".profile", "r");
    path = getenv("PATH");
    int fromFile = 1;

    while(myshrc != NULL)
    {
        if(fgets(s, MAX, myshrc))
        {
            stripRN(s);
            if(strlen(s) != 0)
                doWork(s, &prevCommand, &path, &directory, &aliasHead, &histHead, fromFile);
        }
        else
        {
            fclose(myshrc);
            myshrc = NULL;
        }
    }

    while(myshrc_history != NULL)
    {
        if(fgets(s, MAX, myshrc_history))
        {
            stripRN(s);
            if(strlen(s) != 0)
                addToHist(s,&histHead);
        }
        else
        {
            fclose(myshrc_history);
            myshrc_history = NULL;
        }
    }
    while(profile != NULL)
    {
        if(fgets(s, MAX, profile))
        {
            stripRN(s);
            if(strlen(s) != 0)
            {
                setPath("PATH", s, 1);
                path = getenv("PATH");
            }
        }
        else
        {
            fclose(profile);
            profile = NULL;
        }
    }


    fromFile = 0;
    printf("?: ");
    fgets(s, MAX, stdin);
    while(strcmp(s, "exit\n") != 0)
    {
        doWork(s, &prevCommand, &path, &directory, &aliasHead, &histHead, fromFile);
        printf("?: ");
        fgets(s, MAX, stdin);
    }

	myshrc_history = fopen(".myshrc_history", "w");

    int x = getListCount(&histHead);
    if(x > histFileSize)
    {
        x = x - histFileSize;
        printToFileFromIndex(&histHead,x, myshrc_history);
    }
    else
        printListToFile(histHead,myshrc_history);

    if(prevCommand != NULL)
        free(prevCommand);
	fclose(myshrc_history);
	clearList(&aliasHead);
	clearList(&histHead);


    return 0;
}// end main
