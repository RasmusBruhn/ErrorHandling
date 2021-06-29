#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

void TestExit(uint64_t ErrorID);

#define ERR_MAXARCHIVED 3
#define ERR_MAXLENGTH 50
#define ERR_EXITFUNC &TestExit
#include "Error.h"

int main(int argc, char **argv)
{
    // Test error type and ID
    printf("Error type initialisation: %lu\nError ID initialisation: %lX\n\n", ERR_GetErrorType(), ERR_GetErrorID());

    // Test error message initialisation
    printf("Error message initialisation: %s\n\n", ERR_GetError());

    // Test an error message
    _ERR_SetError(0x00000101, "First error %d", 1);
    printf("Error message: %s\n\n", ERR_GetError());

    // Test updated error type and ID
    printf("Error type updated: %lu\nError ID updated: %lX\n\n", ERR_GetErrorType(), ERR_GetErrorID());

    // Test added message
    _ERR_AddError(0x00000202, "Second error %d", 2);
    printf("Error message added: %s\n\n", ERR_GetError());

    // Test updated error type and ID
    printf("Error type updated: %lu\nError ID updated: %lX\n\n", ERR_GetErrorType(), ERR_GetErrorID());

    // Test foreign message
    _ERR_AddErrorForeign(0x00000303, "Foreign", "Third error %d", 3);
    printf("Error message foreign added: %s\n\n", ERR_GetError());

    // Test updated error type ID
    printf("Error type updated: %lu\nError ID updated: %lX\n\n", ERR_GetErrorType(), ERR_GetErrorID());

    // Test too long
    _ERR_SetError(0x05430121, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    printf("Error message too long: %s\n\n", ERR_GetError());

    // Test %
    _ERR_AddErrorForeign(0x00000104, "Test %", "Test");
    printf("Error message with %%: %s\n\n", ERR_GetError());

    // Test updated error type and ID
    printf("Error type updated: %lu\nError ID updated: %lX\n\n", ERR_GetErrorType(), ERR_GetErrorID());

    // Test the log
    ERR_ClearArchive();
    _ERR_SetError(1, "1");
    _ERR_SetError(2, "2");
    _ERR_AddError(3, "3");
    printf("Error log:\n");
    char *Mes = NULL;
    while ((Mes = ERR_GetArchivedError()) != NULL) printf("Message: %s\n", Mes);
    printf("\n");

    // Test log overflow
    ERR_ClearArchive();
    _ERR_SetError(1, "1");
    _ERR_SetError(2, "2");
    _ERR_SetError(3, "3");
    _ERR_SetError(4, "4");
    _ERR_SetError(5, "5");
    printf("Error log overflow:\n");
    while ((Mes = ERR_GetArchivedError()) != NULL) printf("Message: %s\n", Mes);
    printf("\n");

    // Test the log file
    FILE *LogFile = fopen("c/ErrorHandling/ErrorLog.txt", "w+");

    if (LogFile == NULL)
        printf("Unable to open file: %s\n", strerror(errno));

    _ERR_SetLogFile(LogFile);

    // Test normal error
    _ERR_SetError(0x0101, "First error");

    // Test foreign
    _ERR_AddErrorForeign(0x0102, "Foreign error", "Second error");

    // Test adding error
    _ERR_SetError(0x0103, "Third error");
    _ERR_AddError(0x0104, "Fourth error");

    fclose(LogFile);

    return 0;
}

void TestExit(uint64_t ErrorID)
{
    printf("Exit function worked\n\n");
}