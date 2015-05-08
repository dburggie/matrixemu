#include <Terminal.h>
#include <ncurses.h>
#include <unistd.h> //for usleep()

int matrix::Terminal::initialized = 0;
int matrix::Terminal::rows = 0;
int matrix::Terminal::cols = 0;
int matrix::Terminal::delay = 1; // wait one tenth for input
int matrix::Terminal::paletteSize = 0;

matrix::Terminal::Terminal() { };

matrix::Terminal::~Terminal() { };




void matrix::Terminal::init()
{
	initscr();
	cbreak();
	halfdelay(delay);
	noecho();
	curs_set(0);//cursor invisible
	start_color();
	getmaxyx(stdscr, rows, cols);
	initialized = 1;
	blank();
}


void matrix::Terminal::end()
{
	blank();
	draw();
	endwin();
}



//reds/greens/blues are arrays of color intensity values 0-1000
//only the first 8 values will be read
//the value at index 0 will be the background color off all the pairs
void matrix::Terminal::makePalette(int count, int reds[], int greens[], int blues[])
{
	if (!initialized) return;

	int i;
	for (i = 0; i < 8 && i < count; i++)
	{
		init_color(i, reds[i], greens[i], blues[i]);
		init_pair(i,i,0);
	}

	this->paletteSize = 8 < count ? 8 : count;
}

int matrix::Terminal::getPaletteSize()
{
	return matrix::Terminal::paletteSize;
}




void matrix::Terminal::blank()
{
	if (!initialized) return;

	int y,x;

	for (y = 0; y < rows; y++)
	{
		for (x = 0; x < cols; x++)
		{
			mvaddch(y,x,' '); //ncurses function
		}
	}

	move(0,0); //ncurses function
}


void matrix::Terminal::draw()
{
	if (!initialized) return;
	refresh();
}



void matrix::Terminal::pause()
{
	cbreak();
	getch();
	halfdelay(delay);
}


void matrix::Terminal::pause(int ms)
{
	usleep(ms * 1000);
}


void matrix::Terminal::getSize(int & y, int & x)
{
	getmaxyx(stdscr,y,x);
}


void matrix::Terminal::output(int y, int x, int c)
{
	if (!initialized) return;
	if (y < 0 || y > rows) return;
	if (x < 0 || x > cols) return;

	mvaddch(y,x,c);
	move(0,0);
}


void matrix::Terminal::output(int y, int x, int c, int color)
{
	if (!initialized) return;
	if (y < 0 || y > rows) return;
	if (x < 0 || x > cols) return;

	mvaddch(y,x,c | COLOR_PAIR(color));
	move(0,0);
}

