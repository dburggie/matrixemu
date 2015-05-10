#ifndef _MATRIX_H
#define _MATRIX_H

#include <Terminal.h>
#include <Column.h>
#include <Linker.h>

namespace matrixemu
{
	class Matrix
	{
		private:
			Terminal * terminal;
			Linker<Column> * columns;

			void drawFrame(int timestamp);
			void addNewColumn();

		public:
			Matrix();
			~Matrix();

			void run(int frames);
	};
}

#endif
