CC = g++
CFLAGS = -c -g
LDFLAGS = -g
SRC = ${wildcard src/*.cpp}
HDR = ${wildcard include/*.h}
OBJ = ${SRC:.c=.o}
EXEC = main.exe

all: ${SRC} ${OBJ} ${EXEC}

debug: all
debug: CFLAGS += -DDEBUG

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	del /S src/*.o 
	del /s ${EXEC}