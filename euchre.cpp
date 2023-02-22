// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include "Pack.h"
#include "Player.h"
using namespace std;

void print_warning();

class Game {
    public:
        Game(istream& is, bool shuffleDeck, int points, 
        string p0_name, string p0_strat,
        string p1_name, string p1_strat,
        string p2_name, string p2_strat,
        string p3_name, string p3_strat ) {

        };

        void play() {
            
        };

    private:
        std::vector<Player*> players;
        Suit trump;
        Pack pack;
        bool shuffled = false;

        int player_order(Player* dealer, int distance) {
            int position;

            for (int i = 0; i < 4; i++) {
                if (players[i] == dealer) {
                    position = i;
                }
            }

            return (position + distance) % 4;
        };

        void shuffle() {
            if (shuffled) {
                pack.shuffle();
            } else {
                pack.reset();
            }
        };

        void deal(Player* dealer, int position) {
            int pos;

            for (int batch = 0; batch < 8; batch++) {
                pos = player_order(dealer, batch);
                switch (batch) {
                    case 0: case 2: case 5: case 7:
                        players[pos]->add_card(pack.deal_one());
                        players[pos]->add_card(pack.deal_one());
                        players[pos]->add_card(pack.deal_one());
                        break;
                    default:
                        players[pos]->add_card(pack.deal_one());
                        players[pos]->add_card(pack.deal_one());
                        break;
                }
            }

        };

        void make_trump(Player* dealer) {
            const Card upcard = pack.deal_one();
            int pos;
            for (int turn = 0; turn < 4; turn++) {
                pos = player_order(dealer, turn);
                if (players[pos]->make_trump(upcard, ((pos % 4) == 0), 1, trump)) {
                    break;
                }
            }

            if () {

            };       
        };

        void play_hand() {

        };
};



int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream input;
    input.open(filename);
    if(!input.is_open()) {
        cout << "Error opening " << filename << endl;
        return -1;
    }

    string shuffle_str = argv[2];
    bool shuffle;
    if (shuffle_str == "shuffle") {
        shuffle = true;
    } else if (shuffle_str == "noshuffle") {
        shuffle = false;
    } else {
        print_warning();
        return -1;
    }

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

    Game game = Game(input, shuffle, points, 
                        p0_name, p0_strat, 
                        p1_name, p1_strat, 
                        p2_name, p2_strat,
                        p3_name, p3_strat);
    return 0;
}

void print_warning() {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
}