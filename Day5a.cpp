#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input" << std::endl;
    return 1;
  }

  std::regex seedPattern("(\\d+)");
  std::regex linePattern("(\\d+) (\\d+) (\\d+)");
  std::regex mapPattern("map");
  std::smatch matches;

  std::vector<long long> source;
  std::vector<long long> destination;

  std::string line;
  std::getline(input, line);
  while (std::regex_search(line, matches, seedPattern)) {
    long long s = std::stoll(matches[1].str());
    source.push_back(s);
    destination.push_back(s);
    line = matches.suffix();
  }

  while (std::getline(input, line)) {

    if (std::regex_search(line, mapPattern)) {
      source = destination;
      continue;
    }
    
    while (std::regex_search(line, matches, linePattern)) {
      long long dest = std::stoll(matches[1].str());
      long long src = std::stoll(matches[2].str());
      long long range = std::stoll(matches[3].str());

      for (int i = 0; i < source.size(); i++) {
        if (source[i] >= src && source[i] <= src + range - 1) {
          long long sourceRange = source[i] - src;
          destination[i] = dest + sourceRange;
        }
      }
      line = matches.suffix();
    }
  }
  std::sort(destination.begin(), destination.end());

  std::cout << "Lowest location for the initial seed numbers is " << destination[0] << std::endl;
  return 0;
}