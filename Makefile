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

CMD = "find tools -type f -perm /u=x,g=x,o=x -exec ls {} \; | xargs"

#export all variables
export

# yee not the prettiest but easy as hell
include/alu_ops.h: include/gen_inst.py
	python include/gen_inst.py > include/alu_ops.h

$(SOURCES): include/alu_ops.h $(HEADERS) build

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
	rm -rf build include/alu_ops.h $(EXEC_FILES)

tools: $(TARGET_LIB_SHARED)
	make -C tools all

all: tools
	$(eval EXEC_FILES := $(shell find tools -type f -perm /u=x,g=x,o=x -exec ls {} \; | xargs))
	cp $(EXEC_FILES) ./build

upload: all
	$(eval EXEC_FILES := $(shell find build -type f -perm /u=x,g=x,o=x -exec ls {} \; | xargs))
	scp $(EXEC_FILES) $(USER)@up:~


DOCS_RST = $(wildcard docs/sphinx/source/*.rst)
docs: $(DOCS_RST) $(SOURCES)
	make -C docs/sphinx html

host-docs: docs
	python -m http.server --directory docs/sphinx/build/html


.PHONY: all clean static dynamic tools upload docs host-docs
.DEFAULT_GOAL := upload
