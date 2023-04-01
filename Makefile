OPT = -O3

include ../Library/make/InitMakefile

Error_tb: Error_tb.c Error2.h _Error2.h Error2.c ErrorLog.h _ErrorLog.h | -lErrorLog
	$(CC) $(CCFLAGS) -o $@ $< $|

include ../Library/make/DefaultMakefile
