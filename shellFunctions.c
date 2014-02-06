#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shellFunctions.h"
#include "linkedList.h"
#include "keyVal.h"
#include "FileUtil.h"

void forkIt(char ** argv)
{

	pid_t pid = fork();
	int status;// child;

	if(pid != 0 && !hasAmper) //parent
	{
	    wait(&status);
	}
	else if(pid != 0)
    {
        waitpid(pid,&status,0);
    }
	else
	{
	    //setpgid(0, 0);
		execvp(*argv, argv);
		status = getCount(argv);
		printf("Incorrect Input.\n");
		clean(status, argv);
		exit(-1);
	}

}// end forkIt

char * removeChar(char *str, char * token)
{

    char *output= (char *) calloc(strlen(str) + 1, sizeof(char));
    int i, j;
    for (i = 0, j = 0; i<strlen(str); i++,j++)
    {
        if (str[i] != token[0])
            output[j]=str[i];
        else
            j--;
    }
    output[j]=0;
    return output;
}

int getCount(char ** argv)
{
	int x = 0;

	while(argv[x] != NULL)
		x++;
	return x;
}

void clean(int argc, char **argv)
{
    int x = 0;
    for(x = 0; x < argc; x++)
        free(argv[x]);
    free(argv);
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

char ** makeArgs(char *s, int * argc)
{
    char ** args = NULL;
    char * toke = NULL;
    char * myStringCopy = NULL;
    int x = 0, tot = 0;

    myStringCopy = (char *)calloc(strlen(s)+1, sizeof(char*));
    strcpy(myStringCopy,s);
    toke = strtok(myStringCopy, " ");
	stripRN(toke);

    while(toke != NULL)
    {
        tot++;
        toke = strtok(NULL, " ");
    }

    args = (char**) calloc(tot+1, sizeof(char*));
    strcpy(myStringCopy, s);
    toke = strtok(myStringCopy, " ");
	stripRN(toke);
    args[x] = (char*) calloc(strlen(toke)+1,sizeof(char));
    strcpy(args[x],toke);

    while(x < tot-1)
    {
        x++;
        toke = strtok(NULL," ");
		stripRN(toke);
        args[x] = (char*) calloc(strlen(toke)+1,sizeof(char));
        strcpy(args[x],toke);
    }

    free(myStringCopy);
    *argc = tot;
    return args;

}// end makeArgs

void pipeIt(char **prePipe, char **postPipe)
{

    pid_t pid = fork();
    int status;

    if (pid != 0) //parent
    {
        waitpid(-1, &status, 0);
        status = getCount(postPipe);
        clean(status, postPipe);
        status = getCount(prePipe);
        clean(status, prePipe);
    }

    else
    {
        int fd[2];


        if (pipe(fd) == -1)
        {
            perror("PIPE FAILURE");
            exit(1);
        }

        if (fork() == 0)
        {
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            execvp(prePipe[0], prePipe);
            printf("Incorrect Pre-Pipe Instruction\n");
            status = getCount(prePipe);
            clean(status, prePipe);
        }

        else // parent
        {
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            execvp(postPipe[0], postPipe);
            printf("Incorrect Post-Pipe Instruction\n");
            status = getCount(postPipe);
            clean(status, postPipe);
        }
    }

}// end pipeIt

void redirection(char **pre, char **post, int inOrOut)
{
    pid_t pid =  fork();
    char input[MAX], output[MAX];
    int tot = 0;
    int status;


	if(pid != 0 && !hasAmper) //parent
	{
	    wait(&status);
        tot = getCount(pre);
        clean(tot, pre);
        tot = getCount(post);
        clean(tot, post);
	}
	else if(pid != 0)
    {
        waitpid(pid,&status,0);
        tot = getCount(pre);
        clean(tot, pre);
        tot = getCount(post);
        clean(tot, post);
    }
    else
    {

        /* Be childish */
        if (inOrOut == 0)
        {
            strcpy(input, post[0]);
            int fd1 = open(input, O_RDONLY, 0);
            dup2(fd1, STDIN_FILENO);
            close(fd1);
        }

        if (inOrOut == 1)
        {
            strcpy(output, post[0]);
            int fd2 = open(output, O_WRONLY | O_CREAT, 0666);
            dup2(fd2, STDOUT_FILENO);
            close(fd2);
        }

        execvp(pre[0], pre);
        printf("Failed to exec %s\n", pre[0]);
        exit(1);
    }
}
int parseSides(char *s, char ***leftSide, char *** rightSide, char *token)
{
    char *left = NULL, * right = NULL;
    int leftTot = 0, rightTot = 0;
    char *myStringCopy = (char *) calloc(strlen(s) + 1, sizeof(char));

    strcpy(myStringCopy, s);
    left = strtok(myStringCopy, token);
    stripRN(left);
    right = strtok(NULL, "");

    if (right == NULL)
    {
        free(myStringCopy);
        return -1;
    }

    else
        stripRN(right);

    (*leftSide) = makeArgs(left, &leftTot);
    (*rightSide) = makeArgs(right, &rightTot);

    free(myStringCopy);

    return 1;

}// end parsePipe

void createAlias(char * s, Node ** aliasHead)
{
    if(strstr(s, "=") == NULL || strstr(s, "\"") == NULL)
        printf("Not a proper Alias Command.\n");
    else
    {
        char *key = NULL, *value = NULL;
        char *myStringCopy = (char *) calloc(strlen(s) + 1, sizeof(char));
        KeyVal * newAlias = NULL;
        int isGood = 1;

        strcpy(myStringCopy, s);
        strtok(myStringCopy, " ");
        key = strtok(NULL, "=");

        isGood = hasSpace(key);

        if(!isGood)
            printf("Not a proper Alias Command.\n");
        else if(findNode(*aliasHead, key) != NULL)
            printf("%s is already aliased to a command\n", key);
        else
        {
            value = strtok(NULL, "\"");
            while(strcmp(value, " ") == 0)
                value = strtok(NULL, "\"");

            if(key == NULL || value == NULL)
                printf("Not a proper Alias Command.\n");
            else
            {
                newAlias = createKeyVal(key,value);
                addLast(newAlias, aliasHead);
            }
        }
        free(myStringCopy);
    }
}

void setPath(char * s, char * path, int replace)
{
    char * key = NULL;
    char * myStringCopy = (char*) calloc(strlen(path) + 1, sizeof(char));
    strcpy(myStringCopy, path);

    strtok(myStringCopy, ":");
    key = strtok(NULL, "");

    setenv("PATH", key, replace);

    free(myStringCopy);
}


void removeAlias(char * s, Node ** aliasHead)
{

        char *key = NULL;
        char *myStringCopy = (char*) calloc(strlen(s) +1, sizeof(char));

        strcpy(myStringCopy, s);
        strtok(myStringCopy, " ");
        key = strtok(NULL, "");
        if(key == NULL)
            printf("Not a proper UnAlias Command.\n");
        else
        {
            if(findNode(*aliasHead, key) != NULL)
                removeNode(aliasHead,key);
            else
                printf("Sorry, %s is not an aliased command\n", key);
        }
        free(myStringCopy);

}


void addToHist(char * s, Node ** histHead)
{
        KeyVal * newHist;
        char key[MAX];
        int listCount = (getListCount(histHead) +1);
        sprintf(key,"%d", listCount);
        stripRN(key);
        newHist = createKeyVal(key, s);
        if(listCount > histFileSize)
            removeFirst(histHead);
        addLast(newHist, histHead);
}

int hasSpace(char * word)
{
    int x = 0;
    while (x < strlen(word) - 1)
    {
        if(isspace(word[x]))
            return 0;
        x++;
    }
    return 1;
}


char * finalString(char * words, Node * aliasHead)
{
    char * fString = (char*)calloc(4096, 1);
    KeyVal *swapper = NULL;
    char * toke = NULL;
    if((toke = strtok(words, " "))!= NULL)
    {
        if((swapper = findNode(aliasHead,toke))!= NULL)
        {
            strcat(fString, swapper->value);
        }
        else
        {
            strcat(fString, toke);
        }

        while((toke = strtok(NULL, " ")) != NULL)
        {
            if((swapper = findNode(aliasHead,toke))!= NULL)
            {
                strcat(fString, " ");
                strcat(fString, swapper->value);
            }
            else
            {
                strcat(fString, " ");
                strcat(fString, toke);
            }
        }
    }
    stripRN(fString);
    return fString;
}


void doWork(char * s, char ** prevCommand, char ** path, char ** directory, Node ** aliasHead, Node ** histHead, int fromFile)
{

	char ** argv = NULL, **prePipe = NULL, **postPipe = NULL, **post = NULL, **pre = NULL, *fString = NULL, * temp = NULL;
    int argc;

    stripRN(s);

    if(strcmp(s, "!!") == 0 && fromFile == 0)
    {
        fString = finalString(*prevCommand, *aliasHead);
        strcpy(s, fString);
    }
    if(s[0] == '!' && s[1] != '!' && fromFile == 0)
    {
        temp = removeChar(s, "!");
        KeyVal * cmd = findNode(*histHead, temp);
        fString = finalString(cmd->value, *aliasHead);
    }
    else
    {
        if(*prevCommand != NULL)
        {
            if(strcmp(*prevCommand, s) != 0 && fromFile == 0)
            {
                addToHist(s, histHead);
                free(*prevCommand);
            }
        }
        else
            addToHist(s, histHead);
    }
    if(fromFile == 0)
        *prevCommand = strdup(s);
    if(strstr(s, "unalias"))
    {
        removeAlias(s, aliasHead);
    }
    else
    {
        if(strstr(s, "&") != NULL)
        {
            fString = finalString(removeChar(s, "&"), *aliasHead);
            hasAmper = 1;
        }
        else if(fString == NULL)
            fString = finalString(s, *aliasHead);

        stripRN(fString);
        argv = makeArgs(fString,&argc);

        if(strstr(argv[0], "PATH=") != NULL)
        {
            setPath(fString, *path, 0);
        }
        else if(strstr(argv[0], "HISTSIZE=") != NULL)
        {
            strtok(fString, "=");
            histSize = atoi(strtok(NULL,""));
        }
        else if(strstr(argv[0], "HISTFILESIZE=") != NULL)
        {
            strtok(fString, "=");
            histFileSize = atoi(strtok(NULL,""));
        }
        else if(strcasecmp(argv[0], "alias") == 0)
        {
            if(strcasecmp(fString, "alias") == 0)
                printList(*aliasHead);
            else
                createAlias(fString, aliasHead);
        }
        else if(strcasecmp(fString, "history") == 0)
        {
            int x = getListCount(histHead);
            if(x > histSize)
            {
                x = x - histSize;
                printFromIndex(histHead,x);
            }
            else
                printList(*histHead);
        }
        else if(strcasecmp(argv[0], "cd") == 0)
        {
            *directory = argv[1];
            chdir(argv[1]);
        }
        else if(strstr(fString, "|") != NULL)
        {
            parseSides(fString, &prePipe, &postPipe, "|");
            pipeIt(prePipe, postPipe);
        }
        else if(strstr(fString, "<") != NULL)
        {
            parseSides(fString, &pre, &post, "<");
            redirection(pre, post, 0);
        }
        else if(strstr(fString, ">") != NULL)
        {
            parseSides(fString, &pre, &post, ">");
            redirection(pre, post, 1);
        }
        else
        {
            forkIt(argv);
        }
  	}
    freeCharPP(argv);
  	free(fString);
  	free(temp);
}

void freeCharPP(char ** argv)
{
    if(argv != NULL)
    {
        int x = 0;
        int argc = getCount(argv);
        for(x = 0; x < argc; x++)
            if(argv[x] != NULL)
            {
                free(argv[x]);
                argv[x] = NULL;
            }
        if(argv != NULL)
            free(argv);
        argv = NULL;
    }

}

