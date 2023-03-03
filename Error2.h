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

#ifndef ERR_MERGE
#define ERR_MERGE " <- " // How to merge error messages
#endif

// Create names
#define __ERR_SETUPNAME(NAME) ERR_PREFIX##_##NAME
#define ERR_SETUPNAME(NAME) __ERR_SETUPNAME(NAME)
#define __ERR_SETUPNAMEINT(NAME) _##ERR_PREFIX##_##NAME
#define ERR_SETUPNAMEINT(NAME) __ERR_SETUPNAMEINT(NAME)
#define __ERR_SETUPNAMEPRE(NAME) __##ERR_PREFIX##_ERR_##NAME
#define ERR_SETUPNAMEPRE(NAME) __ERR_SETUPNAMEPRE(NAME)

// Gets the error message
// Returns a copy of the error string
#define ERR_ERRORGET ERR_SETUPNAME(ErrorGet)

// Gets the first archieved error
// Returns the first archieved error which must be freed by the user, NULL if non are available
#define ERR_ERRARCHIVE ERR_SETUPNAME(ErrorArchive)

// Clears all of the errors
// Returns nothing
#define ERR_ERRORCLEAR ERR_SETUPNAME(ErrorClear)

// Sets an error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
#define ERR_ERRORSET ERR_SETUPNAMEINT(ErrorSet)

// Combines an error message and saves it
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// VarArgs: The format values for the Format string
// OverwriteMessage: If true then it will overwrite the last error message
#define __ERR_ERRORSET ERR_SETUPNAMEPRE(ErrorSet)

// List of all saved error messages
#define ERR_MESSAGELIST ERR_SETUPNAMEPRE(MessageList)

// The last message that occured
#define ERR_MESSAGELAST ERR_SETUPNAMEPRE(MessageLast)

// The number of stored error messages
#define ERR_MESSAGECOUNT ERR_SETUPNAMEPRE(MessageCount)

// The current message
#define ERR_CURRENTMES ERR_SETUPNAMEPRE(CurrentMes)

// True if a memory error has occured
#define ERR_MEMORYERROR ERR_SETUPNAMEPRE(MemoryError)

// Struct to save error type
#define __ERR_ERRORMESTYPE ERR_SETUPNAMEPRE(__ErrorType)
#define ERR_ERRORMESTYPE ERR_SETUPNAMEPRE(ErrorType)

// Standard message if a memory error occured
#define ERR_MEMORYERRORMES "Unable to allocate memory"

// If no error has occured
#define ERR_NOERRORMES "No error has occured"

// Error types
#define ERR_TYPEERROR true
#define ERR_TYPEWARNING false

typedef struct __ERR_ERRORMESTYPE ERR_ERRORMESTYPE;

// Struct to save error type
struct __ERR_ERRORMESTYPE 
{
    char *mes;
    bool type;
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

// Sets an error
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// ...: The format values for the Format string
void ERR_ERRORSET(const char* File, size_t Line, const char *Format, ...);

// Combines an error message and saves it
// Returns nothing
// File: The path of the file in which the error occured
// Line: The line at which the error occured
// Format: The error message with printf format
// VarArgs: The format values for the Format string
// ErrorType: If it is an error or warning
// OverwriteMessage: If true then it will overwrite the last error message
void __ERR_ERRORSET(const char* File, size_t Line, const char *Format, va_list *VarArgs, bool ErrorType, bool OverwriteMessage);

// List of all saved error messages
ERR_ERRORMESTYPE *ERR_MESSAGELIST = NULL;

// The last message that ocured, NULL if it has already been given
ERR_ERRORMESTYPE *ERR_MESSAGELAST = NULL;

// The number of stored error messages
size_t ERR_MESSAGECOUNT = 0;

// The current message
char *ERR_CURRENTMES = NULL;

// True if a memory error has occured
bool ERR_MEMORYERROR = false;

char *ERR_ERRORGET(void)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
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
    if (ERR_MESSAGELAST == NULL)
        return ERR_NOERRORMES;

    // Get memory for new message
    size_t Length = strlen(ERR_MESSAGELAST->mes);
    ERR_CURRENTMES = (char *)malloc(sizeof(char) * (Length + 1));

    if (ERR_CURRENTMES == NULL)
    {
        ERR_MEMORYERROR = true;
        return ERR_MEMORYERRORMES;
    }

    // Copy error
    strncpy(ERR_CURRENTMES, ERR_MESSAGELAST->mes, Length);

    // Make sure it does not give the same message twice
    ERR_MESSAGELAST = NULL;

    return ERR_CURRENTMES;
}

char *ERR_ERRARCHIVE(void)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELIST;
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
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
        ERR_MESSAGELAST = NULL;

    // Update the message count
    --ERR_MESSAGECOUNT;

    return ERR_CURRENTMES;
}

void ERR_ERRORCLEAR(void)
{
    extern ERR_ERRORMESTYPE *ERR_MESSAGELIST;
    extern ERR_ERRORMESTYPE *ERR_MESSAGELAST;
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

    // Free current message
    if (ERR_CURRENTMES != NULL)
    {
        free(ERR_CURRENTMES);
        ERR_CURRENTMES = NULL;
    }

    // Set the message count to 0
    ERR_MESSAGECOUNT = 0;
}

void ERR_ERRORSET(const char* File, size_t Line, const char *Format, ...)
{
    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    // Set error message
    __ERR_ERRORSET(File, Line, Format, &VarArgs, ERR_TYPEERROR, false);

    va_end(VarArgs);
}

void __ERR_ERRORSET(const char* File, size_t Line, const char *Format, va_list *VarArgs, bool ErrorType, bool OverwriteMessage)
{
    // Get the string to fill and the maximum length to fill it with
    char *String = ERR_CURRENTMES;
    size_t MaxLength = ERR_MAXLENGTH;
    size_t Length;

    // Write error ID
    Length = snprintf(String, MaxLength, "0x%I64X", ErrorID);
    String += Length;
    MaxLength -= Length;

    // Write file and line
    if (FileName != NULL)
    {
        Length = snprintf(String, MaxLength, " (in \"%s\", line: %I32u)", FileName, LineNumber);
        String += Length;
        MaxLength -= Length;
    }

    // Write :
    Length = snprintf(String, MaxLength, ": ");
    String += Length;
    MaxLength -= Length;

    // Write the rest
    int32_t OptimalLength = vsnprintf(String, MaxLength, Format, *VarArgs);

    // Write ... if the message is too long
    if (OptimalLength >= ERR_MAXLENGTH)
    {
        ERR_CURRENTMES[ERR_MAXLENGTH - 2] = '.';
        ERR_CURRENTMES[ERR_MAXLENGTH - 3] = '.';
        ERR_CURRENTMES[ERR_MAXLENGTH - 4] = '.';
    }

    // Add terminating character in case of overflow
    //ERR_CURRENTMES[ERR_MAXLENGTH - 1] = '\0';

    // Write to the error log
    extern FILE *ERR_LOGFILE;

    if (ERR_LOGFILE != NULL)
    {
        time_t CurTime;

        time(&CurTime);

        fprintf(ERR_LOGFILE, "%.24s: %s\n", ctime(&CurTime), ERR_CURRENTMES);
    }

    // Add error message to error message list
    extern char ERR_ERRORMESLIST[];
    extern uint32_t ERR_ERRORMESCOUNT;
    extern uint32_t ERR_ERRORMESSTART;

    // Find the position if there is space
    int32_t Pos = ERR_ERRORMESCOUNT - ((OverwriteMessage) ? (1) : (0));
    
    if (Pos < 0)
        Pos = 0;

    // Increment the counter
    ERR_ERRORMESCOUNT = Pos + 1;

    Pos = (ERR_ERRORMESSTART + Pos) % ERR_MAXARCHIVED;

    if (ERR_ERRORMESCOUNT > ERR_MAXARCHIVED)
    {
        ERR_ERRORMESCOUNT = ERR_MAXARCHIVED;
        ERR_ERRORMESSTART = (ERR_ERRORMESSTART + 1) % ERR_MAXARCHIVED;
    }

    // Set message
    snprintf(ERR_ERRORMESLIST + ERR_MAXLENGTH * Pos, ERR_MAXLENGTH, "%s", ERR_CURRENTMES);

    // If the error type is too large then run exit function
    extern void (*ERR_EXIT)(uint64_t ErrorID);

    if (ErrorType >= ERR_THRESHOLD)
        ERR_EXIT(ErrorID);
}

// Undefine definitions
#undef ERR_PREFIX
#undef ERR_MAXARCHIVED
#undef ERR_MERGE
#undef ERR_MESSAGELIST
#undef ERR_MESSAGELAST
#undef ERR_CURRENTMES
#undef ERR_MEMORYERROR
#undef ERR_ERRORACTIVE
#undef ERR_MEMORYERRORMES
#undef ERR_NOERRORMES
#undef __ERR_ERRORMESTYPE
#undef ERR_ERRORMESTYPE
#undef ERR_TYPEERROR
#undef ERR_TYPEWARNING
#undef ERR_ERRORGET
#undef ERR_ERRORCLEAR
#undef ERR_MESSAGECOUNT
#undef ERR_ERRARCHIVE
#undef ERR_ERRORSET
#undef __ERR_ERRORSET