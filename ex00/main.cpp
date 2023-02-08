#include "Convert.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Too many argument\n";
		return (1);
	}
	
	Convert a(argv[1]);

	a.cast();
	a.print();

	return (0);
}
