
TARGET =	exec# Executable name

CC =		gcc# Compiler

DEBUG =		-g# Debug Mode

OPT =		-O0# Optimization

WARN =		-Wall# Warnings on

PTHREAD = 	-pthread

# Combined flags
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

# GTK Library
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# Linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

# C File Names
FILES= src/main.c src/GUI_Ctrl.c src/Alarm.c src/AlarmSetup.s
# Object File Names
OBJS = main.o GUI_Ctrl.o Alarm.o AlarmSetup.o


out: $(FILES)
	$(CC) -c $(CCFLAGS) $(FILES) $(GTKLIB)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o $(TARGET)