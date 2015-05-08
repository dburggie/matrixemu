#include <cstdlib>
#include <ctime>
#include <Terminal.h>



int itoc(int c)
{
	c %= 10 + 26 + 26;

	if (c < 10) c += 0x30;
	else if (c < (10 + 26)) c += 0x41 - 10;
	else if (c < (10 + 26 + 26)) c += 0x61 - 10 - 26;

	return c;
}




int main()
{
	matrix::Terminal::init();

	std::srand(std::time(NULL));

	int rows,cols,y,x,c,i;
	matrix::Terminal::getSize(rows,cols);

	for (i = 0; i < 10; i++) matrix::Terminal::output(0,i,itoc(i));
	for (i = 0; i < 26; i++) matrix::Terminal::output(1,i,itoc(i+10));
	for (i = 0; i < 26; i++) matrix::Terminal::output(2,i,itoc(i+10+26));
	matrix::Terminal::pause();

	for (i = 0; i < 100; i++)
	{
		c = std::rand() % (10 + 26 + 26);
		if (c < 10) c += 0x30;
		else if (c < (10 + 26)) c += 0x40 - 10;
		else if (c < (10 + 26 + 26)) c += 0x60 - 10 - 26;
		else c = (int) '?';

		x = std::rand() % cols;
		y = std::rand() % rows;

		matrix::Terminal::blank();
		matrix::Terminal::output(y,x,c);
		matrix::Terminal::draw();
		matrix::Terminal::pause();
	}

	matrix::Terminal::end();
	return 0;
}
