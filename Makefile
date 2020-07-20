CC		:= g++
CFLAGS	:= -std=c++17 -Wall -Wextra -g 

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

DEV_IMAGE=mercury
DEV_CONTAINER=$(DEV_IMAGE)-dev

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
EXECUTABLE	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.cpp=.o)

all: $(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)

.PHONY: clean-dev
clean-dev:
	-docker kill $(DEV_CONTAINER)
	-docker rm $(DEV_CONTAINER)
	-docker rmi ($DEV_IMAGE)

.PHONY: dev
dev:
ifeq (, $(shell which docker-compose 2> /dev/null))
	$(error docker-compose not in $(PATH), make sure both docker and docker-compose are installed)
else
	@docker-compose run mercury bash
endif

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)