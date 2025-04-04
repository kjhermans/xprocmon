CFILES:=$(shell ls *.c | sort)
OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
CC=$(ARCH)gcc
AR=$(ARCH)ar
CFLAGS=-g -O2 -Wall -Wextra $(DEBUG)
LIBS=-lX11
TARGET=xprocmon

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(TARGET)
