// bignums.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "b_nums.h"
#include <iostream>

using namespace std;
using namespace BigNumbers;

int main()
{

	b_int l1, l2;

	l1 = -10;
	l2 = -20;

	l1 -= l2;
	cout << l1 << endl;
	
	cin.get();
    return 0;
}
