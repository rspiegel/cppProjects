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
#include "gtest/gtest.h"

using namespace std;

/**
* Our AbstractCell Class, is extended by ConwayCell and FredkinCell.
* Has Cell as friend class so that cell can access the members of the children that it points to.
* Has Life as friend class so that life can access the members of the children.
* protected members:
* member type: the type that this cell is, aka Conway or Fredkin.
* member alive: if the cell is alive, 1 for alive, 0 for dead.
* member age: the age of the cell(not used in ConwayCell).
* member next_state: the next state of the cell. set after first pass of the board to check if the cell will be alive next generation or not.
* virtual methods:
* nextState: takes in teh 8 directions around it and calculates if it will be alive or dead next generation
* printSelf: takes in an ostream variable and tells the cell to print itself
* switchStates: sets it's alive status to the status of next_state
* clone: takes in a char which represents what kind of cell it is and clones itself
*/
class AbstractCell
{
public:
  char type;
  int alive;
  char age;
  int next_state;

	virtual void nextState(int n, int ne, int e, int se, int s, int sw, int w, int nw) = 0;
	virtual void printSelf(ostream& w) = 0;
	virtual void switchStates() = 0;
  virtual AbstractCell* clone(char type) = 0;
	virtual ~AbstractCell() {};
};

/**
* Our ConwayCell class, extends the AbstractCell class publicly
* Char constructor: constructor which takes in the character taken from the input and decides what it's alive status will be. also sets type to 'c' which means it's a ConwayCell
* nextState: takes in the 8 directions around the cell and computes what it's alive status will be on the next generation
* printSelf: takes in an ostream variable and uses that to print itself
* switchStates: sets it's alive status to be it's next_state's status
* clone: takes in a char and returns a clone of itself using that char with the char constructor and returns an AbstractCell pointer.
*/
class ConwayCell : public AbstractCell
{
public:
	ConwayCell(char t)
	{
		type = 'c';
		if(t == '.')
			alive = 0;
		else
			alive = 1;
	}
	void nextState (int n, int ne, int e, int se, int s, int sw, int w, int nw);
	void printSelf(ostream& w);
	void switchStates();
  AbstractCell* clone(char type);
	~ConwayCell() {};
};

/**
* Our FredkinCell class, publicly extends AbstractCell
* Char constructor: constructor which takes in the character taken from the input and decides what it's alive status will be and it's age. also sets type to 'c' which means it's a ConwayCell
* nextState: takes in the 8 directions around the cell(ONLY USES THE 4 CARDINAL DIRECTIONS) and computes what it's alive status will be on the next generation
* printSelf: takes in an ostream variable and uses that to print itself
* switchStates: sets it's alive status to be it's next_state's status
* clone: takes in a char and returns a clone of itself using that char with the char constructor and returns an AbstractCell pointer.
*/

class FredkinCell : public AbstractCell
{
public:
	FredkinCell(char t)
	{
		type = 'f';
		if(t == '-')
		{
			age = '0';
			alive = 0;
		}
		else
		{
			age = t;
			alive = 1;
		}
	}
	void nextState(int n, int ne, int e, int se, int s, int sw, int w, int nw);
	void printSelf(ostream& w);
	void switchStates();
  AbstractCell* clone(char type);
  ~FredkinCell() {};
};

/**
* Our Cell Class, the handler for AbstractCell class
* has Life as a friend class so that life can access it's private variables
* private variables:
* p: a pointer to an AbstractCell
* type: the type of the cell pointed to by p, either c for Conway or f for Fredkin
* alive: the alive status of the cell that is pointed at by p
* next_state: the next state of the cell that is pointed at by p
* age: the age of the cell that is pointed at by p
* methods:
* char constructor: takes in a char and makes a cell of the corresponding type/age and sets p to point to it
* cell constructor: takes in a cell and clones it to create a new one
* nextState: calls the nextState method of the cell pointed at by p
* printSelf: calls the printSelf method of the cell pointed at by p
* switchStates: calls the switchStates method of the cell pointed at by p
* ~destructor: calls delete on p in order to free the memory that it is taking up
*/

class Cell
{
  FRIEND_TEST(CellTest, constructor_1);
  FRIEND_TEST(CellTest, constructor_2);
  FRIEND_TEST(CellTest, constructor_3);
  FRIEND_TEST(CellTest, copy_constructor_1);
  FRIEND_TEST(CellTest, copy_constructor_2);
  FRIEND_TEST(CellTest, copy_constructor_3);
  FRIEND_TEST(CellTest, equal_1);
  FRIEND_TEST(CellTest, equal_2);
  FRIEND_TEST(CellTest, next_state_1);
  FRIEND_TEST(CellTest, next_state_2);
  FRIEND_TEST(CellTest, next_state_3);
  FRIEND_TEST(CellTest, next_state_4);
  FRIEND_TEST(CellTest, switch_state_1);
  FRIEND_TEST(CellTest, switch_state_2);
  FRIEND_TEST(CellTest, switch_state_3);
  FRIEND_TEST(CellTest, switch_state_4);

private:
	template <typename CellType>
	friend class Life;
	AbstractCell* p = nullptr;
  	char type;
	int alive;
	int next_state;
	char age;
public:
  Cell(char t) {
    type = t;
    alive = 0;
    switch(type)
    {
      case '.':
      case '*':
        p = new ConwayCell(type);
        break;
      default:
        p = new FredkinCell(type);
        break;
    }
    alive = p->alive;
    next_state = p->next_state;
    age = '0';
  }
  Cell(const Cell& cell) {
    type = cell.type;
    alive = cell.alive;
    next_state = cell.next_state;
    age = cell.age;
    p = cell.p->clone(type);
  };

	AbstractCell* operator =(AbstractCell* rhs);
	void nextState(int n, int ne, int e, int se, int s, int sw, int w, int nw);
	void printSelf(ostream& w);
	void switchStates();

  ~Cell() {
    delete(p);
  }
};

/**
* Our life class, manages the board and all of the cells
* private variables: 
* board: our board of type CellType, which is passed in with the creation of a Life object through the template
* cell_type: the type of cell that the board is made of, used to decide some actions in Life
* rows: the number of rows in the board
* columns: the number of columns in the board
* num_evos: the number of iterations that the board should go through
* out_freq: the frequency in which the board should be printed
* cur_gen: the current generation that the board is on
* num_alive: the number of alive cells in the board
* methods:
* begin: returns a vector<CellType> iterator which is the first position on the board
* end: returns a vector<CellType> iterator which is the last position on the board
* at: takes in x/y coordinates and returns the cell that is at the position
* addCells: takes in a line from the input file and turns them all into cells
* runLife: runs through the number of iterations required and computes all of the cell's different states, sets them, and prints the board/extra data when necessary
* printBoard: loops through the board calling each cells printSelf method
* countAlive: counts the number of alive cells in the board
*/

template <typename CellType>
class Life {
  FRIEND_TEST(LifeTest, constructor_1);
  FRIEND_TEST(LifeTest, constructor_2);
  FRIEND_TEST(LifeTest, constructor_3);
  FRIEND_TEST(LifeTest, end_3);
  FRIEND_TEST(LifeTest, add_cells_1);
  FRIEND_TEST(LifeTest, add_cells_2);
  FRIEND_TEST(LifeTest, add_cells_3);
  FRIEND_TEST(LifeTest, count_alive_1);
  FRIEND_TEST(LifeTest, count_alive_2);
  FRIEND_TEST(LifeTest, count_alive_3);
  FRIEND_TEST(LifeTest, count_alive_4);
  FRIEND_TEST(LifeTest, count_alive_5);

private:
  vector<CellType> board;
  string cell_type;
  int rows;
  int columns;
  int num_evos;
  int out_freq;

  int cur_gen;
  int num_alive;
public:
  Life(string type, int row, int column, int evolution, int frequency) {
    cell_type = type;
    rows = row;
    columns = column;
    num_evos = evolution;
    out_freq = frequency;
    cur_gen = 0;
    num_alive = 0;
  }

  typename vector<CellType>::iterator begin() {
    return board.begin();
  }

  typename vector<CellType>::iterator end() {
    return board.end();
  }

  CellType at(int x, int y) {
    return board[y + (x * columns)];
  }

  void addCells(string line) {
    for (string::iterator it = line.begin(); it != line.end(); ++it) {
      CellType temp_cell(*it);
      board.push_back(temp_cell);
    }
}

  void runLife(ostream &w) {
    for (cur_gen = 0; cur_gen <= num_evos; ++cur_gen) {
      countAlive();
      if (cur_gen == 0 || cur_gen % out_freq == 0) {
        printBoard(w);

      }
      for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < columns; ++y) {
          int n = 0, ne = 0, e = 0, se = 0, s = 0, sw = 0, w = 0, nw = 0;
          if (x == 0);
          else if (at(x - 1, y).alive) //n
            n = 1;
          if (x == 0 || y == columns - 1);
          else if (at(x - 1, y + 1).alive) //ne
            ne = 1;
          if (y == columns - 1);
          else if (at(x, y + 1).alive) //e
            e = 1;
          if (y == columns - 1 || x == rows - 1);
          else if (at(x + 1, y + 1).alive) //se
            se = 1;
          if (x == rows - 1);
          else if (at(x + 1, y).alive) //s
            s = 1;
          if (x == rows - 1 || y == 0);
          else if (at(x + 1, y - 1).alive) //sw
            sw = 1;
          if (y == 0);
          else if (at(x, y - 1).alive) //w
            w = 1;
          if (x == 0 || y == 0);
          else if (at(x - 1, y - 1).alive) //nw
            nw = 1;
          board[y + (columns * x)].nextState(n, ne, e, se, s, sw, w, nw);
        }
      }
      for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < columns; ++y) {
          board[y + (columns * x)].switchStates();
        }
      }
    }
  }

  void printBoard(ostream &w) {
    w << "Generation = " << cur_gen << ", Population = " << num_alive << "." <<endl;
    for (int x = 0; x < rows; ++x) {
      for (int y = 0; y < columns; ++y) {
        board[y + (columns * x)].printSelf(w);
      }
      w << endl;
    }
    if(cur_gen != num_evos)
      w << endl;
  }

  void countAlive() {
    num_alive = 0;
    for (int i = 0; i < board.size(); i++) {
      if (board[i].alive)
        num_alive++;
    }
  }
  ~Life()

	{
  		board.clear();
  	}
};