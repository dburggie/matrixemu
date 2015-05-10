#include <Terminal.h>

using namespace matrixemu;

int main()
{
	Terminal::init();

	Terminal t;

	t.blank();
	int i;
	for (i = 0; i < 10; i++)
		t.output(0,i,0x30+i,0);//ascii numeral
	for (i = 0; i < 26; i++)
	{
		t.output(1,i,0x41+i,0);//ascii upper case
		t.output(2,i,0x61+i,0);//ascii lower case
	}
	t.draw();

	t.pause(3000);

	t.blank();
	t.draw();

	Terminal::end();

	return 0;
}
