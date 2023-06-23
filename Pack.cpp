// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
	next = 0;
	int k = 0;
	for (int i = 0; i < NUM_SUITS; i++) {
		for (int j = 7; j < NUM_RANKS; j++) {
			cards[k] = Card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
			k++;
		}
	}
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
	next = 0;
	std::string rank, fill, suit;
	for (int i = 0; i < PACK_SIZE; i++) {
		pack_input >> rank >> fill >> suit;
		cards[i] = Card(rank, suit);
	}
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
	Card hold = cards[next];
	next = next + 1;
	return hold;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
	next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
	for (int i = 0; i < 7; i++) {
		auto aux = cards;
		for (int j = 0; j < PACK_SIZE / 2; j++) {
			cards[2 * j] = aux[PACK_SIZE / 2 + j];
			cards[2 * j + 1] = aux[j];
		}
	}
	reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
	if (next > 23) {
		return true;
	}
	else {
		return false;
	}
}