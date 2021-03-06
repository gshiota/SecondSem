#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Flash {
	string color;
	int volume;
	double weight, length;

	void Out();
	bool Seria(char*& data, int& n);
};
void Flash::Out() {
	cout << "Цвет: " << color << " Объём памяти: " << volume << " Длина: " << length << " Вес: " << weight << endl;
}

Flash DeSeria(char* data, int n);

bool Flash::Seria(char*& data, int& n) {
	size_t s = color.size();

	int n0 = sizeof(size_t);
	int n1 = s;
	int n2 = sizeof(int);
	int n3 = sizeof(double);
	int n4 = sizeof(double);

	n = n0 + n1 + n2 + n3 + n4;

	data = new char[n];

	char* d0 = reinterpret_cast<char*>(&s);
	char* d1 = const_cast<char*>(color.c_str());
	char* d2 = reinterpret_cast<char*>(&volume);
	char* d3 = reinterpret_cast<char*>(&length);
	char* d4 = reinterpret_cast<char*>(&weight);

	for (int i = 0; i < n0; i++) data[i] = d0[i];
	for (int i = 0; i < n1; i++) data[i + n0] = d1[i];
	for (int i = 0; i < n2; i++) data[i + n0 + n1] = d2[i];
	for (int i = 0; i < n3; i++) data[i + n0 + n1 + n2] = d3[i];
	for (int i = 0; i < n4; i++) data[i + n0 + n1 + n2 + n3] = d4[i];

	return true;
}
Flash DeSeria(char* data, int n) {
	Flash temp;
	int n0, n1, n2, n3, n4;
	n0 = sizeof(size_t);
	n2 = sizeof(int);
	n3 = sizeof(double);
	n4 = sizeof(double);

	size_t s = *reinterpret_cast<size_t*>(data);
	n1 = s;

	string ss(data + n0, s);
	temp.color = ss;
	temp.volume = *reinterpret_cast<int*>(data + n0 + n1);
	temp.length = *reinterpret_cast<double*>(data + n0 + n1 + n2);
	temp.weight = *reinterpret_cast<double*>(data + n0 + n1 + n2 + n3);

	return temp;
}

struct MyQueue {
	struct Node {
		int n; //Размер серии
		char* data; //Сама серия
		Node* next;
	};
	Node* First = NULL;
	int Count = 0;
	bool Push(char*, int);
	bool Pop(char*&, int&);
	void Info();
};

bool MyQueue::Push(char* data, int n) {
	if (!First) {
		First = new Node;
		First->next = NULL;
		First->data = new char[n];
		for (int i = 0; i < n; i++) {
			First->data[i] = data[i];
		}
		First->n = n;
		Count = 1;
	}
	else {
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->next = NULL;
		temp->next->data = new char[n];
		for (int i = 0; i < n; i++) {
			temp->next->data[i] = data[i];
		}
		temp->next->n = n;
		Count++;
	}
	return true;
}
bool MyQueue::Pop(char*& data, int& n) {
	if (!First) return false;
	Node* temp = First->next;
	n = First->n;
	data = new char[n];

	for (int i = 0; i < n; i++) {
		data[i] = First->data[i];
	}
	delete First->data;
	delete First;
	First = temp;
	Count--;
	return true;
}
void MyQueue::Info() {
	if (!First) cout << "--->Queue is empty" << endl;
	else {
		cout << endl << "Queue info: " << endl;
		cout << "\tQueue size = " << Count << endl;
		//cout << "YeFirst data" << First->data << endl << endl;
		//First->data.Out();
	}
}

MyQueue ReadBinaryFile() {
	MyQueue Q;
	fstream in("out.dat", ios::in | ios::binary);
	if (!in) {
		cout << "-->Error, there are no input binary file" << endl;
		return Q;
	}

	int i = 1, n;
	Flash C;

	while (!in.eof()) {
		if (in.read((char*)&n, sizeof(int))) {
			char* data = new char[n];
			in.read(data, n);
			i++;
			Q.Push(data, n);
			delete[] data;
		}
	}

	in.close();
	return Q;
}
void ClearBinaryFile() {
	fstream out("out.dat", ios::out | ios::binary);
	out.close();
}
void PrintBinaryFile(char* data, int n) {
	fstream out("out.dat", ios::app | ios::binary);
	out.write((char*)&n, sizeof(int));
	out.write(data, n);
	out.close();
}
bool InputBinaryFile() {
	fstream in("out.dat", ios::in | ios::binary);
	if (!in) {
		cout << "-->Error, there are no input binary file" << endl;
		return false;
	}

	int i = 1, n;
	Flash C;

	while (!in.eof()) {
		if (in.read((char*)&n, sizeof(int))) {
			cout << "\t - " << i << " - " << " seria length : " << n << endl << endl;
			char* data = new char[n];
			in.read(data, n);
			i++;
			C = DeSeria(data, n);
			C.Out();
			cout << "\n--------------\n";
		}
	}
	in.close();
	return true;
}



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	int task;
	bool q;
	char* data;
	int n;

	MyQueue Q, I;
	Flash f, h;

	cout << "1 - добавление нового предмета в очередь.\n2 - достать нужный предмет из очереди.\n3 - запись предмета в бинарный файл.\n4 - чтение очереди из бинарного файла.\n5 - очистить бинарный файл.\n6 - очистить очередь.\n\n";

	do {
		cout << "Задание: ";
		cin >> task;
		cout << "\n";

		if (task == 0)
		{
			cout << "До свидание.\n\n";
		}
		if (task == 1)
		{
			cout << "Цвет: "; cin >> f.color;
			cout << "Объём памяти: "; cin >> f.volume;
			cout << "Длина: "; cin >> f.length;
			cout << "Вес: "; cin >> f.weight;

			f.Out();
			cout << "\n";

			f.Seria(data, n);
			Q.Push(data, n);
			delete[] data;
		}
		if (task == 2)
		{
			q = 1;

			cout << "Цвет: "; cin >> h.color;
			cout << "Объём памяти: "; cin >> h.volume;
			cout << "Длина: "; cin >> h.length;
			cout << "Вес: "; cin >> h.weight;
			cout << endl;
			for (unsigned int i = 0; i < Q.Count && q != 0; i++)
			{
				Q.Pop(data, n);
				f = DeSeria(data, n);
				if (f.color == h.color && f.volume == h.volume && f.length == h.length && f.weight == h.weight && q != 0) q = 0;
				if (q != 0) Q.Push(data, n);
				delete[] data;
			}
			if (q != 0)
			{
				cout << "\nТакой флешки нет.\n\n";
			}
		}
		if (task == 3)
		{
			cout << "Цвет: "; cin >> f.color;
			cout << "Объём памяти: "; cin >> f.volume;
			cout << "Длина: "; cin >> f.length;
			cout << "Вес: "; cin >> f.weight;
			cout << endl;

			f.Seria(data, n);
			Q.Push(data, n);
			PrintBinaryFile(data, n);
			Q.Pop(data, n);
		}
		if (task == 4)
		{
			Q = ReadBinaryFile();
			Q.Info();
		}
		if (task == 5)
		{
			ClearBinaryFile();
			cout << "Файл очищен.\n\n";
		}
		if (task == 6)
		{
			while (Q.Pop(data, n))
			{
				f = DeSeria(data, n);
				f.Out();
				delete[] data;
			}
			cout << endl;
		}
		else;
	} while (task != 0);

	while (Q.Pop(data, n)) delete[] data;

	return 0;
}