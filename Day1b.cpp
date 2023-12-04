#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>

int main()
{
  std::ifstream input("input.txt");

  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::vector<std::string> numbers = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  std::string line;
  int total = 0;

  while (std::getline(input, line)) {
    int n = 0;
    int a = 0;
    int b = 0;
    int aIndex = INT32_MAX;
    int bIndex = INT32_MIN;
    for (int i = 0; i < numbers.size(); i++) {
      if ((n = line.find(numbers[i])) != std::string::npos) {
        if (n <= aIndex) {
          aIndex = n;
          a = i;
        }
      }
      if ((n = line.rfind(numbers[i])) != std::string::npos) {
        if (n >= bIndex) {
          bIndex = n;
          b = i;
        }
      }
    }
    if (a > 8)
      a -= 9;
    if (b == INT32_MIN)
      b = a;
    else if (b > 8)
      b -= 9;
    a++;
    b++;
    total += a * 10 + b;
  }
  std::cout << "Total = " << total << std::endl;
  
  return 0;
}