
INSTALLDIR = ~/bin

EXE = MatrixEmu
HDR = source/Terminal.h source/Column.h source/Linker.h source/Matrix.h
OBJ = build/main.o build/Matrix.o build/Linker.o build/Column.o build/Terminal.o

LIBS = -lncurses -lpthread

CC = g++ -std=c++11 -Wall -O0 -Isource


all: ${EXE}


build:
	mkdir -p build


install: ${EXE}
	mkdir -p ${INSTALLDIR}
	cp ${EXE} ${INSTALLDIR}/${EXE}


clean:
	rm -f build/*.o
	rm -f ${TESTS}
	rm -f ${EXE}



${EXE}: ${OBJ}
	${CC} -o $@ $^ ${LIBS}




build/main.o: source/main.cpp build
	${CC} -o $@ -c $<




build/Terminal.o: source/Terminal.cpp source/Terminal.h build
	${CC} -o $@ -c $<




build/Column.o: source/Column.cpp source/Column.h source/Terminal.h build
	${CC} -o $@ -c $<




build/Linker.o: source/Linker.cpp source/Linker.h build
	${CC} -o $@ -c $<




build/Matrix.o: source/Matrix.cpp ${HDR} build
	${CC} -o $@ -c $<
