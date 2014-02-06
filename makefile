mysh:	FileUtil.o keyVal.o linkedList.o shellFunctions.o
	gcc cscd340_w14_hw3.c FileUtil.o keyVal.o linkedList.o shellFunctions.o -o mysh


shellFunctions.o:	shellFunctions.c shellFunctions.h
	gcc -c shellFunctions.c

FileUtil.o:	FileUtil.c FileUtil.h 
	gcc -c FileUtil.c

linkedList.o:	linkedList.c linkedList.h
	gcc -c linkedList.c

keyVal.o:	keyVal.c keyVal.h
	gcc -c keyVal.c
