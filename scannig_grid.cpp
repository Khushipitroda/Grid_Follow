/*
===================================================================================
Program for GRID FOLLOWING ROBOT
===================================================================================

*works with EVEN y-co-ordinates(rows) grids only.
*Snake mode

 >_____________
  _____________|               | W (4)
 |_____________	               |
  _____________|      S (3)----+---> N (1)
 |_____________	               |
x______________|               | E (2)


===================================================================================
(copywrite) © Poornamith
the PAH inv
created: 01-10-2015
revised: 22-10-2015
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
const unsigned short gridR = 10, gridC = 7;

//robot co-ordinates
short r = 0, c = 0;
//robot direction
short botDir = 1;	//initially North


//movements (fn parameters are for DISPLAY PURPOSE ONLY)
void leftNinety(short valR, short valC);	//90degree turns
void rightNinety(short valR, short valC);
void forward(short valR, short valC);
void reverse(short valR, short valC);
void stop(short valR, short valC);

void scanGrid(short row, short col);


//display purpose ONLY
char arr[gridR][gridC] = { 0 };
void showArr(char _arr[gridR][gridC]);
void display(short valR, short valC);
void display(short valR, short valC, char ch);

void main()
{
	/*	grid follow
	(r,c)
	start co-ordinate (0,0)

  end co-oridnate((gridR - 1) , 0 ) or  ( (gridR - 1) , (gridC - 1) )
                 (even,even)           (odd,odd)

	right turn ( r varies , (gridC - 1) )

	left turn (r varies ,0)
	*/

	//starting point
	r = 0;
	c = 0;
	scanGrid(r, c);

	cout << "\n\nEND";

	getch();
}

void scanGrid(short row, short col)
{
	while (row < gridR)
	{
		//1. move until it detects a junction
		//2. detects a junction
		cout << "+";
		//3. save to EEPROM

		display(row, col);

		if (botDir == N)
		{
			if (col < (gridC - 1))
			{
				forward(row, col);
				col++;
			}
			else
			{
				rightNinety(row, col);
				row++;
			}
		}

		else if (botDir == S)
		{
			if (col > 0)
			{
				forward(row, col);
				col--;
			}
			else if (row == gridR - 1)
			{
				rightNinety(row, col);
				row++;
			}
			else	//i.e. (c == 0)
			{
				leftNinety(row, col);
				row++;
			}
		}

		else	//i.e. if (botDir == E)
		{
			if (col == (gridC - 1))
			{
				rightNinety(row, col);
				col--;
			}

			if (col == 0)
			{
				leftNinety(row, col);
				col++;
			}
		}
	}

	cout << "\n\nEND OF SCAN";
	showArr(arr);
	memset(arr, 0, sizeof(arr));	//clear the char arr to 0 = NULL

	cout << "\n\nre-route to Start\n\n";

	while (row > 0)
	{
		row--;

		//1. move until it detects a junction
		//2. detects a junction
		cout << "+";

		display(row, col);

		if (row == 0)
			leftNinety(row, col);
		else
			forward(row, col);
	}
	showArr(arr);
	return;
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
