#ifndef TERMINAL_H
#define TERMINAL_H

namespace matrixemu
{
	class Terminal
	{
		private:
			static int initialized;
			static void init();
			static void end();
			static void UIwatcher(void * terminal);

			int rows;
			int cols;
			int paletteSize;
			int stopflag;

			int ** screen;
			int *  palette;


		public:
			Terminal();
			~Terminal();


			void makePalette(int count, int reds[], int greens[], int blues[]);
			int getPaletteSize();

			int colors(); //0 if no color, -1 if no change color, 1 otherwise

			void blank();
			void draw();

			void pause(int ms); //delay for at least ms milliseconds

			void getSize(int & y, int & x);

			int output(int y, int x, int c);
			int output(int y, int x, int c, int color);

			//returns 1 iff execution must stop now
			int done();
	};
}

#endif
