#include "game.h"
#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <exception>
#include "board.h"
#include "player.h"


int Game::round=0;
int Game::numPlayers=0;
CardDeck Game::_c = CardDeck::make_CardDeck();
CardDeck* Game::c = &_c;
Board Game::gameBoard = Board(c);
std::array<Player , 4> Game::players;
//starts the game, sets the board
Game::Game()
{
	Game::_c = CardDeck::make_CardDeck();
	_c.shuffle();
	Game::c = &_c;
	Game::gameBoard = Board(c);
	Game::round = 0;
	Game::numPlayers = 0;
	const Card * prevCard = nullptr;
	const Card * currentCard = nullptr;
}

//returns which round
int Game::getRound() const
{
	return round;
}

//increments round and resets game state
void Game::nextRound()
{
	//if last turn game is over
	if (round == 6) {
		cout << "Game is over" << endl;
		return;
	}
	//increment
	round++;
	//reset
	gameBoard.reset();
	//print
	cout << endl << gameBoard <<endl << endl;
}

void Game::addPlayer(const Player & _player)
{
	int i=static_cast<int>(_player.getSide());
	if (players[i].getName() == "noName" ) {
		//set player
//		Player p = _player;
		players[i] = _player;
	}
	players[i].setActive(true);
	//increment numplayers
	numPlayers++;
}

Player & Game::getPlayer(Player::Side _side) const
{
	int i = static_cast<int>(_side);
	return players[i];
}

const Card * Game::getPreviousCard() const
{
	return prevCard;
}

const Card * Game::getCurrentCard() const
{
	return currentCard;
}

void Game::setCurrentCard(const Card * _card)
{
	int l = 0;
	int n = 0;
	Card::FaceAnimal animal = _card->operator Card::FaceAnimal();
	Card::FaceBackground background = _card->operator Card::FaceBackground();
	Card::FaceAnimal tempAnimal = static_cast<Card::FaceAnimal>(0);
	Card::FaceBackground tempBackground = static_cast<Card::FaceBackground>(0);

	for (int i = 0; i < 5; i++) {
		tempAnimal = static_cast<Card::FaceAnimal>(i);
		for (int j = 0; j < 5; j++) {
			tempBackground = static_cast<Card::FaceBackground>(j);
			n = j;
			if (animal == tempAnimal && background == tempBackground) break;
		}
		l = i;
		

		if (animal == tempAnimal && background == tempBackground) break;
	}
	Board::Letter _l = static_cast<Board::Letter> (l);
	Board::Number _n = static_cast<Board::Number> (n);
	if (Game::gameBoard.isFaceUp(_l, _n)) {
		Game::gameBoard.turnFaceDown(_l, _n);
	}
	else {
		Game::gameBoard.turnFaceUp(_l, _n);
		//set prev to previous current
		prevCard = currentCard;
		//set current to reference of card
		currentCard = _card;
	}
}

Card * Game::getCard(const Board::Letter & _letter, const Board::Number & _number) const
{
	return gameBoard.getCard(_letter, _number);
}

void Game::setCard(const Board::Letter & _letter, const Board::Number & _number, Card * _cardPtr)
{
	gameBoard.setCard(_letter, _number, _cardPtr);
}

Game::~Game()
{
}

ostream & operator<<(ostream & _oStream, const Game & _game)
{
	_oStream << _game.gameBoard;
	Player p1 = _game.players[0];

	string s;
	int i = static_cast<int>(p1.getSide());
	cout << endl << "****" << endl << i;
	switch (i) {
		//case Side::defaultplayer: s="defaultplayer"; break;
	case 0: s = "top"; break;
	case 1: s = "bottom"; break;
	case 2: s = "left"; break;
	case 3: s = "right"; break;
	}
	if (p1.isActive() == 1) {
		_oStream << p1.getName() << ": " << s << "(active)" << endl;
	}
	else {

		_oStream << p1.getName() << ": " << p1.getNrubies() << " rubies" << endl;
	}
	
	//_oStream << _game.players[0] << endl;
	//_oStream << _game.players[1] << endl;
	//_oStream << _game.players[2] << endl;
	//_oStream << _game.players[3] << endl;

	return _oStream;
}

/*
int main() {
	Game g1 = Game();
	Player p1("chris", 1, 0, Player::Side::top);
	cout << p1;
	g1.addPlayer(p1);
	cout << g1;
}
*/


