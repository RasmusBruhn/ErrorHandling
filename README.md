# ErrorHandling documentation
This is the documentation for the "Error.h" header file (ERR). This header adds some error handling functions which makes it easier to do error handling, creating/retrieving an error only uses one function and it can store an archive of messages. This header can be included multiple times given that the prefix is different.

## Setup:
----------------------------------------------------------------------------------------------------
To include this header into your project you should first set the settings by defining macro constant, then the header should be included:

**ERR_PREFIX**: The prefix for all the functions created, defaults to [ERR].

**ERR_MAXLENGHT**: The maximum length of the error messages including the termination character, defaults to [1000].

**ERR_MAXARCHIVED**: The maximum number of archived messages, after this number is exceeded the oldest messages will be overwritten, defaults to [100].

**ERR_EXITFUNC**: A pointer to an exit function, this will be be executed whenever the error is too bad, have to have the form: [void exitFunc(uint64_t ErrorID)], defaults to the standard [&exit] function.

**ERR_THRESHOLD**: The threshold for when the exit function should activate, it activates whenever the error type is this large or larger, defaults to [3].

**ERR_ERRORTYPE_MASK**: The mask to pick out the error type, defaults to [0x0000FF00].

**ERR_ERRORTYPE_REDUCE**: The value to divide an error ID by after anding with the mask to get the error type, defaults to [0x00000100].

**ERR_MERGE**:          The string to put in the middle of 2 error messages when merging them, used when one error leads to another, defaults to [" <- "].


### Example:
```
#define ERR_PREFIX MYERROR
#define ERR_MAXLENGTH 10000
#define ERR_MAXARCHIVED 10
#define ERR_EXITFUNC &MyExitFunc
#include "Error.h"
```
----------------------------------------------------------------------------------------------------

## ID:
----------------------------------------------------------------------------------------------------
**Error ID standard**: The ID is a 64-bit unsigned integer with standard structure 0xLLLLLLLLFFFFTTEE.

**L**: The library ID, each library created should have its own unique ID, programmes which are not libraries and is not meant to be used in other projects should have library ID of 0. Old libraries from before the V1.2(64Bit) update will also have ID of 0.

**F**: The function ID, each function able to produce errors should have an ID not repeated by any other function in the same library.

**T**: The error type, the different standard types are defined below.

**E**: The unique error ID, each error in a function should have its own unique ID.


**The different default error types**:

**0**: No Error, No error has occured and you should ignore it.

**1**: Warning, An error has occured but the function was still able to finish.

**2**: Error, An error occured which stopped the function from finishing, but the program can still run.

**3**: Fatal Error, An error has occured which has most likely broken the application and it needs to shut down.

These error IDs are just standard but any system can be used, just remember to change ERR_ERRORTYPE_MASK, ERR_ERRORTYPE_REDUCE and ERR_THRESHOLD when changing the standard for the error type. See the bottom of the document for a list of library IDs.

----------------------------------------------------------------------------------------------------


## Functions:
----------------------------------------------------------------------------------------------------
**void _[Prefix]_SetError(uint64_t ErrorID, const char *Format, ...)**:
- Sets the error message so that it can be retrieved with "[Prefix]_GetError()".
- **Return**: Void
- **Arguments**:
  - **ErrorID**: The ID of the error that has occured.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_SetErrorLoc(uint64_t ErrorID, char *FileName, uint32_t LineNumber, const char *Format, ...)**:
- Sets the error message so that it can be retrieved with "[Prefix]_GetError()". Adds filename and line number of the error to the message.
- **Return**: Void
- **Arguments**:
  - **ErrorID**: The ID of the error that has occured.
  - **FileName**: The name of the file in which the error occured.
  - **LineNumber**: The line number where the error occured.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_AddError(uint64_t ErrorID, const char *Format, ...)**:
- Sets the error message with reference to the last error message from this library.
- **Return**: Void
- **Arguments**:
  - **ErrorID**: The ID of the error that has occured.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_AddErrorLoc(uint64_t ErrorID, char *FileName, uint32_t LineNumber, const char *Format, ...)**:
- Sets the error message with reference to the last error message from this library. Adds filename and line number of the error to the message.
- **Return**: Void
- **Arguments**:
  - **ErrorID**: The ID of the error that has occured.
  - **FileName**: The name of the file in which the error occured.
  - **LineNumber**: The line number where the error occured.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_AddErrorForeign(uint64_t ErrorID, const char *ErrorMes, const char *Format, ...)**:
- Sets the error message with reference to another message.
- **Return**: Void
- **Arguments**:
  - **ErrorID**: The ID of the error that has occured.
  - **ErrorMes**: The message to reference.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_AddErrorForeignLoc(uint64_t ErrorID, char *FileName, uint32_t LineNumber, const char *ErrorMes, const char *Format, ...)**:
- Sets the error message with reference to another message. Adds filename and line number of the error to the message.
- **Return**: Void
- **Arguments**:
  - **ErrorID**: The ID of the error that has occured.
  - **FileName**: The name of the file in which the error occured.
  - **LineNumber**: The line number where the error occured.
  - **ErrorMes**: The message to reference.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_SetLogFile(FILE *LogFile)**:
- Sets the error log file to write the errors in, it will overwrite errors repeated by AddError. It will also write the time of the error.
- **Return**: Void
- **Arguments**:
  - **LogFile**: The file to write the error log to, should be opened using "w+" mode.

**char *[Prefix]_GetError(void)**:
- Retrieves the error message, the message should be printed or copied immediately since any later call of GetError will overwrite it.
- **Return**: The error message.

**char *[Prefix]_GetArchivedError(void)**:
- Retrieves the oldest archived error message.
- **Return**: The error message, NULL if there is none.

**void [Prefix]_ClearArchive(void)**:
- Clears the archive of old messages.
- **Return**: Void
	
**uint64_t [Prefix]_GetErrorType(void)**:
- Retrieves the worst error type that has occured.
- **Return**: The error type.

**uint64_t [Prefix]_GetErrorID(void)**:
- Retrieves the ID of the last error that occured.
- **Return**: The error ID.

----------------------------------------------------------------------------------------------------

## Library ID:
----------------------------------------------------------------------------------------------------
**Main programme/old libraries**: 0

**Debug**: 1

**Views**: 2

**Settings**: 3

**Files**: 4

----------------------------------------------------------------------------------------------------