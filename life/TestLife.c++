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
#include "gtest/gtest.h"

using namespace std;

TEST(LifeTest, constructor_1) {
  Life<ConwayCell> life("ConwayCell", 2, 3, 1, 1);
  ASSERT_EQ(2, life.rows);
}

TEST(LifeTest, constructor_2) {
  Life<FredkinCell> life("FredkinCell", 2, 3, 1, 1);
  ASSERT_EQ(2, life.rows);
}

TEST(LifeTest, constructor_3) {
  Life<Cell> life("Cell", 2, 3, 1, 1);
  ASSERT_EQ("Cell", life.cell_type);
}

TEST(LifeTest, begin_1) {
  Life<ConwayCell> life("ConwayCell", 2, 3, 1, 1);
  vector<ConwayCell>::iterator it = life.begin();
  life.addCells("...");
  ASSERT_EQ(it, it);
}

TEST(LifeTest, end_1) {
  Life<ConwayCell> life("ConwayCell", 2, 3, 1, 1);
  vector<ConwayCell>::iterator it = life.end();
  ASSERT_EQ(it, it);
}

TEST(LifeTest, at_1) {
  Life<ConwayCell> life("ConwayCell", 1, 3, 1, 1);
  string temp = "*..";
  life.addCells(temp);
  ostringstream oss;
  life.at(0, 0).printSelf(oss);
  ASSERT_EQ("*", oss.str());
}

TEST(LifeTest, at_2) {
  Life<FredkinCell> life("FredkinCell", 1, 3, 1, 1);
  string temp = "-0-";
  life.addCells(temp);
  ostringstream oss;
  life.at(0, 1).printSelf(oss);
  ASSERT_EQ("0", oss.str());
}

TEST(LifeTest, at_3) {
  Life<Cell> life("Cell", 3, 3, 0, 1);
  string temp = "...";
  life.addCells(temp);
  temp = "-0-";
  life.addCells(temp);
  temp = "...";
  life.addCells(temp);
  ostringstream oss;
  life.at(1, 1).printSelf(oss);
  ASSERT_EQ("0", oss.str());
}

TEST(LifeTest, add_cells_1) {
  Life<ConwayCell> life("ConwayCell", 1, 3, 1, 1);
  string temp = "*..";
  life.addCells(temp);
  ASSERT_EQ(3, life.board.size());
}

TEST(LifeTest, add_cells_2) {
  Life<Cell> life("Cell", 3, 3, 1, 1);
  string temp = "...";
  life.addCells(temp);
  temp = "*0*";
  life.addCells(temp);
  temp = "...";
  life.addCells(temp);
  ASSERT_EQ(9, life.board.size());
}

TEST(LifeTest, add_cells_3) {
  Life<Cell> life("Cell", 3, 5, 1, 1);
  string temp = ".....";
  life.addCells(temp);
  temp = ".*0*.";
  life.addCells(temp);
  temp = ".....";
  life.addCells(temp);
  ASSERT_EQ(15, life.board.size());
}

TEST(LifeTest, run_life_1) {
  Life<ConwayCell> life("ConwayCell", 1, 3, 0, 0);
  string temp = "*..";
  life.addCells(temp);
  ostringstream oss;
  life.runLife(oss);
  ASSERT_EQ("Generation = 0, Population = 1.\n*..\n", oss.str());
}

TEST(LifeTest, run_life_2) {
  Life<Cell> life("Cell", 3, 3, 1, 1);
  string temp = "...";
  life.addCells(temp);
  temp = "*0*";
  life.addCells(temp);
  temp = "...";
  life.addCells(temp);
  ostringstream oss;
  life.runLife(oss);
  ASSERT_EQ("Generation = 0, Population = 3.\n...\n*0*\n...\n\nGeneration = 1, Population = 2.\n.*.\n.-.\n.*.\n", oss.str());
}

TEST(LifeTest, run_life_3) {
  Life<Cell> life("Cell", 3, 5, 1, 1);
  string temp = ".....";
  life.addCells(temp);
  temp = ".*0*.";
  life.addCells(temp);
  temp = ".....";
  life.addCells(temp);
  ostringstream oss;
  life.runLife(oss);
  ASSERT_EQ("Generation = 0, Population = 3.\n.....\n.*0*.\n.....\n\nGeneration = 1, Population = 2.\n..*..\n..-..\n..*..\n", oss.str());
}

TEST(LifeTest, print_board_1) {
  Life<ConwayCell> life("ConwayCell", 1, 3, 0, 0);
  string temp = "*..";
  life.addCells(temp);
  ostringstream oss;
  life.printBoard(oss);
  ASSERT_EQ("Generation = 0, Population = 0.\n*..\n", oss.str());
}

TEST(LifeTest, print_board_2) {
  Life<FredkinCell> life("FredkinCell", 1, 3, 0, 0);
  string temp = "-0-";
  life.addCells(temp);
  ostringstream oss;
  life.printBoard(oss);
  ASSERT_EQ("Generation = 0, Population = 0.\n-0-\n", oss.str());
}

TEST(LifeTest, print_board_3) {
  Life<Cell> life("Cell", 1, 3, 0, 0);
  string temp = "-*-";
  life.addCells(temp);
  ostringstream oss;
  life.printBoard(oss);
  ASSERT_EQ("Generation = 0, Population = 0.\n-*-\n", oss.str());
}

TEST(LifeTest, count_alive_1) {
  Life<ConwayCell> life("ConwayCell", 1, 3, 1, 1);
  string temp = "*..";
  life.addCells(temp);
  life.countAlive();
  ASSERT_EQ(1, life.num_alive);
}

TEST(LifeTest, count_alive_2) {
  Life<FredkinCell> life("FredkinCell", 2, 3, 1, 1);
  string temp = "-0-";
  life.addCells(temp);
  temp = "000";
  life.addCells(temp);
  life.countAlive();
  ASSERT_EQ(4, life.num_alive);
}

TEST(LifeTest, count_alive_3) {
  Life<Cell> life("Cell", 1, 3, 1, 1);
  string temp = "*.0";
  life.addCells(temp);
  life.countAlive();
  ASSERT_EQ(2, life.num_alive);
}

TEST(LifeTest, count_alive_4) {
  Life<Cell> life("Cell", 1, 3, 1, 1);
  string temp = "*.0";
  life.addCells(temp);
  temp = "***";
  life.addCells(temp);
  life.countAlive();
  ASSERT_EQ(5, life.num_alive);
}

TEST(LifeTest, count_alive_5) {
  Life<Cell> life("Cell", 1, 3, 1, 1);
  string temp = "*.0";
  life.addCells(temp);
  temp = ".--";
  life.addCells(temp);
  life.countAlive();
  ASSERT_EQ(2, life.num_alive);
}

TEST(ConwayTest, constructor_1) {
  ConwayCell cell('.');
  ASSERT_EQ(0, cell.alive);
}

TEST(ConwayTest, constructor_2) {
  ConwayCell cell('*');
  ASSERT_EQ(1, cell.alive);
}

TEST(ConwayTest, constructor_3) {
  ConwayCell cell('.');
  ASSERT_EQ('c', cell.type);
}

TEST(ConwayTest, next_state_1) {
  ConwayCell cell('.');
  cell.nextState(0,0,0,0,0,0,0,0);
  ASSERT_EQ(0, cell.next_state);
}

TEST(ConwayTest, next_state_2) {
  ConwayCell cell('.');
  cell.nextState(0,1,0,0,1,1,0,1);
  ASSERT_EQ(0, cell.next_state);
}

TEST(ConwayTest, next_state_3) {
  ConwayCell cell('.');
  cell.nextState(0,1,0,0,1,1,0,0);
  ASSERT_EQ(1, cell.next_state);
}

TEST(ConwayTest, next_state_4) {
  ConwayCell cell('.');
  cell.nextState(1,1,1,1,1,1,1,1);
  ASSERT_EQ(0, cell.next_state);
}

TEST(ConwayTest, print_1) {
  ConwayCell cell('*');
  ostringstream oss;
  cell.printSelf(oss);
  const char ret = oss.str().c_str()[0];
  ASSERT_EQ('*', ret);
}

TEST(ConwayTest, print_2) {
  ConwayCell cell('.');
  ostringstream oss;
  cell.printSelf(oss);
  const char ret = oss.str().c_str()[0];
  ASSERT_EQ('.', ret);
}

TEST(ConwayTest, switch_state_1) {
  ConwayCell cell('.');
  cell.nextState(0,0,0,0,0,0,0,0);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(ConwayTest, switch_state_2) {
  ConwayCell cell('.');
  cell.nextState(0,1,0,0,1,1,0,1);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(ConwayTest, switch_state_3) {
  ConwayCell cell('.');
  cell.nextState(0,1,0,0,1,1,0,0);
  cell.switchStates();
  ASSERT_EQ(1, cell.alive);
}

TEST(ConwayTest, switch_state_4) {
  ConwayCell cell('.');
  cell.nextState(1,1,1,1,1,1,1,1);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(ConwayTest, clone_1) {
  ConwayCell cell('*');
  AbstractCell* cp = cell.clone('*');
  ASSERT_EQ(cp->type, cell.type);
  delete (cp);
}

TEST(ConwayTest, clone_2) {
  ConwayCell cell('*');
  AbstractCell* cp = cell.clone('.');
  ASSERT_EQ(cp->type, cell.type);
  delete (cp);
}

TEST(ConwayTest, clone_3) {
  ConwayCell cell('.');
  AbstractCell* cp = cell.clone('.');
  ASSERT_EQ(cp->type, cell.type);
  delete (cp);
}

TEST(FredkinTest, constructor_1) {
  FredkinCell cell('-');
  ASSERT_EQ(0, cell.alive);
}

TEST(FredkinTest, constructor_2) {
  FredkinCell cell('0');
  ASSERT_EQ(1, cell.alive);
}

TEST(FredkinTest, constructor_3) {
  FredkinCell cell('-');
  ASSERT_EQ('f', cell.type);
}

TEST(FredkinTest, next_state_1) {
  FredkinCell cell('-');
  cell.nextState(0,0,0,0,0,0,0,0);
  ASSERT_EQ(0, cell.next_state);
}

TEST(FredkinTest, next_state_2) {
  FredkinCell cell('-');
  cell.nextState(0,1,0,0,1,1,0,1);
  ASSERT_EQ(1, cell.next_state);
}

TEST(FredkinTest, next_state_3) {
  FredkinCell cell('-');
  cell.nextState(1,1,1,0,1,1,0,0);
  ASSERT_EQ(1, cell.next_state);
}

TEST(FredkinTest, next_state_4) {
  FredkinCell cell('-');
  cell.nextState(1,1,1,1,1,1,1,1);
  ASSERT_EQ(0, cell.next_state);
}

TEST(FredkinTest, print_1) {
  FredkinCell cell('0');
  ostringstream oss;
  cell.printSelf(oss);
  const char ret = oss.str().c_str()[0];
  ASSERT_EQ('0', ret);
}

TEST(FredkinTest, print_2) {
  FredkinCell cell('-');
  ostringstream oss;
  cell.printSelf(oss);
  const char ret = oss.str().c_str()[0];
  ASSERT_EQ('-', ret);
}

TEST(FredkinTest, switch_state_1) {
  FredkinCell cell('-');
  cell.nextState(0,0,0,0,0,0,0,0);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(FredkinTest, switch_state_2) {
  FredkinCell cell('-');
  cell.nextState(0,1,0,0,1,1,0,1);
  cell.switchStates();
  ASSERT_EQ(1, cell.alive);
}

TEST(FredkinTest, switch_state_3) {
  FredkinCell cell('-');
  cell.nextState(1,1,1,0,1,1,0,0);
  cell.switchStates();
  ASSERT_EQ(1, cell.alive);
}

TEST(FredkinTest, switch_state_4) {
  FredkinCell cell('-');
  cell.nextState(1,1,1,1,1,1,1,1);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(FredkinTest, clone_1) {
  FredkinCell cell('0');
  AbstractCell* cp = cell.clone('0');
  ASSERT_EQ(cp->type, cell.type);
  delete (cp);
}

TEST(FredkinTest, clone_2) {
  FredkinCell cell('0');
  AbstractCell* cp = cell.clone('-');
  ASSERT_EQ(cp->type, cell.type);
  delete (cp);
}

TEST(FredkinTest, clone_3) {
  FredkinCell cell('0');
  AbstractCell* cp = cell.clone('-');
  ASSERT_EQ(cp->age, cell.age);
  delete (cp);
}

TEST(CellTest, constructor_1) {
  Cell cell('*');
  ASSERT_EQ(1, cell.alive);
}

TEST(CellTest, constructor_2) {
  Cell cell('0');
  ASSERT_EQ(1, cell.alive);
}

TEST(CellTest, constructor_3) {
  Cell cell('-');
  ASSERT_EQ('-', cell.type);
}

TEST(CellTest, copy_constructor_1) {
  Cell cell('.');
  Cell cell2(cell);
  ASSERT_EQ(cell.type, cell2.type);
}

TEST(CellTest, copy_constructor_2) {
  Cell cell('*');
  Cell cell2(cell);
  ASSERT_EQ(cell.type, cell2.type);
}

TEST(CellTest, copy_constructor_3) {
  Cell cell('0');
  Cell cell2(cell);
  ASSERT_EQ(cell.type, cell2.type);
}

TEST(CellTest, equal_1) {
  Cell cell('.');
  Cell cell2('-');
  delete(cell.p);
  cell = cell2;
  ASSERT_EQ(cell.alive, cell2.alive);
}

TEST(CellTest, equal_2) {
  Cell cell('*');
  Cell cell2('0');
  delete(cell.p);
  cell = cell2;
  ASSERT_EQ(cell.alive, cell2.alive);
}

TEST(CellTest, next_state_1) {
  Cell cell('*');
  cell.nextState(0,0,0,0,0,0,0,0);
  ASSERT_EQ(0, cell.next_state);
}

TEST(CellTest, next_state_2) {
  Cell cell('-');
  cell.nextState(0,1,0,0,1,1,0,1);
  ASSERT_EQ(1, cell.next_state);
}

TEST(CellTest, next_state_3) {
  Cell cell('*');
  cell.nextState(1,1,1,0,1,1,0,0);
  ASSERT_EQ(0, cell.next_state);
}

TEST(CellTest, next_state_4) {
  Cell cell('-');
  cell.nextState(1,1,1,1,1,1,1,1);
  ASSERT_EQ(0, cell.next_state);
}

TEST(CellTest, print_1) {
  Cell cell('0');
  ostringstream oss;
  cell.printSelf(oss);
  const char ret = oss.str().c_str()[0];
  ASSERT_EQ('0', ret);
}

TEST(CellTest, print_2) {
  Cell cell('*');
  ostringstream oss;
  cell.printSelf(oss);
  const char ret = oss.str().c_str()[0];
  ASSERT_EQ('*', ret);
}

TEST(CellTest, switch_state_1) {
  Cell cell('.');
  cell.nextState(0,0,0,0,0,0,0,0);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(CellTest, switch_state_2) {
  Cell cell('-');
  cell.nextState(0,1,0,0,1,1,0,1);
  cell.switchStates();
  ASSERT_EQ(1, cell.alive);
}

TEST(CellTest, switch_state_3) {
  Cell cell('*');
  cell.nextState(1,1,1,0,1,1,0,0);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

TEST(CellTest, switch_state_4) {
  Cell cell('.');
  cell.nextState(1,1,1,1,1,1,1,1);
  cell.switchStates();
  ASSERT_EQ(0, cell.alive);
}

