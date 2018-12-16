// Snake Game.cpp : Defines the entry point for the console application.
//Simple Snake Game in C++ Console
//Made by following a 3-parts tutorial from youtube
//https://www.youtube.com/watch?v=E_-lMZDi7Uw&list=PLrjEQvEart7dPMSJiVVwTDZIHYq6eEbeL&index=1



#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

bool gameOver;
bool continueGame;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup()
{
	gameOver = false;
	continueGame = true;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
	for (int i = 0; i < 100; i++)
	{
		tailX[i] = 0;
		tailY[i] = 0;
	}
	
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 1; i < height-1; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0||j==(width-1))
				cout << "#";
			else if (i == y&&j == x)
				cout << "O";
			else if (i == fruitY&&j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j&&tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";
				
			}
	
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
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
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	
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

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > (width-1) || x <0 || y > (height-1) || y < 0)
		//gameOver = true;
	if (x == width - 1) x = 1; else if (x == 0) x = width - 2;
	if (y == height - 1) y = 1; else if (y == 0) y = height - 2;
	
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x&&tailY[i] == y)
			//gameOver = true;
			continueGame = false;

	if (x == fruitX&&y == fruitY)
	{
		score += 10;
		do
		{
			fruitX = rand() % width;
			fruitY = rand() % height;
		} while (fruitX == 0 || fruitX == width - 1 || fruitY == 0 || fruitY == height - 1);
		
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(200);
		//sleep(100); - for linux
		if (!continueGame)
		{
			cout << endl;
			cout << "Game Over" << endl << "Do you want to start a new game?" << endl << "Yes or No";
			cout << endl;
			if (_getch() == 'y')
				Setup();
			else gameOver = true;
		}
	}
    //return 0;
}

