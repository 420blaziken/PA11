/// HEADERS //////////////////////////////////////////////////////////////////////////////
#include<iostream>
/// CLASSES //////////////////////////////////////////////////////////////////////////////
class Cars
{
private:
	int type;
	char direction;
	int x, y;
public:
/// Function: Default Constructor
/// Requirements: None
/// Results: Constructor. Initializes data members for a Cars object.
/** This function doesn't really do too much since we eventually parameterize/
	* assign values to them later on. */
	Cars()
	{
		type=x=y=69; /* :^) */
		direction=' ';
	}
/// Function: Parameterized Constructor
/// Parameters: Variables to assign values to respective data members
/// Results: Constructor. Initializes data members to a specific value.
/** This function takes in user-defined input and stores it into data
	* members. It essentially just follows the input order. */
	Cars(int size, char orientation, int row, int col)
	{
		type=size;
		direction=orientation;
		x=row;
		y=col;
	}
/// Function: Overloaded Assignment Operator
/// Requirements: That the Cars objects are not on the same address.
/// Results: Assignment operator. Allows for easy transfer of data between objects.
/** This function just assigns data to their respective data members. Comparable to that
		of the Parameterized Constructor. */
	Cars& operator= (const Cars& other)
	{
		if(this!=&other)
		{
			this->type=other.type;
			this->direction=other.direction;
			this->x=other.x;
			this->y=other.y;
		}
		return *this;
	}
/// Function(s): Get Methods
/// Requirements: None
/// Results: Get Methods. Returns value of data members.
/** The following get functions are necessary for getting access to the data members of
	* The Cars object outside of the scope of the class. */
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getType()
	{
		return type;
	}
	char getDirection()
	{
		return direction;
	}
/// Function: Move Forward
/// Requirements: 2D char array
/// Results: Moves Car forward on the board.
/** This function performs the action of moving the Car forwards, with respect to the 'head'
	* of the Car. If it's vertical, move south. If it's horizontal, move east. */
	bool moveForward(char** board)
	{
		if(direction=='V')
		{
			if(type==2)
			{
				if(x+2<6 && board[x+2][y]=='-')
				{
					board[x][y]='-';
					board[x+2][y]='V';
					x++;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(type==3)
			{
				if(x+3<6 && board[x+3][y]=='-')
				{
					board[x][y]='-';
					board[x+3][y]='V';
					x++;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if(direction=='H')
		{
			if(type==2)
			{
				if(y+2<6 && board[x][y+2]=='-')
				{
					board[x][y]='-';
					board[x][y+2]='H';
					y++;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(type==3)
			{
				if(y+3<6 && board[x][y+3]=='-')
				{
					board[x][y]='-';
					board[x][y+3]='H';
					y++;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
/// Function: Move Backward
/// Requirements: 2D char array
/// Results: Moves Car backward on the board.
/** This function performs the action of moving the Car backwards, with respect to the 'head'
	* of the Car. If it's vertical, move north. If it's horizontal, move west. */
	bool moveBackward(char** board)
	{
		if(direction=='V')
		{
			if(type==2)
			{
				if(x-1>=0 && board[x-1][y]=='-')
				{
					board[x+1][y]='-';
					board[x-1][y]='V';
					x--;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(type==3)
			{
				if(x-1>=0 && board[x-1][y]=='-')
				{
					board[x+2][y]='-';
					board[x-1][y]='V';
					x--;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if(direction=='H')
		{
			if(type==2)
			{
				if(y-1>=0 && board[x][y-1]=='-')
				{
					board[x][y+1]='-';
					board[x][y-1]='H';
					y--;
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(type==3)
			{
				if(y-1>=0 && board[x][y-1]=='-')
				{
					board[x][y+2]='-';
					board[x][y-1]='H';
					x--;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
/// Function: Did We Win
/// Requirements: None
/// Results: Returns a bool
/** This function checks if the Car is touching the edge of the board. Since the target Car
	* is always going to be horizontal, it only checks the y-coordinate of the head. Because
	* the head of the Car is the eastmost segment of the car, it checks if the vehicle itself
	* touches the end of the board. */
	bool didWeWin()
	{
		if(y==4)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
/// FUNCTION DECLARATIONS ////////////////////////////////////////////////////////////////
/// Function: Clear Table
/// Parameters: 2D char array
/// Results: Prints the board
void clearTable(char** board);
/// Function: Print Table
/// Parameters: 2D char array
/// Results: Prints the board
void setTable(char** board, Cars inventory[], int car_amount);
/// Function: Solve It
/// Parameters: x2 2D char arrays, number of moves, the Cars array, and the number of cars
/// Results: Returns the minimum number of moves necessary to solve puzzle
void solveIt(char** board, Cars carArray[], int numCars, int numMoves, int &bestMove);

/// MAIN FUNCTION ////////////////////////////////////////////////////////////////////////
int main()
{
	int car_amount=1, car_size, car_x, car_y;
	char car_direction;
	int total_moves=10;
	int scenario=1;
	char** board=new char*[6];
	//GENERATING GAME BOARD
	for(int index=0;index<6;index++)
	{
		board[index]=new char[6];
	}
	//USER INPUT
	while(car_amount!=0)
	{
		clearTable(board);
		total_moves=0;
		std::cin >> car_amount;
		if(car_amount==0)
		{
			return 0;
		}
		Cars car_inventory[car_amount];
		for(int index=0;index<car_amount;index++)
		{
			std::cin >> car_size;
			std::cin >> car_direction;
			std::cin >> car_x;
			std::cin >> car_y;
			Cars temp(car_size, car_direction, car_x, car_y);
			car_inventory[index]=temp;
		}
		//BOARD SETUP
		setTable(board, car_inventory, car_amount);
		solveIt(board, car_inventory, car_amount, 0, total_moves);
		//OUTPUT
		std::cout<<"Scenario "<<scenario<<" requires "<<total_moves<<" moves"<<std::endl;
		scenario++;
	}
	return 0;
}

/// FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////////
/// Function: Clear Table
/// Parameters: 2D char array
/// Results: Clears the board
/** This function generates a clear game board before the cars are added in. */
void clearTable(char** board)
{
	for(int index=0;index<6;index++)
	{
		for(int subindex=0;subindex<6;subindex++)
		{
			board[index][subindex]='-';
		}
	}
}
/// Function: Set Table
/// Parameters: 2D char array, Cars array, int for number of cars
/// Results: Adds the Cars to the board
/** This function simply updates the board with the contents of the Cars objects. */
void setTable(char** board, Cars car_inventory[], int car_amount)
{
	int car_size, car_x, car_y;
	char car_direction;
	for(int index=0;index<car_amount;index++)
	{
		car_size=car_inventory[index].getType();
		car_direction=car_inventory[index].getDirection();
		car_x=car_inventory[index].getX();
		car_y=car_inventory[index].getY();
		if(car_size==2)
		{
			if(car_direction=='H')
			{
				board[car_x][car_y]='H';
				board[car_x][car_y+1]='H';
			}
			else if(car_direction=='V')
			{
				board[car_x][car_y]='V';
				board[car_x+1][car_y]='V';
			}
		}
		else if(car_size==3)
		{
			if(car_direction=='H')
			{
				board[car_x][car_y]='H';
				board[car_x][car_y+1]='H';
				board[car_x][car_y+2]='H';
			}
			else if(car_direction=='V')
			{
				board[car_x][car_y]='V';
				board[car_x+1][car_y]='V';
				board[car_x+2][car_y]='V';

			}
		}
	}
}
/// Function: Solve It
/// Parameters: x2 2D char arrays, number of moves, the Cars array, and the number of cars
/// Results: Returns the minimum number of moves necessary to solve puzzle
/** This function is supposed to return the minimum number of moves necessary to solve any
	* given puzzle (given it was fewer than 10 moves). However, I ran into the issue of my
	* function being unable to properly move backwards, since it always wanted to move
	* forwards after moving backwards. I tried to get help with this issue to no avail.
	* My apologies, this function doesn't work as needed.
	* UPDATE: I was able to solve my issue after realizing that my moveBackward function
	* was a little bit buggy, since I messed up one of the coordinates. I also realized
	* that we needed to initialize the best moves variable at 10, instead of 0. This was
	* the reason why this function was acting all funky. */
void solveIt(char** board, Cars carArray[], int numCars, int numMoves, int &bestMove)
{
	if (carArray[0].didWeWin()==true)
	{
		bestMove = numMoves;
	}
	else if(carArray[0].didWeWin()==false)
	{
		for (int index=0;index<numCars;index++)
		{
			if (bestMove >= 0 && numMoves+1<= bestMove)
			{
				if (carArray[index].moveForward(board)==true)
				{
					numMoves++;
					solveIt(board, carArray, numCars, numMoves, bestMove);
					carArray[index].moveBackward(board);
					numMoves--;
				}
				if (carArray[index].moveBackward(board)==true)
				{
					numMoves++;
					solveIt(board, carArray, numCars, numMoves, bestMove);
					carArray[index].moveForward(board);
					numMoves--;
				}
			}
		}
	}
}
