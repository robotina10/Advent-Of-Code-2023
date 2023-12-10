#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ctype.h>

int isAdjacent(int col, int startPos, int endPos)
{
  int a = startPos == col || endPos == col;
  int b = startPos == col - 1 || endPos == col - 1;
  int c = startPos == col + 1 || endPos == col + 1;
  int d = startPos < col && endPos > col;
  //a = 0;
  //b = 0;
  //c = 0;
  //d = 0;
  if (a || b || c || d)
    return 1;
  return 0;
}

int findGearRatio(int row, int col, std::vector<std::string> &grid)
{
  int endRow = row;
  if (endRow + 1 < grid.size())
    endRow++;

  if (row > 0)
    row -= 1;

  std::smatch match;
  std::regex pattern("(\\d+)");

  int a = 0;
  int b = 0;
  for (int i = row; i <= endRow; i++) {
    std::string line = grid[i];

    int startPos = 0;
    int endPos = 0;
    while (std::regex_search(line, match, pattern)) {
      startPos += match.position();
      endPos = startPos + match[1].str().length() - 1;
      if (isAdjacent(col, startPos, endPos)) {
        if (a) {
          b = std::stoi(match[1].str());             
          return a * b;
        }
        else {
          a = std::stoi(match[1].str());
        }
      }
      else if (endPos > col + 1) {
        break;
      }
      startPos = endPos + 1;
      line = match.suffix();
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

  std::regex pattern("(\\*)");
  std::smatch match;

  int sum = 0;
  for (int i = 0; i < grid.size(); i++) {
    int col = 0;
    line = grid[i];
    while (std::regex_search(line, match, pattern)) {
      col += match.position();
      sum += findGearRatio(i, col, grid);
      col++;
      line = match.suffix();
    }
  }

  std::cout << "Sum of gear ratios = " << sum << std::endl;
  return 0;
}