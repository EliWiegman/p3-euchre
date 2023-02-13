using namespace std;
#include "Pack.h"

Pack::Pack() {
    for (int i = 0; i < PACK_SIZE; i++) {
        for (int s = SPADES; s <= DIAMONDS; s++) {
            Suit suit = static_cast<Suit>(s);
            
            for (int r = TWO; r <= ACE; r++) {
                Rank rank = static_cast<Rank>(r);
                cards[i] = Card(rank, suit); 
            }
        }
    }
};

Pack::Pack(std::istream& pack_input) {
    string line;
    int index = 0;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> cards[i];
    }
};

Card Pack::deal_one() {
    next++;
    return cards[next-1];
};

void Pack::reset() {
    next = 0;
};

void Pack::shuffle() {
    reset();
    
    array<Card, PACK_SIZE> copy;
    for (int shuffle = 0; shuffle < 7; shuffle++) {
        for (int i = 0; i < PACK_SIZE; i += 2) {
            copy[i] = cards[(PACK_SIZE / 2) + i];
            copy[i+1] = cards[i / 2];
        }
        cards = copy;
    }
};

bool Pack::empty() const {
    return (next == cards.size() - 1);
};


