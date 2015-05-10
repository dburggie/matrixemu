
INSTALLDIR = ~/bin

EXE = MatrixEmu
HDR = source/Terminal.h source/Column.h source/Linker.h source/Matrix.h
OBJ = build/main.o build/Matrix.o build/Column.o build/Terminal.o build/debug.o

LIBS = -lncurses -lpthread

CC = g++ -std=c++11 -Wall -Isource


all: ${EXE}


build:
	mkdir -p build


install: ${EXE}
	mkdir -p ${INSTALLDIR}
	cp ${EXE} ${INSTALLDIR}/${EXE}


clean:
	rm -f build/*.o
	rm -f ${EXE}



${EXE}: ${OBJ}
	${CC} -o $@ $^ ${LIBS}




build/main.o: source/main.cpp build
	${CC} -o $@ -c $<




build/Terminal.o: source/Terminal.cpp source/Terminal.h build
	${CC} -o $@ -c $<

build/Terminal.test.o: test/Terminal.test.cpp
	${CC} -o $@ -c $<

Terminal.test: build/Terminal.o build/Terminal.test.o
	${CC} -o $@ $^ ${LIBS}



build/Column.o: source/Column.cpp source/Column.h source/Terminal.h build
	${CC} -o $@ -c $<




build/Matrix.o: source/Matrix.cpp ${HDR} build
	${CC} -o $@ -c $<




build/debug.o: source/debug.cpp source/debug.h
	${CC} -o $@ -c $<
