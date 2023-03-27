#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
//#include <Debug2.h>

#define ERR_PREFIX ERR1
#define ERR_MAXARCHIVED 3
#define ERR_MAXLENGTH 10
#include "Error2.c"
#define _ERR1_ErrorSet(Format, ...) __ERR1_ErrorSet(__FILE__, __LINE__, Format __VA_OPT__(,) __VA_ARGS__)
#define _ERR1_ErrorAdd(Format, ...) __ERR1_ErrorAdd(__FILE__, __LINE__, Format __VA_OPT__(,) __VA_ARGS__)
#define _ERR1_ErrorAddExternal(ExternalMessage, Format, ...) __ERR1_ErrorAddExternal(__FILE__, __LINE__, ExternalMessage, Format __VA_OPT__(,) __VA_ARGS__)

#define ERR_PREFIX ERR2
#define ERR_MAXARCHIVED 1
#define ERR_MAXLENGTH 100
#include "Error2.c"
#define _ERR2_ErrorSet(Format, ...) __ERR2_ErrorSet(__FILE__, __LINE__, Format __VA_OPT__(, ) __VA_ARGS__)
#define _ERR2_ErrorAdd(Format, ...) __ERR2_ErrorAdd(__FILE__, __LINE__, Format __VA_OPT__(, ) __VA_ARGS__)
#define _ERR2_ErrorAddExternal(ExternalMessage, Format, ...) __ERR2_ErrorAddExternal(__FILE__, __LINE__, ExternalMessage, Format __VA_OPT__(, ) __VA_ARGS__)

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    int ErrorID = 0;

    // Test no error
    printf("Testing no error (%d):\n", ErrorID);
    printf("%s\n", ERR1_ErrorGet());

    // Test normal error
    printf("\nTesting normal error (%d):\n", ErrorID);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    printf("%s\n", ERR1_ErrorGet());
    printf("%s\n", ERR1_ErrorGet());

    // Test add error
    printf("\nTesting add error (%d):\n", ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);
    printf("%s\n", ERR1_ErrorGet());

    // Test external error
    printf("\nTesting add external error (%d):\n", ErrorID);
    _ERR1_ErrorAddExternal("External Error", "Error %d", ++ErrorID);
    printf("%s\n", ERR1_ErrorGet());

    // Test archive
    printf("\nTesting archive (%d):\n", ErrorID);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    for (char *Mes = ERR1_ErrorArchive(); Mes != NULL; Mes = ERR1_ErrorArchive())
        printf("%s\n", Mes);
    printf("%s\n", ERR1_ErrorGet());

    // Testing clear
    printf("\nTesting clear (%d):\n", ErrorID);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    ERR1_ErrorClear();
    for (char *Mes = ERR1_ErrorArchive(); Mes != NULL; Mes = ERR1_ErrorArchive())
        printf("%s\n", Mes);
    printf("%s\n", ERR1_ErrorGet());

    // Testing overflow of message
    printf("\nTesting message overflow (%d):\n", ErrorID);
    _ERR1_ErrorSet("This is a very long message");
    printf("%s\n", ERR1_ErrorGet());

    // Testing overflow of errors
    printf("\nTesting archive overflow (%d):\n", ErrorID);
    for (int i = 0; i < 5; ++i)
        _ERR1_ErrorSet("Error %d", ++ErrorID);
    for (char *Mes = ERR1_ErrorArchive(); Mes != NULL; Mes = ERR1_ErrorArchive())
        printf("%s\n", Mes);

    // Testing file
    FILE *Log1 = fopen("ErrorLog1.txt", "w");
    ERR_LogCreate(Log1);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);

    // Testing file overwrite
    FILE *Log2 = fopen("ErrorLog2.txt", "w");
    ERR_LogCreate(Log2);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);

    // Testing file removal
    ERR_LogDestroy();
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);

    // Testing 2 error imports
    printf("\nTesting 2 imports (%d):\n", ErrorID);
    ERR1_ErrorClear();
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR2_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR2_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);
    _ERR2_ErrorAdd("Error %d", ++ErrorID);
    printf("%s\n", ERR1_ErrorGet());
    printf("%s\n", ERR2_ErrorGet());
    for (char *Mes = ERR1_ErrorArchive(); Mes != NULL; Mes = ERR1_ErrorArchive())
        printf("%s\n", Mes);
    for (char *Mes = ERR2_ErrorArchive(); Mes != NULL; Mes = ERR2_ErrorArchive())
        printf("%s\n", Mes);

    // Test 2 error imports with file
    FILE *Log3 = fopen("ErrorLog3.txt", "w");
    ERR_LogCreate(Log3);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);
    _ERR2_ErrorSet("Error %d", ++ErrorID);
    _ERR2_ErrorAdd("Error %d", ++ErrorID);
    _ERR1_ErrorSet("Error %d", ++ErrorID);
    _ERR1_ErrorAdd("Error %d", ++ErrorID);
    _ERR2_ErrorSet("Error %d", ++ErrorID);
    _ERR2_ErrorAdd("Error %d", ++ErrorID);

    ERR1_ErrorClear();
    ERR2_ErrorClear();
    ERR_LogDestroy();

    fclose(Log1);
    fclose(Log2);
    fclose(Log3);

    //DBG_MemoryPrint();

    printf("\nDone\n");

    return 0;
}
