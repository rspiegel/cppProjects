#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "maze.h"

using namespace std;

int main()
{
	maze x;
	x.parse_board(cin);
	x.run();
	x.print_board(cout);
	return 0;
}