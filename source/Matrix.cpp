//namespace matrixemu
#include <Terminal.h> //class Terminal
#include <Column.h>   //class Column
#include <Linker.h>   //class Linker<T>
#include <Matrix.h>   //Implementing this

//namespace std
#include <cstdlib> //rand()

using namespace matrixemu;

Matrix::Matrix()
{
	terminal = new Terminal();
	columns = new Linker<Column>();
}

Matrix::~Matrix()
{
	if (terminal) delete terminal;
	if (columns) delete columns;
}


void Matrix::run(int frames)
{
	//we run until we've rendered enough frames or our terminal member has
	//detected a quit signal from the user.
	//we clear the screen when we're done and exit.

	setupColors();
	
	int i, spawnpoint = 0;
	for (i = 0; i < frames; i++)
	{
		if (i == spawnpoint)
		{
			addNewColumn();
			spawnpoint += 1 + (rand() % 5);
		}

		drawFrame(i);
		terminal->pause(25); //25 ms pause or 40 fps

		if (terminal->done()) break;
	}

	terminal->blank();
	terminal->draw();
}


void Matrix::setupColors()
{
	int r[8], g[8], b[8], i;
	for (i = 0; i < 8; i++)
	{
		r[i] = 0;
		g[i] = 125 * i;
		b[i] = 0;
	}
	terminal->makePalette(8,r,g,b);
}

void Matrix::addNewColumn()
{
	//init new column;
	int xpos, speed, length;
	xpos = rand() % terminal->getWidth();
	speed = 1 + (rand() % 10);
	length = 1 + (rand() % 50);

	Column * column = new Column(terminal, xpos);

	if (!column) 
	{
		return;
	}
	
	column->setSpeed(speed);
	column->setLength(length);

	//init new link and add to list
	Linker<Column> * link = new Linker<Column>(column);
	if (!link)
	{
		delete column;
		return;
	}

	link->append(columns);
}

void Matrix::drawFrame(int timestamp)
{
	Linker<Column> * node = columns->next();
	Linker<Column> * tmp;

	terminal->blank();

	while (node != columns)
	{
		tmp = node->next();
		node->get()->draw(timestamp);

		//delete node if it's offscreen now
		if (node->get()->offscreen())
		{
			delete node;
		}

		node = tmp;
	}

	terminal->draw();
}
