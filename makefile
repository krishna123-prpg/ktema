CC:=gcc
CC_FLAGS:= -O3 -std=c17
CC_ERR_FLAGS:=
ifeq (${OS},Windows_NT)
	PLATFORM := windows
else
	PLATFORM := posix
endif
ifeq (${PLATFORM},windows)
    RM := del /Q
    RMDIR := rmdir /S /Q
    MKDIR := mkdir
    CP := copy
else
    RM :=rm -f
    RMDIR := rm -rf
    MKDIR :=mkdir -p
    CP := cp
endif
.PHONY: build_dir all clean
all: build_dir ktema clean
build_dir:
	${MKDIR} build
ktema: build/main.o build/template.o build/file.o build/argtable3.o build/command.o
	${CC} -o $@ ${CC_FLAGS} ${CC_ERR_FLAGS} $^
build/main.o: main.c
	${CC} ${CC_FLAGS} ${CC_ERR_FLAGS} -Iinclude -c $^ -o $@
build/template.o:  others/template.c
	${CC} ${CC_FLAGS} ${CC_ERR_FLAGS} -Iinclude -c $^ -o $@
build/file.o:  others/file.c
	${CC} ${CC_FLAGS} ${CC_ERR_FLAGS} -Iinclude -c $^ -o $@
build/argtable3.o:  cli_args/argtable3.c
	${CC} ${CC_FLAGS} ${CC_ERR_FLAGS} -Iinclude -c $^ -o $@
build/command.o:  cli_args/command.c
	${CC} ${CC_FLAGS} ${CC_ERR_FLAGS} -Iinclude -c $^ -o $@
clean:
	${RMDIR} build
