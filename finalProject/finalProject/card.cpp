#include "card.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;


int Card::getNRows() {
	return this->numRows;
}
char Card::getAnimal() const {
	char a;
	//check each case
	if (this->animal == Card::FaceAnimal::Penguin) a = 'P';
	else if (this->animal == Card::FaceAnimal::Sheep) a = 'S';
	else if (this->animal == Card::FaceAnimal::Donkey) a = 'D';
	else if (this->animal == Card::FaceAnimal::Gorilla) a = 'G';
	else if (this->animal== Card::FaceAnimal::Fish) a = 'F';
	//return char a
	return a;
}

char Card::getColor() const {
	char c;
	//check each case
	if (this->background == Card::FaceBackground::red) c='R';
	else if (this->background == Card::FaceBackground::orange) c = 'O';
	else if (this->background == Card::FaceBackground::yellow) c = 'Y';
	else if (this->background == Card::FaceBackground::green) c = 'G';
	else if (this->background == Card::FaceBackground::blue) c = 'B';
	//return char c
	return c;
}

Card::Card(FaceAnimal _animal, FaceBackground _background) : 
	animal{ _animal }, background{ _background }{
	//get char of animal and color
	char _color = this->getColor();
	char _animalType = this->getAnimal();
	//set string values
	std::string temp;
	temp += _color;
	temp += _color;
	temp += _color;
	temp += _color;
	temp += _animalType;
	temp += _color;
	temp += _color;
	temp += _color;
	temp += _color;
	//set row value
	row = temp;
}

Card::~Card()
{
}

string Card::operator()(int _rowNum) const {
	string _rowString;
	//set each row for the string
	for (int i = 0; i < 3; i++) {
		_rowString += row[3*_rowNum+i];
	}
	return _rowString;
}

//animal operator
Card::operator FaceAnimal() const {
	return animal;
}

//color operator
Card::operator FaceBackground() const {
	return background;
}
