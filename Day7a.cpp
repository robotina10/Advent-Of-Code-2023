#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

struct Hand
{
  int strength;
  int bid;
  std::string cards;
};

struct Cards
{
  int occurence;
  char type;
};

int compareHands(Hand a, Hand b)
{
  std::vector<char> cardTypes = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
  if (a.strength != b.strength) {
    return a.strength < b.strength;
  }
  for (int i = 0; i < a.cards.size(); i++) {
    if (a.cards[i] != b.cards[i]) {
      int cardA = 0;
      int cardB = 0;
      for (int j = 0; j < cardTypes.size(); j++) {
        if (a.cards[i] == cardTypes[j]) {
          cardA = j + 1;
        }
        else if (b.cards[i] == cardTypes[j]) {
          cardB = j + 1;
        }
        if (cardA && cardB) {
          return cardA > cardB;
        }
      }
    }
  }
  return 0;
}


void rateHand(Hand &hand)
{
  std::vector<Cards> cards;
  for (char c: hand.cards) {
    int incremented = 0;
    for (Cards &card: cards) {
      if (card.type == c) {
        card.occurence++;
        incremented = 1;
        break;
      }
    }
    if (!incremented) {
      cards.push_back({1, c});
    }
  }

  int three = 0;
  int pair = 0;
  int high = 0;

  for (Cards card: cards) {
    switch (card.occurence) {
      case 1:
        high++;
        break;
      case 2:
        pair++;
        break;
      case 3:
        three++;
        break;
      case 4:
        hand.strength = 6;
        return;
      case 5:
        hand.strength = 7;
        return;
    }
  } 

  if (three && pair) {
    hand.strength = 5;
  }
  else if (three) {
    hand.strength = 4;
  }
  else if (pair == 2) {
    hand.strength = 3;
  }
  else if (pair = 1) {
     hand.strength = 2;
  }
  else if (high == 5) {
    hand.strength = 1;
  }
}

int main()
{
  std::ifstream input("input.txt");
  if (!input.is_open()) {
    std::cout << "Cannot open input\n";
    return -1;
  }

  std::regex pattern("(.+) (\\d+)");
  std::smatch matches;

  std::string line;

  std::vector<Hand> hands;

  while (std::getline(input, line)) {
    while (std::regex_search(line, matches, pattern)) {
      Hand hand = {0, std::stoi(matches[2].str()), matches[1].str()};
      rateHand(hand);   
      hands.push_back(hand);   
      line = matches.suffix();
    }
  }

  std::sort(hands.begin(), hands.end(), compareHands);

  long long total = 0;
  for (int i = 0; i < hands.size(); i++) {
    total += hands[i].bid * (i + 1);
  }

  std::cout << "Total winnings = " << total << std::endl;

  return 0;
}