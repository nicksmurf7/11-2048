/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Modified by: Nicolas Murphy
 * Date: 13 March 2019
 */

#include <iostream>
#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;

// CONSTANTS (IF ANY) GO HERE

// FUNCTION PROTOTYPES GO HERE
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);
void play();
void current_board(int board[4][4],int score);
void addRand(int board[4][4]);
void createBoard();
void move(char input,int board[4][4],int score);
void left(int board[4][4],int score);
void right(int board[4][4],int score);
void up(int board[4][4],int score);
void down(int board[4][4],int score);
void print(int board[4][4],int score);
void scorecalc(int score);
void check(int board[4][4]);
void addRandStart(int board[4][4]);
bool possible_move(int board[4][4]);
void scoreboard(int board[4][4]);
bool testfor0(int board[4][4]);

int main() {
    play();
    return 0;
}

void play() {
    // START YOUR CODE HERE
  srand(time(0));
  cout << "Welcome to 2048." << endl;
  createBoard();
}

/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
     return result;
}
/* Converts an int to string.
 * Returns the string form of the given int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}

/* Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}

//This creates the board with two random numbers at the beginning and calls
//the recursive function current board,  which keeps the game going. 
void createBoard(){
  int board[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };
  int score = 0;
  addRandStart(board);
  print(board,score);
  current_board(board,score);
}


//This randomly picks two spots on the initial, blank board to put
//two 2s. 
void addRandStart(int board[4][4]){
  int B;
  int C;
  B = (rand() % 4);
  C = (rand() % 4);
  if (board[B][C] == 0) {
    board[B][C] = 2;
  }
  int D;
  int E;
  D = (rand()%4);
  E = (rand()%4);
  if (board[D][E] == 0){
    board[D][E] = 2;
  }
  else
    addRandStart(board);
}

//This function checks the board for an open space to add a new number.
bool testfor0(int board[][4]){
  int counter = 0;
  for(int r = 0; r < 4; r++){
    for(int c  = 0; c < 4; c++){
      if(board[r][c] ==  0){
	counter++;
      }
    }
  }
      if(counter > 0){
	return true;
      }
      else{
	return false;
      }
    }

//This randomly finds and picks an empty spot on the board to put
//either a 2 or 4, with a 10% chance of a 4. 
void addRand(int board[][4]) {
  if (testfor0(board) == true){
    int B;
    int D;
    B = (rand() % 4);
    D = (rand() % 4);
    int S;
    int a;
    S = (rand() % 100 + 1);
    if ( S < 90 ){
      a = 2;
    }
    if ( S >= 90 ){
      a = 4;
    }
    if ( board[B][D] ==  0){
      board[B][D]  = a;
    }
    else if ( board[B][D] != 0){
      addRand(board);
    }
  } 
  if(testfor0(board) == false){
}
}

//Allows the user to input 'a' or 'd' until the game is over and
//prints the board  after every move.
void current_board(int board[4][4],int score) {
  check(board);
  char input;
  cout << "Please enter 'w','a','s' or 'd'" << endl;
  cin >> input;
  move(input,board,score);
  print(board,score);
}


//This reads the user input and calls the function matching
//what the user wants to do to the board (left or right)
void move(char input, int board[4][4],int score){
  if ( input == 'a' || input == 'A' ) {
    left(board,score);
  }
  if ( input == 'd' || input == 'D' ) {
    right(board,score);
  }
  if ( input == 's' || input == 'S' ) {
    down(board,score);
  }
  if ( input == 'w'  || input == 'W' ) {
    up(board,score);
  }
  if ( input == 'q' || input == 'Q'  ) {
    exit(1);
  }
  else
    cout << "Invalid Input." << endl;
  current_board(board,score);
}


//This function firsts shifts all of the current elements on the board
//to the left, then combines them. It also calls the function
//to check if  the game is over. It then recursively calls
//current_board to continue the game.  
void left(int board[4][4],int score){
  for (int r = 3; r > -1; r--){
    for (int i = 0; i < 4; i++){
    for (int n = 1; n < 4; n++){
      if (board[r][i] == 0 && board[r][n] != 0 && n > i){
	board[r][i] = board[r][n];
	board[r][n] = 0;
      }
    }
  }
    check(board);
  bool neglectable = false;
  for (int i = 0; i < 3; i++){
    for (int n = 1; n < 3; n++){
      if ( board[r][i] == board[r][i + 1] ){
        board[r][i] = 2 * board[r][i];
        board[r][i+1] = 0;
	score = score + board[r][i];
        neglectable = true;
      }
      if ( board[r][n] != 0 && n > i + 1 && neglectable){
	board[r][i + 1] = board[r][n];
	board[r][n] = board[r][n+1];
	board[r][n+1] = 0;
      }
    }
  }
  }
  check(board);
  addRand(board);
  print(board,score);
  current_board(board,score);
}


//This function firsts shifts all of the current elements on the board      
//to the right, then combines them. It also calls the function   
//to check if  the game is over. It then recursively calls                 
//current_board to continue the game.                                       
void right(int board[4][4],int score){
  for (int r = 3; r > -1; r--){
  for (int i = 3; i > -1; i--){
    for (int n = 2; n > -1; n--){
      if (board[r][i] == 0 && board[r][n] != 0 && i > n){
        board[r][i] = board[r][n];
        board[r][n] = 0;
      }
  }
  }
  check(board);
  bool neglectable = false;
  for (int i = 3; i > 0; i--){
    for (int n = 2; n > 0; n--){
      if ( board[r][i] == board[r][i - 1] ){
        board[r][i] = 2 * board[r][i];
        board[r][i - 1] = 0;
	score = score + board[r][i];
        neglectable = true;
      }
      if ( board[r][n] != 0 && n < i - 1 && neglectable){
        board[r][i - 1] = board[r][n];
        board[r][n] = board[r][n-1];
	board[r][n-1] = 0;
      }
    }
  }
  }
  check(board);
  addRand(board);
  print(board,score);
  current_board(board,score);
}


//This function first shifts all of the current elements on the baord
//upwards, then combines them. It also calls the function
//to check if the game is over. It then recursively calls
//current_board to continue the game. 
void up(int board[4][4],int score){
  for (int c = 0; c < 4; c++){
    for (int i = 0; i < 4; i++){
      for (int n = 1; n < 4; n++){
	if (board[i][c] == 0 && board[n][c] != 0 && n > i){
	  board[i][c] = board[n][c];
	  board[n][c] = 0;
	}
      }
    }
    check(board);
    bool neglectable = false;
    for (int i = 0; i < 3; i++){
      for (int n = 1; n < 3; n++){
	if (board[i][c] == board[i+1][c]){
	  board[i][c] = 2 * board[i][c];
	    board[i+1][c] = 0;
	    score = score + board[i][c];
	    neglectable = true;
	  }
	if (board[n][c] != 0 && n > i + 1 && neglectable){
	    board[i+1][c] = board[n][c];
	    board[n][c] = board[n+1][c];
	    board[n+1][c] = 0;
	  }
      }
    }
  }
  check(board);
  addRand(board);
  print(board,score);
  current_board(board,score);
}


//This function first shifts all of the current elements on the board
//downwards, then combines them. It also calls the function
//to check if the game is over. It then recursively calls
//current_board to continue the game. 
void down(int board[4][4],int score){
  for(int c = 3; c > -1; c--){
    for(int i = 3; i > -1; i--){
      for(int n = 2; n > -1; n--){
	if( board[i][c] == 0 && board[n][c] != 0 && i > n){
	  board[i][c] = board[n][c];
	  board[n][c] = 0;
	}
      }
    }
    check(board);
    bool neglectable = false;
    for(int i = 3; i > 0; i--){
      for(int n = 2; n > 0; n--){
	if( board[i][c] == board[i - 1][c] ){
	  board[i][c] = 2 * board[i][c];
	  board[i-1][c] = 0;
	  score = score + board[i][c];
	  neglectable = true;
	}
	if (board[n][c] != 0 && n < i - 1 && neglectable){
	  board[i-1][c] = board[n][c];
	  board[n][c] = board[n-1][c];
	  board[n-1][c] = 0;
	}
      }
    }
  }
  check(board);
  addRand(board);
  print(board,score);
  current_board(board,score);
}
	   



//This function checks if the user is able to move. 
//If not, then the game is ended.
void check(int board[4][4]){
 int counter = 0;
 for (int i = 0; i < 4; i++){
   for(int n = 0; n < 3; n++){
     if(board[i][n] != 0 && board[i][n+1] != 0){
       if(board[i][n] != board[i][n+1]){
	 counter++;
       }
     }
   }
 }
 for(int i = 0; i < 3; i++){
   for(int n = 0; n < 4; n++){
     if(board[i][n] != 0 && board[i+1][n] != 0){
       if(board[i][n] != board[i+1][n]){
	 counter++;
       }
     }
   }
 }
 if(counter == 24 && possible_move(board) == true){
     cout<< "Game over! You will never beat me." <<  endl;
     exit(1);
   }
 else if(possible_move(board) == false){
    }
}

//This is a helper function for the check(board) function
bool possible_move(int board[][4]){
  for(int i = 1; i < 3; i++){
    for(int n = 1; n < 3; n++){
      if((board[i][n] != 0)){
      if (board[i][n] != board[i+1][n]){
	if(board[i][n] != board[i][n+1]){
	    if(board[i][n] != board[i-1][n]){
	      if(board[i][n] != board[i][n-1]){
		return true;
	      }
	    }
	  }
	  }
      }
	else
	  return false;
  }
}
  return 0;
}

//This function turns the score into a string and prints it.
void scorecalc(int score){
  string result;
  result = int2string(score);
  cout << "Current Score: " << result << endl;
}


//This function prints the board.
void print(int board[][4],int score){
  scorecalc(score);
  for (int n = 0; n < 4; n++){
    for (int i = 0; i < 4; i++){
      if (board[n][i] == 0) {
	print_padded_string("-");
    }
    else{
      // ADD SCORECALCULATOR                                               
      print_padded_string(int2string(board[n][i]));
    }
    }
    cout << endl;
  }
}


