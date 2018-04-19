#include <bits/stdc++.h>
#include "windows.h"
using namespace std;
#define BLANK 0
#define N 9
typedef vector<vector<int>> vvi;

//Set x, y co-ordinates
void gotoxy(int x, int y){
  COORD coord;
  coord.X=x;
  coord.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//find the block in the grid whose value is not yet recognised
bool findBlankLoc(vvi &grid, int &row, int &col){
  for(row = 0; row < N; row++)
    for(col = 0; col < N; col++)
      if(grid[row][col] == BLANK) return true;
  return false;
}

//Check whether a num is present in a respective row or not
bool inRow(vvi &grid, int row, int num){
  for(int i =0 ; i < N; i++)
    if(grid[row][i] == num) return true;
  return false;
}

//Check where a num is present in a respective column or not
bool inCol(vvi &grid, int col, int num){
  for(int i = 0; i < N; i++)
    if(grid[i][col] == num) return true;
  return false;
}

//Check whether a num is present in a 3x3-sized block of the grid or not
bool inBox(vvi &grid, int boxBegRow, int boxBegCol, int num){
  for(int row = 0; row < 3; row++)
    for(int col = 0; col <3; col++)
      if(grid[row + boxBegRow][col + boxBegCol] == num) return true;
  return false;
}

/*
* Check whether is it possible to insert a num at the block or not
* This only happens if Num is not present in the row, column or
* 3x3-sized block of the Grid
*/
bool isSafe(vvi &grid, int &row, int &col, int &num){
  return !inRow(grid, row, num) && !inCol(grid, col, num) &&
  !inBox(grid, row-row%3, col - col%3, num);
}

// Function to solve the sudoku problem
bool solveSudoku(vvi &grid){
  int row, col;
  if(!findBlankLoc(grid,row,col)) return true;
  for(int num = 1; num <= N; num++ ){
    if(isSafe(grid,row,col,num)){
      grid[row][col] = num;
      if(solveSudoku(grid)) return true;
      grid[row][col] = BLANK;
    }
  }
  return false;
}

//print the solved sudoku
void printSolution(vvi &grid);

//Utility function that calls solveSudoku to solve sudoku
void solveSudokuUtil(vvi &grid){
  if(solveSudoku(grid)) printSolution(grid);
  else {
    system("cls");
    gotoxy(30,11);
    cout << "No Solution Exists";
  }
}

//Get unsolved sudoku from the user
void getGrid(vvi &grid){
  system("cls");
  int x = 30 , y = 11;
  gotoxy(x++,y++);
  cout << "Enter the sudoku (0 for Blank): ";
  x += 3;
  y++;
  for(int i=0; i < N; i++){
    gotoxy(x,y++);
    for(int j = 0; j < N; j++)
      cin >>grid[i][j];
  }
  solveSudokuUtil(grid);
}

void printSolution(vvi &grid){
  int x = 34, y = 13;
  system("cls");
  for(int row = 0; row < N; row++){
    gotoxy(x,y++);
    for(int col = 0; col < N; col++)
      cout << grid[row][col] << " ";
  }
  y+=3;
  x-=3;
  gotoxy(x,y++);
  cout << "Y : Solve Next Suduko | Any other key to exit";

  gotoxy(x,y++);
  char ch;
  cin.ignore();
  ch = cin.get();
  if(ch  == '\n'){
    system("cls");
    gotoxy(0,11);
    cout << "Exiting";
    return;
  }
  else if(ch == 'Y' || ch == 'y'){
    getGrid(grid);
  }
  else{
    system("cls");
    gotoxy(0,11);
    cout << "Exiting";
    return;
  }
}

int main(){
  vvi grid(9,vector<int> (9,BLANK));
  getGrid(grid);
  return 0;
}

/* Test sudoku: Level: HARD
0 0 0 0 0 0 0 0 0
0 0 8 6 4 7 9 0 0
0 2 0 0 3 0 0 6 0
1 0 0 0 5 0 0 0 4
5 4 0 0 8 0 0 9 3
7 0 0 0 9 0 0 0 6
0 9 0 0 1 0 0 3 0
0 0 5 9 6 8 1 0 0
0 0 0 0 0 0 0 0 0
-------sol-------
6 7 1 8 2 9 3 4 5
3 5 8 6 4 7 9 2 1
9 2 4 5 3 1 8 6 7
1 6 9 7 5 3 2 8 4
5 4 2 1 8 6 7 9 3
7 8 3 2 9 4 5 1 6
2 9 7 4 1 5 6 3 8
4 3 5 9 6 8 1 7 2
8 1 6 3 7 2 4 5 9
*/
