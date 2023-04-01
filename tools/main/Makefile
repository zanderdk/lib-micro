CC = gcc
CFLAGS = -Wl,-rpath . -O0 -fPIE -Wno-unused-function -Wno-unused-variable -ggdb -Wall -masm=intel
STATIC_CFLAGS = -static -Wl,-R . -O0 -fPIE -Wno-unused-function -Wno-unused-variable -ggdb -Wall -masm=intel
TARGET = main
TARGET_STATIC = $(TARGET)_static

ARCHIVE_FILE =  $(wildcard $(BUILD_DIR)/*.a)

CFLAGS_STATIC = -static -O0 -fPIE -Wno-unused-function -Wno-unused-variable -ggdb -Wall -masm=intel -I $(INCLUDE_DIR)

LIBS = -l $(LIBARY_PATH)

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h) $(wildcard ucode/*.h)

$(SOURCES): $(HEADERS)

$(TARGET_STATIC): $(SOURCES)
	gcc $(STATIC_CFLAGS)  -I $(INCLUDE_DIR) $^ $(ARCHIVE_FILE) -o $@

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -L $(BUILD_DIR) $^ -lmicro -o $@

all: $(TARGET_STATIC) $(TARGET)

clean:
	rm -f $(TARGET_STATIC) $(TARGET)

.PHONY: all clean
.DEFAULT_GOAL := all
