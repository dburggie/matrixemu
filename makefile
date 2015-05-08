
CC = g++ -Wall -O0 -Isource




clean:
	rm -f build/*.o
	rm -f build/*.test







build/Terminal.o: source/Terminal.cpp source/Terminal.h
	${CC} -o $@ -c $<

build/Terminal.test.o: test/Terminal.test.cpp
	${CC} -o $@ -c $<

Terminal.test: Terminal.test.o Terminal.o
	${CC} -o $@ $^ -lncurses






build/Column.o: source/Column.cpp source/Column.h build/Terminal.o
	${CC} -o $@ -c $<

build/Column.test.o: test/Column.test.cpp build/Column.o
	${CC} -o $@ -c $<

Column.test: build/Column.test.o build/Column.o build/Terminal.o
	${CC} -o $@ $^ -lncurses
	
	


