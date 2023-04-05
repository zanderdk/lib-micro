CC = gcc
CFLAGS = -O0 -fPIE -Wno-unused-function -Wno-unused-variable -ggdb -Wall -masm=intel -I include/
TARGET_LIB_SHARED = build/libmicro.so
TARGET_LIB_STATIC = build/libmicro.a

SHARED_LDFLAGS = -Wl,-whole-archive $(TARGET_LIB_STATIC) -Wl,-no-whole-archive -shared

BUILD_DIR = $(CURDIR)/build
INCLUDE_DIR = $(CURDIR)/include

SOURCES = $(wildcard source/*.c)
OBJECTS = $(patsubst source/%.c, build/%.o, $(SOURCES))
HEADERS = $(wildcard include/*.h) $(wildcard include/ucode/*.h)

#export all variables
export

include/inst.h: include/gen_inst.py
	./include/gen_inst.py > include/inst.h

$(SOURCES): include/inst.h $(HEADERS) build

build:
	mkdir build

$(OBJECTS): build/%.o: source/%.c
	$(CC) $(CFLAGS) -c $< -o $@

${TARGET_LIB_STATIC}: $(OBJECTS)
	ar rcs $@ $(OBJECTS)

$(TARGET_LIB_SHARED): ${TARGET_LIB_STATIC}
	$(CC) $(CFLAGS) ${SHARED_LDFLAGS} -o $@ $^

static: ${TARGET_LIB_STATIC}
dynamic: ${TARGET_LIB_SHARED}

DIRECTORIES = $(wildcard tools/*/)

clean:
	$(eval EXEC_FILES := $(shell find tools -type f -perm /u=x,g=x,o=x -exec ls {} \; | xargs))
	rm -rf build include/inst.h $(EXEC_FILES) docs/doxygen/build docs/sphinx/build/

tools: $(TARGET_LIB_SHARED)
	make -C tools all

all: tools
	$(eval EXEC_FILES := $(shell find tools -type f -perm /u=x,g=x,o=x -exec ls {} \; | xargs))
	cp $(EXEC_FILES) ./build

upload: all
	$(eval EXEC_FILES := $(shell find build -type f -perm /u=x,g=x,o=x -exec ls {} \; | xargs))
	scp $(EXEC_FILES) $(USER)@up:~


DOCS_RST = $(wildcard docs/sphinx/source/*.rst)
docs: $(DOCS_RST) $(SOURCES) docs/sphinx/source/conf.py
	make -C docs/sphinx html

host-docs: docs
	sphinx-autobuild docs/sphinx/source/ docs/sphinx/build/html

remote:
	rsync -avzh ./* $(USER)@up:~/lib-micro/
	ssh $(USER)@up "make -C lib-micro all"

.PHONY: all clean static dynamic tools upload docs host-docs remote
.DEFAULT_GOAL := upload
