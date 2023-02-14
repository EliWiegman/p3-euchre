#include "Pack.h"
using namespace std;

Pack::Pack() {
    reset();
    int index = 0;

    for (int s = SPADES; s <= DIAMONDS; s++) {
        Suit suit = static_cast<Suit>(s);

        for (int r = NINE; r <= ACE; r++) {
            Rank rank = static_cast<Rank>(r);
            cards[index] = Card(rank, suit); 
            index++;
        }
    }
};

Pack::Pack(std::istream& pack_input) {
    reset();
    string line;
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
            copy[i] = cards[(PACK_SIZE / 2) + i / 2];
            copy[i+1] = cards[i / 2];
        }

        for (int i = 0; i < PACK_SIZE; i++) {
            cards[i] = copy[i];
        }
    }
};

bool Pack::empty() const {
    return (next == (cards.size()));
};


