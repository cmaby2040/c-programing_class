#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using std::ostream;
using std::string;
using std::cout;
using std::cin;
#ifndef REWARD_H
#define REWARD_H
//declare RewardDeck
class RewardDeck;
class Reward {
public:
	//ruby enumerator
	enum Rubies {
		one=0, 
		two, 
		three, 
		four
	};
	operator int() const;
private:
	//RewardDeck friend
	friend class RewardDeck;
	//variable
	Rubies rubyValue;
	//ctor
	Reward(Rubies _rubyValue);
	//dtor
	~Reward();
	//ostream operator
	friend ostream& operator<<(ostream& _oStream, const Reward& _reward);
};
#endif