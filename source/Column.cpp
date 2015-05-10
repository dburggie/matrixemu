#include <Column.h>
#include <Terminal.h>
#include <cstdlib>

using namespace matrixemu;

static int randomc()
{
	int c = std::rand() % (10 + 26 + 26);

	if (c < 10) return c + 0x30; //ascii numeral	
	else c -= 10;

	if (c < 26) return c + 0x41; //ascii upper case
	else c -= 26;

	if (c < 26) return c + 0x61; //ascii lower case
	else return '?';
}



Column::Column(Terminal * term, int xpos)
{
	this->ypos = 0;
	this->xpos = xpos;
	this->speed = 1; //update every tick
	this->buffer = NULL;
	this->setLength(10); //sets len and ymin
	this->setTerminal(term); //sets term, ymax, buffer
	this->done = (this->ymin < this->ymax);
}

Column::~Column()
{
	if (this->buffer)
	{
		delete [] buffer;
	}
}

//private
void Column::increment()
{
	this->ypos++;
	this->ymin++;
	this->done = (this->ymin < this->ymax);
}

void Column::setLength(int len)
{
	if (len < 1) len = 1;
	this->len = len;
	this->ymin = 1 + this->ypos - this->len;

	if (this->buffer) delete [] this->buffer;

	this->buffer = new int [len];

	int i;
	for (i = 0; i < len; i++)
	{
		this->buffer[i] = randomc();
	}

}

void Column::setSpeed(int speed) { this->speed = speed; }
int Column::getSpeed() { return this->speed; }
int Column::offscreen() { return this->done; }

void Column::draw(int timestamp)
{
	if (this->done || !this->term) return;

	int colors = term->getPaletteSize(); //palette should be bright to dim 0 - n
	int charsPerColor = this->len / colors;
	if (this->len % colors) charsPerColor++;

	int i, y, x = this->xpos;

	for (i = 0; i < this->len; i++)
	{
		y = this->ypos - i;
		if (y < 0) break;
		if (y - i > this->ymax) continue;

		this->term->output(y-i,x,this->buffer[y], i/charsPerColor);
	}

	if (timestamp % this->speed == 0) this->increment();
}
