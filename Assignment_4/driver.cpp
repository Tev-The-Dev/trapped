// Bob Myers
// Test program that was provided to the students

#include <iostream>
using namespace std;

#include "grid.h"


int main()
{
	/*
 	//Tested and works
	//Grid g1;
	//g1.Display();


	Grid g2(6,6);

//	g2.Display();

	g2.PutDown(10,3);
	g2.PutDown(7,13);
	g2.PutDown(7,1);
	g2.PutDown(1,13);
	g2.PutDown(1,1);
	g2.PutDown(11,9);
	g2.PutDown(7,2);
	g2.PutDown(12,11);
	
	// cout << "placing block at 0,0" << g2.PlaceBlock(0,0)<< endl;
	// cout << "placing block at 3,7" << g2.PlaceBlock(3,7) << endl;
	// cout << "placing block at 1,6" << g2.PlaceBlock(1,6) << endl;
	// cout << "placing block at -1,0" << g2.PlaceBlock(-1,0) << endl;
	


	//g2.PutDown(g2.GetRow(), g2.GetCol());
	

//	g2.PickUp();
//	g2.TurnLeft();	

//	g2.Move(3);
	g2.Display();

	g2.Grow(20,21);
	g2.Display();


	return 0;


*/


  // set up the initial grid

  Grid g(9,15,2,13,Grid::WEST);

  g.Display();
  g.PutDown(2,1);

  for (int i = 0; i < 7; i++)
  {
     g.PlaceBlock(i,11);
     g.PlaceBlock(i,7);
     g.PlaceBlock(i,3);
     g.PlaceBlock(i+2,5);
     g.PlaceBlock(i+2,9);
  }

  g.Display();
  // now start moving

  g.TurnLeft();
  g.Move(5);
  g.Display();

  g.TurnLeft();
  g.TurnLeft();
  g.TurnLeft();
  g.Move(1);
  g.Display();  

  for (int i = 0; i < 2; i++)
  {
    g.Move(2);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(6);
    g.Display();  

    g.PutDown();
    g.Display();  

    g.TurnLeft();
    g.Move(2);
    g.Display();

    g.TurnLeft();
    g.Move(6);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
  }

  g.Move(3);
  g.Display();

  g.TurnLeft();
  g.TurnLeft();
  g.TurnLeft();
  g.Move(5);
  g.Display();

  g.PickUp();
  g.Display();

  g.TurnLeft();
  g.Move(1);
  g.Display();

  g.TogglePath();
  g.Display();
  g.TogglePath();
  g.Display();
}

