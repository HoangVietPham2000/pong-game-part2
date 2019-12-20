#ifndef __CFOOD_H__
#define __CFOOD_H__
#include <iostream>
#include <cstdlib>
#include "console.h"
#include <cmath>
using namespace std;
class cFood
{
public:
	int x, y;
	int bonus;
	int color;
	cFood();
	~cFood();

	int eatFood();
};

#endif

