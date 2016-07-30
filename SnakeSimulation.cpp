/* :snake::snake::snake::snake::snake::snake::snake::snake::snake::snake:
Typical Snake game
made using vc++ 2015
move using w,a,s,d or arrow keys
x to pause game anytime
L to suicide

if need arises to compile on linux
replace Sleep function in main
find alternatives for _kbhit() and _getch() used in chDirection

to run compile using vc++
Code Ownership: Joydeep Halder
*/

//Snake Game
#include "stdafx.h" 
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include <windows.h>
#include<conio.h>
#include"graphics.h"
using namespace std;
#define height 24
#define width 20
#define MAXTAIL height*width -1 
#define HEADCHAR 'O'
#define TAILCHAR 'o'
#define FRUITCHAR '*'
#define SIDEBORDER '|'
#define TOPbOTTOMbORDER '-'



using namespace std;

bool gameover = false;
char a[height][width];

int headX, headY, fruitX, fruitY, score; //X and Y coordinates of head and fruit
enum Dir {HALT,LEFT, RIGHT, UP, DOWN};
Dir d;
//movement of snake ie direction
bool horizontal = true;
bool vertical = true;
//last direction travelled

int tailLen = 0;
//length of tail

struct tail {
	int tailX[MAXTAIL]; //X coordinate of tail element
	int tailY[MAXTAIL]; //Y coordinate of tail element

};

tail t;
// t is the tail

//one time initialization at the beginning
void Initiate() {
	d = HALT;
	score = 0;
	headX = height / 2;
	headY = width / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	
	for (int i = 0; i < MAXTAIL; i++)
	{
		t.tailX[i] = -1;
		t.tailY[i] = -1;
	}
	//initialise tail with -1


}

//movement of the snake basically updation at every instance
void movement() {

	int prevHeadX = headX, prevHeadY = headY;
	

	switch (d) {
	
	case UP: {
		if (headY == 0)
			headY = height-1;
		else
			headY--; }
			 break;

	case DOWN: {
		if (headY == height-1)
			headY = 0;
		else
			headY++; }
			   break;
	case LEFT: {
		if (headX == 0)
			headX = width-1;
		else
			headX--; }
			   break;
	case RIGHT: {
		if (headX == width-1)
			headX = 0;
		else
			headX++; }
				break;
	case HALT: break;
	}

	if (headX == fruitX && headY == fruitY) {
		//upon eating the fruit
		score += 10;
		tailLen++;
		fruitX = rand() % width;
		fruitY = rand() % height;

	}
	//updating tail
	for (int i = tailLen - 1, j = tailLen - 1; i >0;i--,j-- )
	{
		t.tailX[i] = t.tailX[i-1];
		t.tailY[j] = t.tailY[j-1];
	

	}
	//tl=2 i=1
	//fixing first tail item when length is atleast 1 because indices 0 and 1 will have same values after the above loop
	if (tailLen) {
		t.tailX[0] = prevHeadX;
		t.tailY[0] = prevHeadY;
	}
		

}

void chdirection() {

	//kbhit checks if keyboard key eists in the buffer
	
	if (_kbhit()) {
	
		switch (_getch()) {
		
		case 'w':
		case 'W': if(horizontal){						//can only move vertical if previous move was horizontal
										d = UP;
			horizontal=false;
			vertical = true;
		}
			break;
			//move up
		case 's':
		case 'S': if (horizontal) {
										d = DOWN;
			horizontal = false;
			vertical = true;
			 }
			break;
			//move down

		case 'a' : 
		case 'A': if (vertical) {		//can only move horizontal if previous move was vertical				
										d = LEFT;
		
			horizontal = true;
			vertical = false;
		}
			break;
			//move left


		case 'd':
		case 'D': if (vertical) {						d = RIGHT;
		
			horizontal = true;
			vertical = false;

		}
			break;
			//move right

		case 'x':
		case 'X': {
			while (1) {
				if (_getch() == 'x')
					break;
			}
		}break;
		case 'l':
		case 'L': gameover = true;   
			break;

												//LETS MAKE ARROW KEYS WORK TOO
		case 224: {
			/*arrow keys first return 224 to the buffer 
			then correspondingly 72 for up
			80 for down
			75 for left	
			77 for right*/
			switch (_getch()) {
			
			case 72: if (horizontal) {						//up arrow key
												d = UP;
				horizontal = false;
				vertical = true;
			}break;
				
			case 80: if (horizontal) {					//down arrow key
											d = DOWN;
				horizontal = false;
				vertical = true;
			}break;
			
			case 75: if (vertical) {				//left arrow key
												d = LEFT;

				horizontal = true;
				vertical = false;
			}break;

			case 77: if (vertical) {					//right arrow key
											d = RIGHT;

				horizontal = true;
				vertical = false;

			}
					  break;
					  //move right
			
			
			}
		}break;
		}
	
	}


}
void printMatrix();
void Draw() {

	

	cout << "\t\tScore=" << score<<endl;
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	//top margin
	
	int k = 0;

		for (int i = 0; i < height; i++)
		{
			for (int j = -1; j <= width; j++)
			{
				if (j == -1 || j == width)
					cout << "#";
				else if (j == headX && i == headY)
					cout << "0"; //head of snake
				else if (i == fruitY && j == fruitX)
					cout << "*"; //fruit
				else if (i == t.tailY[k] && j == t.tailX[k]) {
					cout << "o";
					k++;

				}
				else cout << " ";
			}
			cout << endl;
		}
	
	for (int i = 0; i < width+2; i++)
		cout << "#";

	printf("\n\nX: %d Y: %d\nTail Length=%d\n", headX, headY,tailLen);

	
	//tail coordinates
	for (int i = 0; i < tailLen; i++)
	{
		cout << " " << t.tailX[i];
	}
	cout << endl;
	for (int i = 0; i < tailLen; i++)
	{
		cout << " " << t.tailY[i];
	}
	cout << endl;

	//bottom margin


}
void newDraw() {

	//top margin

	//constructing matrix
	//fill with spaces first
	//setcolor(0);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
				a[i][j] = ' ';

	a[headY][headX] = HEADCHAR;
	//head

	for (int i = 0; i < tailLen; i++)
		a[t.tailY[i]][t.tailX[i]] = TAILCHAR;
	//tail

	a[fruitY][fruitX] = FRUITCHAR;
	//fruit

	//print matrix now
	 printMatrix();
}
void printMatrix(){

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\t\tScore=" << score << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	for (int i = 0; i < width + 2; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << TOPbOTTOMbORDER;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = -1; j <= width; j++) {
			if (j == -1 || j == width) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << SIDEBORDER;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else if (j == fruitX && i == fruitY) {
				//colouring fruit :grapes:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << a[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else if (j == headX && i == headY) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << a[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else cout << a[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << TOPbOTTOMbORDER;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	//bottom margin
	/*	Debugging purposes
	printf("\n\nX: %d Y: %d\nTail Length=%d\n", headX, headY, tailLen);

	Prints Tail CoOrdinates


	for (int i = 0; i < tailLen; i++)
	{
	cout << " " << t.tailX[i];
	}
	cout << endl;
	for (int i = 0; i < tailLen; i++)
	{
	cout << " " << t.tailY[i];
	}
	cout << endl;

	*/


}  

void chkCollision() {
	for (int i = 0; i < tailLen; i++)
		if (t.tailX[i] == headX	&&	t.tailY[i] == headY)
			gameover = true;
}

//collision detection :bomb:


void blinkSnake() {
	while (1) {
	
		if (_kbhit()) {
			if (_getch() == 'z' || _getch() == 'Z')
				return;
		}
		
		for (int i = 0; i < tailLen; i++)
			a[t.tailY[i]][t.tailX[i]] = ' ';

		a[headY][headX] = ' ';
		printMatrix();
		printf("\nGAME OVER!!\nFinal score=%d\n", score);
		cout << "press z to exit";
		//printed matrix without snake
		Sleep(1000);
		system("cls");
		newDraw();
		printf("\nGAME OVER!!\nFinal score=%d\n", score);
		cout << "press z to exit";
		Sleep(1000);
		system("cls");
	//	blinkSnake();
	}
} //:sna
int main() {
	
	///initgraph(); //graphics.h begin	:thumbsup:

	TCHAR *sourceTitle = TEXT("Bad Snake Game Rip Off");//TCHAR to provide portability...both char and wchar
	SetConsoleTitle(sourceTitle);

	Initiate();
	int a = 80;
	
	while (!gameover) {

		system("cls");
		newDraw();//print the board
	 chdirection();//change direction
		movement();//reflect the change in direction
		chkCollision();//chk if there is a collision
		Sleep(a);//game becomes too fast without this
	
		
	}
	
	system("cls");
	blinkSnake();
	//cout << "press enter to exit" << endl;
	
	}

