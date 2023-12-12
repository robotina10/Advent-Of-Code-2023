#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input" << std::endl;
    return 1;
  }

  std::smatch match;
  std::regex skipPattern("(Card\\s+\\d+:)");
  std::regex winningPattern("(\\d+) (\\|)?");
  std::regex numberPattern("(\\d+)");

  int totalPoints = 0;
  std::string line;
  while (std::getline(input, line)) {
    std::regex_search(line, match, skipPattern);
    line = match.suffix();
    int nums[100];
    for (int i = 0; i < 100; i++) {
      nums[i] = 0;
    }

    while (std::regex_search(line, match, winningPattern)) {
      std::cout << match[1].str() << match[2].str() << std::endl;
      nums[std::stoi(match[1].str())] = 1;
      line = match.suffix();
      if (match[2].matched) {
        break;
      }
    }
    int points = 0;
    while (std::regex_search(line, match, numberPattern)) {
      int num = std::stoi(match[1].str());
      if (nums[num]) {
        if (!points) {
          points = 1;
        }
        else {
          points *= 2;
        }
      }
      line = match.suffix();
    }
    totalPoints += points;
  }
  std::cout << "Worth of cards in points is " << totalPoints << std::endl;
  return 0;
}