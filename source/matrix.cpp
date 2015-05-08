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
	int count = 0, i;

	//perform the loop
	for (i = 0; i < 200; i++)
	{
		//we'll do 100 columns with random lengths
		if (count++ < 100)
		{
			column = std::rand() % cols;
			length = 5 + (rand() % 10) + (rand() % 10);
			
			tmp = new matrix::Column(column,rows);
			
			tmp->setSpeed(speed);
			tmp->setLength(length);
			tmp->insert(columns);
		}

		//do the draw
		matrix::Terminal::blank();
		matrix::Column::drawAll(columns);
		matrix::Terminal::draw();
		matrix::Terminal::pause();
	}

	delete columns;

	matrix::Terminal::end();

	return 0;
}


