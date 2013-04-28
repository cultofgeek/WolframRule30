/*////////////////////////////////////////////////////////////
Cellular Automata by Won You

This program simulates Rule 30 of Stephen Wolfram's cellular
automata. The theory here is quite simple. We start off with
some initial state provided by a 1-dimensional world.
State's are either alive or dead, represented by a "*" or a
blank character " ".  The next generation of this world is
then printed on the next line.  Here's where Rule 30 comes in.
There are 8 possible transition states. A new cell's state is
determined by the state of the 3 cells adjacent to it from the
previous generation.

For example, 
Let's look at how the cell state for the cell at index1 for
gen1 would be determined.  

indices: 0123456
gen0:   " * "
gen1:   "***"

We start off by examining the cells directly above it, which
is the cells in gen0 (short for generation 0). The states
are dead, alive, dead.  We have a rule that states that 
this will yield an alive state.  Therefore, it would be set to
alive. Notice that if we're at the edge, say at index0, we have 
no third cell directly adjacent to it on the left-hand side, so 
we take that to be dead.

The code is fairly straight-forward.  It takes in one 
command line argument.  Typing a filename after the name
of the program will cause the program to read in the 
initial start state from the file.  I haven't added any
sort of error-handling in the program.
///////////////////////////////////////////////////////////*/

#include <iostream>
#include <cstdlib>
#include "cell.h"

using namespace std;

int main(int argc, char* argv[]){

    int      nrows=50,
	     ncols=20,
	     generations=1;  /*This is completely useless
                               because the number of rows 
                               determines the number of generations */
    char     answer='y';

    /*Use the command line argument to specify a file with 
      a custom start state*/ 
    if (argc>1){
       CellAutomata wolfram;
       wolfram.getCmd(argc, argv);
       wolfram.readWorld();

       wolfram.setGen(generations);
       wolfram.animate();
    }
    else{
    while (answer!='q'){
        cout << "How many rows? ";  /*The rows represents the number of generations*/
	cin >> nrows;		       
        cout << "How many columns? ";
	cin >> ncols;		       

        CellAutomata wolfram(nrows, ncols, generations);

        /*The world is initialized to a random start state*/
        wolfram.initializeWorld();   	
	wolfram.print();
        wolfram.animate();  

        cout << "\nPress q to quit: ";
        cin >> answer;
    }

   }
return EXIT_SUCCESS;
}