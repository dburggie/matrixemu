//namespace matrixemu
#include <Terminal.h>
#include <Matrix.h>

//namespace std
#include <cstdlib> //std::srand()
#include <ctime>   //std::time()

using namespace matrixemu;

int main()
{
	//seed the prng
	std::srand(std::time(NULL));

	//turn on curses mode
	Terminal::init();

	Matrix m;
	m.run(200);

	//turn off curses mode
	Terminal::end();

	return 0;

}
