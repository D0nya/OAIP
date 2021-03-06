#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct time
{
	int tm_min;		//минуты, 0-59
	int tm_hour;	//часы, 0-23
	int tm_min_sum; //(часы * 60) + минуты
};
struct trip
{
	int num;
	int busType;
	string point;
	time time1;
	time time2;
};

string add_information(string, trip*, int);
string show_information(string);

void searchReturn(trip* trips, int i_key) {
	cout << "Номер поездки: " << trips[i_key].num << "\t";
	cout << "Пункт назначения: " << trips[i_key].point << "\t";
	switch (trips[i_key].busType) {
	case 1: cout << "Тип автобуса: Большой\t";
		break;
	case 2: cout << "Тип автобуса: Средний\t";
		break;
	case 3: cout << "Тип автобуса: Маленький\t";
		break;
	case 4: cout << "Тип автобуса: 2-ух этажный\t";
		break;
	}
	cout << "Время отправления: " << trips[i_key].time1.tm_hour << ":" << trips[i_key].time1.tm_min << "\t";
	cout << "Время прибытия: " << trips[i_key].time2.tm_hour << ":" << trips[i_key].time2.tm_min << endl;
	cout << endl;
}
void fillFile(trip* trips, int size, string path) {
	ofstream fout;
	fout.open(path, ofstream::out);

	if (!fout.is_open())
	{
		cout << "Ошибка" << endl;
	}

	for (int i = 0; i < size; i++) {
		fout << "Номер поездки: " << trips[i].num << "\t";
		fout << "Пункт назначения: " << trips[i].point << "\t";

		switch (trips[i].busType) {
		case 1: fout << "Тип автобуса: Большой\t";
			break;
		case 2: fout << "Тип автобуса: Средний\t";
			break;
		case 3: fout << "Тип автобуса: Маленький\t";
			break;
		case 4: fout << "Тип автобуса: 2-ух этажный\t";
			break;
		}
		fout << "Время отъезда: " << trips[i].time1.tm_hour << ":" << trips[i].time1.tm_min << "\t";
		fout << "Время прибытия: " << trips[i].time2.tm_hour << ":" << trips[i].time2.tm_min << "\t";
	}
	cout << endl;
	fout.close();

}

void linearSearch(trip*, int);
void binarySearch(trip*, int);

string selectionSort(string, trip*, int);
string quickSort(string, trip*, int);

int main()
{
	setlocale(LC_ALL, "RUS");
	string path = "trip.txt";
	int cod, size;

	cout << "Введите размер: ";
	cin >> size; cout << endl;
	trip *trips = new trip[size];

	while (true) {
		cout << "Выберите функцию: \n" << endl;

		cout << "\t 1 - Добавить информацию в файл\n" << endl;

		cout << "\t 2 - Вывести информацию из файла на экран\n" << endl;

		cout << "\t 3 - Линейный поиск\n" << endl;

		cout << "\t 4 - Бинарный поиск\n" << endl;

		cout << "\t 5 - Сортировка методом прямого выбора\n" << endl;

		cout << "\t 6 - Quick Sort\n" << endl;

		cout << "\t ELSE - Выйти из программы" << endl;
		cin >> cod; cout << endl;

		switch (cod)
		{
		case 1:
			add_information(path, trips, size); 
			break;
		case 2: show_information(path);
			break;
		case 3: linearSearch(trips, size);
			break;
		case 4: binarySearch(trips, size);
			break;
		case 5: selectionSort(path, trips, size);
			break;
		case 6: quickSort(path, trips, size);
			break;
		default: return 0;
		}
	}
	return 0;
}

string add_information(string path, trip *trips, int size)
{
	string result = "";
	int* x = new int[size];
	int* y = new int[size];
	int kod;

	for (int i = 0; i < 10; i++) {
		x[i] = rand() % 59;
		y[i] = rand() % 23;
	}


	cout << "RANDOM - 1 " << endl;
	cout << "Manual - 2" << endl;
	cout << "EXIT - ELSE" << endl;
	cin >> kod;

	switch (kod)
	{
	case 1:
		for (int i = 0; i < size; i++) {
			trips[i].num = i + 1;
			cout << "point : "; cin >> trips[i].point;
			trips[i].busType = rand() % 3 + 1;
			trips[i].time1.tm_hour = 5;
			trips[i].time1.tm_min = 55;
			trips[i].time2.tm_hour = y[i];
			trips[i].time2.tm_min = x[i];
			trips[i].time2.tm_min_sum = (trips->time2.tm_hour * 60) + trips[i].time2.tm_min;
		}
		break;
	case 2:
		for (int i = 0; i < size; i++) {
			do {
				cout << "Номер поездки: ";
				cin >> trips[i].num;
				if (trips[i].num <= 0) cout << "Wrong number!" << endl;
			} while (trips[i].num <= 0);

			cout << "Пункт назначения: ";
			cin >> trips[i].point;

			do {
				cout << "Тип автобуса (Большой = 1, Средний = 2, Маленький = 3, 2-ух этажный = 4): ";
				cin >> trips[i].busType;
			} while (trips[i].busType < 1 && trips[i].busType > 4);

			do {
				cout << "Введите время отъезда: " << endl << "\t Часы: ";
				cin >> trips[i].time1.tm_hour;
				cout << "\t Минуты: ";
				cin >> trips[i].time1.tm_min;
				if (trips[i].time1.tm_hour < 0 || trips[i].time1.tm_hour > 23 || trips[i].time1.tm_min < 0 || trips[i].time1.tm_min > 59) {
					cout << "Wrong Time!" << endl;
				}
			} while (trips[i].time1.tm_hour < 0 || trips[i].time1.tm_hour > 23 || trips[i].time1.tm_min < 0 || trips[i].time1.tm_min > 59);

			do {
				cout << "Введите время прибытия: " << endl << "\t Часы: ";
				cin >> trips[i].time2.tm_hour;
				cout << "\t Минуты: ";
				cin >> trips[i].time2.tm_min;
				if (trips[i].time2.tm_hour < 0 || trips[i].time2.tm_hour > 23 || trips[i].time2.tm_min < 0 || trips[i].time2.tm_min > 59) {
					cout << "Wrong Time!" << endl;
				}
				trips[i].time2.tm_min_sum = (trips->time2.tm_hour * 60) + trips[i].time2.tm_min;
			} while (trips[i].time2.tm_hour < 0 || trips[i].time2.tm_hour > 23 || trips[i].time2.tm_min < 0 || trips[i].time2.tm_min > 59);
		}
		break;
	default:
		break;
	}

	fillFile(trips, size, path);
	return result;
}

string show_information(string path)
{
	ifstream fin;
	fin.open(path);
	string result = "";

	if (!fin.is_open())
	{
		cout << "Ошибка" << endl;
	}
	else
	{
		cout << "Файл открыт\n" << endl;

		string str;
		result = str;

		while (!fin.eof())
		{
			str = "";
			getline(fin, str);
			cout << str << endl;
		}
	}
	fin.close();
	return result;
}

void linearSearch(trip *trips, int size) {
	int i_key = 0, kod = 0;
	time f_key;
	cout << "Время прибытия: " << endl;
	cout << "Часы: "; cin >> f_key.tm_hour;
	cout << "Минуты: "; cin >> f_key.tm_min;
	cout << endl;

	for (int i = 0; i < size; i++)
		if (trips[i].time2.tm_hour == f_key.tm_hour && trips[i].time2.tm_min == f_key.tm_min) {
			kod = 1;
			i_key = i;
			searchReturn(trips, i_key);
		}

	if (kod == 0) {
		cout << "Рейсов не найдено\n" << endl;
		return;
	}
}

void binarySearch(trip *trips, int size) {
	int kod = 0, m, i_key = 0, j = size - 1;
	time f_key;
	cout << "Время прибытия: " << endl;
	cout << "Часы: "; cin >> f_key.tm_hour;
	cout << "Минуты: "; cin >> f_key.tm_min;
	cout << endl;

	while (i_key < j) {
		m = (i_key + j) / 2;
		if (trips[m].time2.tm_hour == f_key.tm_hour < f_key.tm_hour && trips[m].time2.tm_min == f_key.tm_min < f_key.tm_min) i_key = m + 1;
		else  j = m;
	}


	if (trips[i_key].time2.tm_hour != f_key.tm_hour) 
	{
		cout << "Рейсов не найдено\n" << endl;
		return;	// Элемент не найден
	}		 


	else searchReturn(trips, i_key);

}

string selectionSort(string path, trip *trips, int size)
{
	string result = "";
	int m, j;
	trip temp;
	for (int i = 0; i < size - 1; i++) {
		m = i;
		for (j = i + 1; j < size; j++) {
			if (trips[j].time2.tm_hour < trips[m].time2.tm_hour) m = j;
			else if (trips[j].time2.tm_hour == trips[m].time2.tm_hour) {
				if (trips[j].time2.tm_min < trips[m].time2.tm_min) m = j;
			}
		}
		temp = trips[m];  					// Переставляем элементы
		trips[m] = trips[i];
		trips[i] = temp;
	}
	fillFile(trips, size, path);
	return result;
}

string quickSort(string path, trip *trips, int size) {
	string result = "";

	struct{
		int l;
		int r;
	} stack[20];

	int i, j, left, right, s = 0;
	trip temp, x;
	stack[s].l = 0; stack[s].r = size - 1;

	while (s != -1) {
		left = stack[s].l; right = stack[s].r;
		s--;
		while (left < right) {
			i = left; j = right; x = trips[(left + right) / 2];
			while (i <= j) {
				while (trips[i].time2.tm_min_sum < x.time2.tm_min_sum) i++;
				while (trips[j].time2.tm_min_sum > x.time2.tm_min_sum) j--;
				if (i <= j) {
					temp = trips[i];
					trips[i] = trips[j];
					trips[j] = temp;
					i++; j--;
				}
			}

			if ((j - left) < (right - i)) {			//Выбор более краткой части
				if (i < right) { s++; stack[s].l = i; stack[s].r = right; }
				right = j;
			}
			else {
				if (left < j) { s++; stack[s].l = left; stack[s].r = j; }	
				left = i;
			}
		}
	}

	fillFile(trips, size, path);
	return result;
}