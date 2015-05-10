#include <Terminal.h>

using namespace matrixemu;

int main()
{
	Terminal::init();

	Terminal t;

	t.blank();
	t.output(0,0,42);
	t.draw();

	t.pause(1000);

	t.blank();
	t.draw();

	Terminal::end();

	return 0;
}
