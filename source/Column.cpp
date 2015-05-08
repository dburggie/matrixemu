#include <cstdlib>
#include <Column.h>
#include <Terminal.h>


static int rtoc(int r)
{
	r %= 10 + 26 + 26;
	if (r < 10) return r + 0x30;
	r -= 10;
	if (r < 26) return r + 0x41;
	r -= 26;
	return r + 0x61;
	
}

//constructor
matrix::Column::Column(int column, int height)
{
	this->head = this;
	this->next = this;
	this->prev = this;

	this->column = column;
	this->speed = 0;
	this->length = 10;
	this->position = 0;
	this->height = height;

	this->buffer = NULL;

	this->offscreen = 0;
	if (this->height <= 0) this->offscreen = 1;
	else this->buffer = new int[height];

	//fill buffer with random characters
	int i, c;
	for (i = 0; i < height; i++)
	{
		c = rtoc(std::rand() % (10 + 26 + 26));
		if (this->buffer) this->buffer[i] = c;
	}
}



void matrix::Column::setSpeed(int speed)
{
	this->speed = speed;
}



void matrix::Column::setLength(int length)
{
	if (length < 0) length = 0;
	this->length = length;
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





int matrix::Column::increment()
{
	this->position++;

	if (1 + this->position - this->length >= this->height)
	{
		this->offscreen = 1;
	}

	return this->offscreen;
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


matrix::Column * matrix::Column::remove()
{
	//if next == this, there're no nodes left after removal
	if (this == this->next) return NULL;

	//to accomplish the removal, we must do two things:
	//	1) unlink the node
	//	2) adjust the head pointer of all nodes if this one is the head

	//unlink the node
	this->next->prev = this->prev;
	this->prev->next = this->next;


	//adjust the head node if this is head
	matrix::Column * head = this->head;

	if (this == head)
	{
		head = this->next;
		matrix::Column * node = this->next->next;
		head->head = head;
		while (head != node)
		{
			node->head = head;
			node = node->next;
		}
	}

	this->head = this;
	this->next = this;
	this->prev = this;

	return head;
}


int matrix::Column::isOffscreen()
{
	return this->offscreen;
}


void matrix::Column::draw()
{
	if (this->offscreen) return;

	//we start at (position,column) and draw upwards
	int i;
	
	int x = this->column;
	int y = this->position;

	for (i = 0; i < this->length; i++)
	{
		if (y-i >= this->height) continue;
		if (y-i < 0) break;
		matrix::Terminal::output(y-i,x,this->buffer[y-i]);
	}
}








void matrix::Column::drawAll(matrix::Column * head)
{
	head = head->head;

	//never draw the head
	matrix::Column * node = head->next;
	matrix::Column * tmp = NULL;

	while (node != head)
	{
		node->draw();
		tmp = node;
		node = node->next;
		if (tmp->increment())
		{
			tmp->remove();
			delete tmp;
			tmp = NULL;
		}
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
