CC = gcc
CFLAGS = -O0 -static -ggdb -Wall

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

U_SOURCES := $(wildcard ucode/*.u)
U_HEADERS = $(U_SOURCES:.u=.h)

TARGET = main

upload: $(TARGET)
	scp main up:/home/zander/

./ucode/%.h: ./ucode/%.u
	./CustomProcessingUnit/uasm-lib/uasm.py -i $^ --avoid_unk_256 -o $@

build-ucode: $(U_HEADERS)

build: $(TARGET)

$(TARGET): build-ucode
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) ucode/*.h

.PHONY: upload build build-ucode
.DEFAULT_GOAL := upload
