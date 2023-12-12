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

  int cardIndex = 0;
  int instances[1000];
  for (int i = 0; i < 1000; i++) {
    instances[i] = 1;
  }

  int totalScratchcards = 0;
  std::string line;
  while (std::getline(input, line)) {
    std::regex_search(line, match, skipPattern);
    line = match.suffix();
    int nums[100];
    for (int i = 0; i < 100; i++) {
      nums[i] = 0;
    }

    while (std::regex_search(line, match, winningPattern)) {
      nums[std::stoi(match[1].str())] = 1;
      line = match.suffix();
      if (match[2].matched) {
        break;
      }
    }
    int nextInstance = cardIndex + 1;
    while (std::regex_search(line, match, numberPattern)) {
      int num = std::stoi(match[1].str());
      if (nums[num]) {
        instances[nextInstance++] += instances[cardIndex];
      }
      line = match.suffix();
    }
    totalScratchcards += instances[cardIndex];
    cardIndex++;
  }
  std::cout << "Total number of scrathcards is " << totalScratchcards << std::endl;
  return 0;
}