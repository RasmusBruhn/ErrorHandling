#ifndef ERRORLOG_INCLUDED3
#define ERRORLOG_INCLUDED3

#include <stdio.h>
#include "_ErrorLog.h"

#ifdef __cplusplus
extern "C"
{
#endif

// The file to log to
FILE *__ERR_LogFile = NULL;

// Sets the log file, will overwrite any existing log files
// Returns nothing
// File: The file pointer of the log file
void ERR_LogCreate(FILE *File)
{
    extern FILE *__ERR_LogFile;

    __ERR_LogFile = File;
}

// Removes the log file, make sure to run this before closing the file
// Returns nothing
void ERR_LogDestroy(void)
{
    extern FILE *__ERR_LogFile;

    __ERR_LogFile = NULL;
}

// Prints to the log file if it exists
// Returns nothing
void __ERR_LogPrint(const char *Mes)
{
    extern FILE *__ERR_LogFile;

    if (__ERR_LogFile != NULL)
        fprintf(__ERR_LogFile, "%s\n", Mes);
}

#ifdef __cplusplus
}
#endif

#endif
