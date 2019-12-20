#include "cFood.h"

cFood::cFood()
{
	this->x = random(20, 60);
	this->y = random(10, 34);
	this->bonus = random(1, 8);
	this->color = random(1,10);
}
cFood::~cFood() {
	return;
}

int cFood::eatFood()
{

	return this->bonus;
}
