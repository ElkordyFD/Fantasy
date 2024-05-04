#include<iostream>
#include"InputHandler.h"


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
