//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"

using namespace std;

struct Pen
{
	string color, kind;
	float weight, length;
	void Out();
};

struct Product {
	int volume;
	double price;
	void Out();
};

struct MyStack
{
	struct Node
	{
		Pen data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(Pen);
	bool Pop(Pen&);
	void Info();
};

struct MyQueue {
	struct Node {
		Product data;
		Node* next;
	};
	int remain;
	double profit = 0;
	Node* First = NULL;
	int Count = 0;
	bool Push(Product);
	bool Pop(Product&);
	void Info();
	int Sell(int, double, bool);
};

bool MyStack::Pop(Pen& data)
{
	if (!Top) return false;
	Node* temp = Top->prev;
	data = Top->data; delete Top;
	Top = temp; Count--;
	return true;
}

bool MyQueue::Pop(Product& data) {
	if (!First) return false;
	Node* temp = First->next;
	data = First->data;
	remain -= First->data.volume;
	delete First;
	First = temp;
	Count--;
	return true;
}

bool MyStack::Push(Pen data)
{
	if (!Top)
	{
		Top = new Node;
		Top->prev = NULL;
		Count = 1;
	}
	else
	{
		Node* temp;
		temp = new Node;
		temp->prev = Top;
		Top = temp;
		Count++;
	}
	Top->data = data;//!!!Узкое место
	return true;
}

bool MyQueue::Push(Product data) {
	if (!First) {
		First = new Node;
		First->next = NULL;
		First->data = data;
		Count = 1;
		remain = First->data.volume;
	}
	else {
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		remain += temp->next->data.volume;
		temp->next->next = NULL;
		Count++;
	}
	return true;
}

void MyStack::Info()
{
	if (!Top)
		cout << "---> Cтек пуст.\n" << endl;
	else
	{
		cout << endl << "Информация о стеке:" << endl;
		cout << "\tРазмер стека = " << Count << "\n\n";
		Top->data.Out();
		cout << endl;
		//cout << "\tTop data =" << Top->data << endl << endl;
	}
}

void MyQueue::Info() {
	if (!First) {
		cout << "--->Очередь пуста" << endl;
		cout << "\nОстаток = " << remain << "\nДоход = " << profit;
	}
	else {
		cout << endl << "Информация: " << endl;
		cout << "\tРазмер очереди = " << Count << endl;
		//cout << "YeFirst data" << First->data << endl << endl;
		First->data.Out();

		cout << "\nОстаток = " << remain << "\nДоход = " << profit;
	}
}

void Pen::Out()
{
	cout << "Цвет: " << color << " | Тип ручки: " << kind << " | Вес: " << weight << " гр." << " | Длина: " << length << " см " << endl;
};

void Product::Out() {
	cout << "\nКоличество = " << volume << ' ' << "Цена = " << price << endl;
}

int MyQueue::Sell(int volume, double price, bool fsell) {
	//cout << "\nDebugging:\n" << volume << endl;
	Product temp;

	if (volume == 0) return true;


	if (price < First->data.price && fsell == true) {
		cout << "\nСлишком низкая цена\n";
		return false;
	}
	else {
		if (volume > remain) {
			cout << "\nНедостаточно товаров\n";
			return -1;
		}
		if (First->data.volume > volume) {
			First->data.volume -= volume;
			profit += (price - First->data.price) * volume;
			//profit += price * volume;
			remain -= volume;
			return 0;
		}
		else {
			profit += (price - First->data.price) * First->data.volume;
			volume -= First->data.volume;
			Pop(temp);
			return volume;
		}
	}
}

void Push(MyStack&);
bool GetFile(MyStack&);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	int №;

	do
	{
		cout << "\nВыберите задание(1-2): ";
		cin >> №; cout << endl;

		if (№ == 1)
		{
			cout << "\nРабота со стеком.\n\n";
			Pen k, f;
			int task, i = 0, n, n1;

			MyStack S, I;

			cout << "Действие над стеком:\n1 - Добавить товар в корзину.\n2 - Вытащить товар из корзины.\n3 - Очистить корзину.\n4 - взять элементы из файла.\n5 - содержимое корзины.\n\n";
			do {
				cout << "Действие: ";
				cin >> task;
				cout << "\n";

				if (task == 1)
				{
					Push(S);
				}

				else if (task == 2)
				{

					cout << "По скольким характеристикам выбирать ручкe, по 1 или 4? ";
					cin >> n; cout << endl;

					if (n == 1)
					{
						n = 0;
						cout << "По какой характеристике?\n1 - цвет\n2 - тип ручки\n3 - длина\n4 - вес\nХарактеристика: "; cin >> n1;
						cout << "\n";

						if (n1 == 1)
						{
							n = 1;
							cout << "Цвет: "; cin >> f.color; cout << endl;
							while (S.Pop(k))
							{
								I.Push(k);
								if (k.color == f.color && n != 0)
								{
									I.Pop(k);
									n = 0;
								}
							}
							while (I.Pop(k))
							{
								S.Push(k);
							}
							if (n != 0)
							{
								cout << "\nТакой ручки нет.\n\n";
							}
						}

						else if (n1 == 2)
						{
							n = 1;
							cout << "Тип ручки: "; cin >> f.kind; cout << endl;
							while (S.Pop(k))
							{
								I.Push(k);
								if (k.kind == f.kind && n != 0)
								{
									I.Pop(k);
									n = 0;
								}
							}
							while (I.Pop(k))
							{
								S.Push(k);
							}
							if (n != 0)
							{
								cout << "\nТакой ручки нет.\n\n";
							}

						}

						else if (n1 == 3)
						{
							n = 1;
							cout << "Длина: "; cin >> f.length; cout << endl;
							while (S.Pop(k))
							{
								I.Push(k);
								if (k.length == f.length && n != 0)
								{
									I.Pop(k);
									n = 0;
								}
							}
							while (I.Pop(k))
							{
								S.Push(k);
							}
							if (n != 0)
							{
								cout << "\nТакой ручки нет.\n\n";
							}
						}

						else if (n1 == 4)
						{
							n = 1;
							cout << "Вес: "; cin >> f.weight; cout << endl;
							while (S.Pop(k))
							{
								I.Push(k);
								if (k.weight == f.weight && n != 0)
								{
									I.Pop(k);
									n = 0;
								}
							}
							while (I.Pop(k))
							{
								S.Push(k);
							}
							if (n != 0)
							{
								cout << "\nТакой ручки нет.\n\n";
							}
						}
						else
							if (n != 0)
							{
								cout << "\nТакой ручки нет.\n\n";
							}

					}

					else if (n == 4)
					{
						cout << "Цвет: ";
						cin >> f.color;
						cout << "Тип ручки: ";
						cin >> f.kind;
						cout << "Длина: ";
						cin >> f.length;
						cout << "Вес: ";
						cin >> f.weight;
						cout << endl;
						while (S.Pop(k))
						{
							I.Push(k);
							if (k.weight == f.weight && k.kind == f.kind && k.length == f.length && k.weight == f.weight && n != 0)
							{
								I.Pop(k);
								n = 0;
							}
						}
						while (I.Pop(k))
						{
							S.Push(k);
						}
						if (n != 0)
						{
							cout << "\nТакой ручки нет.\n\n";
						}
					}
					else { cout << "Вы ввели неверную характеристику."; }

				}

				else if (task == 3)
				{

					while (S.Pop(k));
					S.Info();
				}

				else if (task == 4 && i == 0)
				{
					i = 1;
					GetFile(S);
					S.Info();
				}

				else if (task == 4 && i == 1)
				{
					cout << "Данные из файла уже были взяты.\n\n";
				}

				else if (task == 5)
				{
					cout << "___________________________\n\n";
					while (S.Pop(k))
					{
						I.Push(k);
						k.Out();
					}
					while (I.Pop(k))
					{
						S.Push(k);
					}
					//cout << " " << k;
					cout << endl;
					cout << "___________________________\n";
					cout << endl;
				}
				else if(task < 0 || task > 5) cout << "Данного действия не существует. Повторите попытку.\n\n";
			} while (task != 0);
		}

		else if (№ == 2)
		{

			int n = 10, num = 1;
			Product k;
			MyQueue Q;

			int  i = 1;
			float cost, count1;

			do {
				do {
					cout << "Введите кол-во товара для продажи: ";
					cin >> count1; cout << "\n\n";
					if (count1 < 0)
					{
						cout << "Вы ввели неверное кол-во товара. Повторите попытку.\n\n";
					}
					else i = 0;
				} while (i != 0);

				do {
					cout << "Введите стоимость товара для продажи: ";
					cin >> cost; cout << "\n\n";
					if (cost < 0)
					{
						cout << "Вы ввели неверную стоимость товара. Повторите попытку.\n\n";
					}
					else i = 1;
				} while (i = 0);

				Product k1 = { count1, cost };
				Q.Push(k1);

				cout << "Добавить ещё 1 партию?\n(0 - закончить).\nОтвет: ";
				cin >> num; cout << "\n\n";
			} while (num != 0);

			Q.Info();
			int sellc, sellp, selld;
			do {
				cout << "\n__________________\n";
				cout << "\nВведите кол-во товара на продажу (0 для выхода): ";
				cin >> sellc;
				if (sellc > 0) {
					cout << "\nВведите стоимость продажи: ";
					cin >> sellp;
					if (sellp < 0) sellp = 0;
					selld = Q.Sell(sellc, sellp, true);
					while (selld > 0) {
						selld = Q.Sell(selld, sellp, false);
					}
					Q.Info();
				}
			} while (sellc > 0);
			cout << "\n__________________\n";
			while (Q.Pop(k)) k.Out();
			cout << endl;
			Q.Info();


		}
		else if (№ == 0)
			cout << "\nДосвидание.\n" << endl;

		else cout << "\nВы выбрали несуществующий номер, повторите попытку.\n" << endl;

	} while (№ != 0);

	return 0;
}

bool GetFile(MyStack& Stack) {
	ifstream F("file.txt");
	if (!F) {
		cout << "Файл не был найден." << endl;
		return false;
	}
	else
	{
		Pen k;

		while (F >> k.color >> k.kind >> k.length >> k.weight) {//Пока можем извлечь
			Stack.Push(k);
		}

		F.close();
		return true;
	}
}

void Push(MyStack& Stack)
{
	Pen k;
	cout << "Цвет: ";
	cin >> k.color;
	cout << "Тип ручки: ";
	cin >> k.kind;
	cout << "Длина: ";
	cin >> k.length;
	cout << "Вес: ";
	cin >> k.weight;
	Stack.Push(k);
	cout << endl;
}