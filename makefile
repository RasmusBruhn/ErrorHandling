OPT = -O0
WARNINGS = -Wall -Wextra
LIBRARY = -I../Library -L. -L../Library/libs
OPTIONS = -g
LIBS = -lError

CC = gcc
CCFLAGS = $(WARNINGS) $(LIBRARY) $(LIBS) $(OPTIONS) $(OPT)
LIBFLAGS1 = -c -fPIC
LIBFLAGS2 = -shared

ifeq ($(OS),Windows_NT)
	EXEEXT = .exe
	DLLEXT = .dll
else
	EXEEXT = 
	DLLEXT1 = .o
	DLLEXT2 = .so
endif

Error_tb$(EXEEXT): Error_tb.c Error2.c _Error2.h ErrorLog.h _ErrorLog.h libError$(DLLEXT2)
	$(CC) $(CCFLAGS) Error_tb.c -o Error_tb$(EXEEXT)

libError$(DLLEXT2): libError$(DLLEXT1)
	$(CC) $(CCFLAGS) libError$(DLLEXT1) $(LIBFLAGS2) -o libError$(DLLEXT2)

libError$(DLLEXT1): ErrorLog.c ErrorLog.h _ErrorLog.h
	$(CC) $(CCFLAGS) ErrorLog.c $(LIBFLAGS1) -o libError$(DLLEXT1)

clean:
	rm -f *.exe *_tb *.o *.dll *.so
