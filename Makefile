CC		:= g++
CFLAGS	:= -std=c++17 -Wall -Wextra -g 

BIN		:= bin
SRC		:= src
INCLUDE	:= include

DEV_IMAGE=mercury
DEV_CONTAINER=$(DEV_IMAGE)-dev

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
else
EXECUTABLE	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

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

.PHONY: package
package:
ifeq (, $(shell which python3 2> /dev/null))
	$(error python3 is needed to package Mercury)
else
	@echo "python3 -m quom $(SOURCES) mercury.hpp -s '~> stitch <~' -g MERCURY_.+_HPP"
endif


run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ 