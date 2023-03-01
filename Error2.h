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
#define __ERR_SETUPNAMEPRE(NAME) __##ERR_PREFIX##_##NAME
#define ERR_SETUPNAMEPRE(NAME) __ERR_SETUPNAMEPRE(NAME)

// Gets the error message
// Returns a copy of the error string
#define ERR_ERRORGET ERR_SETUPNAME(ErrorGet)

// List of all saved error messages
#define ERR_MESSAGELIST ERR_SETUPNAMEPRE(MessageList)

// The position of the current error
#define ERR_ERRORPOS ERR_SETUPNAMEPRE(CurrentErrorPos)

// True if an error is pending
#define ERR_ERRORACTIVE ERR_SETUPNAMEPRE(ErrorActive)

// The position of the first archived error
#define ERR_ARCHIVEPOS ERR_SETUPNAMEPRE(ArchivePos)

// Gets the error message
// Returns a copy of the error string
char *ERR_ERRORGET(void);

// List of all saved error messages
char *ERR_MESSAGELIST[ERR_MAXARCHIVED];

// The position of the current error
size_t ERR_ERRORPOS = 0;

// The position of the first archived error
size_t ERR_ARCHIVEPOS = 1;

// True if an error is pending
bool ERR_ERRORACTIVE = false;

char *ERR_ERRORGET(void)
{
    extern char *ERR_MESSAGELIST[];
    extern size_t ERR_ERRORPOS;

    snprintf(ERR_RETURNMES, ERR_MAXLENGTH, "%s", ERR_CURRENTMES);

    return ERR_RETURNMES;
}

void ERR_ERRORSET(const char* File, uint32_t Line, const char *Format, ...)
{
    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    // Set error message
    __ERR_ERRORSET(File, Line, Format, &VarArgs, false);

    va_end(VarArgs);
}

// Undefine definitions
#undef ERR_PREFIX
#undef ERR_MAXARCHIVED
#undef ERR_MERGE
#undef ERR_MESSAGELIST
#undef ERR_CURRENTERRORPOS
#undef ERR_ERRORACTIVE
#undef ERR_ERRORGET