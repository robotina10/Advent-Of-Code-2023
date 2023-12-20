#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <cmath>

int numDigits(long long n) {
  int x = 0;
  while (n > 0) {
    n /= 10;
    x++;
  }
  return x;
}

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

  long long time = 0;
  long long recordDist = 0;
  int exponent1 = 0;
  int exponent2 = 0;
  for (int i = times.size() - 1; i >= 0; i--) {
    time += times[i] * std::pow(10, exponent1);
    recordDist += distances[i] * std::pow(10, exponent2);
    exponent1 = numDigits(time);
    exponent2 = numDigits(recordDist);
  }

  long long possibleRecords = 0;
  for (long long t = 0; t < time; t++) {
    long long remainingTime = time - t;
    if (remainingTime * t > recordDist) {
      possibleRecords++;
    }
    else if (possibleRecords > 0) {
      break;
    }
  }

  std::cout << "Total = " << possibleRecords << std::endl;

  return 0;
}