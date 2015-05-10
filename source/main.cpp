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

	debug("std::srand() success");

	//turn on curses mode
	Terminal::init();

	debug("matrixemu::Terminal::init() success");

	Matrix m;
	debug("matrixemu::Matrix::Matrix() success");

	m.run(200);
	debug("matrixemu::Matrix::run() success");

	//turn off curses mode
	Terminal::end();
	debug("matrixemu::Terminal::end() success");

	return 0;

}
