#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

struct Pos
{
  int x;
  int y;
};

bool isPipe(int x, int y, std::vector<std::string> &board)
{
  if (board[x][y] == '.') {
    return 0;
  }
  return 1;
}

void findNeighbours(std::vector<Pos> &neighbours, Pos curr, std::vector<std::string> &board) 
{
  int x = board[0].size();
  int y = board.size();
  if (curr.x + 1 < x && isPipe(curr.x + 1, curr.y, board)) {
    neighbours.push_back({curr.x + 1, curr.y});
  }
  if (curr.x - 1 >= 0 && isPipe(curr.x - 1, curr.y, board)) {
    neighbours.push_back({curr.x - 1, curr.y});
  }
  if (curr.y + 1 < y && isPipe(curr.x, curr.y + 1, board)) {
    neighbours.push_back({curr.x, curr.y + 1});
  }
  if (curr.y - 1 >= 0 && isPipe(curr.x, curr.y - 1, board)) {
    neighbours.push_back({curr.x, curr.y - 1});
  }
}

bool findStart(Pos &start, std::vector<std::string> &board)
{
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[i][j] == 'S') {
        start = {i, j};
        return true;
      }
    }
  }
  return false;
}

bool canConnect(Pos curr, Pos next, std::vector<std::string> &board)
{
  char pipe = board[next.x][next.y];
| is a vertical pipe connecting north and south.
- is a horizontal pipe connecting east and west.
L is a 90-degree bend connecting north and east.
J is a 90-degree bend connecting north and west.
7 is a 90-degree bend connecting south and west.
F is a 90-degree bend connecting south and east.
  switch (board[curr.x][curr.y]) {
    case '|':
      if (pipe == 'L' || pipe == 'J' || pipe == '7' || pipe == 'F') {
        return 1;
      }
      break;
    case '-':
      if (pipe == 'L' || pipe == 'J') {
        return 1;
      }
      break;
    case 'L':
      if (pipe == '|' || pipe == '-' || pipe == 'J') {
        return 1;
      }
      break;
    case 'J':
      if () {
        return 1;
      }
      break;
    case '7':
      if () {
        return 1;
      }
      break;
    case 'F':
      if () {
        return 1;
      }
      break;
  }
  return false;
}

int findFarthestPoint(Pos start, std::vector<std::string> &board)
{
  int steps = 1;
  Pos prev = start;
  Pos curr = start;

  do {
    std::vector<Pos> neighbours;
    findNeighbours(neighbours, curr, board);

    for (Pos n: neighbours) {
      if (n.x == prev.x && n.y == prev.y) {
        continue;
      }
      if (canConnect(curr, n, board)) {
        prev = curr;
        curr = n;
        steps++;
        break;
      }
    }
  }
  while (curr.x != start.x && curr.y != start.y);

  return steps / 2;
}

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
  }

  std::vector<std::string> board;
  int i = 0;
  while (std::getline(input, board[i])) {
    i++;
  }

  Pos start;
  findStart(start, board);

  int steps = findFarthestPoint(start, board);

  std::cout << "Steps " << steps << std::endl;
  return 0;
}