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

/**
* ConwayCell's printSelf method, if the cell is alive then print out a '*', if it's dead print out a '.'
* @param w the ostream variable that it is passed and is used to print itself 
*/
void ConwayCell::printSelf(ostream& w)
{
    if(this->alive)
		w << '*';
  else
		w << '.';
}

/**
* FredkinCell's printself method, if the cell is dead print out a '-', if the cell is alive, check it's age, if it is >9 then print out a '+', else print it's age
* @param w the ostream variable that it is passed in order to print itself 
*/
void FredkinCell::printSelf(ostream& w)
{
	if(this->alive)
		if(this->age > '9')
			w << '+';
		else
			w << this->age;
	else
		w << '-';
}

/**
* ConwayCell's nextState method, takes in the alive state of it's surroundings and calculates what it's next state will be.
* if it is alive and it has 2 or 3 neighbors then it will stay alive, if it is dead and it has 3 alive neighbors then it will become alive, otherwise the cell will die
* @param n the alive status of the cell's north neighbor
* @param ne the alive status of the cell's northeast neighbor
* @param e the alive status of the cell's east neighbor
* @param se the alive status of the cell's southeast neighbor
* @param s the alive status of the cell's south neighbor
* @param sw the alive status of the cell's southwest neighbor
* @param w the alive status of the cell's west neighbor
* @param nw the alive status of the cell's northwest neighbor
*/
void ConwayCell::nextState(int n, int ne, int e, int se, int s, int sw, int w, int nw)
{
	int neighbors = n+ne+e+se+s+sw+w+nw;
	if(this->alive && (neighbors == 3 || neighbors == 2))
	{
		this->next_state = 1;
	}
	else if (!this->alive && neighbors == 3)
	{
		this->next_state = 1;
	}
	else
	{
		this->next_state = 0;
	}
}

/**
* ConwayCell's switchStates method, when called it sets it's alive status to be the status of the nest_state variable 
*/
void ConwayCell::switchStates()
{
	this->alive = this->next_state;
}

/**
* ConwayCell's clone method, takes in a char which is the char taken from the board and returns a clone of itself
* @param type the char taken from the board, used to determine the alive status of the initial cell
* @return an AbstractCell* to the ConwayCell that has been created 
*/
AbstractCell* ConwayCell::clone(char type) {
  return new ConwayCell(type);
}

/**
* FredkinCell's nextstate method, takes in the alive statuses of the neighboring cells and determines it's next state.
* if it was dead and has 1 or 3 neighbors it become alive, if it was alive and has 1 or 3 neighbors it stays alive and increments it's age otherwise it dies.
* @param n the alive status of the cell's north neighbor
* @param ne the alive status of the cell's northeast neighbor *** NOT USED
* @param e the alive status of the cell's east neighbor
* @param se the alive status of the cell's southeast neighbor *** NOT USED
* @param s the alive status of the cell's south neighbor
* @param sw the alive status of the cell's southwest neighbor *** NOT USED
* @param w the alive status of the cell's west neighbor
* @param nw the alive status of the cell's northwest neighbor *** NOT USED
*/
void FredkinCell::nextState(int n, int ne, int e, int se, int s, int sw, int w, int nw)
{
	int neighbors = n+e+s+w;
	if(!this->alive && (neighbors == 1 || neighbors == 3))
	{
		this->next_state = 1;
	}
	else if(this->alive && (neighbors == 1 || neighbors == 3))
	{
		this->next_state = 1;
		if(age <= '9')
			this->age++;
	}
	else
	{
		this->next_state = 0;
	}
}

/**
* FredkinCell's switchStates method, sets it's alive status to be the value of the next_state variable 
*/
void FredkinCell::switchStates()
{
	this->alive = this->next_state;
}

/**
* FredkinCell's clone method, takes in a char and creates a new FredkinCell based on that char
* @param type the char taken off the board, used to determine it's age and alive status
* @return an AbstractCell pointer to the cell that was newly created 
*/
AbstractCell* FredkinCell::clone(char type) {
  return new FredkinCell(type);
}

/**
* Cell's printSelf method, calls the printSelf method of the pointer that it holds
* @param w the ostream variable used by the cell pointed to by p in order to print itself 
*/
void Cell::printSelf(ostream& w)
{
	this->p->printSelf(w);
}

/**
* Cell's nextState method, takes in the alive statuses of the cells around the cell and determines it's next_state
* Cell calls the nextState method on the cell pointed to by pointer p. after doing so set all of this cells variables to match the cell pointed to by p.
* if the cell that p is pointing at is age 2, delete p and make a new alive conwaycell
* @param n the alive status of the cell's north neighbor
* @param ne the alive status of the cell's northeast neighbor
* @param e the alive status of the cell's east neighbor
* @param se the alive status of the cell's southeast neighbor
* @param s the alive status of the cell's south neighbor
* @param sw the alive status of the cell's southwest neighbor
* @param w the alive status of the cell's west neighbor
* @param nw the alive status of the cell's northwest neighbor
*/
void Cell::nextState(int n, int ne, int e, int se, int s, int sw, int w, int nw)
{
	this->p->nextState(n, ne, e, se, s, sw, w, nw);
	this->alive = this->p->alive;
	this->next_state = this->p->next_state;
	if(this->p->type == 'f')
		this->age = this->p->age;
	if(this->age == '2')
	{
		delete p;
		p = new ConwayCell('*');
	}
}

/**
* Cell's assignment operator, sets this cell to be pointing at a clone of the rhs
* @param rhs the cell that this cell is being set to equal
* @return an AbstractCell point that points to the new p that has just been set by clone 
*/
AbstractCell* Cell::operator =(AbstractCell* rhs)
{
  this->p = rhs->clone(this->type);
	return p;
}

/**
* Cell's switchStates method, sets this cells alive status to be the status of the next_state variable
* and call the switchStates method of the cell pointed at by p 
*/
void Cell::switchStates()
{
	this->alive = this->next_state;
	this->p->switchStates();
}