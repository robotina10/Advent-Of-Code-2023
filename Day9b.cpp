#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

void generateDifferences(std::vector<std::vector<int>> &vec)
{
  while (true) {
    vec.push_back({});
    int size = vec.size() - 1;
    int prev = vec[size - 1][0];

    for (int i = 1; i < vec[size - 1].size(); i++) {
      int curr = vec[size - 1][i];
      vec[size].push_back(curr - prev);
      prev = vec[size - 1][i];
    }

    bool brk = true;
    for (int n: vec[size]) {
      if (n != 0) {
        brk = false;
        break;
      }
    }
    if (brk) {
      return;
    }
  }
}

int extrapolate(std::vector<std::vector<int>> &vec )
{
  for (int i = vec.size() - 1; i > 0; i--) {
    vec[i - 1].insert(vec[i-1].begin(), vec[i - 1][0] - vec[i][0]);
  }
  return vec[0][0];
}

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
  }

  std::regex pattern("(-?\\d+)");
  std::smatch match;

  std::string line;

  long long sum = 0;
  while (std::getline(input, line)) {
    std::vector<std::vector<int>> extrapolations;
    extrapolations.push_back({});
    while (std::regex_search(line, match, pattern)) {
      extrapolations[0].push_back(std::stoi(match[1].str()));
      line = match.suffix();
    }
    generateDifferences(extrapolations);
    sum += extrapolate(extrapolations);
  }

  std::cout << "Sum of extapolated previous values is " << sum << std::endl;
  return 0;
}