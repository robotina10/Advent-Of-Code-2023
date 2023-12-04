#include <iostream>
#include <fstream>
#include <string>

int main()
{
  std::ifstream input("input.txt");

  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::string line;
  int total = 0;

  while (std::getline(input, line)) {
    int a = 0;
    int b = -1;

    for (int n: line) {
      n -= 48;
      if (n >= 0 && n < 10) {
        if (a)
          b = n;
        else
          a = n;
      }
    }
    if (b < 0)
      b = a;
    total += a * 10 + b;
  }
  std::cout << "Total = " << total << std::endl;
  
  return 0;
}