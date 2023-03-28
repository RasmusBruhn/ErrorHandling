#ifndef ERRORLOG_INCLUDED2
#define ERRORLOG_INCLUDED2

#ifdef __cplusplus
extern "C" {
#endif

#include "ErrorLog.h"

// Prints to the log file if it exists
// Returns nothing
void __ERR_LogPrint(const char *Mes);

#ifdef __cplusplus
}
#endif

#endif
