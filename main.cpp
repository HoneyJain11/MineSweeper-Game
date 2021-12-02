#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#define BOMB '*'
#define CELL '+'
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define USER_POS '#'
#define PRESS 'p'
#define PRESSED ' '

using namespace std;

int rows = 9, columns = 9, bombs = 10 , isGameFinished = 0;
char board [100][100],inputBoard[100][100];
bool uncovered[100][100];
int userRows = 0;
int userColumns = 0;

bool IsInside (int row , int col)
{
  return 0 <= row && row < rows && 0 <= col && col < columns;
}
void PlaceBombs()
{
  vector<pair<int , int>> positions;
    for(int x = 0; x < rows; ++x)
    for(int y = 0; y < columns; ++y)
    positions.push_back(make_pair(x,y));
    random_shuffle(positions.begin(),positions.end());
    for(int i =0 ; i< bombs; ++i)
    {
      board[positions[i].first][positions[i].second] = BOMB;
    }
}
int CalculateNo(int x,int y)
{
  int numBombs = 0;
  for(int x_offset = -1; x_offset <= 1; ++x_offset)
    for(int y_offset = -1; y_offset <= 1; ++y_offset)
    {
      int nextRow = x + x_offset , nextColumn = y + y_offset;
      if(IsInside(nextRow,nextColumn) && board[nextRow][nextColumn] == BOMB)
      ++numBombs;
    }    
        return numBombs;

}
void InitializeBoard()
{
    for(int x = 0; x < rows; ++x)
    for(int y = 0; y < columns; ++y)
    board[x][y] = inputBoard [x][y] = CELL;
    PlaceBombs();
    for(int x = 0; x < rows; ++x)
    for(int y = 0; y < columns; ++y)
    if(board[x][y] != BOMB)
    board[x][y] = CalculateNo(x,y) + '0';
}
void PrintBoard()
{
  for(int x = 0; x < rows; ++x)
  {
      for(int y = 0; y < columns; ++y)
  {
    cout<< inputBoard[x][y];
  }
    cout<<"\n";
  }
}
void TriggerPress(int row,int column)
{
  if(uncovered[row][column])
  return;
  if(board[row][column]==BOMB)
  {
    isGameFinished = 1;
    cout << "Game Over !\n";
     for(int x = 0; x < rows; ++x)
    {
        for(int y = 0; y < columns; ++y)
        if(board [x][y] == BOMB)
        cout << BOMB;
        else
         cout<< inputBoard[x][y];
         cout << "\n";
    }    
  }
  else 
  {
    uncovered[row][column] = 1;
    inputBoard[row][column] = board[row][column];
    if(inputBoard[row][column] == '0')
    {
     for(int x_offset = -1; x_offset <= 1; ++x_offset)
      for(int y_offset = -1; y_offset <= 1; ++y_offset)
      {
      int nextRow = row + x_offset , nextColumn = column + y_offset;
      if(IsInside(nextRow,nextColumn))
        TriggerPress(nextRow,nextColumn);
      }
    }
  }
}

void ProcessCommand(char command)
{
  int nextRow = userRows , nextColumn = userColumns;
  if(command == UP)
  {
    --nextRow;
  }
  else if (command == DOWN)
  {
     ++nextRow;
  }
  else if (command == RIGHT)
  {
   ++nextColumn;
  }
  else if (command == LEFT)
  {
   --nextColumn;
  }
  if(!IsInside(nextRow,nextColumn))
  return;
  if(!uncovered[userRows][userColumns])
  inputBoard[userRows][userColumns] = CELL;
  else
  inputBoard[userRows][userColumns] = board[userRows][userColumns];
  userRows = nextRow;
  userColumns = nextColumn;
  inputBoard[userRows][userColumns] = USER_POS;
  if(command == PRESS)
  {
    TriggerPress(userRows,userColumns);
  }
}
void StartGame()
{
 userRows = userColumns = 0; 
 isGameFinished = 0; 
 InitializeBoard();
 inputBoard[userRows][userColumns] = USER_POS;
}
bool CheckGameover()
{
  int covered = 0;
  for(int x = 0; x < rows; ++x)
    for(int y = 0; y < columns; ++y)
    covered = covered + 1 - uncovered[x][y];
    if(covered == BOMB)
    {
      cout<<"Congrats\nYou Won the Game !\n";
      isGameFinished = 1;
      return true;
    }
    return false;
}
int main() 
{
  srand(time(0)); 
 
  StartGame();
   while(!isGameFinished)
  {
    PrintBoard();
    char command;
    cout<<"Input Command : ";
    cin>> command;
    ProcessCommand(command);
    isGameFinished = CheckGameover(); 
  } 
} 