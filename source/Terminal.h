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
			static int delay;

		public:
			~Terminal();
			
			static void init();
			static void end();
			static void makePalette(int count, int reds[], int greens[], int blues[]);

			static void blank();
			static void draw();
			static void pause();

			static void getSize(int & y, int & x);

			static void output(int y, int x, int c);
			static void output(int y, int x, int c, int color);
	};
}

#endif
