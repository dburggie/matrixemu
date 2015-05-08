
CC = g++ -Wall -O0 -Isource




clean:
	rm -f build/*.o
	rm -f *.test




TESTS = Terminal.test Column.test
tests: ${TESTS}





build/Terminal.o: source/Terminal.cpp source/Terminal.h
	${CC} -o $@ -c $<

build/Terminal.test.o: test/Terminal.test.cpp
	${CC} -o $@ -c $<

Terminal.test: build/Terminal.test.o build/Terminal.o
	${CC} -o $@ $^ -lncurses






build/Column.o: source/Column.cpp source/Column.h build/Terminal.o
	${CC} -o $@ -c $<

build/Column.test.o: test/Column.test.cpp build/Column.o
	${CC} -o $@ -c $<

Column.test: build/Column.test.o build/Column.o build/Terminal.o
	${CC} -o $@ $^ -lncurses




build/letter.test.o: test/letter.test.cpp
	${CC} -o $@ -c $<

letter.test: build/letter.test.o build/Terminal.o
	${CC} -o $@ $^ -lncurses

