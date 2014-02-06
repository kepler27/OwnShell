//Frank Kepler 1/11/2014 CSCD340 HW1
#ifndef FILEUTIL_H_INCLUDED
#define FILEUTIL_H_INCLUDED

FILE * openUnknownFile(char * mode);
FILE * openKnownFile(char * fn, char * mode);
char * getFileName();
void stripRN(char * word);

#endif // FILEUTIL_H_INCLUDED
