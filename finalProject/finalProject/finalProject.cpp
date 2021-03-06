// finalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "player.h"
#include "rules.h"
#include "game.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using std::cout;
using std::endl;
using std::string;

int main() { //need to add the shuffle feature into the board still
	int gametype, numberplayers,displaytype;
	string s, name, subName;
	bool doneLoop = false;
	//try catch loop for the int game type
	while (!doneLoop) {
		try {
			cout << " which type of game would you like to play 1)expert 2)regular \n";
			cin >> gametype;
			if ((gametype != 1 || gametype != 2) && (gametype == 1 || gametype != 2) && (gametype != 1 || gametype == 2)) {
				throw - 1;
			}
			doneLoop = true;
		}
		catch (int) {
			cout << "must be an interger value 1 or 2" << endl;

		}
	}
	doneLoop = false;
	while (!doneLoop) {
		try {
			cout << " which type of display would you like to play 1)expert 2)regular \n";
			cin >> displaytype;
			if ((gametype != 1 || gametype != 2) && (gametype == 1 || gametype != 2) && (gametype != 1 || gametype == 2)) {
				throw - 1;
			}
			doneLoop = true;
		}
		catch (int) {
			cout << "must be an interger value 1 or 2" << endl;

		}
	}
	doneLoop = false;
	//try catch loop for the # of players
	while (!doneLoop) {
		try {
			cout << "how many player would you like between 2-4:" << endl;
			cin >> numberplayers;
			if (numberplayers < 2) {
				throw - 1;
			}if (numberplayers > 4) {
				throw - 1;
			}
			doneLoop = true;
		}
		catch (int) {
			cout << "must be an interger value between 2-4" << endl;
		}
	}
	//Game game = Game();
	//build the names for each player
	for (int i = 1; i < numberplayers+1; i++) {
		cout << "type player " << i << " name." << endl;//just a plus one here instead of the i=1
		cin >> name;
		s += name + "!";  //fix this here it is wack could be put together
		
	}
	Game game = Game();
	size_t j = 0;
	//add players into the game
	for (int i = 0; i < numberplayers; ++i) {//creates each player
		if (i == 0) {//parse string
			j = s.find_first_of('!');
		}
		else {
			j = s.find_first_of('!', j);
		}
		if (i == 0) {
			subName = s.substr(0, j);
		}
		else {
			subName = s.substr(1, j - 1);
		}
		s = s.erase(0, j);//get rid of old nam
		Player::Side side; //creating each player object
		if (i == 0) {
			side = Player::Side::top;
		}
		else if (i == 1) {
			side = Player::Side::bottom;
		}
		else if (i == 2) {
			side = Player::Side::left;
		}
		else {
			side = Player::Side::right;
		}
		Player p1(subName, 1, 0, side);
		cout << p1 << endl;
		game.addPlayer(p1); //add player into game
	}
	
	Rules r = Rules();
	//main game loop
	while (r.gameOver(game) == false) {
		game.getGameBoard().reset();
		//make all players active
		for (int i = 0; i < numberplayers; ++i) {
			auto val = static_cast<Player::Side>(i);
			if (game.getPlayer(val).isActive() == false) {
				game.getPlayer(val).setActive(true);
			}
		}
		//show cards for each player
		for (int i = 0; i < numberplayers; ++i) {// order is top,bootom left right to show the cards 7 seconds to memorize
			if (game.getRound() != 0) {
				break;
			}
			auto val2 = static_cast<Player::Side>(i);
			if (i == 0) {
				game.getGameBoard().turnFaceUp(Board::Letter::A, Board::Number::_2);
				game.getGameBoard().turnFaceUp(Board::Letter::A, Board::Number::_3);
				game.getGameBoard().turnFaceUp(Board::Letter::A, Board::Number::_4);
			}
			else if (i == 1) {
				game.getGameBoard().turnFaceUp(Board::Letter::E, Board::Number::_4);
				game.getGameBoard().turnFaceUp(Board::Letter::E, Board::Number::_3);
				game.getGameBoard().turnFaceUp(Board::Letter::E, Board::Number::_2);
			}
			else if (i == 2) {
				game.getGameBoard().turnFaceUp(Board::Letter::B, Board::Number::_1);
				game.getGameBoard().turnFaceUp(Board::Letter::D, Board::Number::_1);
				game.getGameBoard().turnFaceUp(Board::Letter::C, Board::Number::_1);
			}
			else {
				game.getGameBoard().turnFaceUp(Board::Letter::B, Board::Number::_5);
				game.getGameBoard().turnFaceUp(Board::Letter::D, Board::Number::_5);
				game.getGameBoard().turnFaceUp(Board::Letter::C, Board::Number::_5);
			}
			cout << game << endl;
			cout << "cards for player: " << game.getPlayer(val2).getName() << endl;
			std::this_thread::sleep_for(std::chrono::seconds(7)); //need to change this back to a reasnoble value
			game.getGameBoard().reset();
		}
		cout << game << endl;
		int firstPerson = 0;
		while (r.roundOver(game) == false) {//fix the catch so that can catch if both are wrong(need one more loop throw shit on all maximums of values)
			string coords;
			cout << "type the coordinates of the card you want to pick player: " << static_cast<int>(r.getCurrentSide()+1) << endl;
			cin >> coords;
			Board::Letter letter;
			Board::Number number;
			if (coords[0] == 'a' || coords[0] == 'A') {
				letter = Board::Letter::A;
			}
			else if (coords[0] == 'b' || coords[0] == 'B') {
				letter = Board::Letter::B;
			}
			else if (coords[0] == 'c' || coords[0] == 'C') {
				letter = Board::Letter::C;
			}
			else if (coords[0] == 'd' || coords[0] == 'D') {
				letter = Board::Letter::D;
			}
			else if (coords[0] == 'e' || coords[0] == 'E') {
				letter = Board::Letter::E;
			}
			if (coords[1] == '1') {
				number = Board::Number::_1;
			}
			else if (coords[1] == '2') {
				number = Board::Number::_2;
			}
			else if (coords[1] == '3') {
				number = Board::Number::_3;
			}
			else if (coords[1] == '4') {
				number = Board::Number::_4;
			}
			else if (coords[1] == '5') {
				number = Board::Number::_5;
			}
			//cout << letter << " " << number << endl;
			Card* c = nullptr;
			if (firstPerson == 0) {
				//cout << "does it get here" << endl;
				game.getGameBoard().turnFaceUp(letter, number);
				cout << game;
				c = game.getCard(letter, number);
				//cout << game.getGameBoard().isFaceUp(letter, number) << endl;
				game.setCurrentCard(c);
				firstPerson++;
				r.getNextPlayer(game);
			}
			else {//not the first player case 
				game.getGameBoard().turnFaceUp(letter, number);
				cout << game;
				std::this_thread::sleep_for(std::chrono::seconds(3));//increase this to 3
				c = game.getCard(letter, number);
				game.setCurrentCard(c);
				if (r.isValid(game)) {//after turn 1 is good
					r.getNextPlayer(game);
				}
				else {//after turn 1 is bad
					Player::Side p = r.getCurrentSide();
					game.getPlayer(p).setActive(false);
					r.getNextPlayer(game);
				}
				if (r.roundOver(game)) {
					Reward* r1 = game.getRewardDeck()->getNext();
					game.getPlayer(r.getCurrentSide()).addReward(*r1);
					for (int i = 0; i < numberplayers; i++) {
						Player::Side i1 = static_cast<Player::Side>(i);
						cout << game.getPlayer(i1).getNrubies() << endl;;
					}
					cout << " round over" << game.getRound() << endl;
					game.nextRound();//change the value of the round back to 6
				}
			}
		}
		
		cout << "-----------Winners screen-----------------" << endl;
		for (int i = 0; i < numberplayers; ++i) {
			auto val = static_cast<Player::Side>(i);
			game.getPlayer(val).setActive(false);
			cout << game.getPlayer(val) << endl;
		}
		cout << " \n \n \n\ \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";
	}
	return 0;
}
//*/
			
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
