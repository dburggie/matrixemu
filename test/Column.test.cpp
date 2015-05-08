#include <Terminal.h>
#include <Column.h>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(time(NULL)); //seed the rng in Column

	matrix::Terminal::init();

	int rows,cols;
	matrix::Terminal::getSize(rows,cols);

	int i;
	matrix::Column * column = NULL;

	for (i = 0; i < 10; i++)
	{
		column = new matrix::Column(NULL,std::rand() % cols,0,4,rows);
		do {
			matrix::Terminal::blank();
			column->draw();
			matrix::Terminal::draw();
			matrix::Terminal::pause();
		} while (!column->increment());

		delete column;
		column = NULL;
	}

	matrix::Terminal::end();

	return 0;
}


