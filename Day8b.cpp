#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <functional>

struct Node
{
  std::string start;
  std::string left;
  std::string right;
};

class HashTable
{
  int size;
  std::vector<std::list<Node>> table;

  int hashFunc(const std::string &s)
  {
    std::hash<std::string> h;
    return h(s) % size;
  }

  public:
  HashTable(int initialSize) : table(initialSize) {
    size = initialSize;
  }

  void insertItem(const Node &a);

  bool get(const std::string &s, Node &node);
};

void HashTable::insertItem(const Node &a)
{
  int hash = hashFunc(a.start);
  table[hash].push_back(a);
}

bool HashTable::get(const std::string &s, Node &node)
{
  int hash = hashFunc(s);
  for (const Node &n: table[hash]) {
    if (s == n.start) {
      node = n;
      return true;
    }
  }
  return false;
}

long long gcd(long long a, long long b) // greatest common divisor
{
  while (b != 0) {
    long long temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

long long lcm(long long a, long long b) // least common multiple
{
  if (a && b) {
    return std::abs(a * b) / gcd(a, b);
  }
  return 0;
}

long long lcmOfVector(std::vector<int> v)
{
  long long result = v[0];
  for (int i = 1; i < v.size(); i++) {
    result = lcm(result, v[i]);
  }
  return result;
}

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input.txt" << std::endl;
    return -1;
  }

  std::regex pattern("([A-Z0-9]{3}) = \\(([A-Z0-9]{3}), ([A-Z0-9]{3})\\)");
  std::smatch matches;

  std::string instructions;
  getline(input, instructions);

  HashTable hashTable(10000);
  std::string line;
  std::vector<Node> A;
  while (std::getline(input, line)) {
    if (std::regex_search(line, matches, pattern)) {
      Node n = {matches[1].str(), matches[2].str(), matches[3].str()};
      hashTable.insertItem(n);
      if (matches[1].str().back() == 'A') {
        A.push_back(n);
      }
    }
  }
  input.close();

  std::vector<int> stepsToZ;
  for (int i = 0; i < A.size(); i++) {
    int steps = 0;
    while (true) {
      int index = steps % instructions.size();
      if (instructions[index] == 'L') {
        hashTable.get(A[i].left, A[i]);
      }
      else {
        hashTable.get(A[i].right, A[i]);
      }
      steps++;
      if (A[i].start.back() == 'Z') {
        stepsToZ.push_back(steps);
        break;
      }
    }
  }

  long long steps = lcmOfVector(stepsToZ);

  std::cout << "steps = " << steps << std::endl;
 
  return 0;
}