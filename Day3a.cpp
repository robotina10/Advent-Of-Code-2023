#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ctype.h>

int hasAdjacentSymbol(int row, int col, int digits, std::vector<std::string> &grid)
{
  int endRow = row;
  int endCol = col + digits;
  if (endRow + 1 < grid.size())
    endRow++;
  if (endCol + 1 < grid[0].size())
    endCol++;

  if (row > 0)
    row -= 1;
  if (col > 0)
    col -= 1;

  for (int i = row; i <= endRow; i++) {
    for (int j = col; j <= endCol; j++) {
      if (grid[i][j] != '.' && !std::isdigit(grid[i][j])) {
        return 1;
      }
    }
  }
  return 0;
}

int main()
{
  std::ifstream input("input.txt");

  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::string line;

  std::vector<std::string> grid;
  while (std::getline(input, line)) {
    grid.push_back(line);
  }

  input.close();

  std::regex pattern("(\\d+)");
  std::smatch match;

  int col = 0;
  int sum = 0;
  for (int i = 0; i < grid.size(); i++) {
    line = grid[i];
    while (std::regex_search(line, match, pattern)) {
      col += match.position();
      if (hasAdjacentSymbol(i, col, match[1].str().length() - 1, grid)) {
        sum += std::stoi(match[1].str());
      }
      col += match[1].str().length();
      line = match.suffix();
    }
    col = 0;
  }

  std::cout << "Sum of part numbers = " << sum << std::endl;
  return 0;
}
