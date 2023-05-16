#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <tuple>

using namespace std;


const int width = 8;
const int height = 8;




int print_board(char grid[width][height])
{
  cout << "\n\n\n\n"  << endl;
  int count = 0;
  for(int i = 0; i < width; i++){
    cout << "\n"  << endl;
    for(int j = 0; j < height; j++){
      cout << "|" << grid[j][i];      
      count++;
    }
  }
  cout << "\n\n\n\n"  << endl;
  return 1;
}

int print_board_with_position(char grid[width][height], int x, int y)
{
  int count = 0;
  for(int i = 0; i < width; i++){
    cout << "\n"  << endl;
    for(int j = 0; j < height; j++){
      if(x==j && y==i){
        cout << "|" << grid[i][j];
      }else{
        cout << " " << grid[i][j];
      }
      
      count++;
    }
  }
  return 1;
}

bool complete(char grid[width][height])
{
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(grid[i][j]==0){
        cout << "\n Sudoku is not complete \n"  << endl;
        return false;
      }
    }
  }
  cout << "\n Sudoku is complete  \n"  << endl;
  print_board(grid);
  return true;
}


bool check(char grid[width][height], int x, int y, int num)
{
  // check column
  for(int m=0; m<width; m++){
    if(grid[m][y]==num){
      cout << "\n Return_#1 \n";
      return false;
    }
  }
  // check row
  for(int n=0; n<height; n++){
    if(grid[x][n]==num){
      cout << "\n Return_#2 \n";
      return false;
    }
  }
  // check box
  int x0 = x - (x%3);
  int y0 = y - (y%3);
  cout << "\n x0: " << x0 << endl;
  cout << "\n y0: " << y0 << endl;
  print_board_with_position(grid, x0, y0);
  for(int l = 0; l < 3; l++){
    for(int m = 0; m < 3; m++){
        if(grid[x0+l][y0+m]==num){
            cout << "\n Return_#3 \n";
            return false;
        }
    }
  }


  return true;
}

std::tuple<int, int> find_random_empty_spot(char grid[width][height])
{
    int random_width = rand() % width;
    int random_height = rand() % height;
    while(grid[random_width][random_height] != 0){
      random_width = rand() % width;
      random_height = rand() % height;
    }
    return  {random_width, random_height};
}

std::tuple<int, int> find_empty_spot(char grid[width][height])
{
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        if(grid[i][j]==0){
          return  {i, j};
        }
      }
    }
    return  {-1, -1};
}


bool move_pawn(char grid[width][height], int x, int y){
  if(grid[x][y]=='p'){
    // grid[x][y] = 
  }
  return true;
}

bool init_grid(char grid[width][height])
{
    
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < width; j++)
      {
         grid[i][j] = ' ';
      }
    }
    // Pawns
    for(int i = 0; i < width; i++)
    {
      grid[i][1] = 'p';
      grid[i][height-2] = 'p';
    }

    // Bishop
    grid[2][0] = 'b';
    grid[5][0] = 'b';
    grid[2][height-1] = 'b';
    grid[5][height-1] = 'b';

    // Knight
    grid[1][0] = 'k';
    grid[5][0] = 'k';
    grid[2][height-1] = 'k';
    grid[5][height-1] = 'k';

    // Queen
    grid[3][0] = 'q';
    grid[3][height-1] = 'q';

    // King
    grid[4][0] = 'K';
    grid[4][height-1] = 'K';

    return true;
}

bool solve(char grid[width][height])
{
  auto [x, y] = find_empty_spot(grid);
  cout << "\n x : " <<  x << endl;
  cout << "\n y : " <<  y << endl;
  if(x == -1 || y == -1){
    print_board(grid);
    cout << "\n\n ------------COMPLETED------------ \n\n";
    return true;
  }
  for(int i = 1; i <= 9; i++){
    if(check(grid, x, y, i)){
      grid[x][y] = i;
      cout << "\n grid[x][y] = i; \n";
      cout << "\n i : " <<  i << endl;
      if(solve(grid)){
        return true;
      }
      grid[x][y] = 0;
    }
  }
  return false;
}


int main () {
    char grid[width][height];
    init_grid(grid);
    print_board(grid);
}



