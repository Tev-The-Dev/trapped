/*
	Member Data
	char player;

	int row, column, counter;
	int board[40][40];
*/
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "grid.h"

using namespace std;
Grid::Grid()
{	
	cout << "Default stuff" << endl;
	player = '>';
	row = 1;
	column = 1;
	board[0][0] = player;
	ShowPath = true;
}

Grid::Grid(int r, int c)
{
	srand(time(0));
	ShowPath = true;

	row = r;
	column = c;

	if(r < 3)
		row = 3;;
	if(r > 40)
		row = 40;
	if(c < 3)
		column = 3;
	if(c > 40)
		column = 40;

	InitBoard();
	InitPlayer();
	//board[row][column];

	cout<< "grid size is: " << row << "," << column << endl; 

	CreateWall();
	CreateExit();

	cout << "Is front clear? " << FrontIsClear() << endl;
	cout << "Is right clear? " << RightIsClear() << endl;
	
}
Grid::Grid(int r, int c, int mr, int mc, int d)
{
	ShowPath = true;
	InitBoard(r,c);
	InitPlayer(mr, mc, d);	

}

bool Grid::Move(int s)
{
	char orig_v;
	orig_v = board[p_row][p_column];

	int orig_r, orig_c;
	orig_r = p_row; orig_c = p_column;

	char orig_b[40][40];
	CopyGrid(board,orig_b);


	for(int i = 0; i < s; i++)
	{
		if(FrontIsClear())
		{
			if(board[p_row][p_column] == '@') {
				cout << "PRotect the space with a 0" << endl;
				board[p_row][p_column] = 'O';
			}
			if(board[p_row][p_column] == 'O') {
				board[p_row][p_column] = 'O';
			}
			if(board[p_row][p_column] == '.') {
				board[p_row][p_column] = ' ';
			}
			//if(board[p_row][p_column] != 'O') {
			//	board[p_row][p_column] = ' ';
			//	cout << "You did not touch an object so space it out" << endl;
			//} else {
		//		cout << "Use 0 for " << p_row << ", " << p_column << endl;
		//	}
			
			if(p_face == 0)
				p_row -= 1;
			
			if(p_face == 1)
				p_column -= 1;
		
			if(p_face == 2)
				p_row += 1;
	
			if(p_face == 3)
				p_column += 1;

					
			//boundary check mack sure player stays on grid
			if(p_row >= row || p_row < 0 || p_column >= column || p_column < 0)
			{
		
				CopyGrid(orig_b,board);
				p_row = orig_r;p_column = orig_c;
				return false;
			}
		}
		else
		{
			CopyGrid(orig_b,board);
			p_row = orig_r;p_column = orig_c;
			return false;
		}

	}
	
	if(orig_v == '@')
		board[orig_r][orig_c] = 'O';
	else
		board[orig_r][orig_c] = ' ';

	if(board[p_row][p_column]== 'O')
		board[p_row][p_column] = '@';
	else 	
		board[p_row][p_column] = player;
		
					
	return true;
}

void Grid::TogglePath()
{
	ShowPath = !ShowPath;

}

void Grid::TurnLeft()
{
	p_face += 1;
	if(p_face == 4)
		p_face = 0;

	if(p_face == 0)
		player = '^';
	else if(p_face == 1)
		player = '<';
	else if(p_face == 2)
		player = 'v';
	else
		player = '>';
	
	if ( board[p_row][p_column] !=  '@' )
		board[p_row][p_column] = player;
}

void Grid::PutDown()
{
	board[p_row][p_column] = '@';

}
bool Grid::PutDown(int r, int c)
{
     //cout << "__putDown: r is:" << r << " and c: " << c << endl;
	//check if r and c exist in the board
	if(r < 0)
	{
		//cout << "Case 0's r and c " << r << "," << c << endl;
		return false;
	}
	if(r >= row)
	{
		//cout << "Case 1's r and c " << r << "," << c << endl;
		return false;
	}
	if(c < 0)
		{
		//cout << "Case 2's r and c " << r << "," << c << endl;
		return false;
	}
	if(c >= column)
		{
		//cout << "Case 3's r and c " << r << "," << c << endl;
		return false;
	}

	//Check if there is a barier or item in poisition (r,c)
			 //cout << "r,c, board is: " << r << "," << c <<
			  //"[" << board[r][c] << "]" << endl;

	if(board[r][c] == '#')
		{
			//cout << "p_row,p_column, board is: " << p_row << "," << p_column <<
			 //"[" << board[p_row][p_column] << "]" << endl;
			return false;
		}
	if(board[r][c] == 'O')
		return false;
	if(board[r][c] == '@')
		return false;

	 //all tests passed return true for success
	if(board[r][c]==player)
		board[r][c] = '@';
	else
		board[r][c] = 'O';
	
	return true;

}

bool Grid::PickUp()
{
	if(board[p_row][p_column]=='@')
	{
		board[p_row][p_column] = player;
		return true;
	}
	
	return false;

}

bool Grid::PlaceBlock(int r, int c)
{

    // cout << "__placeblock: r is:" << r << " and c: " << c << endl;
	//check if r and c exist in the board
	if(r < 0)
	{
		//cout << "Case 0's r and c " << r << "," << c << endl;
		return false;
	}
	if(r >= row)
	{
		//cout << "Case 1's r and c " << r << "," << c << endl;
		return false;
	}
	if(c < 0)
		{
		//cout << "Case 2's r and c " << r << "," << c << endl;
		return false;
	}
	if(c >= column)
		{
		//cout << "Case 3's r and c " << r << "," << c << endl;
		return false;
	}
		
	if(board[r][c]=='.')
	{
		board[r][c] = '#';
		return true;
	}
	
	return false;

}


void Grid::Grow(int gr, int gc)
{
	row = gr;
	column = gc;
	
	if(row >= 40)
		row = 39;
	if(column >= 40)
		column = 39;
}


void Grid::Display() const
{

	cout << "The Grid: " << endl;

	//display column header
	/*for(int k = 0; k <= column; k++)
	{
		if(k < 9)
			cout << k << "  ";
		else 
			cout << k << " ";
	}
	cout << endl;*/

	for(int i = 0; i < row; i++)
	{
		//display row header	
		//cout << i+1 << " ";
		/*if(i >= 9)
			cout << i+1;
		else	
			cout << i+1 << " ";*/

		for(int j = 0; j < column; j++)
		{
			if(board[i][j] == ' ' && !ShowPath)
				//cout <<  " " <<"." << " ";
				cout <<"." << " ";
			else
				//cout << " " <<board[i][j] << " ";
				cout <<board[i][j] << " ";
		}
		cout << endl;
	}



}

   // Accessors
bool Grid::FrontIsClear() const
{

	switch(p_face)
	{
	case 0:
		if(board[p_row-1][p_column] == '#')
			return false;
		
		break;
	case 1:
		if(board[p_row][p_column-1] == '#')
			return false;
		break;
	case 2: 
		if(board[p_row+1][p_column] == '#')
			return false;		
		break;
	case 3:
		if(board[p_row][p_column+1] == '#')
			return false;
		break;
	}

	return true;
}

bool Grid::RightIsClear() const
{
	switch(p_face)
	{
	case 0:
		if(board[p_row][p_column+1] == '#')
			return false;
		
		break;
	case 1:
		if(board[p_row-1][p_column] == '#')

			return false;
		break;
	case 2: 
		if(board[p_row][p_column-1] == '#')
			return false;		
		break;
	case 3:
		if(board[p_row+1][p_column] == '#')
			return false;
		break;
	}

	return true;

}
int Grid::GetRow() const
{
	return p_row;
}
int Grid::GetCol() const
{
	return p_column;
}
int Grid::GetNumRows() const
{
	return row;
}
int Grid::GetNumCols() const
{
	return column;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//									Beginning of
//									Private Functions 
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


bool Grid::IsValidExit()
{
	bool flag = true;
	if(exit_row == 0 && exit_column == 0)
		return false;
	if(exit_row == 0 && exit_column == column - 1)
		return false;
	if(exit_row == row - 1 && exit_column == 0)
		return false;
	if(exit_row == row - 1 && exit_column == column - 1)
		return false;


	return true;
	


}   

void Grid::CreateWall()
{
	for(int i=0; i<column;i++)
	{
		board[0][i] = '#';
		board[row-1][i] = '#';
	}

	for(int i=0; i<row;i++)
	{
		board[i][0] = '#';
		board[i][column - 1] = '#';
	}

}

//assign exit row and exit column values
void Grid::CreateExit()
{
	do
	{
	int wall = GetRandomWall();
	cout << "Exit Wall is: " << wall << endl;
	if (wall == 1 || wall == 3)
		exit_row = rand() % row;
			
	if(wall == 0 || wall == 2)
		exit_column = rand() % column;
	if(wall == 0)
		exit_row = 0;
	if(wall == 1)
		exit_column = 0;
	if(wall == 2)
		exit_row = row-1;
	if( wall == 3)
		exit_column = column-1;

	//cout << "exits is at [" << exit_row +1<< "," << exit_column +1 << "] " <<endl;
	}while(!IsValidExit());
 	cout << "Exit displays at [" << exit_row +1<< "," << exit_column +1 << "] " <<endl;
	board[exit_row][exit_column] = ' ';
}

int Grid::GetRandomWall()
{

	return rand() % 4;

}

void Grid::InitBoard()
{
	for(int x = 0; x < 40; x++)
		for(int j = 0; j < 40; j++)
			board[x][j] = '.';

}

void Grid::InitBoard(int r, int c)
{
	row = r; column = c;	
	cout << "Made it to _initboard with 2 params " << endl;
	for(int x = 0; x < row; x++)
		for(int y = 0; y < column; y++)
			board[x][y] = '.';

}

void Grid::InitPlayer()
{

	p_face = GetRandomWall();

	if(p_face == 0)
		player = '^';
	else if(p_face == 1)
		player = '<';
	else if(p_face == 2)
		player = 'v';
	else
		player = '>';

	p_row = (rand() %(row -2) )+1;
	p_column = (rand() % (column - 2))+1;

	board[p_row][p_column] = player;

	cout << "Player displays at [" << p_row +1<< "," << p_column +1 << "] " <<endl;
	cout << "Player is facing: "<< p_face << endl;
	//cout << "p_row and p_column is: " << p_row << "," << p_column << endl;

}

void Grid::InitPlayer(int mr, int mc, int d)
{
	p_face = d;	
	if(p_face == NORTH)
		player = '^';
	else if(p_face == WEST)
		player = '<';
	else if(p_face == SOUTH)
		player = 'v';
	else
		player = '>';

	if(mr < 0)
		p_row = 1;
	else
		p_row = mr;
	
	if(mr >= row )
		p_row = row -1;
	else
		p_row = mr;

		
	if(mc < 0)
		p_column = 1;
	else
		p_column = mc;
	
	if(mc >= column )
		p_column = column -1;
	else
		p_column = mc;

	board[p_row][p_column] = player;
}

void Grid::CopyGrid(const char source[40][40], char destination[40][40])
{
	for(int i = 0; i < row; i++)
		for(int j = 0; j < column; j++)
			destination[i][j] = source[i][j];


}
