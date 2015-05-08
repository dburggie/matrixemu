#ifndef _COLUMN_H
#define _COLUMN_H

namespace matrix
{
	// this class is a circular linked list of column data
	class Column
	{
		private:
			Column * head;
			Column * next;
			Column * prev; 

			int column; //what terminal column this Column draws to
			int speed; //number of hundredths to wait for the next increment
			int length; //how long the tail is
			int position; //how far down the head is
			int height; //how many rows in the terminal

			int offscreen; //signals the Column is ready to be deleted

			int * buffer;

		public:
			Column(int column, int height);
			~Column();

			int increment();

			void insert(Column * list);
			void setSpeed(int speed); //number of ticks before increment
			int getSpeed();
			void setLength(int length);

			int isOffscreen();

			Column * remove();

			void draw();
			static void drawAll(Column * head);
	};
}

#endif
