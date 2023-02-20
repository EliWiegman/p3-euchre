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
            
            switch (round) {
                case 1:
                    const Suit upcard_suit = upcard.get_suit();
                    int trump_cards = 0;

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

                case 2:
                    const Suit next_suit = Suit_next(upcard.get_suit());
                    int trump_cards = 0;

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

                default:
                    break;
            }
        }

        void add_and_discard(const Card &upcard) {
            hand.push_back(upcard);

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
        }
        
        Card play_card(const Card &led_card, Suit trump) {
            assert(false);
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
            assert(false);
        }

        bool make_trump(const Card &upcard, bool is_dealer,
                        int round, Suit &order_up_suit) const {
            assert(false);
        }

        void add_and_discard(const Card &upcard) {
            assert(false);
        }

        Card lead_card(Suit trump) {
            assert(false);
        }

        Card play_card(const Card &led_card, Suit trump) {
            assert(false);
        }
    private:
        string name;
};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  if (strategy == "Simple") {
    return new SimplePlayer(name);
  } else if (strategy == "Human") {
    // return new HumanPlayer(name);
  }

  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}


