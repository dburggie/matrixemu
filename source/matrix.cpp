#include <Column.h>
#include <Terminal.h>

#include <iostream>//for cout
#include <cstdlib> //for atoi(), srand(), and rand()
#include <ctime>   //for time() (to seed rand)

void setupColors();
void printUsage(const char * name);

int main(int argc, char * argv[])
{
	int seconds = 10;


	if (argc > 2) 
	{
		printUsage(argv[0]);
		return 0;
	}



	if (argc == 2)
	{
		seconds = std::atoi(argv[1]);
		if (seconds <= 0)
		{
			printUsage(argv[0]);
			return 0;
		}
	}

	//seed the rng
	std::srand(std::time(NULL));

	//initialize screen
	matrix::Terminal::init();
	setupColors();

	//Column(Column * head, int column, int speed, int length, int height);
	matrix::Column * columns = new matrix::Column(0,0);
	matrix::Column * tmp = NULL;

	//get terminal size
	int rows,cols;
	matrix::Terminal::getSize(rows,cols);

	//set up for loop
	int column, speed = 1, length;
	int tick, nextSpawn = 1;
	int runtime = seconds * 50;

	//perform the loop
	//we'll do 50 ticks per second
	for (tick = 1; tick < runtime; tick++)
	{
		if (tick == nextSpawn)
		{
			nextSpawn = 1 + tick + (std::rand() % 2);

			column = std::rand() % cols;
			speed = 1 + (std::rand() % 10);
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
		matrix::Terminal::pause(20);//this is 1/50 of a second
		if (matrix::Terminal::done()) break;
	}

	delete columns;

	matrix::Terminal::end();

	return 0;
}



void printUsage(const char * name)
{
	std::cout << "    usage: " << name << " [seconds]\n";
}


void setupColors()
{
	int r[8], g[8], b[8];
	
	int i;
	for (i = 0; i < 8; i++)
	{
		r[i] = 0;
		g[i] = 125 * i;
		b[i] = 0;
	}

	matrix::Terminal::makePalette(8,r,g,b);
}
