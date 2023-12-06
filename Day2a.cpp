#include <iostream>
#include <string>
#include <fstream>
#include <regex>


int main()
{
  std::fstream input("input.txt");

  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::string line;

  int redCubes = 12;
  int greenCubes = 13;
  int blueCubes = 14;

  int id = 1;
  int totalID = 0;

  std::regex pattern("(\\d+) (red|green|blue)");
  std::smatch match;

  while (std::getline(input, line)) {
    bool valid = true;
    int maxRed = 0;
    int maxGreen = 0;
    int maxBlue = 0;

    while (std::regex_search(line, match, pattern)) {
      if (!match[1].matched || !match[2].matched) {
        continue;
      }

      int num = std::stoi(match[1].str());
      std::string color = {match[2].str()};

      if (color == "red" && num > maxRed) {
        maxRed = num;
      }
      else if (color == "green" && num > maxGreen) {
        maxGreen = num;
      }
      else if (color == "blue" && num > maxBlue) {
        maxBlue = num;
      }

      if (maxRed > redCubes || maxBlue > blueCubes || maxGreen > greenCubes) {
        valid = false;
        break;
      }

      line = match.suffix();
    }

    if (valid) {
      totalID += id;
    }
    id++;
  }
  std::cout << "TotalID = " << totalID << std::endl;

  return 0;
}