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
      cout << "|" << grid[j][i].type;      
      count++;
    }
  }
  cout << "\n\n\n\n"  << endl;
  return 1;
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
  if(grid[j+2][i+1].type!=" "){
    // Bishop are a score of 2
    string t = grid[j+2][i+1].type;
    if(t=="b")
      score += 2;
    if(t=="k")
      score += 3;
    if(t=="q")
      score += 4;
    if(t=="K")
      score += 10;
  }
  if(grid[j+2][i-1].type!=" "){
    // Bishop are a score of 2
    string t = grid[j+1][i+2].type;
    if(t=="b")
      score += 2;
    if(t=="k")
      score += 3;
    if(t=="q")
      score += 4;
    if(t=="K")
      score += 10;
  }
  if(grid[j+1][i+2].type!=" "){
    // Bishop are a score of 2
    string t = grid[j-1][i+2].type;
    if(t=="b")
      score += 2;
    if(t=="k")
      score += 3;
    if(t=="q")
      score += 4;
    if(t=="K")
      score += 10;
  }
  if(grid[j+1][i-2].type!=" "){
    // Bishop are a score of 2
    string t = grid[j-2][i+1].type;
    if(t=="b")
      score += 2;
    if(t=="k")
      score += 3;
    if(t=="q")
      score += 4;
    if(t=="K")
      score += 10;
  }
  if(grid[j-2][i-1].type!=" "){
    // Bishop are a score of 2
    string t = grid[j-1][i+2].type;
    if(t=="b")
      score += 2;
    if(t=="k")
      score += 3;
    if(t=="q")
      score += 4;
    if(t=="K")
      score += 10;
  }
  if(grid[j-2][i-1].type!=" "){
    // Bishop are a score of 2
    string t = grid[j-2][i+1].type;
    if(t=="b")
      score += 2;
    if(t=="k")
      score += 3;
    if(t=="q")
      score += 4;
    if(t=="K")
      score += 10;
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
      if(grid[l][m].type == "b"){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m].type == "k"){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m].type == "q"){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m].type == "K"){
        // Queen are a score of 5
        score += 5;
      }
    }
    l = j;
    m = i;
    while((l < height) && (m < width)){
      l++;
      m--;
      if(grid[l][m].type == "b"){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m].type == "k"){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m].type == "q"){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m].type == "K"){
        // Queen are a score of 5
        score += 5;
      }
    }
    l = j;
    m = i;
    while((l < height) && (m < width)){
      l--;
      m++;
      if(grid[l][m].type == "b"){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m].type == "k"){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m].type == "q"){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m].type == "K"){
        // Queen are a score of 5
        score += 5;
      }
    }
    l = j;
    m = i;
    while((l < height) && (m < width)){
      l--;
      m--;
      if(grid[l][m].type == "b"){
        // Bishop are a score of 2
        score += 2;
      }
      if(grid[l][m].type == "k"){
        // Knight are a score of 3
        score += 3;
      }
      if(grid[l][m].type == "q"){
        // Queen are a score of 4
        score += 4;
      }
      if(grid[l][m].type == "K"){
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
      if(grid[l][m].type != " "){
        if(grid[l][m].type == "b"){
          score += 2;
        }
        if(grid[l][m].type == "k"){
          score += 3;
        }
        if(grid[l][m].type == "q"){
          score += 4;
        }
        if(grid[l][m].type  == "K"){
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
  if(grid[x][y]=="p"){
    
  }
  return true;
}

bool init_grid(Piece grid[width][height])
{
    
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < width; j++)
      {
         grid[i][j].type = " ";
      }
    }
    // Pawns
    for(int i = 0; i < width; i++)
    {
      grid[i][1].type = "p";
      grid[i][height-2].type = "p";
    }

    // Bishop
    grid[2][0].type = "b";
    grid[5][0].type = "b";
    grid[2][height-1].type = "b";
    grid[5][height-1].type = "b";

    // Knight
    grid[1][0].type = "k";
    grid[5][0].type = "k";
    grid[2][height-1].type = "k";
    grid[5][height-1].type = "k";

    // Queen
    grid[3][0].type = "q";
    grid[3][height-1].type = "q";

    // King
    grid[4][0].type = "K";
    grid[4][height-1].type = "K";

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



