// Lab01.cpp : Defines the entry point for the console application.
//VAR4

#include "stdafx.h"
#include <iostream>

using namespace std;

double Fb(int);
double Fb_R(int);

void main()
{
	int n, kod;
	while (true) {
		do{
			cout << "Input number (<=40)"; cin >> n; cout << endl;
		} while (n > 40);
		cout << " Recurs - 0\n Simple - 1\n Else - Exit" << endl << endl;
		cin >> kod;
		switch (kod) {
		case 0: 
			cout << "Recurse = " << Fb_R(n) << endl;
			break;
		case 1:
			cout << "Simple = " << Fb(n) << endl;
			break;
		default: return;
			}
		cout << endl;
	}
}

double Fb(int n) {
	double f0 = 0;
	double f1 = 1;
	double f = 0;
	for (int i = 1; i < n; i++) {
		f = f0 + f1;
		f0 = f1;
		f1 = f;
	}
	return f;
} 
double Fb_R(int n) {
	double fib;
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		fib = Fb_R(n - 1) + Fb_R(n - 2);
		return fib;
}