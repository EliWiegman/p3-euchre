// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include "Pack.h"
#include "Player.h"
using namespace std;

void print_warning();

class Game {
 public:
  Game(/* ... */);
  void play();

 private:
  std::vector<Player*> players;
  Pack pack;
  // ...

  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
  // ...
};

int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream input;
    input.open(filename);
    if(!input.is_open()) {
        cout << "Error opening " << filename << endl;
        return -1;
    }

    string shuffle = argv[2];
    if (!((shuffle == "shuffle") || (shuffle == "noshuffle"))) {
        print_warning();
        return -1;
    };

    int points = atoi(argv[3]);
    if (!((points <= 100) && (points > 0))) {
        print_warning();
        return -1;
    }

    string p0_name = argv[4];
    string p0_strat = argv[5];
    if (!((p0_strat == "Simple") || (p0_strat == "Human"))) {
        print_warning();
        return -1;
    };

    string p1_name = argv[6];
    string p1_strat = argv[7];
    if (!((p1_strat == "Simple") || (p1_strat == "Human"))) {
        print_warning();
        return -1;
    };

    string p2_name = argv[8];
    string p2_strat = argv[9];
    if (!((p2_strat == "Simple") || (p2_strat == "Human"))) {
        print_warning();
        return -1;
    };

    string p3_name = argv[10];
    string p3_strat = argv[11];
    if (!((p3_strat == "Simple") || (p3_strat == "Human"))) {
        print_warning();
        return -1;
    };

    return 0;
}

void print_warning() {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
}