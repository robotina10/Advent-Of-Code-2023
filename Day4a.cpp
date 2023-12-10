#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input" << std::endl;
    return 1;
  }

  std::regex winningPattern("(\\d+)+ |");
  std::regex numberPattern("| (\\d+)+");
  std::smatch match;

  std::string line;
  while (std::getline(input, line)) {
    while (std::regex_search(line, match, numberPattern))
  }
  return 0;
}