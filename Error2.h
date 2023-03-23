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

// Sets the log file, will overwrite any existing log files
// Returns nothing
// File: The file pointer of the log file
void ERR_LogCreate(FILE *File);

// Removes the log file, make sure to run this before closing the file
// Returns nothing
void ERR_LogDestroy(void);
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

// Gets the error message
// Returns a copy of the error string
char *ERR_ERRORGET(void);

// Gets the first archieved error
// Returns the first archieved error, NULL if non are available
char *ERR_ERRARCHIVE(void);

// Clears all of the errors
// Returns nothing
void ERR_ERRORCLEAR(void);

// Undefine definitions
#ifndef ERR_BUILD

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

#endif