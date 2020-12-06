# tools
CC := gcc
RM := rm -f

# flags
CFLAGS := -ggdb -Wno-format-security
LDFLAGS :=
LDLIBS :=

.PHONY: default all clean

default: all

all: demo_target demo_exploit

demo_target : demo_target.c demo_setup.c
	$(CC) $(CFLAGS) -pthread -o demo_target demo_setup.c demo_target.c

demo_exploit : demo_exploit.c
	$(CC) $(CFLAGS) -pthread -o demo_exploit demo_exploit.c

clean:
	$(RM) demo_target demo_exploit demo_target.o demo_setup.o demo_exploit.o
