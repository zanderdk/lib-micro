DIRECTORIES = $(wildcard */)

all:
	for f in $(DIRECTORIES) ; do make -C $$f all ; done

.PHONY: all
.DEFAULT_GOAL := all
