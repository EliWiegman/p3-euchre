// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include "Pack.h"

using namespace std;

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player {
    public:
        SimplePlayer(string n) {
            name = n;
        }

        const string & get_name() const {
            return name;
        }

        void add_card(const Card &c) {
            hand.push_back(c);
        }

        bool make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const {
            int trump_cards;
            Suit upcard_suit;
            Suit next_suit;

            if (round == 1) {
                upcard_suit = upcard.get_suit();
                trump_cards = 0;

                /* order up if that would mean they have two or more 
                cards that are face or ace cards of the trump suit */
                for (int i = 0; i < MAX_HAND_SIZE; i++) {
                    if (hand.at(i).is_face_or_ace() 
                        && hand.at(i).is_trump(upcard_suit)) {
                        trump_cards++;
                    }
                };

                if (trump_cards >= 2) {
                    order_up_suit = upcard_suit;
                    return true;
                }
                
                return false;
            } else if (round == 2) {
                next_suit = Suit_next(upcard.get_suit());
                trump_cards = 0;

                if (is_dealer) {
                    order_up_suit = next_suit;
                    return true;
                }

                /* order up if that would mean they have two or more 
                cards that are face or ace cards of the trump suit */
                for (int i = 0; i < MAX_HAND_SIZE; i++) {
                    if (hand.at(i).is_face_or_ace() 
                        && hand.at(i).is_trump(next_suit)) {
                        trump_cards++;
                    }
                };

                if (trump_cards >= 1) {
                    order_up_suit = next_suit;
                    return true;
                }

                return false;
            } else {
                return false;
            }
        }

        void add_and_discard(const Card &upcard) {
            hand.push_back(upcard);
            Card min = hand[0];
            int min_index = 0;
            for (int i = 1; i <= MAX_HAND_SIZE; i++) {
                if (Card_less(hand[i], min, upcard.get_suit())) {
                    min = hand[i];
                    min_index = i;
                }
            }

            hand.erase(hand.begin() + min_index);
        }

        Card lead_card(Suit trump) 
        {
            Card max = hand[0];
            int counter = 1;
            while (max.get_suit() == trump || counter < hand.size())
            {
                max = hand[counter];
                counter++;
            }

            if (counter == hand.size() + 1)
            {
                for (int i = 1; i < hand.size(); i++)
                {
                    if (hand[i] > max)
                    {
                        max = hand[i + 1];
                    }
                }
            }

            else
            {
                for (int i = 1; i < hand.size(); i++)
                {
                    if (hand[i] > max)
                    {
                        if (hand[i].get_suit() != trump)
                        {
                            max = hand[i + 1];
                        }
                    }
                }
            }
            // wrote this to get it to compile
            return max;
        }
        
        // Possibly may not check a case where the first card is the highest card on suit of led card
        Card play_card(const Card &led_card, Suit trump) {
            int suitCounter = 0;
            Card min = hand[0];
            Card max = hand[0];
            for (int i = 0; i < hand.size(); i++)
            {
                if (hand[i].get_suit() == led_card.get_suit())
                {
                    suitCounter++;
                }
            }
            if (suitCounter == 0)
            {
                for (int j = 1; j < hand.size();  j++)
                {
                    if (Card_less(hand[j], min, trump))
                    {
                        min = hand[j];
                    }
                }
                return min;
            }
            for (int j = 1; j < hand.size();  j++)
            {
                if (Card_less(max, hand[j], trump))
                {
                    if (hand[j].get_suit() == led_card.get_suit())
                    {
                        max = hand[j];
                    }
                }
            }
            return max;
        }

    private:
        string name;
        vector<Card> hand;
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(string n) {
            name = n;
        }

        const string & get_name() const {
            return name;
        }

        void add_card(const Card &c) {
            hand.push_back(c);
            std::sort(hand.begin(), hand.end());
        }

        bool make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const {
            string choice;
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

            cin >> choice;
            if (choice != "pass")
            {
                if (choice == "Clubs") 
                {
                    order_up_suit = CLUBS;
                    return true;
                }
                else if (choice == "Diamonds") 
                {
                    order_up_suit = DIAMONDS;
                    return true;
                }
                else if (choice == "Hearts") 
                {
                    order_up_suit = HEARTS;
                    return true;
                }
                else
                {
                    order_up_suit = CLUBS;
                    return true;                    
                }
            } 
            else
            {
                return false;
            }
        }

        void add_and_discard(const Card &upcard) {
            string choice;
            hand.push_back(upcard);
            print_hand();
            cout << "Discard upcard: [-1]\n";
            cout << "Human player " << name << ", please select a card to discard:\n";
            if (choice == "-1")
            {
                hand.erase(hand.begin() + hand.size() - 1);
            }
            else
            {
                hand.erase(hand.begin() + stoi(choice));
            }
        }

        Card lead_card(Suit trump) {
            print_hand();
            cout << "Human player " << name << ", please select a card:\n";
            string choice;
            cin >> choice;
            return hand[stoi(choice)];
        }

        Card play_card(const Card &led_card, Suit trump) {
            print_hand();
            cout << "Human player " << name << ", please select a card:\n";
            string choice;
            cin >> choice;
            return hand[stoi(choice)];
        }
    private:
        string name;
        vector<Card> hand;

        void print_hand() const {
            for (size_t i=0; i < hand.size(); ++i) {
                cout << "Human player " << name << "'s hand: "
                    << "[" << i << "] " << hand[i] << "\n";
            }
        }
};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  if (strategy == "Simple") {
    return new SimplePlayer(name);
  } else if (strategy == "Human") {
    return new HumanPlayer(name);
  }

  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}


