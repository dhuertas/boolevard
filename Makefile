#
# Boolean expression evaluator
# @author Dani Huertas
# @email huertas.dani@gmail.com
#
CC = g++
CFLAGS = -Wall -std=c++11
SHELL = /bin/bash

TARGET = bxe

LIBS =

INCLUDE = -I./src

SOURCES = $(shell find ./src -type f -name '*.cc' | sort)

OBJS = $(shell find ./src -type f -name '*.cc' | sort | sed -e 's/\.cc/\.o/g' -e 's/src\//obj\//g')

.PHONY: all test clean

all: debug

debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)

depend: _depend

_depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) $(INCLUDE) -MM $^ > ./.depend;

obj/%.o: src/%.cc
	@mkdir -m 755 -p $$(dirname $@)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

test: release
	python test/test.py

clean:
	@rm -f .depend
	@rm -rf obj
	@rm -rf out
	@rm -rf ./*.out
	@rm -f $(TARGET)
