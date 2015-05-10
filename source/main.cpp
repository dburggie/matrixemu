//namespace matrixemu
#include <Terminal.h>
#include <Matrix.h>
#include <debug.h>

//namespace std
#include <cstdlib>  //std::srand() std::atoi() std::exit()
#include <ctime>    //std::time()
#include <iostream> //std::cout

using namespace matrixemu;

static void usage(int argc, const char * argv[]); //calls exit(1)

int main(int argc, const char *argv[])
{
	if (argc > 2)
	{
		usage(argc,argv);
	}

	int frames = 1000;

	if (argc == 2)
	{
		frames = 40 * std::atoi(argv[1]);
		if (!frames)
		{
			usage(argc,argv);
		}
	}

	//seed the prng
	std::srand(std::time(NULL));

	//turn on curses mode
	Terminal::init();

	Matrix m;
	m.run(frames);

	Terminal::end();

	return 0;
}


static void usage(int argc, const char * argv[])
{
	if (argc == 2)
	{
		std::cout << "    \"" << argv[1] << "\" could not be interpreted as an integer.\n";
	}
	std::cout << "    Usage: " << argv[0] << " [approx. run time in seconds]\n";

	std::exit(1);
}
