/**
@File : rushhour.cpp
@Author: Ryan Kim
@Version: 1
@Brief: This file includes the implementation of all of the functions required to use an inputted car's information to place it on a 6x6
		board and solves it and outputs the minimal number of turns to solve.
@Detail: This program gets an input from the console to be used carCount. While the carCount is greater than 0, a board is dynamically 
allocated to be of size 6x6, which is only dynamically allocated in order to pass the board through functions by address. The board is then passed into 
the function loadBoard which then takes care of the inputs and places the inputted cars onto the board. Various functions are created in order to return 
the different details of the car while only passing in the board and the car number in these respective functions. All of these functions are then 
utilized to make functions that will move the car forwards and backwards, and then a recursive function is called which moves each car forwards or 
backwards one at a time until a solution is found.
@date: Wednesday, October 4, 2017
**/

//
//HEADER FILES/////////////////////////////////////////
//
#include <iostream>
using namespace std;

/** void loadBoard();
 * This function will place the cin 'd cars onto the 6x6 board.
 * 
 * This function will take in an input for the length of the car, orientation of the car, and the row and column coordinates of the northernmost (if  
 * vertical) or westernmost (if horizontal) cell of the car that it takes up. These inputs are taken as many times as there are cars, and the digits 
 *variable is used to indicate the car number. A function is called as the condition of an if statement to show whether or not the car can be placed, and 
 *if there is enough space for the car to be placed, a for loop will be called that will account for the length of the vehicle by incrementing 2 or 3 
 *times from the row or column position, depending on the orientation. 
 *
 *@param char** board	the board used to initialize 
 *@return void
 *@pre The board is uninitialized
 *@post The grid will be initialized
 */
void loadBoard(char** board, int carCount);

/**
 * This function will analyze the board and search for a specific car and if it is orientated veritcally or horizontally on the board.
 * 
 * This function will take in the board and car number. The coordinates, held by two int's: x, y, call the getCar_row and getCar_col functions respectively, and will use them to locate the head of the car on the board. A nested if statement, one to account for out of bounds, and one that checks the condition that the next cell in the next row or column contains the same number as the previous cell. This check will either return H or V, for horizontal and vertical.
 * 
 *
 *@param char** board, int carNum		passes in board to be analyzed, passes in carNum to know which car to search for
 *@return char
 *@pre The board has cars on it
 *@post Car #carNum 's orientation can be accessed through this function
 */
char getCarOrientation(char** board, int carNum);

/**
 * This function will analyze the board and will search for the first instance of an element in the board that matches carNum
 * 
 * This function will take in the board and car number. Two integers are defined, i and j, to 0. A while loop checks the condition that board[i][j] is 
 * not equal to carNum, and that i does not go out-of-bounds, or greater than 6. While this loop runs, j is incremented, and when j is larger than 5, it
 * will be reinitialized to 0, and i will increment. As this is the function to return the row, i is returned.
 * 
 *@param char** board, int carNum		passes in board to be analyzed, passes in carNum to know which car to search for
 *@return int
 *@pre The board has cars on it
 *@post Car #carNum 's row coordinate can be accessed through this function
 */
int getCar_row(char** board, int carNum);

/**
 * This function will analyze the board and will search for the first instance of an element in the board that matches carNum
 * 
 * This function will take in the board and car number. Two integers are defined, i and j, to 0. A while loop checks the condition that board[i][j] is 
 * not equal to carNum, and that i does not go out-of-bounds, or greater than 6. While this loop runs, j is incremented, and when j is larger than 5, it
 * will be reinitialized to 0, and i will increment. As this is the function to return the column, j is returned.
 * 
 *@param char** board, int carNum		passes in board to be analyzed, passes in carNum to know which car to search for
 *@return int
 *@pre The board has cars on it
 *@post Car #carNum 's column coordinate can be accessed through this function
 */
int getCar_col(char** board, int carNum);

/**
 * This function will analyze the board and make sure that a car placed in its position will not go out of bounds or overlap another car.
 * 
 * This function will take in all of the car's information as well as the board itself. An if statement chooses the action between a horizontally or 
 * vertically orientated car. Depending on the car's orientation, another if statement will make sure that the row or column number of the car's initial 
 * position is in the bounds of the board and 1 or 2 spaces to the right or down are blank spaces and are also inside the bounds of the board. If and 
 *only if all of these conditions are met, then the function will return true.
 * 
 *@param char ** board, int row, int col, int length, char orientation	
 *@return bool
 *@pre board must be initialized
 *@post a bool that is returned will represent if there is enough space to place a specific car with specific coordinates, length, and orientation
 */
bool enoughSpaceToPlace( char ** board, int row, int col, int length, char orientation);

 /**
 * This function will read the board for a specific car and determine whether the car's length is 2 or 3
 * 
 * This function will search for a car. Utilizing a function defined earlier, the orientation of the car will determine which way the function will 
 * search along the board. If the orientation is horizontal, an if statement will check to see if the car is occupying an index 2 spaces to the right, 
 * and also make sure that this index is not outside of the bounds of the board. If the statement is true, then the length will be 3, or else the length 
 * must be 2. This check is similar if the orientation is vertical in that it will check if the car is occupying the index 2 spaces south of the starting 
 * position. 
 *
 *@param char ** board, int carNum
 *@return int
 *@pre the board must have cars on it
 *@post n/a
 */
int getCarLength(char** board, int carNum);

/**
 * This function will analyze a board and check if the car whose number matches the carnumber has an empty space in front of it to move into.
 * 
 * This function finds the coordinates, length, and orientation of car #carNum using the functions that were already defined to return these values. 
 * Using this information, this function uses an if statement to divide the check between orientations, and checks to see if the space that is its length 
 * distance away (either downwards or to the right) from its coordinate is an empty space and inside the bounds of the board. It will return the result 
 * of this check. 
 * 
 *@param char ** board, int carNum
 *@return bool
 *@pre board must have cars on it
 *@post n/a
 */
bool CanMoveForward(char** board, int carNum);

/**
 * This function will analyze a board and check if the car whose number matches the carnumber has an empty space in front of it to move into.
 * 
 * This function finds the coordinates, length, and orientation of car #carNum using the functions that were already defined to return these values. 
 * Using this information, this function uses an if statement to divide the check between orientations, and checks to see if the space that is its length 
 * distance away (either upwards or to the left) from its coordinate is an empty space and inside the bounds of the board. It will return the result 
 * of this check. 
 * 
 *@param char ** board, int carNum
 *@return bool
 *@pre board must have cars on it
 *@post n/a
 */
bool CanMoveBackward(char** board, int carNum);

/**
 * This function will assign the coordinate that car #carNum was on to a blank space while assigning the cell after the rightmost or southernmost cell to 
 * its carNumber.
 * 
 * This function finds the coordinates, length, and orientation of car #carNum using the functions that were already defined to return these values. 
 * If the conditions that make the function CanMoveForward == true, then it will delete the current coordinate of the car and assign the cell after its 
 * length distance away (either downwards or to the right) to the carnumber
 * 
 *@param char ** board, int carNum
 *@return bool
 *@pre CanMoveForward == true		//the space in front of the car is open and in the bounds of the board
 *@post The car's first cell will be deleted and the cell [row+length][col] or [row][col+length] will have the car's number assigned to it.
 */
bool moveForward(char** board, int carNum);

/**
 * This function will assign the coordinate that car #carNum was on to a blank space while assigning the cell after the leftmost or northernmost cell to 
 * its carNumber.
 * 
 * This function finds the coordinates, length, and orientation of car #carNum using the functions that were already defined to return these values. 
 * If the conditions that make the function CanMoveBackward == true, then it will delete the current coordinate of the car and assign the cell after its 
 * length distance away (either upwards or to the left) to the carnumber
 * 
 *@param char ** board, int carNum
 *@return bool
 *@pre CanMoveBack == true		//the space in front of the car is open and in the bounds of the board
 *@post The car's first cell will be deleted and the cell [row-length][col] or [row][col-length] will have the car's number assigned to it.
 */
bool moveBackward(char** board, int carNum);

/**
 * This function will find a solution for a given board and will calculate the a solution with the lowest possible number of moves
 * 
 * While the rightmost column is not equal to car #1, or '0', for each car, the function will move the car forwards or backwards if the next move's 
 * movecount is less than the best moves. This is to make sure that the number of moves can never be more than the max number of moves, or 10. If the car
 * moves forward or backward, moves is incremented and the solveIt function is called recursively. This will result in moving all of the cars forwards 
 * or backwards one at a time until a solution is reached. If the number of moves to a solution is lower than the current best moves value, then that 
 * number will become the new best.
 * 
 *@param char** board, int moves, int &best, int carCount		//best is passed by reference in order to be passed through the recursive calls
 *@return void
 *@pre board is not solved
 *@post board is solved with all possible combinations and solutions
 */
void solveIt( char** board, int moves, int &best, int carCount);
//void printBoard( char** board);

//
//Main Function///////////
//
int main(){
	int carCount = 1;
	bool gameExists = 1;
	int scenario = 0;
	while(gameExists){
		cin >> carCount;
		scenario++;
		if(carCount == 0){
			gameExists = 0;
		}
		else{	
			//beginning of creating and loading board
			//dynamically creating new board//
			char** board = new char *[6];				
			for(int i = 0; i < 6; i++){					
				board[i] = new char[6];					
			}

			//fills the board with '-' or empty space
			for(int i = 0; i < 6; i++){
				for(int j = 0; j < 6; j++){
					board[i][j] = '-';
				}
			}
			//loads board
			loadBoard(board, carCount);						
/*---------------------------the debug zone ------------------------------------------*/

int best = 10, moves = 0;
//	cout << "starting board" << endl;
//	printBoard(board);

	solveIt(board, moves, best, carCount);


	cout << "Scenario " << scenario << " requires " << best << " moves" << endl;			
			
		}//else end
	}//while end	
return 0;
}

void solveIt( char** board, int moves, int &best, int carCount){
	if( getCar_col(board, 0) +1  == 5){
		best = moves;
	}
	else{
		for(int carNum = 0; carNum < carCount; carNum++){
			if( moves + 1 < best ){
 				if (moveForward(board, carNum)) {
					moves++;
					solveIt(board, moves, best, carCount);
					moveBackward (board, carNum);
					moves--;
				}
			}
			if (moves + 1 < best) {
				if (moveBackward(board, carNum)) {
					moves++;
					solveIt(board, moves, best, carCount);
					moveForward(board, carNum);
					moves--;
				}
			}
		}
	}
}



/*
void printBoard( char** board){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
*/

/* ------------------------------board manipulation----------------------------- */
bool moveForward(char** board, int carNum){
	int x = getCar_row(board, carNum);
	int y = getCar_col(board, carNum);
	int length = getCarLength(board, carNum);
	char orientation = getCarOrientation(board, carNum);
	char digit = '0' + carNum;
	if(orientation == 'H'){
		if(CanMoveForward(board, carNum)){
			board[x][y] = '-';
			board[x][y+length] = digit;	
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(CanMoveForward(board, carNum)){
			board[x][y] = '-';
			board[x+length][y] = digit;
			return true;
		}
		else{
			return false;		
		}
	}
}

bool CanMoveForward(char** board, int carNum){
	char orientation = getCarOrientation(board, carNum);
	int length = getCarLength(board, carNum);
	int x = getCar_row(board, carNum);
	int y = getCar_col(board, carNum);
		
	if(orientation == 'H'){
		if( y+length < 6 && board[x][y+length] == '-' ){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if( x+length < 6 && board[x+length][y] == '-' ){
			return true;		
		}
		else{

			return false;
		}
	}
}

bool CanMoveBackward(char** board, int carNum){
	char orientation = getCarOrientation(board, carNum);
	int length = getCarLength(board, carNum);
	int x = getCar_row(board, carNum);
	int y = getCar_col(board, carNum);
		
	if(orientation == 'H'){
		if( y-1 >= 0 && board[x][y-1] == '-'){
			return true;
		}
		else{
///			cout << "Can't move car #" << carNum << endl;
			return false;
		}
	}
	else{
		if( x-1 >= 0 && board[x-1][y] == '-'){
			return true;		
		}
		else{
//			cout << "Can't move car #" << carNum << endl;		
			return false;
		}
	}
}

bool moveBackward(char** board, int carNum){
	int x = getCar_row(board, carNum);
	int y = getCar_col(board, carNum);
	int length = getCarLength(board, carNum);
	char orientation = getCarOrientation(board, carNum);
	char digit = '0' + carNum;
	if(orientation == 'H'){
		if(CanMoveBackward(board, carNum)){
			board[x][y+length-1] = '-';
			board[x][y-1] = digit;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(CanMoveBackward(board, carNum)){
			board[x-1][y] = digit;
			board[x+length-1][y] = '-';			
			return true;
		}
		else{
			return false;
		}
	}
}

int getCarLength(char** board, int carNum){
	char orientation = getCarOrientation(board, carNum);
	int length = 0;
	int x, y;
	x = getCar_row(board, carNum);
	y = getCar_col(board, carNum);
	char digit = '0' + carNum;
	if(orientation == 'H'){
		if( y+2 < 6 && board[x][y+2] == digit){
			length = 3;
			return length;
		}
		else{
			length = 2;
			return length;
		}
	}
	else{
		if( x+2 < 6 && board[x+2][y] == digit){
			length = 3;
			return length;
		}
		else{
			length = 2;
			return length;
		}
	}
}

char getCarOrientation(char** board, int carNum){
	int x, y;
	x = getCar_row(board, carNum);
	y = getCar_col(board, carNum);
	char digit = '0' + carNum;
	if( y+1 < 6 ){
		if( board[x][y+1] == digit ){
			return 'H';
		}
	}
	if( x+1 < 6){
		if( board[x+1][y] == digit ){
			return 'V';
		}
	}
	else{
		return 'H';
	}
}

//getCar functions finds the coordinates of the head of the car
int getCar_row(char** board, int carNum){			
	int i = 0, j = 0;
	char digit = '0' + carNum;
	while(board[i][j] != digit && i < 6){				//searches for carNum in the board
		j++;
		if(j > 5){
			j = 0;
			i++;
		}
	}				//searches for carNum in the board	
	return i;
}

int getCar_col(char** board, int carNum){
	int i = 0, j = 0;
	char digit = '0' + carNum;
	while(board[i][j] != digit && i < 6){				//searches for carNum in the board
		j++;
		if(j > 5){
			j = 0;
			i++;
		}
	}
	return j;
}

bool enoughSpaceToPlace( char** board, int row, int col, int length, char orientation){
	bool flag = 1; 			//is there enough space to place the car?
	if(orientation == 'H'){
		for( int i = 0; i < length; i++){						//horizontal check
			if( (col+i) >= 6 || board[row][col+i] != '-' ){		//checks for out of bounds or if car is already placed
				flag = 0;
				return flag;
			}
			else{
				flag = 1;
			}
		}
		return flag;
	}
	else if(orientation == 'V'){
		for( int i = 0; i < length; i++){								//vertical check
			if( (row+i) >= 6 || board[row+i][col] != '-' ){				//checks for out of bounds or if car is already placed
				flag = 0;
				return flag;
			}
			else{
				flag = 1;
			}
		}
		return flag;
	}
}






void loadBoard(char** board, int carCount){
	int length, row, col; /**< Length of car, row position of car, and column position of car*/
	int carNumber; 		 /** < Number of Car (for representation) */
	char orientation;	/**< Orientation of Car (horizontal or vertical) */
	char digits; 		/** < Indirectly converts the carNumber from an int to a char type. */
	for(carNumber = 0; carNumber < carCount; carNumber++){
		cin >> length >> orientation >> row >> col;
		digits = '0' + carNumber;
		if(length < 2 || length > 3){
			cout << "invalid length, input new length\n";
		}
		if(orientation != 'H' && orientation != 'V') {
			cout << "invalid orientation, input new orientation\n";
		}
		else if(orientation == 'H'){

			if(enoughSpaceToPlace(board, row, col, length, orientation)){
				for(int i = 0; i < length; i++){
					board[row][col+i] = digits;
				}
			}
			else{
				cout << "Not enough space to place: Car #" << digits << ".\n";
			}			
		}
		else if(orientation == 'V'){						//VERTICAL IS UP AND DOWN
			if(enoughSpaceToPlace(board, row, col, length, orientation)){
				for(int i = 0; i < length; i++){
					board[row+i][col] = digits;
				}
			}
			else{
				cout << "Not enough space to place: Car #" << digits << ".\n";
			}	
		}
	}// for end
}

