// LAB05.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Stack {
	double inf;
	Stack *next;
};

int priority(char);
Stack* InStack(Stack*, double);
Stack* OutStack(Stack*, double&);
double masz[122];
char str[100], strp[100];
void AddPostFix(char*, char*);
double rasAV(char*, double*);

int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "Введите a: " << endl; cin >> masz[int('a')];
	cout << "Введите b: " << endl; cin >> masz[int('b')];
	cout << "Введите c: " << endl; cin >> masz[int('c')];
	cout << "Введите d: " << endl; cin >> masz[int('d')];
	cout << "Введите f: " << endl; cin >> masz[int('f')];
	AddPostFix(str, strp);
	cout << endl << strp;
	double s = rasAV(strp, masz);
	cout << endl << "Результат: " << s << endl;
	return 0;
}

Stack* InStack(Stack *sp, double inf) {
	Stack *spt = new Stack;
	spt->inf = inf;
	spt->next = sp;
	return spt;
}

Stack* OutStack(Stack *sp, double &inf) {
	Stack *spt = sp;
	inf = sp->inf;
	sp = sp->next;
	delete spt;
	return sp;
}

int priority(char ch) {
	switch (ch) {
	  case '(': case ')': return 0;
	  case '+': case '-': return 1;
	  case '*': case '/': return 2;
	  default: return -1;
	}
}

void AddPostFix(char *strin, char *strout) {
	Stack *sp = NULL;
	int n = 0; int cnt = -1;
	char ch;
	double inf;

	cout << "Введите выражение (a,b,c,d,f) : " << endl; cin >> str;
	strin = str;

	for (unsigned int i = 0; i < strlen(strin); i++) {
		ch = strin[i];
		//Если это операнд

		if (ch >= 'A') {

			if (ch >= 'a' && ch <= 'f' && ch != 'e')
			{
				strout[n++] = ch;
			}
			else 
			{
				cout << "Неверный операнд!" << endl;
				return AddPostFix(strin, strout);
			}
	
		continue;
		}
		//Если стэк пуст или найдена открывающая скобка
		if ((sp == NULL) || (ch == '(')) { sp = InStack(sp, ch); cnt++; continue; }
		//Если найдена закрывающая скобка
		if (ch == ')') {
			while (sp->inf != '(') {
				sp = OutStack(sp, inf);
				strout[n++] = (char)inf;
			}
			sp = OutStack(sp, inf); //Удаление закрывающей скобки
			cnt--;
			continue;
		}
		//Если операция 
		int pr = priority(ch);
		while (sp != NULL && priority((char)sp->inf) >= pr) {
			sp = OutStack(sp, inf);
			strout[n++] = (char)inf;
		}
		sp = InStack(sp, ch);
	} //end for

	if (cnt != 0) {
		cout << "Недостаточно скобок!" << endl;
		return AddPostFix (strin, strout);
	}

	while (sp != NULL) {
		sp = OutStack(sp, inf);
		strout[n++] = (char)inf;
	}
	strout[n++] = '\0';
}

double rasAV(char *str, double *mz) {
	Stack *sp = NULL;
	char ch;
	double inf, inf1, inf2;
	for (unsigned int i = 0; i < strlen(str); i++) {
		ch = str[i];
		//Если найден операнд
		if (ch >= 'A') { sp = InStack(sp, mz[int(ch)]); continue; }
		//Если найден знак операции
			sp = OutStack(sp, inf2);
			sp = OutStack(sp, inf1);
			switch (ch) {
			case '+': sp = InStack(sp, inf1 + inf2); break;
			case '-': sp = InStack(sp, inf1 - inf2); break;
			case '*': sp = InStack(sp, inf1 * inf2); break;
			case '/': sp = InStack(sp, inf1 / inf2); break;
			}
	}
	sp = OutStack(sp, inf);
	return inf;
}