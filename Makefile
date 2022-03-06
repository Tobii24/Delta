CC = g++
CFLAGS = -c -g
LDFLAGS = -g
SRC = ${wildcard src/*.cpp}
HDR = ${wildcard include/*.h}
OBJ = ${SRC:.cpp=.o}
EXEC = main.exe

all: ${SRC} ${OBJ} ${EXEC}

debug: all
debug: CFLAGS += -DDEBUG

.SILENT:
${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.cpp ${HDR}
	${CC} ${CFLAGS} $< -o $@

clear:
	del /S *.o >nul 2>&1
	del /s ${EXEC} >nul 2>&1

.PHONY: all
run: ${EXEC}
	./${EXEC} compile ./test/first.dlt