#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

struct interval 
{
  long long src;
  long long range;
};

bool isSmaller(interval &a, interval &b)
{
  return a.src < b.src;
}

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input" << std::endl;
    return 1;
  }

  std::regex seedPattern("(\\d+) (\\d+)");
  std::regex linePattern("(\\d+) (\\d+) (\\d+)");
  std::regex mapPattern("map");
  std::smatch matches;

  std::vector<interval> sources;
  std::vector<interval> destinations;

  std::string line; 
  std::getline(input, line);
  while (std::regex_search(line, matches, seedPattern)) {
    long long seed = std::stoll(matches[1].str());
    long long range = std::stoll(matches[2].str());
    sources.push_back({seed, range - 1});
    line = matches.suffix();
  }
  
  std::vector<int> converted;
  int firstMap = 1;
  while (std::getline(input, line)) {
    if (line.size() == 0) {
      continue;
    }
    else if (std::regex_search(line, mapPattern)) {
      if (firstMap) {
        firstMap = 0;
        continue;
      }

      for (int i = destinations.size() - 1; i >= 0; i--) {
        if (converted.size()) {
          int j = converted[converted.size() - 1];
          sources[j] = destinations[i];
          converted.pop_back();
        }
        else {
          sources.push_back(destinations[i]);
        }
        destinations.pop_back();
      }
      continue;
    }

    while (std::regex_search(line, matches, linePattern)) {
      long long dest = std::stoll(matches[1].str());
      long long src = std::stoll(matches[2].str());
      long long range = std::stoll(matches[3].str()) - 1;
 
      for (int i = 0; i < sources.size(); i++) {
        interval loc = sources[i];

        if (loc.src < src && loc.src + loc.range > src) {
          if (loc.src + loc.range >= src + range) {
            destinations.push_back({dest, range});
            sources[i] = {loc.src , src - loc.src - 1};
            sources.push_back({src + range + 1, loc.src + loc.range - (src + range) - 1});
          }
          else {
            destinations.push_back({dest, (loc.src + loc.range) - src});
            sources[i] = {loc.src , src - loc.src - 1};
          }
        }
        else if (loc.src >= src) {
          if (loc.src + loc.range <= src + range) {
            destinations.push_back({dest + (loc.src - src), loc.range});
            converted.push_back(i);
          }
          else if (loc.src < src + range) {
            destinations.push_back({dest + (loc.src - src), range - (loc.src - src)});
            sources[i] = {src + range + 1, loc.src + loc.range - (src + range) - 1};
          }
        }
        else {
          continue;
        }
      }  
      line = matches.suffix();    
    }
  }
  for (interval n: destinations) {
    sources.push_back(n);
  }
  std::sort(sources.begin(), sources.end(), isSmaller);

  std::cout << "Lowest location for the initial seed numbers is " << sources[0].src << std::endl;
  return 0;
}