#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifndef ERR_PREFIX
#define ERR_PREFIX ERR // The prefix used
#endif

#ifndef ERR_MAXARCHIVED
#define ERR_MAXARCHIVED 100 // The maximum number of archived messages
#endif

#ifndef ERR_MAXLENGTH
#define ERR_MAXLENGTH 1000 // The maximum length of the formatted error message, the actual error message can be longer
#endif

// Set up logging
#ifndef ERR_INCLUDED
#define ERR_INCLUDED

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

#endif

// Create names
#define __ERR_SETUPNAME(NAME, PREFIX) PREFIX##_##NAME
#define ERR_SETUPNAME(NAME, PREFIX) __ERR_SETUPNAME(NAME, PREFIX)
#define __ERR_SETUPNAMEINT(NAME, PREFIX) _##PREFIX##_##NAME
#define ERR_SETUPNAMEINT(NAME, PREFIX) __ERR_SETUPNAMEINT(NAME, PREFIX)
#define __ERR_SETUPNAMEPRE(NAME, PREFIX) __##PREFIX##_##NAME
#define ERR_SETUPNAMEPRE(NAME, PREFIX) __ERR_SETUPNAMEPRE(NAME, PREFIX)
#define __ERR_SETUPNAMEHID(NAME, PREFIX) __##PREFIX##_ERR_##NAME
#define ERR_SETUPNAMEHID(NAME, PREFIX) __ERR_SETUPNAMEHID(NAME, PREFIX)

// Gets the error message
// Returns a copy of the error string
#define ERR_ERRORGET ERR_SETUPNAME(ErrorGet, ERR_PREFIX)

// Gets the first archieved error
// Returns the first archieved error which must be freed by the user, NULL if non are available
#define ERR_ERRARCHIVE ERR_SETUPNAME(ErrorArchive, ERR_PREFIX)

// Clears all of the errors
// Returns nothing
#define ERR_ERRORCLEAR ERR_SETUPNAME(ErrorClear, ERR_PREFIX)

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

// Struct to save error type
#define __ERR_ERRORMESTYPE ERR_SETUPNAMEHID(__ErrorType, ERR_PREFIX)
#define ERR_ERRORMESTYPE ERR_SETUPNAMEHID(ErrorType, ERR_PREFIX)

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

// Gets the error message
// Returns a copy of the error string
char *ERR_ERRORGET(void);

// Gets the first archieved error
// Returns the first archieved error, NULL if non are available
char *ERR_ERRARCHIVE(void);

// Clears all of the errors
// Returns nothing
void ERR_ERRORCLEAR(void);

// Cleans up everything when a memory error occures
// Returns nothing
void ERR_MEMORYERRORCLEAN(void);

// Sets an error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
void ERR_ERRORSET(const char* File, size_t Line, const char *Format, ...);

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

// List of all saved error messages
ERR_ERRORMESTYPE *ERR_MESSAGELIST = NULL;

// The last message that ocured, NULL if it has already been given
ERR_ERRORMESTYPE *ERR_MESSAGELAST = NULL;

// True if there is an error ready
bool ERR_ERRORACTIVE = false;

// The number of stored error messages
size_t ERR_MESSAGECOUNT = 0;

// The current message
char *ERR_CURRENTMES = NULL;

// True if a memory error has occured
bool ERR_MEMORYERROR = false;

char *ERR_ERRORGET(void)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
    extern bool ERR_ERRORACTIVE;
    extern char *ERR_CURRENTMES;
    extern bool ERR_MEMORYERROR;

    // Make sure there is no memory error
    if (ERR_MEMORYERROR)
        return ERR_MEMORYERRORMES;

    // Remove old message
    if (ERR_CURRENTMES != NULL)
    {
        free(ERR_CURRENTMES);
        ERR_CURRENTMES = NULL;
    }

    // Make sure there is an error
    if (!ERR_ERRORACTIVE)
        return ERR_NOERRORMES;

    // Get memory for new message
    size_t Length = strlen(ERR_MESSAGELAST->mes);
    ERR_CURRENTMES = (char *)malloc(sizeof(char) * (Length + 1));

    if (ERR_CURRENTMES == NULL)
    {
        ERR_MEMORYERRORCLEAN();
        return ERR_MEMORYERRORMES;
    }
    
    // Copy error
    snprintf(ERR_CURRENTMES, Length + 1, "%s", ERR_MESSAGELAST->mes);

    // Make sure it does not give the same message twice
    ERR_ERRORACTIVE = false;

    return ERR_CURRENTMES;
}

char *ERR_ERRARCHIVE(void)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELIST;
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
    extern bool ERR_ERRORACTIVE;
    extern size_t ERR_MESSAGECOUNT;
    extern char *ERR_CURRENTMES;
    extern bool ERR_MEMORYERROR;

    // Make sure there is no memory error
    if (ERR_MEMORYERROR)
        return NULL;

    // Remove old message
    if (ERR_CURRENTMES != NULL)
    {
        free(ERR_CURRENTMES);
        ERR_CURRENTMES = NULL;
    }

    // Make sure there is an error
    if (ERR_MESSAGELIST == NULL)
        return NULL;

    // Get message
    ERR_CURRENTMES = ERR_MESSAGELIST->mes;

    // Remove the message from the list
    ERR_ERRORMESTYPE *NextError = ERR_MESSAGELIST->next;
    free(ERR_MESSAGELIST);
    ERR_MESSAGELIST = NextError;

    // Remove last message
    if (NextError == NULL)
    {
        ERR_MESSAGELAST = NULL;
        ERR_ERRORACTIVE = false;
    }

    // Update the message count
    --ERR_MESSAGECOUNT;

    return ERR_CURRENTMES;
}

void ERR_ERRORCLEAR(void)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELIST;
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
    extern bool ERR_ERRORACTIVE;
    extern size_t ERR_MESSAGECOUNT;
    extern char *ERR_CURRENTMES;

    // Free all memory
    ERR_ERRORMESTYPE *TempMem;

    while (ERR_MESSAGELIST != NULL)
    {
        TempMem = ERR_MESSAGELIST->next;
        free(ERR_MESSAGELIST->mes);
        free(ERR_MESSAGELIST);
        ERR_MESSAGELIST = TempMem;
    }

    // Set last message to NULL
    ERR_MESSAGELAST = NULL;
    ERR_ERRORACTIVE = false;

    // Free current message
    if (ERR_CURRENTMES != NULL)
    {
        free(ERR_CURRENTMES);
        ERR_CURRENTMES = NULL;
    }

    // Set the message count to 0
    ERR_MESSAGECOUNT = 0;
}

void ERR_MEMORYERRORCLEAN(void)
{
    extern bool ERR_MEMORYERROR;

    // Set the memory error to true
    ERR_MEMORYERROR = true;

    // Clear the errors
    ERR_ERRORCLEAR();

    // Write to file
    __ERR_LogPrint(ERR_MEMORYERRORMES);
}

void ERR_ERRORSET(const char* File, size_t Line, const char *Format, ...)
{
    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    // Set error message
    __ERR_ERRORSET(File, Line, Format, VarArgs, NULL, false);

    va_end(VarArgs);
}

void ERR_ERRORADD(const char *File, size_t Line, const char *Format, ...)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;

    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    // Set error message
    if (ERR_MESSAGELAST == NULL)
        __ERR_ERRORSET(File, Line, Format, VarArgs, NULL, false);

    else
        __ERR_ERRORSET(File, Line, Format, VarArgs, ERR_MESSAGELAST->mes, true);

    va_end(VarArgs);
}

void ERR_ERRORADDEXTERNAL(const char *File, size_t Line, const char *ExternalMessage, const char *Format, ...)
{
    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    // Set error message
    __ERR_ERRORSET(File, Line, Format, VarArgs, ExternalMessage, false);

    va_end(VarArgs);
}

void __ERR_ERRORSET(const char* File, size_t Line, const char *Format, va_list VarArgs, const char *PrevMes, bool OverwriteMessage)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELIST;
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
    extern bool ERR_ERRORACTIVE;
    extern size_t ERR_MESSAGECOUNT;
    extern bool ERR_MEMORYERROR;

    // Make sure there is no memory error
    if (ERR_MEMORYERROR)
        return;

    // Get the formatted string
    char Mes[ERR_MAXLENGTH + 1];
    vsnprintf(Mes, ERR_MAXLENGTH + 1, Format, VarArgs);

    // Calculate the length of the error
    size_t Digits = 0;
    
    for (size_t LineDigits = Line; LineDigits > 0; LineDigits /= 10)
        ++Digits;

    size_t Length = strlen(File) + Digits + 10 + strlen(Mes);
    size_t ExtraLength = 0;
    
    if (PrevMes != NULL)
        ExtraLength = strlen(PrevMes) + 4;

    // Create the new error
    ERR_ERRORMESTYPE *ErrorMes = (ERR_ERRORMESTYPE *)malloc(sizeof(ERR_ERRORMESTYPE));

    if (ErrorMes == NULL)
    {
        ERR_MEMORYERRORCLEAN();
        return;
    }

    // Add the message
    ErrorMes->mes = (char *)malloc(sizeof(char) * (Length + ExtraLength + 1));

    if (ErrorMes->mes == NULL)
    {
        ERR_MEMORYERRORCLEAN();
        return;
    }

    // Fill values
    ErrorMes->next = NULL;
    snprintf(ErrorMes->mes, Length + 1, "\"%s\" line %lu: %s", File, Line, Mes);

    if (PrevMes != NULL)
        snprintf(ErrorMes->mes + Length, ExtraLength + 1, " <- %s", PrevMes);

    // Print to file
    __ERR_LogPrint(ErrorMes->mes);

    // Add it to the list
    if (ERR_MESSAGELAST != NULL)
    {
        if (OverwriteMessage)
        {
            free(ERR_MESSAGELAST->mes);
            ERR_MESSAGELAST->mes = ErrorMes->mes;
            free(ErrorMes);
            ErrorMes = ERR_MESSAGELAST;
            --ERR_MESSAGECOUNT;
        }

        else
            ERR_MESSAGELAST->next = ErrorMes;
    }

    ERR_MESSAGELAST = ErrorMes;
    ERR_ERRORACTIVE = true;
    ++ERR_MESSAGECOUNT;

    // Add it to the start of the list
    if (ERR_MESSAGELIST == NULL)
        ERR_MESSAGELIST = ErrorMes;

    // Remove from start of message list if needed
    if (ERR_MESSAGECOUNT > ERR_MAXARCHIVED)
    {
        ERR_ERRORMESTYPE *NewList = ERR_MESSAGELIST->next;
        free(ERR_MESSAGELIST->mes);
        free(ERR_MESSAGELIST);
        ERR_MESSAGELIST = NewList;
        --ERR_MESSAGECOUNT;
    }
}

// Undefine definitions
#undef ERR_PREFIX
#undef ERR_MAXARCHIVED
#undef ERR_MAXLENGTH
#undef ERR_ERRORGET
#undef ERR_ERRARCHIVE
#undef ERR_ERRORCLEAR
#undef ERR_MEMORYERRORCLEAN
#undef ERR_ERRORSET
#undef ERR_ERRORADD
#undef ERR_ERRORADDEXTERNAL
#undef __ERR_ERRORSET
#undef ERR_MESSAGELIST
#undef ERR_MESSAGELAST
#undef ERR_ERRORACTIVE
#undef ERR_MESSAGECOUNT
#undef ERR_CURRENTMES
#undef ERR_MEMORYERROR
#undef __ERR_ERRORMESTYPE
#undef ERR_ERRORMESTYPE
#undef ERR_MEMORYERRORMES
#undef ERR_NOERRORMES