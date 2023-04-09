OPT = -O3
PREREQUISITES = _Error2.h Error2.c ErrorLog.h _ErrorLog.h
ADDLINKER = -lErrorLog
MAKELINKER = libErrorLog.dll

include ../Library/make/InitMakefile

ifeq ($(OS), Windows_NT)
Error2_tb.exe libErrorLog.dll:
else
Error2_tb libErrorLog.so libErrorLog.a:
endif

include ../Library/make/DefaultMakefile