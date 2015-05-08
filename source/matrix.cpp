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
	matrix::Column * columns = new matrix::Column(NULL,	0,0,0,0);
	std::cerr << "made head column\n";
	matrix::Column * tmp = NULL;

	//get terminal size
	int rows,cols;
	matrix::Terminal::getSize(rows,cols);
	std::cerr << "got terminal size " << rows << "," << cols << "\n";

	//set up for loop
	int column, speed = 0, length;
	int count = 0, i;

	//perform the loop
	for (i = 0; i < 200; i++)
	{
		//we'll do 100 columns with random lengths
		if (count++ < 100)
		{
			column = std::rand() % cols;
			length = 5 + (rand() % 10) + (rand() % 10);
			tmp = new matrix::Column(columns,column,speed,length,rows);
			std::cerr << "instantiated new column number" << count << "\n";
		}

		//do the draw
		matrix::Terminal::blank();
		matrix::Column::drawAll(columns);
		matrix::Terminal::draw();
		matrix::Terminal::pause();
	}

	delete columns;
	std::cerr << "deleted columns\n";

	matrix::Terminal::end();
	std::cerr << "all done\n";

	return 0;
}


