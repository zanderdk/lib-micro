CC = gcc
CFLAGS = -O0 -static -ggdb -Wall -masm=intel

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

U_SOURCES := $(wildcard ucode/*.u)
U_HEADERS = $(U_SOURCES:.u=.h)

TARGET = main

upload: $(TARGET)
	scp main $(USER)@up:~

./ucode/%.h: ./ucode/%.u
	./CustomProcessingUnit/uasm-lib/uasm.py -i $^ --avoid_unk_256 -o $@

build-ucode: $(U_HEADERS)

build: $(TARGET)

# yee not the pretiest but easy as hell
alu_ops.h: gen_inst.py
	python gen_inst.py > alu_ops.h

$(TARGET): build-ucode alu_ops.h $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) ucode/*.h

.PHONY: upload build build-ucode
.DEFAULT_GOAL := upload
