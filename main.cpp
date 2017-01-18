#include <iostream>
#include <conio.h>
#include<Windows.h>
using namespace std;

bool gameOver, movement;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDirection{STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}

void Draw()
{
	system("cls"); // clears the screen 

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height;i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width-1)
				cout << "#";
			else
			{
				if (i == y && j == x)
					cout << "O";
				else if (i == fruitY && j == fruitX)
					cout << "F";
				else 
				{
					bool print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailX[k] == j && tailY[k] == i)
						{
							cout << "o";
							print = true;
						}
						
					}
					if (!print)
						cout << " ";
					
				}
					
			}
		}
		

		cout << endl;
	}
	for (int i = 0; i < width; i++)
		cout << "#";

	cout << endl;
	cout << "Score:" << score << endl;
		
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd' :
			dir = RIGHT;
			break;
		case 's' :
			dir = DOWN;
			break;
		case 'w' :
			dir = UP;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic()
{
	int locationheadx = x;
	int locationheady = y;
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;


	}
	movement = false;
	switch (dir)
	{
	case LEFT :
		//if (tailX[1] == x - 1)
			//break;
		x--;
		movement = true;
		break;
	case RIGHT :
		//if (tailX[1] == x + 1)
			//break;
		x++;
		movement = true;
		break;
	case DOWN :
		//if (tailY[1] == y + 1)
			//break;
		y++;
		movement = true;
		break;
	case UP :
		//if (tailY[1] == y - 1)
			//break;
		y-- ;
		movement = true;
		break;
	default : 
		break;
	}
	//if (x > width || x < 0 || y < 0 || y > height)
		//gameOver = true;
	if (movement == true)
	{
		if (x >= width - 1) x = 1;
		if (x <= 0) x = width - 2;
		if (y >= height) y = 0;
		if (y < 0) y = height - 1;
		for (int i = 0; i < nTail; i++)
			if (tailX[i] == x && tailY[i] == y)
				gameOver = true;
		if (x == fruitX && y == fruitY)
		{
			score += 10;
			nTail++;
			fruitX = rand() % width;
			fruitY = rand() % height;

		}
	}
	
}

int main()
{
	
	Setup();
	while(!gameOver)
	{
		
		Draw();
		Input();
		Logic();
		Sleep(80);

	}
		return 0;
}

