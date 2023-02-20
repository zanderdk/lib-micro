CC = gcc
CFLAGS = -O0 -static -ggdb -Wall

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

upload: main
	scp main myldero@up:/home/myldero/

build-ucode:
	./CustomProcessingUnit/uasm-lib/uasm.py -i ucode/fix_in.u --avoid_unk_256 -o ./ucode/fix_in.h
	./CustomProcessingUnit/uasm-lib/uasm.py -i ucode/cpuid.u --avoid_unk_256 -o ./ucode/cpuid.h
	./CustomProcessingUnit/uasm-lib/uasm.py -i ucode/trace.u --avoid_unk_256 -o ./ucode/trace.h
	./CustomProcessingUnit/uasm-lib/uasm.py -i ucode/match_and_patch_hook.u --avoid_unk_256 -o ./ucode/match_and_patch_hook.h
	./CustomProcessingUnit/uasm-lib/uasm.py -i ucode/match_and_patch_init.u --avoid_unk_256 -o ./ucode/match_and_patch_init.h
	./CustomProcessingUnit/uasm-lib/uasm.py -i ucode/ldat_read.u --avoid_unk_256 -o ./ucode/ldat_read.h

build: main

main: build-ucode
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

clean:
	rm -f $(OBJECTS) ucode/*.h

.PHONY: upload

