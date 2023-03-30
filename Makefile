CC = gcc
CFLAGS = -O0 -Wno-unused-function -Wno-unused-variable -static -ggdb -Wall -masm=intel -Iinclude/

SOURCES = $(wildcard source/*.c)
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(wildcard include/*.h) $(wildcard include/ucode/*.h)

TARGET = build/main

upload: $(TARGET)
	scp $(TARGET) $(USER)@up:~

build: $(TARGET)

# yee not the prettiest but easy as hell
include/alu_ops.h: include/gen_inst.py
	python include/gen_inst.py > include/alu_ops.h

$(TARGET): include/alu_ops.h $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) include/alu_ops.h

.PHONY: upload build
.DEFAULT_GOAL := upload
