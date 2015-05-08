#include <cstdlib>
#include <Column.h>
#include <Terminal.h>

//constructor
matrix::Column::Column(
		matrix::Column * head, 
		int column, 
		int speed, 
		int length, 
		int height
	) //end parameters
{
	this->insert(head);

	this->column = column;
	this->speed = speed;
	this->length = length;
	this->position = 0;

	this->height = height;

	this->buffer = new int[height];


	//fill buffer with random characters
	int i, c;
	for (i = 0; i < height; i++)
	{
		c = rand() % (10 + 26 + 26);
		if (c < 10) c += 0x30; //make ascii number
		else if (c < 10 + 26) c += 0x40; //make ascii upper case
		else if (c < 10 + 26 + 26) c += 0x60; //make ascii lower case
		else c = (int) '?'; //this shouldn't happen
		buffer[i] = c;
	}
}

matrix::Column::~Column()
{
	if (this == this->head)
	{
		while (this->next != this) delete this->next;
	}

	else
	{
		this->remove();
	}

	delete [] buffer;
}

void matrix::Column::insert(matrix::Column * head)
{
	if (head)
	{
		head = head->head;
		this->head = head;
		this->next = head;
		this->prev = head->prev;
		this->prev->next = this;
		head->prev = this;
	}

	else
	{
		this->head = head;
		this->next = this;
		this->prev = this;
	}
}

/*
#ifndef _COLUMN_H
#define _COLUMN_H

		private:
			Column * first;
			Column * next;
			Column * prev; 

			int column; //what terminal column this Column draws to
			int speed; //number of hundredths to wait for the next increment
			int length; //how long the tail is
			int position; //how far down the head is

			int buffer[];

		public:
			Column(Column * list, int column, int speed, int length);
			~Column();

			void increment();

			void insert(Column * list);
			void remove();

			void draw(int maxY);
*/
