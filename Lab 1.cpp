#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

float* MemoryArray(int);
void OutputArray(int, float*);
void One(int&, float*&);
void Two(int&, float*&);
void Three(int&, float*&);
void Four(int&, float*&);

int main()
{
	setlocale(LC_ALL, "Rus");

	int count, tip, №;

	cout << "Выберите тип массива.\n1 - отсортированный.\n2 - рандомные числа.\n3 - массив из файла.\n";

	do {
		cout << "\nТип: "; cin >> tip;
		if (tip < 0 || tip>3) cout << "\nВы ввели неверный тип. Повторите попытку.\n";
	} while (tip < 0 || tip>3);

	if (tip != 3) { cout << "Задайте размерность массива: "; cin >> count; cout << endl; }
	float *arr = MemoryArray(count);

	if (tip == 1)
	{
		for (int i = 0; i < count; i++)
		{
			arr[i] = i;
		}
	}
	if (tip == 2)
	{
		for (int i = 0; i < count; i++)
		{
			arr[i] = rand() % count;
		}
	}
	OutputArray(count, arr);

	do {
		cout << "\n\nВыберите номер задания для выполнения.\n1 - добавить элемент k - ую позицию в массиве.\n2 - удалить k - ый элемент массива.\n3 - добавить элемент массива после встреченного элемента с заданным значением.";
		cout << "\n4 - удалить все элементы массива с заданным значением.\n\nЗадание: "; cin >> №; cout << "\n";

		if (№ == 1) One(count, arr);
		if (№ == 2) Two(count, arr);
		if (№ == 3) Three(count, arr);
		if (№ == 4) Four(count, arr);

		cout << "\n";
		OutputArray(count, arr);
	} while (№ != 0);
}

float* MemoryArray(int count)
{
	float* arr = new float[count];
	return arr;
}
void OutputArray(int count, float* arr)
{
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << " ";
	}
}
void One(int &count, float *&arr)
{
	int index; float number;
	cout << "Задайте число, которое будет добавлено в массив.\nЧисло: "; cin >> number;
	cout << "Задайте место(индекс) на которое будет подставлено число.\n";
	do {
		cout << "Место: "; cin >> index;
		if (index < 0 || index > count) cout << "Данное место недоступно. Повторите попытку.\n\n";
	} while (index < 0 || index > count);
	count = count + 1;
	float* buff = new float[count];
	for (int i = 0; i < index; i++)
	{
		buff[i] = arr[i];
	}
	buff[index] = number;
	for (int i = index + 1; i < count; i++)
	{
		buff[i] = arr[i - 1];
	}
	delete[] arr;
	arr = buff;
}
void Two(int& count, float*& arr)
{
	int index;
	cout << "Выбирите место, с которого нужно удалить элемент.\n\n";
	do {
		cout << "Место: "; cin >> index;
		if (index < 0 || index > count) cout << "Вы выбрали несуществующее место.\n\n";
	} while (index < 0 || index > count);
	float* buff = new float[count - 1];
	for (int i = 0; i < index; i++)
	{
		buff[i] = arr[i];
	}
	for (int i = index; i < count; i++)
	{
		buff[i] = arr[i + 1];
	}
	delete[] arr;
	arr = buff;
	count -= 1;
}
void Three(int& count, float*& arr)
{
	int element; float number; int z = 0, index;
	cout << "Задайте число, которое будет добавлено в массив.\nЧисло: "; cin >> number;
	cout << "Задайте элемент, после которого будет подставлено число.\nЭлемент:"; cin >> element;
	for (int i = 0; i < count && z == 0; i++)
	{
		if (arr[i] == element) { z = 1; index = i;}
	}
	if (z == 0) cout << "\nТаких элементов нет.\n";
	else
	{
		float* buff = new float[count + 1];
		for(int i = 0; i <= index; i++)
		{
			buff[i] = arr[i];
		}
		index++;
		buff[index] = number;
		for (int i = index; i < count; i++)
		{
			buff[i+1] = arr[i];
		}
		delete[] arr;
		arr = buff;
		count=count+1;
	}
}
void Four(int& count, float*& arr)
{
	float element; int z = 0;
	cout << "Задайте элемент, который будет удалён.\nЭлемент:"; cin >> element;
	for (int i = 0; i < count; i++)
	{
		if (arr[i] == element) z++;
	}
	if (z == 0) cout << "\nТаких элементов нет.\n";
	else
	{
		float* buff = new float[count - z];
		z = 0;
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == element)
			{
				z++;
			}
			else buff[i - z] = arr[i];
		}
		delete[] arr;
		arr = buff;
		count = count - z;
	}
}