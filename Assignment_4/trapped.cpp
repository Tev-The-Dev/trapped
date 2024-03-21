
#include <iostream>
#include "grid.h"

using namespace std;

void TurnRight(Grid& g);
void MoveRight(Grid& g);
bool LeftIsClear(Grid& g);
void MoveBack(Grid& g);
void TurnBack(Grid& g);
void FindExit();

int main()
{	
	bool FoundIt = false;
	bool Done = false;
	int x, y;
	cout << "You are a prisoner of the mole people. You have escaped your encapturement. " << endl;
	cout << "Now you must escape their underground layer. Good Luck!" << endl;
	
	cout << "How big is their dungeon?" << endl;
		cin >> x >> y;
	
	Grid g(x,y);
	
	g.Display();
	
	do
	{
		if(g.FrontIsClear())
			g.Move(1);
		else
		{	
			g.TurnLeft();
			FoundIt = true;
		}

		if(FoundIt && g.RightIsClear())
		{
			MoveRight(g);
			Done = true;

		}

		if(g.GetRow() == 0)
			Done = true;
		if(g.GetRow() == g.GetNumRows())
			Done = true;
		
		if(g.GetCol() == 0)
			Done = true;
		if(g.GetCol() == g.GetNumCols())
			Done = true;
	
	} while(!Done);
	
	g.TogglePath();
	
	g.Display();	
	
	cout << endl;
	cout << "Final position of the mover is: " << g.GetRow() << ","  << g.GetCol() << endl; 
	cout << "You have made it out alive, now go write a book." << endl;
}


void TurnRight(Grid& g)
{
	g.TurnLeft();
	g.TurnLeft();
	g.TurnLeft();
}

void MoveRight(Grid& g)
{
	TurnRight(g);
	g.Move(1);
}

bool LeftIsClear(Grid& g)
{
	bool IsClear = false;
	g.TurnLeft();
	if(g.FrontIsClear())
	{
		IsClear = true;
	}
	TurnRight(g);
	return IsClear;
}

void MoveBack(Grid& g)
{
	g.TurnLeft();
	g.TurnLeft();
	g.Move(1);
	g.TurnLeft();
	g.TurnLeft();

}
void FindExit()
{
	//move to the edge, check if the exit is on the right

}












