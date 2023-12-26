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

  Node get(const std::string &s);

};

void HashTable::insertItem(const Node &a)
{
  int hash = hashFunc(a.start);
  table[hash].push_back(a);
}

Node HashTable::get(const std::string &s)
{
  int hash = hashFunc(s);
  for (const Node &n: table[hash]) {
    if (s == n.start) {
      return n;
    }
  }
}

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input.txt" << std::endl;
    return -1;
  }

  std::regex pattern("([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)");
  std::smatch matches;

  std::string instructions;
  getline(input, instructions);

  HashTable hashTable(10000);
  std::string line;
  while (std::getline(input, line)) {
    if (std::regex_search(line, matches, pattern)) {
      hashTable.insertItem({matches[1].str(), matches[2].str(), matches[3].str()});
    }
  }
  input.close();

  Node current = hashTable.get("AAA");
  int steps = 0;
  int i = 0;
  while (true) {
    if (i == instructions.size()) {
      i = 0;
    }
    if (instructions[i++] == 'L') {
      current = hashTable.get(current.left);
    }
    else {
      current = hashTable.get(current.right);
    }
    steps++;
    if (current.start == "ZZZ") {
      break;
    }
  }

  std::cout << "steps = " << steps << std::endl;
 
  return 0;
}