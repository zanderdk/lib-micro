CC = gcc
CFLAGS = -O0 -Wno-unused-variable -static -ggdb -Wall -masm=intel

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

TARGET = main

upload: $(TARGET)
	scp mai* $(USER)@up:~

build: $(TARGET)

# yee not the prettiest but easy as hell
alu_ops.h: gen_inst.py
	python gen_inst.py > alu_ops.h

$(TARGET): alu_ops.h $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: upload build
.DEFAULT_GOAL := upload
