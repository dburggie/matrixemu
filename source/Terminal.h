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
			static int paletteSize;

			//user interface stop flag
			static int stopflag;
			static void UIwatcher();

		public:
			~Terminal();
			
			static void init();
			static void end();
			static void makePalette(int count, int reds[], int greens[], int blues[]);
			static int getPaletteSize();

			static int colors(); //0 if no color, -1 if no change color, 1 otherwise

			static void blank();
			static void draw();
			static void pause();
			static void pause(int ms); //delay for at least ms milliseconds

			static void getSize(int & y, int & x);

			static void output(int y, int x, int c);
			static void output(int y, int x, int c, int color);

			//returns 1 iff execution must stop now
			static int done();
	};
}

#endif
