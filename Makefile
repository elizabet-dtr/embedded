#
# HelloWorld Makefile
#

GC = gcc
GCC = arm-linux-gcc
SOURCES = helloWorld.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -O2 -Wall -Werror
LDFLAGS = -lrt
TARGET = helloWorldT
HOST = helloWorldH

.PHONY: all clean

all: $(HOST) $(TARGET)

$(HOST): $(HOST).o
	$(GC) -o $@ $^ $(LDFLAGS)
	@echo Binaries for HOST are made

$(HOST).o: $(SOURCES)
	$(GC) -c $(CFLAGS) -o $@ $^

$(TARGET): $(TARGET).o
	$(GCC) -o $@ $^ $(LDFLAGS)
	@echo Binaries for TARGET are made

$(TARGET).o: $(SOURCES)
	$(GCC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(HOST) $(HOST).o
	rm -rf $(TARGET) $(TARGET).o
