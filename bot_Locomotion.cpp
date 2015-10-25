/*
===================================================================================
Program for GRID FOLLOWING ROBOT
===================================================================================

*locomotes the robot on the shortest possible path


			| W (4)
			|
    	     S (3)----+---> N (1)
			|
			| E (2)


===================================================================================
(copywrite) © Poornamith
the PAH inv
created: 21-10-2015
revised: 23-10-2015
www.poornamith.azurewebsites.net
===================================================================================
*/

#include <iostream>
#include <conio.h>

//North, South, East, West directions(see above comments)
#define N 1
#define E 2
#define S 3
#define W 4

using namespace std;


//grid co-ordinates
const unsigned short gridR = 4, gridC = 4;

//robot co-ordinates
short r = 0, c = 0;
//robot direction
short botDir = N;	//initially North

bool wasHere[gridR][gridC] = { 0 };
bool correctPath[gridR][gridC] = {
	{ 1,1,1,1 },
	{ 0,0,0,1 },
	{ 1,1,1,1 },
	{ 1,0,0,0 }

}; // solved maze
short startR = 0, startC = 0;		// Starting R and C values of maze
short endR = 0, endC = 0;		// Ending R and C values of maze

//movements (fn parameters are for DISPLAY PURPOSE ONLY)
void leftNinety(short valR, short valC);	//90degree turns
void rightNinety(short valR, short valC);
void forward(short valR, short valC);
void reverse(short valR, short valC);
void stop(short valR, short valC);
void overTurn(short valR, short valC);


//display purpose ONLY
char arr[gridR][gridC] = { 0 };
void showArr(char _arr[gridR][gridC]);
void display(short valR, short valC);
void display(short valR, short valC, char ch);

bool locomotion();
bool path(short row, short col);

void main()
{
	//set the bot Starting co-ordinates
	startR = 0;
	startC = 0;

	r = startR;
	c = startC;

	endR = 3;
	endC = 0;

	//loop until bot reaches the end co-ordinates
	while (locomotion());

	//show the path as an Array
	showArr(arr);

	getch();
}

bool locomotion()
{
	//1. move until it detects a junction
	//2. detects a junction
	cout << "+";

	//check the element below the current bot Element is accessible
	if (path(r + 1, c))
	{
		//turn the bot according to the 
		if (botDir == N)
			rightNinety(r, c);
		else if (botDir == E)
			forward(r, c);
		else
			leftNinety(r, c);

		//botDir is set to E
		r++;
		return true;
	}
	//check the element left to the current bot Element is accessible
	if (path(r, c - 1))
	{
		if (botDir == E)
			rightNinety(r, c);
		else if (botDir == S)
			forward(r, c);
		else
			leftNinety(r, c);

		//botDir is set to S
		c--;
		return true;
	}
	//check the element right to the current bot Element is accessible
	if (path(r, c + 1))
	{
		if (botDir == N)
			forward(r, c);
		else if (botDir == E)
			leftNinety(r, c);
		else
			rightNinety(r, c);

		//botDir is set to N
		c++;
		return true;
	}
	//check the element above the current bot Element is accessible
	if (path(r - 1, c))
	{
		if (botDir == N)
			leftNinety(r, c);
		else if (botDir == S)
			rightNinety(r, c);
		else
			forward(r, c);

		//botDir is set to W
		r--;
		return true;
	}

	//you are at the END element
	if (botDir == N)
		overTurn(r, c);
	else if (botDir == S)
		forward(r, c);
	else if (botDir == E)
		rightNinety(r, c);
	else
		leftNinety(r, c);

	return false;
}

bool path(short row, short col)
{
	if ((row > gridR - 1) || (col > gridC - 1)) // Checks if not on bottom edge
		return false;

	if ((col < 0) || (row < 0))  // Checks if not on left edge
		return false;

	//if (col > gridC - 1) // Checks if not on right edge
		//return false;

	//if (row < 0) // Checks if not on top edge
		//return false;

	if (correctPath[row][col] == 0 || wasHere[row][col])	// If you are on a wall or already were here
		return false;

	//else
	wasHere[r][c] = true;
	return true;
}

//movements handler functions
void leftNinety(short valR, short valC)
{
	cout << " LEFT ";
	display(valR, valC, 'L');

	if (botDir == N) {
		botDir = W; return;
	}
	if (botDir == W) {
		botDir = S; return;
	}
	if (botDir == S) {
		botDir = E; return;
	}
	if (botDir == E) {
		botDir = N; return;
	}

}
void rightNinety(short valR, short valC)
{
	cout << " RIGHT ";
	display(valR, valC, 'R');

	if (botDir == N) {
		botDir = E; return;
	}
	if (botDir == E) {
		botDir = S; return;
	}
	if (botDir == S) {
		botDir = W; return;
	}
	if (botDir == W) {
		botDir = N; return;
	}
}
void forward(short valR, short valC)
{
	cout << " FW ";
	display(valR, valC, 'F');
}
void reverse(short valR, short valC)
{
	cout << " RV ";
	display(valR, valC, 'w');
}
void stop(short valR, short valC)
{
	cout << " STOP ";
	display(valR, valC, 'X');
}
void overTurn(short valR, short valC)
{
	cout << " OverT ";
	display(valR, valC, 'O');

	if (botDir == N) {
		/*if the junction is like	   |
									---+---
									   |
		//leftNinety(valR, valC);
		//leftNinety(valR, valC);
		*/

		/*if the junction is like	   __|	(or)	|__	 (or)	 __   (or)   ___
																|				|
		//rotate 180 degrees
		//do not use left Ninety x 2
		*/
		botDir = S;
		return;
	}
	if (botDir == E) {
		//rotate 180 degrees
		botDir = W;
		return;
	}
	if (botDir == S) {
		//rotate 180 degrees
		botDir = N;
		return;
	}
	if (botDir == E) {
		//rotate 180 degrees
		botDir = W;
		return;
	}
}

//display co-ordinates
void display(short valR, short valC)
{
	cout << "(" << valR << "," << valC << ")";
}
void display(short valR, short valC, char ch)
{
	arr[valR][valC] = ch;
}
void showArr(char _arr[gridR][gridC])
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
