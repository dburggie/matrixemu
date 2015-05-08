#include <Terminal.h>

using namespace matrix;

int main()
{
	Terminal::init();
	int i;

	int r[8], g[8], b[8];
	for ( i = 0; i < 8; i++ )
	{
		r[i] = 0;
		g[i] = 1000 * i / 8;
		b[i] = 0;
	}

	Terminal::makePalette(8,r,g,b);


	for ( i = 0; i < 8; i++ )
	{
		Terminal::output(4,4+i,i+0x30,i);
	}

	Terminal::draw();

	Terminal::pause();

	Terminal::end();
	return 0;
}
/*
#ifndef TERMINAL_H
#define TERMINAL_H

#include <ncurses.h>
namespace matrix
{
	class Terminal
	{
		private:
			Terminal();
			static int initialized;
			static int rows;
			static int cols;

		public:
			~Terminal();
			
			static void init();
			static void end();
			static void makePalette(int count, int reds[], int greens[], int blues[]);

			static void blank();
			static void draw();
			static void output(int y, int x, int c);
			static void output(int y, int x, int c, int color);
	};
}

#endif
*/
