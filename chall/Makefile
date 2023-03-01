CC = gcc
CFLAGS = -no-pie -fno-stack-protector -Os -ggdb -masm=intel
# gcc -no-pie -O3 -ggdb -masm=intel chall.c -o chall

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

U_SOURCES := $(wildcard ucode/*.u)
U_HEADERS = $(U_SOURCES:.u=.h)

TARGET = chall

upload: build
	scp $(TARGET) $(USER)@up:~
	scp chall.c $(USER)@up:~

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) ucode/*.h

.PHONY: upload build build-ucode
.DEFAULT_GOAL := upload
