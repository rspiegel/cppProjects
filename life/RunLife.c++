#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Life.h"

using namespace std;

int main()
{
	string temp = ""; 						// a temporary variable, used to cin a line and add cells to life's board
	string cell_type = ""; 					// the type of cells that is being created in Life
  	int row = 0; 							// the number of rows in the board
	int column = 0; 						// the number of columns in the board
	int num_evos = 0; 						// the number of evolutions that the cells should go through
	int out_freq = 0; 						// the frequency that the test should be printed
	while(cin.good()) 						// while you aren't at EOF and skipping blank lines
	{
		cin >> cell_type; 					// get cell_type
		cin >> row; 						// get num rows
		cin >> column; 						// get num columns
		cin >> num_evos; 					// get number of evolutions
		cin >> out_freq; 					// get output frequency
		cout << "*** Life<" << cell_type << "> " << row << "x" << column << " ***" << endl<<endl; // print out relevant information about the test

		if(cell_type == "ConwayCell") 		// check if the board is being constructed with ConwayCells
		{
			Life<ConwayCell> x(cell_type, row, column, num_evos, out_freq); // create a life object with all of the information
			for(int i = 0; i < row; ++i)// loop through number of rows
			{
				cin >> temp;
				x.addCells(temp); 			// add cells to the board
			}
			x.runLife(cout); 				// once all cells are added to the board, run it.
		}
		else if(cell_type == "FredkinCell") // check if the board is being constructed with FredkinCells
		{
			Life<FredkinCell> x(cell_type, row, column, num_evos, out_freq); // create a life object with all of the information
      		for(int i = 0; i < row; ++i)	// loop through number of rows
			{
				cin >> temp;
        		x.addCells(temp); 			// add cells to the board
			}
			x.runLife(cout); 				// once all cells are added to the board, run it.
		}
		else if(cell_type == "Cell") 		// check if the board is being constructed with Cells
		{
			Life<Cell> x(cell_type, row, column, num_evos, out_freq); // create a life object with all of the information
      		for(int i = 0; i < row; ++i)	// loop through number of rows
			{
				cin >> temp;
        		x.addCells(temp); 			// add cells to the board
			}
			x.runLife(cout); 				// once all cells are added to the board, run it.
		}
    if(cin.good()) 							// as long as we aren't at EOF, print a new line
      cout << endl;
	}
	return 0;
}