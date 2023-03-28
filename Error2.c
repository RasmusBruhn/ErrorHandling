#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Defines.h>
#include "_Error2.h"

#ifdef __cplusplus
extern "C" {
#endif

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

void ERR_ERRORSET(const char *File, size_t Line, const char *Format, ...)
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

void __ERR_ERRORSET(const char *File, size_t Line, const char *Format, va_list VarArgs, const char *PrevMes, bool OverwriteMessage)
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
    snprintf(ErrorMes->mes, Length + 1, "\"%s\" line " PRINT_UINT64 ": %s", File, Line, Mes);

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
#undef ERR_NOERRORMES
#undef ERR_MEMORYERRORMES

#undef ERR_MEMORYERROR
#undef ERR_CURRENTMES
#undef ERR_MESSAGECOUNT
#undef ERR_ERRORACTIVE
#undef ERR_MESSAGELAST
#undef ERR_MESSAGELIST

#undef ERR_ERRORMESTYPE
#undef __ERR_ERRORMESTYPE

#undef __ERR_ERRORSET
#undef ERR_ERRORADDEXTERNAL
#undef ERR_ERRORADD
#undef ERR_ERRORSET
#undef ERR_MEMORYERRORCLEAN
#undef ERR_ERRORCLEAR
#undef ERR_ERRARCHIVE
#undef ERR_ERRORGET

#undef ERR_SETUPNAMEHID
#undef __ERR_SETUPNAMEHID
#undef ERR_SETUPNAMEPRE
#undef __ERR_SETUPNAMEPRE
#undef ERR_SETUPNAMEINT
#undef __ERR_SETUPNAMEINT
#undef ERR_SETUPNAME
#undef __ERR_SETUPNAME

#undef ERR_MAXLENGTH
#undef ERR_MAXARCHIVED
#undef ERR_PREFIX

#ifdef __cplusplus
}
#endif
