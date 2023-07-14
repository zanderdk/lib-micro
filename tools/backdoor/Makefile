CC = gcc
CFLAGS = -O0 -fPIE -ggdb -Wall -masm=intel -Wmissing-field-initializers -Wno-unused-function -Wno-unused-variable
DYNAMIC_CFLAGS = -Wl,-rpath . $(CFLAGS)
STATIC_CFLAGS = -static -Wl,-R . $(CFLAGS)
TARGET = backdoor
TARGET_STATIC = $(TARGET)_static

ARCHIVE_FILE =  $(wildcard $(BUILD_DIR)/*.a)

LIBS = -l $(LIBARY_PATH)

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h) $(wildcard ucode/*.h)

$(TARGET_STATIC): $(SOURCES) $(HEADERS)
	$(CC) $(STATIC_CFLAGS) -I $(INCLUDE_DIR) $(SOURCES) $(ARCHIVE_FILE) -o $@

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(DYNAMIC_CFLAGS) -I $(INCLUDE_DIR) -L $(BUILD_DIR) $(SOURCES) -lmicro -o $@

all: $(TARGET_STATIC) $(TARGET)

clean:
	rm -f $(TARGET_STATIC) $(TARGET)

.PHONY: all clean
.DEFAULT_GOAL := all
