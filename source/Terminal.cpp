#include <Terminal.h>
#include <thread>
#include <unistd.h>
#include <ncurses.h>


//NOTE: I'm super pedantic with the scoping operator here because the ncurses
//header puts all it's content into the global namespace

/* STATIC MEMBERS */

//private static
int matrixemu::Terminal::initialized = 0;

//public static
void matrixemu::Terminal::init()
{
	if (matrixemu::Terminal::initialized) return;
	initscr();    //start ncurses mode
	cbreak();     //don't buffer keyboard input
	noecho();     //don't echo keyboard to screen
	curs_set(0); //turn off cursor
	matrixemu::Terminal::initialized = 0;
}

//public static
void matrixemu::Terminal::end()
{
	if (!matrixemu::Terminal::initialized) return;

	clear();
	refresh();
	endwin();
	matrixemu::Terminal::initialized = 0;
}

//private static
void matrixemu::Terminal::UIwatcher(void * terminal)
{
	if (!matrixemu::Terminal::initialized) return;
	
	int key;
	matrixemu::Terminal * t = (matrixemu::Terminal *) terminal;
	do {
		key = getch();
	} while (key != 'q');

	t->stopflag = 1;
}





/* PUBLIC MEMBERS */


matrixemu::Terminal::Terminal()
{
	if (!matrixemu::Terminal::initialized)
	{
		this->rows = 0;
		this->cols = 0;
	}

	else
	{
		getmaxyx(stdscr, this->rows, this->cols);
	}

	this->paletteSize = 1;
	this->stopflag = 0;

	if (this->rows)
	{
		this->screen = new int * [this->rows];
	}

	if (this->cols)
	{
		int i; for (i = 0; i < this->rows; i++)
		{
			this->screen[i] = new int [this->cols];
		}
	}

	this->blank();

	//start associated UI
	std::thread UI (matrixemu::Terminal::UIwatcher, (void *) this);
	UI.detach();
}



matrixemu::Terminal::~Terminal()
{
	if (this->screen)
	{
		int i; for (i = 0; i < this->rows; i++)
		{
			if (this->screen[i]) delete [] this->screen[i];
			this->screen[i] = NULL;
		}

		delete [] this->screen;
		this->screen = NULL;
	}
}

void matrixemu::Terminal::makePalette(int count, int r[], int g[], int b[])
{
	//don't use ncurses functions if we haven't called initscr()
	if (!matrixemu::Terminal::initialized) return;

	//skip this if colors aren't supported
	if (!has_colors() || !can_change_color())
	{
		this->paletteSize = 1;
	}

	if (count > 8) count = 8;
	int i;

	//initialize colors
	for (i = 0; i < count; i++)
	{
		init_color(i,r[i],g[i],b[i]);
	}

	//initialize color pairs, zero is background
	for (i = 1; i < count; i++)
	{
		init_pair(i,i,0);
	}

	//set palette size (count - 1 unless count is <= 1)
	this->paletteSize = 1 < count ? count - 1 : 1;
}



int matrixemu::Terminal::getPaletteSize() const
{
	return this->paletteSize;
}



void matrixemu::Terminal::blank()
{
	int y,x;
	for (y = 0; y < this->rows; y++)
	{
		for (x = 0; x < this->cols; x++)
		{
			this->screen[y][x] = (int) ' ';
		}
	}
}



void matrixemu::Terminal::draw() const
{
	int y,x;

	for (y = 0; y < this->rows; y++)
	{
		move(y,0);
		for (x = 0; x < this->cols; x++)
		{
			addch(this->screen[y][x]);
		}
	}

	refresh();
}


void matrixemu::Terminal::pause(int ms) const
{
	usleep(ms * 1000);
}



void matrixemu::Terminal::getSize(int & y, int & x) const
{
	y = this->rows;
	x = this->cols;
}

int matrixemu::Terminal::output(int y, int x, int c)
{
	if ( y < 0 || y >= this->rows || x < 0 || x >= this->cols)
		return 1;
	
	this->screen[y][x] = c;
	return 0;
}



int matrixemu::Terminal::output(int y, int x, int c, int color)
{
	if ( y < 0 
		|| x < 0 
		|| color < 0 
		|| y >= this->rows 
		|| x >= this->cols 
		|| color >= this->paletteSize)
	{
		return 1;
	}
	
	this->screen[y][x] = c | COLOR_PAIR(color);
	return 0;
}


int matrixemu::Terminal::done() const
{
	return this->stopflag;
}
