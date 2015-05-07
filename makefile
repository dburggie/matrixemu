
CC = g++ -Wall -O0 -Isource


Terminal.o: source/Terminal.cpp source/Terminal.h
	${CC} -o $@ -c $<

Terminal.test.o: test/Terminal.test.cpp
	${CC} -o $@ -c $<

Terminal.test: Terminal.test.o Terminal.o
	${CC} -o $@ $^ -lncurses




clean:
	rm *.o
	rm *.test
