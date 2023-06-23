// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include "Player.h"

class SimplePlayer : public Player {
private:
    std::string name;
    int num_cards;
    std::vector<Card> hand;
public:
    SimplePlayer() {
        name = "Computer";
        num_cards = 0;
    }
    SimplePlayer(const std::string& name_input) {
        name = name_input;
        num_cards = 0;
    }
    virtual const std::string& get_name() const {
        return name;
    }

    virtual void add_card(const Card& c) {  
        if (num_cards < MAX_HAND_SIZE) {
            hand.push_back(c);
            num_cards++;
        }
        else {
            assert(false);
        }
    }
    //HELPER FUNCTIONS
    static int max_index(const std::vector<Card> &hold, const std::string& trump) {
        int max = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (Card_less(hold.at(max), hold.at(i), trump)) {
                max = i;
            }
        }
        return max;
    }
    static int max_index(const std::vector<Card>& hold, 
        const std::string& trump, const std::string& cond) {
        int max = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (hold.at(i).get_suit(cond) != cond) {
                max = i;
            }
        }
        for (int i = 0; i < int(hold.size()); i++) {
            if (Card_less(hold.at(max), hold.at(i), trump) 
                && hold.at(i).get_suit(cond) != cond) {
                max = i;
            }
        }
        return max;
    }
    static int max_index(const std::vector<Card>& hold, const std::string& trump, 
        const Card& led_card, const std::string& cond) {
        int max = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (hold.at(i).get_suit(trump) == cond) {
                max = i;
            }
        }
        for (int i = 0; i < int(hold.size()); i++) {
            if (Card_less(hold.at(max), hold.at(i), led_card, trump) 
                && hold.at(i).get_suit(trump) == cond) {
                max = i;
            }
        }
        return max;
    }
    static int min_index(const std::vector<Card>& hold, const std::string& trump) {
        int min = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (Card_less(hold.at(i), hold.at(min), trump)) {
                min = i;
            }
        }
        return min;
    }
    static int min_index(const std::vector<Card>& hold, 
        const std::string& trump, const Card& led_card) {
        int min = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (Card_less(hold.at(i), hold.at(min), led_card, trump)) {
                min = i;
            }
        }
        return min;
    }
    static int suit_count(const std::vector<Card> hold, 
        const std::string suit, const std::string& trump) {
        int count = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (hold.at(i).get_suit(trump) == suit) {
                count++;
            }
        }
        return count;
    }
    static int face_cards_count(const std::string &trump_candidate, 
        const std::vector<Card>& hold) {
        int face_counts = 0;
        for (int i = 0; i < int(hold.size()); i++) {
            if (hold.at(i).is_trump(trump_candidate) && hold.at(i).is_face()) {
                face_counts++;
            }
        }
        return face_counts;
    }
    //END OF HELPER FUNCTIONS
    virtual bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const {
        if (round < 1 || round > 2) {
            assert(false);
        }
        std::vector<Card> Hold = hand;
        int trump_cnt;
        if (round == 1) {
            trump_cnt = face_cards_count(upcard.get_suit(), Hold);
            if (trump_cnt >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        else {
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
                trump_cnt = face_cards_count(Suit_next(upcard.get_suit()), Hold);
                if (trump_cnt >= 1) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    virtual void add_and_discard(const Card& upcard) { 
        if (num_cards < 1) {
            assert(false);
        }
        int min = min_index(hand, upcard.get_suit());
        if (Card_less(hand.at(min), upcard, upcard.get_suit())) {
            hand.erase(hand.begin() + min);
            hand.push_back(upcard);
        }
    }
    virtual Card lead_card(const std::string& trump) {
        if (num_cards < 1) {
            assert(false);
        }
        int play_index;
        int trump_cnt = suit_count(hand, trump, trump);
        if (trump_cnt < int(hand.size())) {
            play_index = max_index(hand, trump, trump);
        }
        else {
            play_index = max_index(hand, trump);
        }
        Card play_crd = hand.at(play_index);
        hand.erase(hand.begin() + play_index);
        num_cards--;
        return play_crd;
    }
    virtual Card play_card(const Card& led_card, const std::string& trump) {
        if (num_cards < 1) {
            assert(false);
        }
        int play_index = 0;
        int led_suit = suit_count(hand, led_card.get_suit(trump), trump);
        if (led_suit > 0) {
            play_index = max_index(hand, trump, led_card, led_card.get_suit(trump));
        }
        else {
            play_index = min_index(hand, trump, led_card);
        }
        Card play_crd = hand.at(play_index);
        hand.erase(hand.begin() + play_index);
        num_cards--;
        return play_crd;
    }
};
class HumanPlayer : public Player {
private:
    std::string name;
    int num_cards;
    std::vector<Card> hand;
public:
    HumanPlayer() {
        name = "Player";
        num_cards = 0;
    }
    HumanPlayer(const std::string& name_input) {
        name = name_input;
        num_cards = 0;
    }
    virtual const std::string& get_name() const {
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card& c) {
        if (num_cards < MAX_HAND_SIZE) {
            hand.push_back(c);
            num_cards++;
        }
        else {
            assert(false);
        }
    }
    static void players_hand(std::vector<Card> &sub, const std::string name) {
        std::sort(sub.begin(), sub.end());
        for (int i = 0; i < int(sub.size()); i++) {
            std::cout << "Human player " << name 
                << "'s hand: [" << i << "] " << sub.at(i) << "\n";
        }
    }
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const {
        if (round < 1 || round > 2) {
            assert(false);
        }
        std::vector<Card> sub = hand;
        players_hand(sub, name);
        /*if (is_dealer && round == 2) {
            order_up_suit = Suit_next(upcard.get_suit());
            std::cout << name << " orders up " << order_up_suit << "\n\n";
            return true;
        }*/
        std::string player_input;
        std::cout << "Human player " 
            << name << ", please enter a suit, or \"pass\":\n";
        std::cin >> player_input;
        if (player_input == "pass") {
            return false;
        }
        else {
            order_up_suit = player_input;
            return true;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card& upcard) {
        players_hand(hand, name);
        int player_input;
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << name 
            << ", please select a card to discard:\n";
        std::cin >> player_input;    
        if (player_input != -1) {
            hand.erase(hand.begin() + player_input);
            hand.push_back(upcard);
        }
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card(const std::string& trump) {
        players_hand(hand, name);
        int player_input;
        std::cout << "Human player " << name << ", please select a card:\n";
        std::cin >> player_input;
        Card Hold = hand.at(player_input);
        hand.erase(hand.begin() + player_input);
        num_cards--;
        return Hold;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card(const Card& led_card, const std::string& trump) {
        players_hand(hand, name);
        int player_input;
        std::cout << "Human player " << name << ", please select a card:\n";
        std::cin >> player_input;
        Card Hold = hand.at(player_input);
        hand.erase(hand.begin() + player_input);
        num_cards--;
        return Hold;
    }
};

Player* Player_factory(const std::string& name,
    const std::string& strategy) {

    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.get_name();
    return os;
}