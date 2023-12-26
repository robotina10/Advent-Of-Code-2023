#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <chrono>

enum Strength {NONE, HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_KIND, FULL_HOUSE, FOUR_OF_KING, FIVE_OF_KIND};

struct Hand
{
  Strength strength;
  int bid;
  std::string cards;
};

struct Card
{
  int occurence;
  char type;
};

bool compareOccurences(Card a, Card b) 
{
  return a.occurence > b.occurence;
}

bool compareHands(Hand a, Hand b)
{
  if (a.strength != b.strength) {
    return a.strength < b.strength;
  }

  std::vector<char> cardTypes = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
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
  int j = 0;
  std::vector<Card> cards;

  for (char c: hand.cards) {
    if (c == 'J') {
      j++;
      continue;
    }

    bool incremented = false;
    for (Card &card: cards) {
      if (card.type == c) {
        card.occurence++;
        incremented = true;
        break;
      }
    }
    if (!incremented) {
      cards.push_back({1, c});
    }
  }

  std::sort(cards.begin(), cards.end(), compareOccurences);
  if (j == 5 || cards[0].occurence == 5) {
    hand.strength = FIVE_OF_KIND;
    return;
  }
  cards[0].occurence += j;

  Strength highCard = NONE;
  Strength onePair = NONE;
  Strength twoPair = NONE;
  Strength threeOfKind = NONE;

  for (Card card: cards) {
    switch (card.occurence) {
      case 1:
        highCard = HIGH_CARD;
        break;
      case 2:
        if (!onePair) {
          onePair = ONE_PAIR;
          break;
        }
        else {
          hand.strength = TWO_PAIR;
          return;
        }
      case 3:
        threeOfKind = THREE_OF_KIND;
        break;
      case 4:
        hand.strength = FOUR_OF_KING;
        return;
      case 5:
        hand.strength = FIVE_OF_KIND;
        return;
    }
  } 

  if (threeOfKind && onePair) {
    hand.strength = FULL_HOUSE;
  }
  else if (threeOfKind) {
    hand.strength = THREE_OF_KIND;
  }
  else if (onePair) {
    hand.strength = ONE_PAIR;
  }
  else if (highCard) {
    hand.strength = HIGH_CARD;
  }
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

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
      Hand hand = {NONE, std::stoi(matches[2].str()), matches[1].str()};
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

  auto stop = std::chrono:: high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << duration.count() << std::endl;
  return 0;
}