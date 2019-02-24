#include <iostream>
#include <fstream>

#include "parser.h"


/// The main entry point for the application
/// argc - the number of command line parameters.  This will always be at least 1
/// argv - the command line parameters.  The first parameter is always the name of the application
int main(int argc, char** argv)
{
	// To run the program, it requires 3 command line parameters:
	// argv[0] - the application name
	// argv[1] - the input file to check
	// argv[2] - the output file for the results
	if (argc != 3)
	{
		std::cout << "Usage:  assignment02 [input file] [output file]" << std::endl;
		return 0;
	}

	// Create the input stream
	std::ifstream fin(argv[1]);

	// Create the output stream
	std::ofstream fout(argv[2]);

	Parser parser(fin, fout);
	parser.Check();

	return 0;
}
