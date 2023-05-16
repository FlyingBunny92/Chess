#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <tuple>

using namespace std;


const int width = 8;
const int height = 8;


class Piece {       // The class
  public:             // Access specifier
    int team;        // Attribute (int variable) 1 for white. 2 for black.
    string type;  // Attribute (string variable)
};



int print_board(Piece grid[width][height])
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

int print_board_with_position(Piece grid[width][height], int x, int y)
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

bool complete(Piece grid[width][height])
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


bool check(Piece grid[width][height], int x, int y, int num)
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

std::tuple<int, int> find_random_empty_spot(Piece grid[width][height])
{
    int random_width = rand() % width;
    int random_height = rand() % height;
    while(grid[random_width][random_height] != 0){
      random_width = rand() % width;
      random_height = rand() % height;
    }
    return  {random_width, random_height};
}

std::tuple<int, int> find_empty_spot(Piece grid[width][height])
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

int calculate_pawn_score(Piece grid[width][height], int score, int j, int i){
      // Pawn
      if(grid[j+1][i+1].type=="p"){
        score++;
      }
      if(grid[j-1][i+1].type=="p"){
        score++;
      }
      return score;
}

int calculate_knight_score(Piece grid[width][height], int score, int j, int i){
  // Knight
  if(grid[j+2][i+1].type=="b"){
    // Bishop are a score of 2
    score += 2;
  }
  if(grid[j+1][i+2].type=="k"){
    // Knight are a score of 3
    score += 3;
  }
  if(grid[j-1][i+2].type=="q"){
    // Queen are a score of 4
    score += 4;
  }
  if(grid[j-2][i+1].type == 'K2'){
    // Queen are a score of 5
    score += 5;
  }
  if(grid[j-1][i-2].type == 'q2'){
    // Queen are a score of 4
    score += 4;
  }
  if(grid[j-2][i-1].type == 'K2'){
    // Queen are a score of 5
    score += 5;
  }


  return score;
}


int calculate_bishop_score(Piece grid[width][height], int score, int j, int i){
    // Bishop
    int l = j;
    int m = i;
    while((l < height) && (m < width)){
      l++;
      m++;
      if(grid[l][m] == 'b2'){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m] == 'k2'){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m] == 'q2'){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m] == 'K2'){
        // Queen are a score of 5
        score += 5;
      }
    }
    l = j;
    m = i;
    while((l < height) && (m < width)){
      l++;
      m--;
      if(grid[l][m] == 'b2'){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m] == 'k2'){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m] == 'q2'){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m] == 'K2'){
        // Queen are a score of 5
        score += 5;
      }
    }
    l = j;
    m = i;
    while((l < height) && (m < width)){
      l--;
      m++;
      if(grid[l][m] == 'b2'){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m] == 'k2'){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m] == 'q2'){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m] == 'K2'){
        // Queen are a score of 5
        score += 5;
      }
    }
    l = j;
    m = i;
    while((l < height) && (m < width)){
      l--;
      m--;
      if(grid[l][m] == 'b2'){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m] == 'k2'){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m] == 'q2'){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m] == 'K2'){
        // Queen are a score of 5
        score += 5;
      }
    }

    return score;
}

int calculate_queen_score(Piece grid[width][height], int score, int j, int i){
  // Queen

  // Check the box
  for(int l = j-1; l <= j+1; l++){
    for(int m = i-1; m <= i+1; m++){
      if(grid[l][m] != ' '){
        if(grid[l][m] == 'b2'){
          score += 2;
        }
        if(grid[l][m] == 'k2'){
          score += 3;
        }
        if(grid[l][m] == 'q2'){
          score += 4;
        }
        if(grid[l][m] == 'K2'){
          score += 5;
        }
      }
    }
  }

  // Check the Bishops path
  calculate_bishop_score(grid, score, j, i);

  return score;
}

bool calculate_score_p1(Piece grid[width][height], int x, int y){
  int score = 0;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){ 
      // Pawn
      calculate_pawn_score(grid, score, j, i);
      
      // Calculate Bishop Score
      calculate_bishop_score(grid, score, j, i);

      // Knight
      calculate_knight_score(grid, score, j, i);

      // Queen

    }
  }
  return true;
}

bool move_pawn(Piece grid[width][height], int x, int y){
  if(grid[x][y]=='p'){
    
  }
  return true;
}

bool init_grid(Piece grid[width][height])
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
      grid[i][1] = 'p1';
      grid[i][height-2] = 'p2';
    }

    // Bishop
    grid[2][0] = 'b1';
    grid[5][0] = 'b1';
    grid[2][height-1] = 'b2';
    grid[5][height-1] = 'b2';

    // Knight
    grid[1][0] = 'k1';
    grid[5][0] = 'k1';
    grid[2][height-1] = 'k2';
    grid[5][height-1] = 'k2';

    // Queen
    grid[3][0] = 'q1';
    grid[3][height-1] = 'q2';

    // King
    grid[4][0] = 'K1';
    grid[4][height-1] = 'K2';

    return true;
}

bool solve(Piece grid[width][height])
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
    Piece grid[width][height];
    init_grid(grid);
    print_board(grid);
}



