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

            t1_points = 0;
            t2_points = 0;
        };

        void play() {
            Player* dealer = players[0];
            int set = 0;
            while (play_hand(set, dealer) == 0) {
                set++;
                dealer = player_sitting(dealer, 1);
            }
        };

    private:
        vector<Player*> players;
        int points_to_win, t1_points, t2_points;
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

            for (int batch = 1; batch <= 8; batch++) {
                pos = player_order(dealer, batch);
                switch (batch) {
                    case 1: case 3: case 6: case 8:
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

        // TODO round 2 can't choose same suit as upcard
        Player* make_trump(Player* dealer, Card* upcard) {
            int pos;
            for (int turn = 1; turn < 9; turn++) {
                pos = player_order(dealer, turn);
                if (players[pos]->make_trump(*upcard, ((pos % 4) == 0), ((turn + 3) / 4), trump)) {
                    cout << players[pos]->get_name() << " orders up " << trump << endl;
                    dealer->add_and_discard(*upcard);
                    return players[pos];
                }
                cout << players[pos]->get_name() << " passes" << endl;
            }
            return dealer;   
        };

        int play_hand(int set, Player* dealer) {
            shuffle();
            deal(dealer);

            cout << "Hand " << set << endl;
            cout << dealer->get_name() <<" deals" << endl;

            upcard = pack.deal_one();
            cout << upcard << " turned up" << endl;
            Player* leader = make_trump(dealer, &upcard);
            cout << endl;
            
            Card leadCard, playedCard, winningCard;
            string winner;
            int seat, first_seat;
            // start with person left to the dealer
            int next_seat = player_order(dealer, 1);
            
            int t1_tricks = 0;
            int t2_tricks = 0;

            // for every trick
            for (int trick = 0; trick < 5; trick++) {
                
                // call lead card on the next player, assigning their choice to leadCard
                first_seat = next_seat;
                leadCard = players[next_seat]->lead_card(trump);
                cout << leadCard << " led by " << players[next_seat]->get_name() << endl; 

                // for the 3 other people on the table
                for (int player = 1; player < 4; player++) {
                    seat = player_order(players[first_seat], player); 
                    
                    // call play card on a player based on the lead card and the trump suit
                    playedCard = players[seat]->
                                 play_card(leadCard, trump);
                    cout << playedCard << " played by " << players[seat]->get_name() << endl; 

                    // if playedCard beats leadCard, set winningCard
                    if (Card_less(winningCard, playedCard, trump)) {
                        winningCard = playedCard;
                        winner = players[seat]->get_name();
                        next_seat = seat;
                    }
                }

                cout << winner << " takes the trick" << endl << endl;
                switch (next_seat) {
                    case 0: case 2:
                        t1_tricks++;
                    default:
                        t2_tricks++;
                }
            }
            
            int team = update_points(leader, t1_points, t2_points);          
            if (team == 1) {
                return 1;
            } else if (team == 2) {
                return 2;
            } else {
                return 0;
            }

        };

        int update_points(Player* ordered_up, int t1, int t2) {
            switch (team(ordered_up)) {
                case 1:
                    switch(t1_points) {
                        case 3: case 4:
                            hand_winners(1);
                            t1_points += 1;
                            break;
                        case 5:
                            hand_winners(1);
                            t1_points += 2;
                            cout << "march!" << endl;
                            break;
                        default:
                            hand_winners(2);
                            cout << "euchred!" << endl;
                            t2_points += 2;
                    }
                    print_score();
                    break;
                case 2:
                    switch(t2_points) {
                        case 3: case 4:
                            hand_winners(2);
                            t2_points += 1;
                            break;
                        case 5:
                            hand_winners(2);
                            t2_points += 2;
                            cout << "march!" << endl;
                            break;
                        default:
                            hand_winners(1);
                            t1_points += 2;
                            cout << "euchred!" << endl;
                            break;
                    }
                    print_score();
                    break;

            }

            if (t1_points >= points_to_win) {
                print_winners(1);
                return 1;
            } else if (t2_points >= points_to_win) {
                print_winners(2);
                return 2;
            }

            return 0;
        }

        void print_winners(int team) {
            if (team == 1) {
                cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << endl;
            } else {
                cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << endl;
            }
        }

        void hand_winners(int team) {
            if (team == 1) {
                cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
            } else {
                cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
            }
        }

        void print_score() {
            cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << t1_points << " points" << endl; 
            cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << t2_points << " points" << endl << endl; 
        }

        int team(Player* player) {
            for (int i = 0; i < 4; i++) {
                switch (player_order(player, 0)) {
                    case 0: case 2:
                        return 1;
                    default:
                        return 2;
                }
            }
            return 0;
        }
};



int main(int argc, char* argv[]) {
    for (int i = 0; i < 12; i++)
    {
        cout << argv[i] << " " ;
    }

    cout << endl;
    
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
    game.play();
    return 0;
}

void print_warning() {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
}