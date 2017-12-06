#include <queue>
#include <iostream>
#include <map>
using namespace std;

struct Car{
	char id;
	char orientation;
	int length;
	int x;
	int y;	
}


int main(){
	int carCount = 1;
	bool gameExists = 1;
	int scenario = 0;
	int moves = 0;
	while(gameExists){
		cin >> carCount;
		scenario++;
		if(carCount == 0){
			gameExists = 0;
		}
		else{
			//load cars onto board	
			//solveIt(board, moves, best, carCount);
			cout << "Scenario " << scenario << " requires " << moves << " moves" << endl;
		}//else end
	}//while end	
return 0;
}
