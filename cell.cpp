/////////////////    cell.h    ////////////////

#include <iomanip>
#include <windows.h>
#include "cell.h"

using namespace std;

//----------------------------------------
//  Clrscr :  This clears the screen, but it
//            only works for Windows.  There's
//            a clear screen function you can 
//            call in Unix, in which case you
//            comment this function and the 
//            windows header file out
//----------------------------------------
void CellAutomata::clrscr() 
{ 
    COORD coordScreen = { 0, 0 }; 
    DWORD cCharsWritten; 
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD dwConSize; 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    
    GetConsoleScreenBufferInfo(hConsole, &csbi); 
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, 
        coordScreen, &cCharsWritten); 
    GetConsoleScreenBufferInfo(hConsole, &csbi); 
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, 
        coordScreen, &cCharsWritten); 
    SetConsoleCursorPosition(hConsole, coordScreen); 
}

void CellAutomata::wait( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * (CLK_TCK/50) ;
  while (clock() < endwait) {}
}

void CellAutomata::initializeWorld()
{

srand(time(0));

int randomizer=boundedRand(0, 1); 

 	for (int j=0; j<ncol; j++){
		
   		   randomizer=boundedRand(0, 1); 
   		   
		   if (randomizer == 1)
			world[0][j] = ' ';
		   else
		    world[0][j] = '*';
		

	}

                
}  

/* Print out the cells onto the screen */
void CellAutomata::print(){


    cout << "\n";
    for ( int a=0; a<ncol; a++)
	cout << "-" ; 
    cout << endl;       
                 
	for (int i=0; i<nrow; i++){

        cout << setw(7);
		for (int j=0; j<ncol; j++){
		
			cout << world[i][j];
		
		}
			cout << '\n';
	}

    cout << "\n";
    for ( int b=0; b<ncol; b++)
	cout << "-" ; 
    cout << endl;                
}  


//---------------------------------------------------
//  Next State: look up the states in the rules
//              there are 8 possible combinations
//              and hence 8 rules.  
//---------------------------------------------------
char CellAutomata::nextState(int rowPos, int colPos)
{
   int i,j, count=0, 
   state[3]={1,1,1};  // State 1 implies the cell is dead
                      // State 2 implies the cell is alive
                      // State 0 implies the cell is in an unknown state 

   
   // Examine the 3 cells directly above it
   if ( valid(rowPos-1,colPos-1) ){
	state[0] = giveState(rowPos-1,colPos-1);	      
   }
   if ( valid(rowPos-1,colPos) ){
	state[1] = giveState(rowPos-1,colPos);	      
   }
   if ( valid(rowPos-1,colPos+1) ){
	state[2] = giveState(rowPos-1,colPos+1);	      
   }   
        
   //The main 8 possible transition states: 

   if (state[0]==2 && state[1]==2 && state[2]==2)
	return ' ';
   if (state[0]==2 && state[1]==2 && state[2]==1)
	return ' ';
   if (state[0]==2 && state[1]==1 && state[2]==2)
	return ' ';
   if (state[0]==2 && state[1]==1 && state[2]==1)
	return '*';
   if (state[0]==1 && state[1]==2 && state[2]==2)
	return '*';
   if (state[0]==1 && state[1]==2 && state[2]==1)
	return '*';
   if (state[0]==1 && state[1]==1 && state[2]==2)
	return '*';
   if (state[0]==1 && state[1]==1 && state[2]==1)
	return ' ';   
   else return '!';  // we have encountered something strange
                     // display a error symbol
     
}//end of nextState


void CellAutomata::setWorld()  
{

    //for each cell, examine what it's next state should be
    //then store that result into a temporary matrix
   	for (int i=1; i<nrow; i++){
   		for (int j=0; j<ncol; j++){
		    world[i][j] = nextState(i,j); 
		}
	}

		
	// }
  
}//end of setWorld

//----------------------------------------------------
// Grab the arguments and set the output file
//----------------------------------------------------
void CellAutomata::getCmd( int argc, char* argv[] ){

   bool fail = false;

   //Make sure there are at least 2 arguments
   if ( argc == 2 ) {

      infile.open(argv[1]);
      fail = !infile;
   }	 
 
   
   if (fail) {
      cout << "Error: The file could not be read\n";
      exit(1);
   }

}


//-----------------------------------------------------------
// initialize the maze matrix to the one contained in the file 
//-----------------------------------------------------------
int CellAutomata::readWorld ( )
{

   int i = 0, j;    // Row and column indices.
   int flag = 0;    // Return value is 0 if file is ok.
   char c;
   nrow = 0; ncol = 0;

   while ( infile && i < N_ROWS_MAX )     // Get the next row
    {
      j = 0; // Column index.
      while ( infile.get(c) && c != '\n' && j < N_COLS_MAX )  
      {
         world[i][j] = c;                   // Next character of maze
         ++j;
      }
      if (j > ncol) 
          ncol = j;            // Count the number of columns in the maze
                               //   (allows non-rectangular mazes).
      if ( infile )     
         ++i;
    }
    nrow= i;                  // Count the number of rows
    
// ---------------------------------------
//  Check Error Conditions.
// ---------------------------------------
    if ( nrow >= N_ROWS_MAX || ncol >= N_COLS_MAX )
    {
       cerr << "Sorry, my " << N_ROWS_MAX << " x " << N_COLS_MAX 
            << " array isn't big enough to hold your maze.\n";
       flag = 1;
    }
    return flag;
}

// The name of this function is misleading. All it does is
// computes the next state of the world and displays it.
void CellAutomata::animate(){

  	       setWorld();                      
               clrscr();
 	       print();

}

