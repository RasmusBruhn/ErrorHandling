#ifndef ERRORLOG_INCLUDED2
#define ERRORLOG_INCLUDED2

#include "ErrorLog.h"

#ifdef __cplusplus
extern "C" {
#endif

// Prints to the log file if it exists
// Returns nothing
void __ERR_LogPrint(const char *Mes);

#ifdef __cplusplus
}
#endif

#endif
