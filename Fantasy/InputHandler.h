#pragma once
#include <iostream>
#include<assert.h>
using namespace std;

class InputHandler {
public:
	//from, to inclusive
	
	static int inputInteger(int from, int to) {
		int x;
		assert(from <= to);
		cin >> x;
		while (x < from || x > to) {
			cout << "Invalid input.";
			cin >> x;
		}
		return x;
	}
	
};