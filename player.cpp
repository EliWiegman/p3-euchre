// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"

using namespace std;

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player {
    public:
        

        const string & get_name() const {
            assert(false);
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
};

class HumanPlayer : public Player {
    private:

    public:

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


