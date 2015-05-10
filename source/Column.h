#ifndef _COLUMN_H
#define _COLUMN_H

#include <Terminal.h>

namespace matrixemu
{
	// this class is a circular linked list of column data
	class Column
	{
		private:
			int ypos;  //y position of head
			int xpos;  //x position of head
			int speed; //ticks per increment
			int len;   //height of column
			int ymin;  //y position of tail
			int ymax;  //the first y position that is offscreen
			int done;  //flags that the column is offscreen and can be deleted

			matrixemu::Terminal * term; //terminal in which we will draw
			int * buffer; //characters in the column

			//private methods
			void increment();

		public:
			Column(matrixemu::Terminal * term, int xpos);
			~Column();


			void setSpeed(int speed); //number of ticks before increment
			int getSpeed();
			void setLength(int length);
			void setTerminal(matrixemu::Terminal * term);

			int offscreen(); //returns 1 if no longer prints

			void draw(int timestamp); //automatically increments after speed ticks
	};
}

#endif
