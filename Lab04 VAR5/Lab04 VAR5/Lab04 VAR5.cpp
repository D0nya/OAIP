// Lab04.cpp : Defines the entry point for the console application.
//Однонаправленный список.

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Spis1 {			//--Декларация однонаправленного списка--//
	int info;			//
	Spis1 *next;		//
}/**begin, *end, *t*/;	//Указатели на начало и конец
												//--Декларация прототипов функций пользователя--//
void Create_Spis1(Spis1**, Spis1**, int);		// Функция создания первого элемента
void View_Spis1(int, Spis1*);					// Функция просмотра двунаправленного списка
void Del_All(Spis1**);							// Функция очистки памяти
void Task(Spis1**, Spis1**);					// Функция замены местами крайних элементов
void addelem(Spis1**, Spis1**, int);			// Функция добавления элемента в выбранную позицию
void del2(Spis1**, Spis1**);					// Функция удаления каждого 2 элемента

int main()
{
	int in, kod;
	Spis1 *begin = NULL;
	Spis1 *end = NULL, *t;
	while (true) {
		cout << "\n\tCreate - 1.\n\tView   - 2.\n\tDel    - 3.\n\tTask   - 4.\n\tEXIT   - 0.\n\t";
		cin >> kod;
		switch (kod)
		{
		case 1:
			cout << "Info = "; cin >> in;
			Create_Spis1(&begin, &end, in);
			cout << "Create = " << in << endl;
			break;
		case 2:
			if (!begin) {
				cout << "Stack is Empty!" << endl;
				break;
			}
			t = begin;
			cout << "--SPISOK--" << endl;
			View_Spis1(kod, t);
			break;
		case 3:
			Del_All(&begin);
			cout << "Memory is Free!" << endl;
			break;
		case 4:
			cout << "Task 5" << endl;
			Task(&begin, &end);
			break;
		case 0:
			if (begin != NULL)
				Del_All(&begin);
			return 0;						//Выход(EXIT)
			break;
		}
	}

	return 0;
}

//--Функция создания первого элемента--//
void Create_Spis1(Spis1 **b, Spis1 **e, int in) {
	Spis1 *t = new Spis1;
	t->info = in;			// Формирование информационной части
	t->next = NULL;			// Формирование адресной части
	if (*b == NULL) 		// Формирование первого элемента
		*b = *e = t;
	else {					// Добавление элемента в конец
		(*e)->next = t;
		*e = t;
	}
}

//--Функция просмотра списка--//
void View_Spis1(int kod, Spis1 *t) {
	//--Просмотр списка с начала--//
	while (t != NULL) {											//Цикл работает, пока t!=NULL
		cout << t << " " << t->info << " " << t->next << endl;	//Выводим информационную часть текущего элемента на экран
		t = t->next;											//Переставляем текущий указатель на следующий элемент, адресс которого находится в поле next текущего элемента t (t->next)
	}
}

//--Функция освобождения памяти--//
void Del_All(Spis1 **p) {
	Spis1 *t = new Spis1;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

//--Функция удаления всех элементов, заканчивающихся на 5--//
void Task(Spis1 **begin, Spis1 **end) {
	Spis1 *t1, *t2, *temp_b;					/* Объявляем 3 временных указателя на переменные типа spis1: t1 и t2 - нужны для обхода списка и временного хранения информации 
																		об элементе; temp_b - создается пустой элемент перед началом списка для учета информации о первом элементе (begin)*/
	temp_b = new Spis1;								// выделяем память для temp_b;
	temp_b->next = *begin;						// указываем адресную часть. Т.е. следующий за этим элементом будет первый элемент списка
	t1 = temp_b;											// ставим указатель перед началом списка (на temp_b)

/*
начинаем с временного начала (temp_b). Если следующий элемент за ним (begin в данном случае)
заканчивается на 5, мы его удаляем. Перед этим во временную переменную t2 вносим информацию о следующем после удаляемого элементе, чтобы потом связать
2 элемента, между которыми находится тот, который заканчивается на 5. 

temp_b->begin->n1->n2->...n->end->NULL
t1 = temp_b;

t1->begin->n1->n2->...n->end->NULL

 допустим begin->info не заканчивается на 5, тогда переходим на begin

 temp_b->t1(begin)->n1->n2->...->n->end->NULL

 пусть n1->info - заканчивается на 5, тогда удаляем его и связываем элементы до и после него

t2 = t1->next->next (который равен n2);

 temp_b->t1(begin)->n1->n2->...->n->end->NULL

 удаляем элемент 
 temp_b->t1(begin)->DELETED n2->...->n->end->NULL

 связывем t1 с t2
 temp_b->t1(begin)->n2->...->n->end->NULL
*/


	while (t1->next != NULL) {				// цикл выполняется до тех пор, пока не дойдет до последнего элемента, у которого ссылка на следующий будет NULL
		if (t1->next->info % 10 == 5) {	// если информационная часть с
			if (t1->next == *begin)				// исключение: если t1->next будет равен begin(begin->info кончается на 5) и мы его удаляем, то нужно перенести начало списка на другой элемент
				*begin = t1->next->next;		// переносим начало на второй элемент списка
			else if (t1->next == *end)		// исключение: если t1->next будет раен end(end->info кончается на 5) и мы его удаляем, то нужно перенести конец списка на другой элемент
				*end = t1;									// переносим конец на t1 (перед концом находится)
			t2 = t1->next->next;					// ставим временный указатель t2 на следующий элемент, после удаляемого
			delete t1->next;							// удаляем элемент, оканчивающийся на 5
			t1->next = t2;								// связываем t1 с t2 
		}
		else t1 = t1->next;							// если информационная честь не кончается на 5, переходим на следующий элемент
	}
	delete temp_b, t1, t2;						// удаляем временные переменные
}