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
