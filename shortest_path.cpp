/*
===================================================================================
Program for GRID FOLLOWING ROBOT
===================================================================================

* based on the Recursive algorithm which is available in Wikipedia written in .java
	https://en.wikipedia.org/wiki/Maze_solving_algorithm

* This Maze solving algorithm can only solve shortest paths for co-ordinates on a single COLUMN.
	i.e. both starting and ending points should be in one single ROW.

* The priority is given row-wise, not column wise
	if you want vice-versa change the rows and columns and some minor tweaks for the recursiveSolve() function


===================================================================================
(copywrite) © Poornamith
the PAH inv
created: 03-10-2015
revised: 22-10-2015
www.poornamith.azurewebsites.net
===================================================================================
*/


#include <iostream>
#include <conio.h>


using namespace std;

//grid co-ordinates
const unsigned short gridR = 4, gridC = 4;

// Scanned maze
//1 = junction/crossable
//2 = wall/no junction/can't cross
short maze[gridR][gridC] = {
	{ 1,2,1,1 },
	{ 1,1,2,1 },
	{ 1,2,1,1 },
	{ 1,1,1,2 }
};


bool wasHere[gridR][gridC] = { 0 };
bool correctPath[gridR][gridC] = { 0 };		// The solution to the maze
short startR = 0, startC = 0;		// Starting R and C values of maze
short endR = 0, endC = 0;		// Ending R and C values of maze

//fn prototypes for solving Maze
void solveMaze();
bool recursiveSolve(int row, int col);


//display purpose ONLY
void showArr(bool _arr[gridR][gridC]);


void main()
{
	solveMaze();
}

void solveMaze()
{
	startR = 0;
	startC = 0;

	endR = 3;
	endC = 0;

	bool pathFound = recursiveSolve(startR, startC);

	if (pathFound)
	{
		cout << "shortest possible path: ";
		//display the path generated
		showArr(correctPath);
	}
	else
		cout << "No solutions to the Maze!.";

	getch();
}

bool recursiveSolve(int row, int col) {
	if (row == endR && col == endC)
	{
		correctPath[row][col] = true;
		return true; // If you reached the end
	}

	if (maze[row][col] == 2 || wasHere[row][col])
		return false;

	// If you are on a wall or already were here
	wasHere[row][col] = true;

	if (row != 0) // Checks if not on top edge
		if (recursiveSolve(row - 1, col))
		{
			// Recalls method one to the top
			correctPath[row][col] = true; // Sets that path value to true;
			return true;
		}
	if (row != gridR - 1) // Checks if not on bottom edge
		if (recursiveSolve(row + 1, col))
		{
			// Recalls method one to the bottom
			correctPath[row][col] = true;
			return true;
		}
	if (col != 0)  // Checks if not on left edge
		if (recursiveSolve(row, col - 1))
		{
			// Recalls method one to the left
			correctPath[row][col] = true;
			return true;
		}
	if (col != gridC - 1) // Checks if not on right edge
		if (recursiveSolve(row, col + 1))
		{
			// Recalls method one to the right
			correctPath[row][col] = true;
			return true;
		}
	return false;
}

//display the array
void showArr(bool _arr[gridR][gridC])
{
	cout << endl << endl;

	for (int i = 0; i < gridR; i++)
	{
		for (int j = 0; j < gridC; j++)
		{
			cout << _arr[i][j] << " ";
		}
		cout << endl;
	}
}
