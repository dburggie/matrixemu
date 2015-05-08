
CC = g++ -std=c++11 -Wall -O0 -Isource
LIBS = -lpthread -lncurses

EXE = matrix

all: ${EXE}


install: ${EXE}
	cp ${EXE} ~/bin/MatrixEmu

clean:
	rm -f build/*.o
	rm -f ${TESTS}
	rm -f ${EXE}




TESTS = Terminal.test Column.test
tests: ${TESTS}



build/matrix.o: source/matrix.cpp
	${CC} -o $@ -c $<

${EXE}: build/matrix.o build/Terminal.o build/Column.o
	${CC} -o $@ $^ ${LIBS}







build/Terminal.o: source/Terminal.cpp source/Terminal.h
	${CC} -o $@ -c $<

build/Terminal.test.o: test/Terminal.test.cpp
	${CC} -o $@ -c $<

Terminal.test: build/Terminal.test.o build/Terminal.o
	${CC} -o $@ $^ ${LIBS}






build/Column.o: source/Column.cpp source/Column.h build/Terminal.o
	${CC} -o $@ -c $<

build/Column.test.o: test/Column.test.cpp build/Column.o
	${CC} -o $@ -c $<

Column.test: build/Column.test.o build/Column.o build/Terminal.o
	${CC} -o $@ $^ ${LIBS}




