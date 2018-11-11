BIN_DIR=$(shell pwd)/bin

build:
	rm -f ./bin/*.o \
    && g++ -Wall -pedantic src/main.cpp -dynamiclib -o ${BIN_DIR}/main.o \
    && g++ ${BIN_DIR}/main.o -o ${BIN_DIR}/json-analyzer
