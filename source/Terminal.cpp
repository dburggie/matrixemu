#include <Terminal.h>
#include <ncurses.h>
#include <unistd.h> //for usleep()
#include <thread>   //std::thread

int matrix::Terminal::initialized = 0;
int matrix::Terminal::rows = 0;
int matrix::Terminal::cols = 0;
int matrix::Terminal::delay = 1; // wait one tenth for input
int matrix::Terminal::paletteSize = 1;


matrix::Terminal::Terminal() { };

matrix::Terminal::~Terminal() { };




void matrix::Terminal::init()
{
	//ncurses init functions
	initscr();
	cbreak();
	halfdelay(delay);
	noecho();
	curs_set(0);//cursor invisible
	start_color();
	getmaxyx(stdscr, rows, cols);
	matrix::Terminal::blank();

	//set init flag
	matrix::Terminal::initialized = 1;

	//start UI thread
	std::thread UIthread(matrix::Terminal::UIwatcher);
	UIthread.detach();
}


void matrix::Terminal::end()
{
	matrix::Terminal::blank();
	matrix::Terminal::draw();
	endwin();
}



//reds/greens/blues are arrays of color intensity values 0-1000
//only the first 8 values will be read
//the value at index 0 will be the background color of all the pairs
//pairs will have foregrounds from max(7,count-1) to 1 descending
void matrix::Terminal::makePalette(int count, int reds[], int greens[], int blues[])
{
	if (!matrix::Terminal::initialized) return;

	//give n colors, get n-1 pairs
	//(n-1,0), (n-2,1), ... , (1,0);


	int cc = 8 < count ? 8 : count;
	int pc = cc - 1;

	int i;

	for (i = 0; i < cc; i++)
	{
		init_color(i,reds[i], greens[i], blues[i]);
	}

	for (i = 0; i < pc; i++)
	{
		init_pair(1 + i, pc - i, 0);
	}

	matrix::Terminal::paletteSize = pc;
}

int matrix::Terminal::getPaletteSize()
{
	return matrix::Terminal::paletteSize;
}




void matrix::Terminal::blank()
{
	if (!matrix::Terminal::initialized) return;

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
	if (!matrix::Terminal::initialized) return;
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
	if (!matrix::Terminal::initialized) return;
	if (y < 0 || y > rows) return;
	if (x < 0 || x > cols) return;

	mvaddch(y,x,c | COLOR_PAIR(color));
	move(0,0);
}


/* USER INTERFACE THREAD STUFF */

int matrix::Terminal::stopflag = 0;

void matrix::Terminal::UIwatcher()
{
	int key;
	do {
		key = getch();
		if (key == 'q')
		{
			matrix::Terminal::stopflag = 1;
		}

		else
		{
			key = ERR;
		}
	} while (key == ERR);
}

int matrix::Terminal::done()
{
	return matrix::Terminal::stopflag;
}

