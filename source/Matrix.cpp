//namespace matrixemu
#include <Terminal.h> //class Terminal
#include <Column.h>   //class Column
#include <Linker.h>   //class Linker<T>
#include <Matrix.h>   //Implementing this
#include <debug.h>

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
	debug("in Matrix::run()");
	//we run until we've rendered enough frames or our terminal member has
	//detected a quit signal from the user.
	//we clear the screen when we're done and exit.
	
	int i, spawnpoint = 0;
	for (i = 0; i < frames; i++)
	{
		if (i == spawnpoint)
		{
			addNewColumn();
			spawnpoint += 1 + (rand() % 5);
		}

		drawFrame(i);

		debug("matrixemu::Matrix::drawFrame() success");

		terminal->pause(50); //50 ms pause or 20 fps

		if (terminal->done()) break;
	}

	terminal->blank();
	terminal->draw();

	debug("end Matrix::run()");
}

void Matrix::addNewColumn()
{
	debug("in Matrix::addNewColumn()");

	//init new column;
	int xpos, speed, length;
	xpos = rand() % terminal->getWidth();
	speed = 1 + (rand() % 10);
	length = 1 + (rand() % 50);

	Column * column = new Column(terminal, xpos);

	if (!column) 
	{
		debug("new Column() fail");
		return;
	}
	
	column->setSpeed(speed);
	column->setLength(length);

	//init new link and add to list
	Linker<Column> * link = new Linker<Column>(column);
	if (!link)
	{
		delete column;
		debug("new Linker<Column>() fail");
		return;
	}

	link->append(columns);

	debug("end Matrix::addNewColumn()");
}

void Matrix::drawFrame(int timestamp)
{
	debug("in Matrix::drawFrame()");

	Linker<Column> * node = columns->next();
	Linker<Column> * tmp;

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

	debug("end Matrix::drawFrame()");
}

/*
		private:
			Terminal * terminal;
			Linker<Column> * columns;

		public:
			Matrix();
			~Matrix();
			void run();
 */
