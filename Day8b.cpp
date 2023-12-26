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
  std::vector<Node> A;
  while (std::getline(input, line)) {
    if (std::regex_search(line, matches, pattern)) {
      Node n = {matches[1].str(), matches[2].str(), matches[3].str()};
      hashTable.insertItem(n);
      if (matches[1].str()[n.start.size() - 1] == 'A') {
        A.push_back(n);
      }
    }
  }
  for (Node n: A){
  std::cout << n.start << std::endl;}
  input.close();

  int steps = 0;
  while (true) {
    int index = steps % instructions.size();
    for (int i = 0; i < A.size(); i++) {
      if (instructions[index] == 'L') {
        A[i] = hashTable.get(A[i].left);
      }
      else {
        A[i] = hashTable.get(A[i].right);
      }
    }
    steps++;

    int brk = 1;
    for (const Node &n: A) {
      if (n.start[n.start.size() - 1] != 'Z') {
        brk = 0;
        break;
      }
    }
    if (brk) {
      break;
    }
  }

  std::cout << "steps = " << steps << std::endl;
 
  return 0;
}