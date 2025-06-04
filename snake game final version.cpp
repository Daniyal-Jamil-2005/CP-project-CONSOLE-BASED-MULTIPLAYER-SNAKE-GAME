#include <iostream>
#include <conio.h>
#include <fstream>      //to handle files
#include <windows.h>    
#include<string>
#include <time.h>       // To make spawn value more random

using namespace std;

bool gameOver;          //variable to track whether or not game is over.
const int width = 52;   //setting width of gameplay area.
const int height = 28;  //setting height of gameplay area.

//initializing the positions of both snakes ,fruit and their scores
int x, y, x2, y2, fruitX, fruitY, score, score2;
//declaring the variables to store tails position as array
int tailX[100], tailY[100], tailX2[100], tailY2[100];
int tail_num, tail_num_2;
char player1[20], player2[20];
//using datatype 'enum' to store fixed set of constants for directions
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
//variables to store current direction and movement of both snakes
eDirecton dir, dir2;
//function prototypes:
void Setup();
void Draw();
void Input();
void Input2();
void Logic();
void Logic2();
void getname();
void saveResults();

//function to initialize gamestate
void Setup()
{
    gameOver = false;
    dir = STOP;
    dir2 = STOP;
    //initial positions of snakes
    x = width / 2;
    y = height / 2;
    x2 = width / 12;
    y2 = height / 3;
    //random spawning of fruit
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
//function to display components of game on console
void Draw()
{
    system("cls"); //system("clear screen");
    cout << endl;
    cout << " ";
    //loop for top border of gamegrid
    for (int i = 0; i < width + 2; i++)
        cout << "=";
    cout << endl;
    //using nested for-loops to have 2-D grid defined by height and width 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //left grid
            if (j == 0)
                cout << " |";
            //displaying body of snakes ,fruit
            if (i == y && j == x)
                cout << "O";
            else if (i == y2 && j == x2)
                cout << "X";
            else if (i == fruitY && j == fruitX)
                cout << "#";
            else
            {
                //clearing the privious printed tails of both snakes
                bool print = false;
                //printing snake tails 
                for (int k = 0; k < tail_num; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                for (int l = 0; l < tail_num_2; l++)
                {
                    if (tailX2[l] == j && tailY2[l] == i)
                    {
                        cout << "x";
                        print = true;
                    }
                }
                //printing empty spaces
                if (!print)
                    cout << " ";
            }
            //right grid
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    cout << " ";
    //bottom grid
    for (int i = 0; i < width + 2; i++)
        cout << "=";
    cout << endl;
    cout << player1 << "'s score: " << score << endl;
    cout << player2 << "'s score: " << score2 << endl;
}
//function to get input 
void Input()
{
    if (_kbhit())           //when a key is pushed _kbhit returns non zero value
    {
        switch (_getch())   //_getch brings the charector from keyboard
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
        case 'x':           //quit button
            gameOver = true;    
            break;

        }
    }
}
//function to get input 
void Input2()
{
    //GetAsyncKeyState is used to indicate whether key is pressed or not
    if (GetAsyncKeyState(VK_LEFT) & 0x8001)
        dir2 = LEFT;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
        dir2 = RIGHT;
    if (GetAsyncKeyState(VK_UP) & 0x8001)
        dir2 = UP;
    if (GetAsyncKeyState(VK_DOWN) & 0x8001)
        dir2 = DOWN;

    if (GetAsyncKeyState('X') & 0x8001)
        gameOver = true;
}
//function for gamelogics
void Logic()
{
    //declaring Array to keep track of tails
    int prevX = tailX[0];       //previous positioning
    int prevY = tailY[0];      
    int prev2X, prev2Y;         //temporary variables to update positioning
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < tail_num; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    //defining movement logic
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
    //logic in case of collision with walls
    if (x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
        cout << player2 << " collided with walls " << endl;
    }

    //    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    //    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    //    for (int i = 0; i < nTail; i++)
    //        if (tailX[i] == x && tailY[i] == y)
    //            gameOver = true;
    
    //logic in case of collision with fruit
    if (x == fruitX && y == fruitY)
    {
        srand(time(0)); // Random seed value for rand based on time
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tail_num++;
    }
}
void Logic2()
{
    int prevX = tailX2[0];
    int prevY = tailY2[0];
    int prev2X, prev2Y;
    tailX2[0] = x2;
    tailY2[0] = y2;
    for (int i = 1; i < tail_num_2; i++)
    {
        prev2X = tailX2[i];
        prev2Y = tailY2[i];
        tailX2[i] = prevX;
        tailY2[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir2)
    {
    case LEFT:
        x2--;
        break;
    case RIGHT:
        x2++;
        break;
    case UP:
        y2--;
        break;
    case DOWN:
        y2++;
        break;
    default:
        break;
    }

    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    if (x2 > width || x2 < 0 || y2 > height || y2 < 0)
    {
        gameOver = true;
        cout << player2 << " collided with walls " << endl;
    }

    //   if (x2 >= width) x2 = 0; else if (x2 < 0) x2 = width - 1;
      // if (y2 >= height) y2 = 0; else if (y2 < 0) y2 = height - 1;

   //    for (int i = 0; i < nTail2; i++)
   //        if (tailX2[i] == x2 && tailY2[i] == y2)
   //            gameOver = true;

    if (x2 == fruitX && y2 == fruitY)
    {
        srand(time(0)); // Random seed value for rand based on time by 'srand'
        score2 += 10;
        fruitX = rand() % width;    //rand() generates random integers w.r.t defined boundaries
        fruitY = rand() % height;
        tail_num_2++;
    }
}
void getname()
{
    cout << "enter player 1 name: ";
    cin.getline(player1,sizeof(player1));

    cout << "enter player 2 name: ";
    cin.getline(player2, sizeof(player2));

    return;
}
void saveResults()
{

    ofstream resultsFile("lexis.txt", ios::app);

    if (resultsFile.is_open()) {

        if (score > score2) {

            resultsFile << "Winner: ";
            resultsFile << player1;
        }
        else if (score2 > score) {

            resultsFile << "Winner: ";
            resultsFile << player2;
        }
        else
            resultsFile << "It's a draw";

        resultsFile << " | Scores: " << player1 << " " << score << " - " << player2 << " " << score2 << endl;

        resultsFile.close();
    }
}
int main()
{
    cout << "WELCOME, TO MULTIPLAYER SNAKE GAME! W,A,S,D FOR PLAYER 1, ARROWS FOR PLAYER 2" << endl;
    cout << "\n" "made by group: daniyal jamil , hafiz hamza(gl),Abdul moiz, aymal ahmad" << endl << "\n";
    getname();
    //Will make cout much faster
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);


    system("MODE con cols=24 lines=25");

    Setup();
    while (!gameOver)
    {

        Draw();
        Input();
        Input2();
        Logic();
        Logic2();
        Sleep(50); //sleep(10);
        if (score > 50 || score2 > 50)
        {
            gameOver = true;
        }
    }



    cout << "============================" << endl;
    if (score > score2)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            cout << "       " << player2 << " won " << endl;
        }
        else
        {
            cout << "       " << player1 << " won" << endl;
        }
    }
    else if (score2 > score)
    {
        if (x2 < 0 || x2 >= width || y2 < 0 || y2 >= height)
        {
            cout << "       " << player1 << " won " << endl;
        }
        else
        {
            cout << "       " << player2 << " won" << endl;
        }
    }
    else
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            cout << "       " << player2 << " won" << endl;
        }
        else if (x2 < 0 || x2 >= width || y2 < 0 || y2 >= height)
        {
            cout << "       " << player1 << " won " << endl;
        }
        else
        {
            cout << "       It's a draw" << endl;
        }
    }
    cout << "============================";
    saveResults();

    return 0;
}
