#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Create names
#ifndef _ERR_SETUPNAME
#define __ERR_SETUPNAME(PREFIX, NAME) PREFIX##_##NAME
#define ERR_SETUPNAME(PREFIX, NAME) __ERR_SETUPNAME(PREFIX, NAME)
#define __ERR_SETUPNAMEINT(PREFIX, NAME) _##PREFIX##_##NAME
#define ERR_SETUPNAMEINT(PREFIX, NAME) __ERR_SETUPNAMEINT(PREFIX, NAME)
#define __ERR_SETUPNAMEPRE(PREFIX, NAME) __##PREFIX##_##NAME
#define ERR_SETUPNAMEPRE(PREFIX, NAME) __ERR_SETUPNAMEPRE(PREFIX, NAME)
#endif

#ifndef ERR_PREFIX
#define ERR_PREFIX ERR // The prefix used
#endif

#ifndef ERR_MAXLENGTH
#define ERR_MAXLENGTH 1000 // The maximum length of an error message
#endif

#ifndef ERR_MAXARCHIVED
#define ERR_MAXARCHIVED 100 // The maximum number of archived messages
#endif

#ifndef ERR_EXITFUNC
void ERR_SETUPNAMEPRE(ERR_PREFIX, ExitFunc)(uint64_t ErrorID) {exit((int32_t)ErrorID);} // Default exit function
#define ERR_EXITFUNC &ERR_SETUPNAMEPRE(ERR_PREFIX, ExitFunc)
#endif

#ifndef ERR_THRESHOLD
#define ERR_THRESHOLD 3 // What error type should run the exit function
#endif

#ifndef ERR_MERGE
#define ERR_MERGE " -> " // How to merge error messages
#endif

#ifndef ERR_ERRORTYPE_MASK
#define ERR_ERRORTYPE_MASK 0x0000FF00 // The mask for finding the error type
#endif

// No error: 0
// Warning: 1
// Error: 2
// Fatal: 3

#ifndef ERR_ERRORTYPE_REDUCE
#define ERR_ERRORTYPE_REDUCE 0x00000100 // How to reduce an ID to get the error type
#endif

// Gets the error message
// Returns a copy of the error string
#define ERR_GETERROR ERR_SETUPNAME(ERR_PREFIX, GetError)

// Sets the error message
// Returns nothing
// ErrorID: The ID of the error
// Format: The format of the error message, follows printf standard
// ...: The variables asked for in Format, also printf standard
#define ERR_SETERROR ERR_SETUPNAMEINT(ERR_PREFIX, SetError)

// Sets the error with reference to some other error
// Returns nothing
// ErrorID: The ID of the error
// ErrorMes: The message to reference
// Format: The format of the error message, follows printf standard
// VarArgs: The variables asked for in Format, also printf standard
// OverwriteMessage: If it should overwrite the last message in the error message list
#define __ERR_ADDERROR ERR_SETUPNAMEPRE(ERR_PREFIX, AddError)

// Sets an error with reference to the last error that occured from this same library
// Returns nothing
// ErrorID: The ID of the error
// Format: The format of the error message, follows printf standard
// ...: The variables asked for in Format, also printf standard
#define ERR_ADDERROR ERR_SETUPNAMEINT(ERR_PREFIX, AddError)

// Sets an error with reference to another error message
// Returns nothing
// ErrorID: The ID of the error
// ErrorMes: The message to reference
// Format: The format of the error message, follows printf standard
// ...: The variables asked for in Format, also printf standard
#define ERR_ADDERRORFOREIGN ERR_SETUPNAMEINT(ERR_PREFIX, AddErrorForeign)

// Set the error message, this is the function that all the others use
// Returns nothing
// ErrorID: The ID of the error
// Format: The format of the error message, follows printf standard
// VarArgs: The variables asked for in Format, also printf standard
#define __ERR_SETERROR ERR_SETUPNAMEPRE(ERR_PREFIX, SetError)

// The current error message
#define ERR_CURRENTMES ERR_SETUPNAMEPRE(ERR_PREFIX, CurrentMes)

// The string which the error message is copied to when given to the user
#define ERR_RETURNMES ERR_SETUPNAMEPRE(ERR_PREFIX, ReturnMes)

// A temperary string used in the add error functions
#define ERR_TEMPMES ERR_SETUPNAMEPRE(ERR_PREFIX, TempMes)

// List of strings with error messages that has occured
#define ERR_ERRORMESLIST ERR_SETUPNAMEPRE(ERR_PREFIX, ErrorMesList)

// Number of archived messages
#define ERR_ERRORMESCOUNT ERR_SETUPNAMEPRE(ERR_PREFIX, ErrorMesCount)

// Where the archived messages begin
#define ERR_ERRORMESSTART ERR_SETUPNAMEPRE(ERR_PREFIX, ErrorMesStart)

// Gets the oldest error message and deletes that from memory
// Returns the error message and NULL if there were none
#define ERR_GETARCHIVEDERROR ERR_SETUPNAME(ERR_PREFIX, GetArchivedError)

// Clears the archive
// Returns nothing
#define ERR_CLEARARCHIVE ERR_SETUPNAME(ERR_PREFIX, ClearArchive)

// The worst error type that has occured
#define ERR_ERRORTYPE ERR_SETUPNAMEPRE(ERR_PREFIX, ErrorType)

// The ID of the last error that occured
#define ERR_ERRORID ERR_SETUPNAMEPRE(ERR_PREFIX, ErrorID)

// Gets the worst error type that has occured
// Returns the error type
#define ERR_GETERRORTYPE ERR_SETUPNAME(ERR_PREFIX, GetErrorType)

// Gets the ID of the last error that occured
// Returns the ID
#define ERR_GETERRORID ERR_SETUPNAME(ERR_PREFIX, GetErrorID)

// Runs when error is too bad, should exit thr program
// Returns nothing
// ErrorID: The error ID that lead to the exit function being run
#define ERR_EXIT ERR_SETUPNAME(ERR_PREFIX, Exit)

// The error logging file
#define ERR_LOGFILE ERR_SETUPNAMEPRE(ERR_PREFIX, LogFile)

// Function to set the log file
// Returns nothing
// LogFile: The file to write error logs to
#define ERR_SETLOGFILE ERR_SETUPNAMEINT(ERR_PREFIX, SetLogFile)

// Gets the error message
// Returns a copy of the error string
char *ERR_GETERROR(void);

// Sets the error message
// Returns nothing
// ErrorID: The ID of the error
// Format: The format of the error message, follows printf standard
// ...: The variables asked for in Format, also printf standard
void ERR_SETERROR(uint64_t ErrorID, const char *Format, ...);

// Sets the error with reference to some other error
// Returns nothing
// ErrorID: The ID of the error
// ErrorMes: The message to reference
// Format: The format of the error message, follows printf standard
// VarArgs: The variables asked for in Format, also printf standard
// OverwriteMessage: If it should overwrite the last message in the error message list
void __ERR_ADDERROR(uint64_t ErrorID, const char *ErrorMes, const char *Format, va_list *VarArgs, bool OverwriteMessage);

// Sets an error with reference to the last error that occured from this same library
// Returns nothing
// ErrorID: The ID of the error
// Format: The format of the error message, follows printf standard
// ...: The variables asked for in Format, also printf standard
void ERR_ADDERROR(uint64_t ErrorID, const char *Format, ...);

// Sets an error with reference to another error message
// Returns nothing
// ErrorID: The ID of the error
// ErrorMes: The message to reference
// Format: The format of the error message, follows printf standard
// ...: The variables asked for in Format, also printf standard
void ERR_ADDERRORFOREIGN(uint64_t ErrorID, const char *ErrorMes, const char *Format, ...);

// Set the error message, this is the function that all the others use
// Returns nothing
// ErrorID: The ID of the error
// Format: The format of the error message, follows printf standard
// VarArgs: The variables asked for in Format, also printf standard
// OverwriteMessage: If it should overwrite the last message in the error message list
void __ERR_SETERROR(uint64_t ErrorID, const char *Format, va_list *VarArgs, bool OverwriteMessage);

// Gets the worst error type that has occured
// Returns the error type
uint64_t ERR_GETERRORTYPE(void);

// Gets the oldest error message and deletes that from memory
// Returns the error message and NULL if there were none
char *ERR_GETARCHIVEDERROR(void);

// Clears the archive
// Returns nothing
void ERR_CLEARARCHIVE(void);

// Runs when error is too bad, should exit thr program
// Returns nothing
// ErrorID: The error ID that lead to the exit function being run
void (*ERR_EXIT)(uint64_t ErrorID) = ERR_EXITFUNC;

// Function to set the log file
// Returns nothing
// LogFile: The file to write error logs to
void ERR_SETLOGFILE(FILE *LogFile);

// The current error message
static char ERR_CURRENTMES[ERR_MAXLENGTH] = "No error has occured";

// The string which the error message is copied to when given to the user
static char ERR_RETURNMES[ERR_MAXLENGTH] = "";

// A temperary string used in the add error functions
static char ERR_TEMPMES[ERR_MAXLENGTH] = "";

// The worst error type that has yet occured
static uint64_t ERR_ERRORTYPE = 0;

// The last error ID
static uint64_t ERR_ERRORID = 0;

// List of old error messages
static char ERR_ERRORMESLIST[ERR_MAXARCHIVED * ERR_MAXLENGTH] = "";

// Number of archived error messages
static uint32_t ERR_ERRORMESCOUNT = 0;

// Where the first archived error message is
static uint32_t ERR_ERRORMESSTART = 0;

// The log file
static FILE *ERR_LOGFILE = NULL;

void ERR_SETLOGFILE(FILE *LogFile)
{
    extern FILE *ERR_LOGFILE;

    ERR_LOGFILE = LogFile;
}

uint64_t ERR_GETERRORTYPE(void)
{
    extern uint64_t ERR_ERRORTYPE;
    
    return ERR_ERRORTYPE;
}

uint64_t ERR_GETERRORID(void)
{
    extern uint64_t ERR_ERRORID;

    return ERR_ERRORID;
}

char *ERR_GETERROR(void)
{
    extern char ERR_CURRENTMES[];
    extern char ERR_RETURNMES[];

    snprintf(ERR_RETURNMES, ERR_MAXLENGTH, "%s", ERR_CURRENTMES);

    return ERR_RETURNMES;
}

void ERR_SETERROR(uint64_t ErrorID, const char *Format, ...)
{
    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    // Set error message
    __ERR_SETERROR(ErrorID, Format, &VarArgs, false);

    va_end(VarArgs);
}

void __ERR_ADDERROR(uint64_t ErrorID, const char *ErrorMes, const char *Format, va_list *VarArgs, bool OverwriteMessage)
{
    extern char ERR_TEMPMES[];
    extern FILE *ERR_LOGFILE;

    // Change write position in error file if it should overwrite the last message
    if (ERR_LOGFILE != NULL)
    {
        int32_t MesLength = strlen(ErrorMes);

        // Go to start of last message
        if (fseek(ERR_LOGFILE, -(MesLength + 1), SEEK_END) != 0)
            fseek(ERR_LOGFILE, 0, SEEK_END);

        else
        {
            // Read the message
            fread(ERR_TEMPMES, sizeof(char), MesLength, ERR_LOGFILE);
            ERR_TEMPMES[MesLength] = '\0';
            
            // Compare the message
            if (strcmp(ErrorMes, ERR_TEMPMES) != 0)
                fseek(ERR_LOGFILE, 0, SEEK_END);

            // Set file to overwrite the last message, 24 for date, 1 for newline and 2 for colon-space
            else
                fseek(ERR_LOGFILE, -(MesLength + 27), SEEK_END);
        }
    }

    // Add the previous error message
    int32_t OptimalLength = snprintf(ERR_TEMPMES, ERR_MAXLENGTH, "%s%s%s", Format, ERR_MERGE, ErrorMes);

    // Add a % if there is a % in previous error message
    for (char *String = ERR_TEMPMES + strlen(ERR_TEMPMES) - 1, *EndString = ERR_TEMPMES + strlen(Format) + strlen(ERR_MERGE) - 1; String > EndString; --String)
        if (*String == '%')
        {
            ++OptimalLength;

            for (char Character = '%', CharacterTemp, *TempString = String + 1, *EndTempString = String + strlen(String) + 2; TempString < EndTempString && TempString - ERR_TEMPMES < ERR_MAXLENGTH - 1; ++TempString)
            {
                CharacterTemp = *TempString;
                *TempString = Character;
                Character = CharacterTemp;
            }
        }

    // Add terminating character in case of overflow
    ERR_TEMPMES[ERR_MAXLENGTH - 1] = '\0';

    // Write ... if the message is too long
    if (OptimalLength >= ERR_MAXLENGTH)
    {
        ERR_TEMPMES[ERR_MAXLENGTH - 2] = '.';
        ERR_TEMPMES[ERR_MAXLENGTH - 3] = '.';
        ERR_TEMPMES[ERR_MAXLENGTH - 4] = '.';
    }

    // Set error message
    __ERR_SETERROR(ErrorID, ERR_TEMPMES, VarArgs, OverwriteMessage);
}

void ERR_ADDERROR(uint64_t ErrorID, const char *Format, ...)
{
    extern char ERR_TEMPMES[];

    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    __ERR_ADDERROR(ErrorID, ERR_GETERROR(), Format, &VarArgs, true);

    va_end(VarArgs);
}

void ERR_ADDERRORFOREIGN(uint64_t ErrorID, const char *ErrorMes, const char *Format, ...)
{
    extern char ERR_TEMPMES[];

    // Setup to get the error messages
    va_list VarArgs;
    va_start(VarArgs, Format);

    __ERR_ADDERROR(ErrorID, ErrorMes, Format, &VarArgs, false);

    va_end(VarArgs);
}

void __ERR_SETERROR(uint64_t ErrorID, const char *Format, va_list *VarArgs, bool OverwriteMessage)
{
    extern char ERR_CURRENTMES[];
    extern uint64_t ERR_ERRORTYPE;
    extern uint64_t ERR_ERRORID;

    // Set error ID
    ERR_ERRORID = ErrorID;

    // Set error type
    uint64_t ErrorType = (ErrorID & ERR_ERRORTYPE_MASK) / ERR_ERRORTYPE_REDUCE;

    if (ERR_ERRORTYPE < ErrorType)
        ERR_ERRORTYPE = ErrorType;

    // Get the string to fill and the maximum length to fill it with
    char *String = ERR_CURRENTMES;
    size_t MaxLength = ERR_MAXLENGTH;
    size_t Length;

    // Write error ID
    Length = snprintf(String, MaxLength, "%lX: ", ErrorID);
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

char *ERR_GETARCHIVEDERROR(void)
{
    extern char ERR_ERRORMESLIST[];
    extern uint32_t ERR_ERRORMESCOUNT;
    extern uint32_t ERR_ERRORMESSTART;

    if (ERR_ERRORMESCOUNT == 0)
        return NULL;

    // Copy the message
    snprintf(ERR_RETURNMES, ERR_MAXLENGTH, "%s", ERR_ERRORMESLIST + ERR_ERRORMESSTART * ERR_MAXLENGTH);

    // Remove message
    ERR_ERRORMESSTART = (ERR_ERRORMESSTART + 1) % ERR_MAXARCHIVED;
    --ERR_ERRORMESCOUNT;

    return ERR_RETURNMES;
}

void ERR_CLEARARCHIVE(void)
{
    extern uint32_t ERR_ERRORMESCOUNT;
    extern uint32_t ERR_ERRORMESSTART;

    ERR_ERRORMESSTART = 0;
    ERR_ERRORMESCOUNT = 0;
}

// Undefine definitions
#undef ERR_PREFIX
#undef ERR_MAXLENGTH
#undef ERR_MAXARCHIVED
#undef ERR_EXITFUNC
#undef ERR_THRESHOLD
#undef ERR_MERGE
#undef ERR_ERRORTYPE_MASK
#undef ERR_ERRORTYPE_REDUCE
#undef ERR_GETERROR
#undef ERR_SETERROR
#undef __ERR_ADDERROR
#undef ERR_ADDERROR
#undef ERR_ADDERRORFOREIGN
#undef __ERR_SETERROR
#undef ERR_CURRENTMES
#undef ERR_RETURNMES
#undef ERR_TEMPMES
#undef ERR_ERRORMESLIST
#undef ERR_ERRORMESCOUNT
#undef ERR_ERRORMESSTART
#undef ERR_GETARCHIVEDERROR
#undef ERR_CLEARARCHIVE
#undef ERR_ERRORTYPE
#undef ERR_ERRORID
#undef ERR_GETERRORTYPE
#undef ERR_GETERRORID
#undef ERR_EXIT
#undef ERR_LOGFILE
#undef ERR_SETLOGFILE