#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ctype.h>

int getInt(int row, int col, std::vector<std::string> &grid)
{
  int i = col;
  std::string num;
  while (i > 0) {
    i--;
    if (!std::isdigit(grid[row][i])) {
      i++;
      break;
    }
  }

  while (i < grid[0].size()) {
    if (std::isdigit(grid[row][i])) {
      num.push_back(grid[row][i++]);
    }
    else
      break;
  }
  return std::stoi(num);
}

int adjacentNumSum(int row, int col, std::vector<std::string> &grid)
{
  int endRow = row;
  int endCol = col;
  if (row < grid.size())
    endRow++;
  if (col < grid[0].size())
    endCol++;

  if (row > 0)
    row -= 1;
  if (col > 0)
    col -= 1;

  int sum = 0;
  for (int i = row; i <= endRow; i++) {
    for (int j = col; j <= endCol; j++) {
      if (std::isdigit(grid[i][j])) {
        std::cout << i << " " << j << " " << getInt(i, j, grid) << std::endl;
        sum += getInt(i, j, grid);
      }
    }
  }
  
  return sum;
}

int main()
{
  std::ifstream input("input.txt");

  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::string line;
  int sum = 0;

  std::vector<std::string> grid;
  while (std::getline(input, line)) {
    grid.push_back(line);
  }

  input.close();

  std::regex pattern("([-+*/=!?@#$%&])");
  std::smatch match;

  int col = 0;
  for (int i = 0; i < 5/* grid.size()*/; i++) {
    line = grid[i];
    while (std::regex_search(line, match, pattern)) {
      col +=  match.position();
      sum += adjacentNumSum(i, col, grid);
      line = match.suffix();
    }
    col = 0;
  }

  std::cout << "Sum of part numbers = " << sum << std::endl;
  return 0;
}