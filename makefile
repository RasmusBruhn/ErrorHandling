OPT = -O0
WARNINGS = -Wall -Wextra
LIBRARY = -I../Library
OPTIONS = -g

CC = gcc
CCFLAGS = $(WARNINGS) $(LIBRARY) $(OPTIONS) $(OPT)

ifeq ($(OS),Windows_NT)
	EXEEXT = .exe
	DLLEXT = .dll
else
	EXEEXT = 
	DLLEXT = .o
endif

Error_tb$(EXEEXT) Error_tb.c Error2.c _Error2.h:
	$(CC) $(CCFLAGS) Error_tb.c -o Error_tb$(EXEEXT)
