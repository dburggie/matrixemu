//namespace matrixemu
#include <Terminal.h>
#include <Matrix.h>
#include <debug.h>

//namespace std
#include <cstdlib>  //std::srand()
#include <ctime>    //std::time()
#include <iostream> //std::cerr

using namespace matrixemu;

int main()
{
	//seed the prng
	std::srand(std::time(NULL));

	//turn on curses mode
	Terminal::init();

	Matrix m;
	m.run(1000);

	Terminal::end();

	return 0;

}
