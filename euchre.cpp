// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <vector>
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
            pack = Pack(is);
            shuffled = shuffleDeck;
            points_to_win = points;

            players.push_back(Player_factory(p0_name, p0_strat));
            players.push_back(Player_factory(p1_name, p1_strat));
            players.push_back(Player_factory(p2_name, p2_strat));
            players.push_back(Player_factory(p3_name, p3_strat));

            point_vector = vector<int>(4, 0);

        };

        void play() {
            
        };

    private:
        vector<Player*> players;
        vector<int> point_vector;
        int points_to_win;
        Suit trump;
        Pack pack;
        Card upcard;
        bool shuffled = false;

        int player_order(Player* player, int distance) {
            int position;

            for (int i = 0; i < 4; i++) {
                if (players[i] == player) {
                    position = i;
                }
            }

            return (position + distance) % 4;
        };

        Player* player_sitting(Player* player, int distance) {
            int position;

            for (int i = 0; i < 4; i++) {
                if (players[i] == player) {
                    position = i;
                }
            }

            return players[(position + distance) % 4];
        };

        Player* partner(Player* player) {
            return player_sitting(player, 2);
        }

        void shuffle() {
            if (shuffled) {
                pack.shuffle();
            } else {
                pack.reset();
            }
        };

        void deal(Player* dealer) {
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

        Card make_trump(Player* dealer, Card* upcard) {
            int pos;
            for (int turn = 0; turn < 8; turn++) {
                pos = player_order(dealer, turn);
                if (players[pos]->make_trump(*upcard, ((pos % 4) == 0), (turn / 4), trump)) {
                    cout << players[pos]->get_name() << " orders up " << trump << endl;
                    dealer->add_and_discard(*upcard);
                    return *upcard;
                } else {
                    cout << players[pos]->get_name() << " passes" << endl;
                }

            }   
        };

        void play_hand(int set, Player* dealer) {
            pack.shuffle();
            deal(dealer);
            cout << "Hand " << set << endl;

            cout << dealer->get_name() <<" deals" << endl;

            upcard = pack.deal_one();
            make_trump(dealer, &upcard);
            cout << endl;

            Card leadCard, playedCard;
            string winner;
            int seat;
            int next_seat = player_order(dealer, 1);
            
            for (int trick = 0; trick < 5; trick++) {
                leadCard = players[next_seat]->lead_card(trump);

                for (int player = 1; player < 4; player++) {
                    seat = player_order(dealer, player);
                    playedCard = players[seat]->
                                 play_card(leadCard, trump);

                    if (Card_less(leadCard, playedCard, trump)) {
                        leadCard = playedCard;
                        winner = players[seat]->get_name();
                        next_seat = seat;
                    }
                }

                cout << winner << " takes the trick" << endl << endl;

                // TODO: points
            }


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