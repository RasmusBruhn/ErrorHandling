#ifndef ERRORLOG_INCLUDED
#define ERRORLOG_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Sets the log file, will overwrite any existing log files
// Returns nothing
// File: The file pointer of the log file
void ERR_LogCreate(FILE *File);

// Removes the log file, make sure to run this before closing the file
// Returns nothing
void ERR_LogDestroy(void);

#ifdef __cplusplus
}
#endif

#endif
