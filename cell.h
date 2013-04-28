/////////////////    cell.h    ////////////////

#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

const int N_ROWS_MAX=50;   /* The hard-coded limits of the matrix */
const int N_COLS_MAX=50;


class CellAutomata{

public:
  CellAutomata() : nrow(N_ROWS_MAX), ncol(N_COLS_MAX){}
  CellAutomata(int row, int col, int gen) : 
                nrow(row), ncol(col), gen(gen)
  {
    for (int i=0; i<nrow; i++)
      for (int j=0; j<ncol; j++)
	world[i][j]=' ';
  }
  void clrscr();
  virtual void initializeWorld();
  void print();
  void getCmd(int argc, char* argv[]);
  void wait(int seconds); 
  virtual void animate();
  virtual char nextState(int x, int y);
  virtual void setWorld();
  int readWorld();
  void setGen( int g ) { gen = g; }

  int giveState(int rowPos, int colPos){

   //Rule1: The current cell is dead      		
   if (world[rowPos][colPos] == ' ')
	 return 1;   

   //Rule2: The current cell is alive
   else if (world[rowPos][colPos] == '*')
     return 2;

   else return 0;
  }


  int roundme( double x ){
    return  static_cast<int> ( x >= 0 ? x + 0.5 : x - 0.5 );
  }

  int boundedRand(int lower, int upper) {
   // Generates a random integer in the given interval [lower, upper]. 
   // Avoids using rand()%n, since the low-end bits of the 
   // output of rand() are often not reliably random; Stroustrup p.685.

    return roundme( (double(rand())/double(RAND_MAX))*(upper-lower) + lower);
  }

  bool valid(int i, int j)
    {
	return(i >= 0 && i < nrow && j >= 0 && j < ncol);
    }


private:
  ifstream infile;
  int nrow;
  int ncol;
  int gen;  //the number of generations
  char world[N_ROWS_MAX][N_COLS_MAX];
  
};

#endif