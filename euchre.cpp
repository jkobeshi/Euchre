// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
static int dealer_index(vector<bool> &player_deals, const int hand) {
	int index = 0;
	for (int i = 0; i < int(player_deals.size()); i++) {
		if (hand % 4 == i) {
			player_deals.at(i) = true;
			index = i;
		}
		else {
			player_deals.at(i) = false;
		}
	}
	return index;
}
static void shuffle_pack(Pack& pack, const string& shuffle) {
	if (shuffle == "shuffle") {
		pack.shuffle();
	}
	else {
		pack.reset();
	}
}
static Card deal_cards(vector<Player*> &players, Pack& pack, const int lead_index) {
	for (int i = 0; i < int(players.size()) * 2; i++) {
		if (i < 4 && (i % 2) == 0) {
			for (int j = 0; j < 3; j++) {
				players.at((lead_index + i) % 4)->add_card(pack.deal_one());
			}
		}
		else if (i < 4 && (i % 2) == 1) {
			for (int j = 0; j < 2; j++) {
				players.at((lead_index + i) % 4)->add_card(pack.deal_one());
			}
		}
		else if (i >= 4 && (i % 2) == 0) {
			for (int j = 0; j < 2; j++) {
				players.at((lead_index + i) % 4)->add_card(pack.deal_one());
			}
		}
		else {
			for (int j = 0; j < 3; j++) {
				players.at((lead_index + i) % 4)->add_card(pack.deal_one());
			}
		}
	}
	Card upcrd = pack.deal_one();
	cout << upcrd << " turned up" << endl;
	return upcrd;
}
static int find_deal(const vector<bool>& player_deals) {
	int index = 0;
	for (int i = 0; i < int(player_deals.size()); i++) {
		if (player_deals.at(i)) {
			index = i;
			break;
		}
	}
	return index;
}
static int order_up_rounds(vector<Player*>& players, const vector<bool> &player_deals, 
	const Card& upcrd, string &trump ) {
	int ordup_index = 0, d_ind = find_deal(player_deals), lead_index = (d_ind + 1) % 4;
	
	for (int i = 0; i < int(players.size()) * 2; i++) {
		if (i < 4 && (players.at((lead_index + i) % 4)->make_trump(upcrd, 
			player_deals.at((lead_index + i) % 4), 1, trump))) {
			cout << players.at((lead_index + i) % 4)->get_name() 
				<< " orders up " << trump << endl;
			players.at(d_ind)->add_and_discard(upcrd);
			ordup_index = (lead_index + i) % 4;
			break;
		}
		else if (i >= 4 && (players.at((lead_index + i) % 4)->make_trump(upcrd,
			player_deals.at((lead_index + i) % 4), 2, trump))) {
			cout << players.at((lead_index + i) % 4)->get_name()
				<< " orders up " << trump << endl;
			ordup_index = (lead_index + i) % 4;
			break;
		}
		else {
			cout << players.at((lead_index + i) % 4)->get_name()
				<< " passes" << endl;
		}
	}
	cout << endl;
	return ordup_index;
}
static void play_euchre(vector<Player*>& players, 
	int lead_index, string trump, vector<int>& tricks_won_cnt) {
	for (int j = 0; j < 5; j++) {
		vector<Card> tricks;
		tricks.push_back(players.at(lead_index)->lead_card(trump));
		cout << tricks.at(0) << " led by " << players.at(lead_index)->get_name() << endl;
		for (int i = 1; i < int(players.size()); i++) {
			tricks.push_back(players.at((lead_index + i) % 4)->play_card(tricks.at(0), trump));
			cout << tricks.at(i) << " played by " 
				<< players.at((lead_index + i) % 4)->get_name() << endl;
		}
		int max_index = 0;
		for (int i = 1; i < int(players.size()); i++) {
			if (Card_less(tricks.at(max_index), tricks.at(i), tricks.at(0), trump)) {
				max_index = i;
			}
		}
		cout << players.at((lead_index + max_index) % 4)->get_name() 
			<< " takes the trick\n\n";
		tricks_won_cnt.at((lead_index + max_index) % 4)++;
		lead_index = (lead_index + max_index) % 4;
	}
}
static void scoring(vector<Player*>& players, 
	vector<int>& tricks, const int ordup_index, vector<int> &pts) {
	int vert_tricks = tricks.at(0) + tricks.at(2);
	int horz_tricks = tricks.at(1) + tricks.at(3);
	if (horz_tricks < vert_tricks) {
		cout << players.at(0)->get_name() << " and " <<
			players.at(2)->get_name() << " win the hand\n";
		if (ordup_index == 0 || ordup_index == 2) {
			if (vert_tricks != 5) {
				pts.at(0) = pts.at(0) + 1;
			}
			else {
				pts.at(0) = pts.at(0) + 2;
				cout << "march!\n";
			}
		}
		else {
			pts.at(0) = pts.at(0) + 2;
			cout << "euchred!\n";
		}
	}
	else {
		cout << players.at(1)->get_name() << " and " <<
			players.at(3)->get_name() << " win the hand\n";
		if (ordup_index == 1 || ordup_index == 3) {
			if (horz_tricks != 5) {
				pts.at(1) = pts.at(1) + 1;
			}
			else {
				pts.at(1) = pts.at(1) + 2;
				cout << "march!\n";
			}
		}
		else {
			pts.at(1) = pts.at(1) + 2;
			cout << "euchred!\n";
		}
	}
	cout << players.at(0)->get_name() << " and " <<
		players.at(2)->get_name() << " have " << pts.at(0) << " points\n";
	cout << players.at(1)->get_name() << " and " <<
		players.at(3)->get_name() << " have " << pts.at(1) << " points\n\n";
}
static void winner(vector<Player*> players, int &team_hor_pts, int &team_ver_pts) {
	if (team_hor_pts < team_ver_pts) {
		cout << players.at(0)->get_name() << " and " 
			<< players.at(2)->get_name() << " win!\n";
	}
	else {
		cout << players.at(1)->get_name() << " and " 
			<< players.at(3)->get_name() << " win!\n";
	}
}
int main(int argc, char* argv[]) {
	if (argc != 12) {
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return 1;
	}
	stringstream pts_in(argv[3]);
	int win_pts; pts_in >> win_pts;
	if ((win_pts < 1 || win_pts > 100) ||
		(string(argv[2]) != "shuffle" && string(argv[2]) != "noshuffle") ||
		(string(argv[5]) != "Human" && string(argv[5]) != "Simple") ||
		(string(argv[7]) != "Human" && string(argv[7]) != "Simple") ||
		(string(argv[9]) != "Human" && string(argv[9]) != "Simple") ||
		(string(argv[11]) != "Human" && string(argv[11]) != "Simple")) {
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return 1;
	}
	ifstream fin; fin.open(argv[1]);
	if (!fin.is_open()) {
		cout << "Error opening " << string(argv[1]) << endl;
		return 1;
	} 
	for (int i = 0; i < argc; i++) {
		cout << argv[i] << " ";
	} cout << endl;
	Pack pack = Pack(fin);
	vector<Player*> players;
	for (int i = 4; i < 12; i = i + 2) {
		players.push_back(Player_factory(string(argv[i]), string(argv[i + 1])));
	}
	vector<bool> player_deals = { false, false, false, false };
	vector<int> scoreboard = { 0, 0, 0 };
	while (scoreboard.at(0) < win_pts && scoreboard.at(1) < win_pts) {
		int dealer = dealer_index(player_deals, scoreboard.at(2));
		cout << "Hand " << scoreboard.at(2) << endl;
		cout << players.at(dealer)->get_name() << " deals" << endl;
		shuffle_pack(pack, string(argv[2]));
		Card upcrd = deal_cards(players, pack, (dealer + 1) % 4);
		string trump;
		int order_up_index = order_up_rounds(players, player_deals, upcrd, trump);
		vector<int> tricks_won_count = { 0, 0, 0, 0 };
		play_euchre(players, (dealer + 1) % 4, trump, tricks_won_count);
		scoring(players, tricks_won_count, order_up_index, scoreboard);
		scoreboard.at(2)++;	
	}
	winner(players, scoreboard.at(1), scoreboard.at(0));
	for (int i = 0; i < int(players.size()); ++i) {
		delete players.at(i);
	} 
	return 0;
}