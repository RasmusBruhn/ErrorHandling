# ErrorHandling documentation
This is the documentation for the "Error2.h" header file (ERR). This header adds some error handling functions which makes it easier to do error handling, creating/retrieving an error can be done with a single printf-like function call and it can store an archive of messages. This header can be included multiple times given that the prefix is different.

## Requirements:
---
Using this library requires the -lErrorLog library
---

## Setup:
---
To include this header into your project you should first set the settings by defining macro constant, then the header should be included:

**ERR_PREFIX**: The prefix for all the functions created, defaults to [ERR].

**ERR_MAXLENGHT**: The maximum length of the error messages excluding the termination character, this is only the formatted message, the actual message with file/line info can be longer, defaults to [1000].

**ERR_MAXARCHIVED**: The maximum number of archived messages, after this number is exceeded the oldest messages will be overwritten, defaults to [100].

After including the header file you must define the 3 macro functions:

```
#define _[PREFIX]_ErrorSet(Format, ...) __[PREFIX]_ErrorSet(__FILE__, __LINE__, Format __VA_OPT__(,) __VA_ARGS__)
#define _[PREFIX]_ErrorAdd(Format, ...) __[PREFIX]_ErrorAdd(__FILE__, __LINE__, Format __VA_OPT__(,) __VA_ARGS__)
#define _[PREFIX]_ErrorAddExternal(ExternalMessage, Format, ...) __[PREFIX]_ErrorAddExternal(__FILE__, __LINE__, ExternalMessage, Format __VA_OPT__(,) __VA_ARGS__)
```

### Example:
```
#define ERR_PREFIX ERR
#define ERR_MAXLENGTH 1000
#define ERR_MAXARCHIVED 100
#include <Error2.c>
#define _ERR_ErrorSet(Format, ...) __ERR_ErrorSet(__FILE__, __LINE__, Format __VA_OPT__(,) __VA_ARGS__)
#define _ERR_ErrorAdd(Format, ...) __ERR_ErrorAdd(__FILE__, __LINE__, Format __VA_OPT__(,) __VA_ARGS__)
#define _ERR_ErrorAddExternal(ExternalMessage, Format, ...) __ERR_ErrorAddExternal(__FILE__, __LINE__, ExternalMessage, Format __VA_OPT__(,) __VA_ARGS__)
```
---

## Functions:
---
**void _[Prefix]_ErrorSet(const char *Format, ...)**:
- Sets the error message so that it can be retrieved with "[Prefix]_ErrorGet()".
- **Return**: Void
- **Arguments**:
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_ErrorAdd(const char *Format, ...)**:
- Sets the error message with reference to the last error message from this library.
- **Return**: Void
- **Arguments**:
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void _[Prefix]_ErrorAddExternal(const char *ExternalMessage, const char *Format, ...)**:
- Sets the error message with reference to an external error message.
- **Return**: Void
- **Arguments**:
  - **ExternalMessage**: The message to reference.
  - **Format**: The format of the message, follows printf standard.
  - **...**: The variables used in Format, follows printf standard.

**void ERR_LogCreate(FILE *File)**:
- Sets the error log file to write the errors in, this file applies to all error libraries, overwrites any existing file.
- **Return**: Void
- **Arguments**:
  - **File**: The file to write the error log to, should be opened using "w" mode.

**void ERR_LogDestroy(void)**:
- Removes the log file, make sure to run this before closing the file
- **Return**: Void

**char *[Prefix]_ErrorGet(void)**:
- Retrieves the error message, the message should be printed or copied immediately since there are no garuentees for when it will be freed.
- **Return**: The error message.

**char *[Prefix]_ErrorArchive(void)**:
- Retrieves the oldest archived error message, the message should be printed or copied immediately since there are no garuentees for when it will be freed.
- **Return**: The error message, NULL if there is none.

**void [Prefix]_ErrorClear(void)**:
- Clears the archive of old messages and frres all memory, should be run before finishing.
- **Return**: Void
	
---
