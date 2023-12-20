#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

int main()
{
  std::fstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::regex timePattern("Time: ");
  std::regex distPattern("Distance: ");
  std::regex numPattern("(\\d+)+");

  std::smatch match;

  std::string line;

  std::vector<int> times;
  std::vector<int> distances;

  while (std::getline(input, line)) {
    int time = 0;
    int dist = 0;
    if (std::regex_search(line, timePattern)) {
      time = 1;
    }
    else if (std::regex_search(line, distPattern)) {
      dist = 1;
    }
    while (std::regex_search(line, match, numPattern)) {
      if (time) {
        times.push_back(std::stoi(match[1].str()));
      }
      else if (dist) {
        distances.push_back(std::stoi(match[1].str()));
      }
      line = match.suffix();
    }
  }

  if (times.size() != distances.size()) {
    std::cout << "Invalid input times.size() != distances.size()\n";
    return 1;
  }

  int total = 0;
  for (int i = 0; i < distances.size(); i++) {
    int time = times[i];
    int recordDist = distances[i];
    int possibleRecords = 0;
    for (int t = 0; t < time; t++) {
      int remainingTime = time - t;
      if (remainingTime * t > recordDist) {
        possibleRecords++;
      }
    }
    if (!total && possibleRecords > 0) {
      total = 1;
    }
    total *= possibleRecords;
  }
  std::cout << "Total = " << total << std::endl;

  return 0;
}