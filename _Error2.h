#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include "_ErrorLog.h"

#define ERR_BUILD
#include "Error2.h"
#undef ERR_BUILD

#ifdef __cplusplus
extern "C" {
#endif

// Cleans up everything when a memory error occures
// Returns nothing
#define ERR_MEMORYERRORCLEAN ERR_SETUPNAMEHID(MemoryErrorClean, ERR_PREFIX)

// Sets an error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
#define ERR_ERRORSET ERR_SETUPNAMEPRE(ErrorSet, ERR_PREFIX)

// Adds an error to the previous error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
#define ERR_ERRORADD ERR_SETUPNAMEPRE(ErrorAdd, ERR_PREFIX)

// Adds an error to an external error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// ExternalMessage: The error message for the external error
// Format: The error message with printf format
// ...: The format values for the Format string
#define ERR_ERRORADDEXTERNAL ERR_SETUPNAMEPRE(ErrorAddExternal, ERR_PREFIX)

// Combines an error message and saves it
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// VarArgs: The format values for the Format string
// OverwriteMessage: If true then it will overwrite the last error message
#define __ERR_ERRORSET ERR_SETUPNAMEHID(ErrorSet, ERR_PREFIX)

// Struct to save error type
#define __ERR_ERRORMESTYPE ERR_SETUPNAMEHID(__ErrorType, ERR_PREFIX)
#define ERR_ERRORMESTYPE ERR_SETUPNAMEHID(ErrorType, ERR_PREFIX)

// List of all saved error messages
#define ERR_MESSAGELIST ERR_SETUPNAMEHID(MessageList, ERR_PREFIX)

// The last message that occured
#define ERR_MESSAGELAST ERR_SETUPNAMEHID(MessageLast, ERR_PREFIX)

// True if there is an error ready
#define ERR_ERRORACTIVE ERR_SETUPNAMEHID(ErrorActive, ERR_PREFIX)

// The number of stored error messages
#define ERR_MESSAGECOUNT ERR_SETUPNAMEHID(MessageCount, ERR_PREFIX)

// The current message
#define ERR_CURRENTMES ERR_SETUPNAMEHID(CurrentMes, ERR_PREFIX)

// True if a memory error has occured
#define ERR_MEMORYERROR ERR_SETUPNAMEHID(MemoryError, ERR_PREFIX)

// Standard message if a memory error occured
#define ERR_MEMORYERRORMES "Unable to allocate memory"

// If no error has occured
#define ERR_NOERRORMES "No error has occured"

typedef struct __ERR_ERRORMESTYPE ERR_ERRORMESTYPE;

// Struct to save error type
struct __ERR_ERRORMESTYPE
{
    char *mes;
    ERR_ERRORMESTYPE *next;
};

// Cleans up everything when a memory error occures
// Returns nothing
void ERR_MEMORYERRORCLEAN(void);

// Sets an error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
void ERR_ERRORSET(const char *File, size_t Line, const char *Format, ...);

// Adds an error to the previous error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
void ERR_ERRORADD(const char *File, size_t Line, const char *Format, ...);

// Adds an error to an external error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// ExternalMessage: The error message for the external error
// Format: The error message with printf format
// ...: The format values for the Format string
void ERR_ERRORADDEXTERNAL(const char *File, size_t Line, const char *ExternalMessage, const char *Format, ...);

// Combines an error message and saves it
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// VarArgs: The format values for the Format string
// ErrorType: If it is an error or warning
// OverwriteMessage: If true then it will overwrite the last error message
void __ERR_ERRORSET(const char *File, size_t Line, const char *Format, va_list VarArgs, const char *PrevMes, bool OverwriteMessage);

#ifdef __cplusplus
}
#endif
