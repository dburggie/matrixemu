#include <Column.h>
#include <Terminal.h>


#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
	//seed the rng
	std::srand(std::time(NULL));

	//initialize screen
	matrix::Terminal::init();

	//Column(Column * head, int column, int speed, int length, int height);
	matrix::Column * columns = new matrix::Column(0,0);
	matrix::Column * tmp = NULL;

	//get terminal size
	int rows,cols;
	matrix::Terminal::getSize(rows,cols);

	//set up for loop
	int column, speed = 1, length;
	int tick, nextSpawn = 1;

	//perform the loop
	//we'll do 100 ticks per second, 10 second run
	for (tick = 1; tick < 1000; tick++)
	{
		if (tick == nextSpawn)
		{
			nextSpawn = 1 + tick + (std::rand() % 10);

			column = std::rand() % cols;
			speed = 2 + (std::rand() % 10);
			length = 5 + (std::rand() % 50);

			tmp = new matrix::Column(column,rows);
			tmp->setSpeed(speed);
			tmp->setLength(length);
			tmp->insert(columns);
		}

		//do the draw
		matrix::Terminal::blank();
		matrix::Column::drawAll(columns,tick);
		matrix::Terminal::draw();
		matrix::Terminal::pause(10);
	}

	delete columns;

	matrix::Terminal::end();

	return 0;
}


