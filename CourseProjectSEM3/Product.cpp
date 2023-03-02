#include "Product.h"
#include <conio.h>
#include "Validation.h"
#include "Constants.h"
#include <iomanip>
#include <iostream>
#include "CursorMove.h"
#include <fstream>
using namespace std;

void Product::addProduct(vector <Product>& pr, User us)	//���������� ������
{
	system("cls");
	Product temp{};
	cout << "�----------------------------------------------------------------------------\n";
	cout << "|            ��������            |   ����(�)  |      �����      | ��������� |\n";
	cout << "�----------------------------------------------------------------------------\n";
	cout << "|" << setw(33) << "|" << setw(13) << "|" << setw(18) << "|" << setw(12) << "|";
	cout << "\n�----------------------------------------------------------------------------\n";
	gotoxy(3, wherey() - 2);
	inputNameString(temp, 1);
	cout << "\n\n                           \n";
	gotoxy(36, wherey() - 3);
	temp.setPrice();
	cout << "\n\n                           \n";
	gotoxy(49, wherey() - 3);
	inputCityString(temp, 1);
	cout << "\n\n                           \n";
	cout << "���������:\n1 - ��������� \n2 - ������������ \n3 - ������ ���� \n4 - ��� ���� � ���� \n5 - ����������� \n6 - ����� � ����� \n7 - �������� \n8 - ������ � ������������";
	gotoxy(70, wherey() - 11);
	temp.setCategory();
	temp.setDate();
	temp.setSellerLogin(us);
	pr.push_back(temp);
	cout << "\n\n                       \n          \n                \n                   \n                 \n                      \n                 \n                  \n             \n                         ";
	gotoxy(0, wherey() - 8);
	cout << "\n����� ������� ��������.\n";
}

void Product::showProduct(vector <Product> pr, int studNum, int& k, bool code)	//�����
{
	if (code == 0)
	{
		cout << "�-------------------------------------------------------------------------------------------\n";
		cout << "|            ��������            |   ����(�)  |      �����      |         ���������         |\n";
		cout << "�-------------------------------------------------------------------------------------------\n";
	}
	else
	{
		k++;
		cout << "| " << setw(31) << pr[studNum].name << "| " << setw(11) << pr[studNum].price << "| " << setw(16) << pr[studNum].city << "| " << setw(26) << CATEGORIES1[pr[studNum].category] << "|";
		cout << "\n�--------------------------------------------------------------------------------------------\n";
	}
}

void Product::showProducts(vector <Product> pr)	//�����
{
	int k = 0;
	cout << "�-----------------------------------------------------------------------------------------------------------------\n";
	cout << "| � |            ��������            |   ����(�)  |      �����      |         ���������         | ���� ���������� |\n";
	cout << "�-----------------------------------------------------------------------------------------------------------------\n";
	while (k < pr.size()) {
		cout << "|" << setw(3) << k + 1 << "| " << setw(31) << pr[k].name << "| " << setw(11) << pr[k].price << "| " << setw(16) << pr[k].city << "| " << setw(26) << CATEGORIES1[pr[k].category] << "|   ";
		pr[k].getPrint();
		cout << "  |";
		cout << "\n�-----------------------------------------------------------------------------------------------------------------\n";
		k++;
	}
}

void Product::showFullProducts(vector <Product> pr, vector <User> us)	//�����
{
	int k = 0;
	int i = 0;
	char bufPhone[1];
	cout << "�----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "| � |            ��������            |   ����(�)  |      �����      |         ���������         | ����� �������� | ���� ���������� |\n";
	cout << "�----------------------------------------------------------------------------------------------------------------------------------\n";
	while (k < pr.size()) {
		cout << "|" << setw(3) << k + 1 << "| " << setw(31) << pr[k].name << "| " << setw(11) << pr[k].price << "| " << setw(16) << pr[k].city << "| " << setw(26) << CATEGORIES1[pr[k].category] << "| ";
		for (i = 0; i < us.size(); i++) 
			if (strcmp(us[i].getLogin(), pr[k].sellerLogin) == 0)
				break;
		cout << setw(15) << us[i].getPhoneNumber() << "|   ";
		pr[k].getPrint();
		cout << "  |";
		cout << "\n�----------------------------------------------------------------------------------------------------------------------------------\n";
		k++;
	}
}

void Product::showStatProducts(vector <Product> pr, vector<int> time)	//�����
{
	int k = 0;
	int i = 0;
	int j = 0;
	int choose = 0;
	cout << "�-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "| � |            ��������            |   ����(�)  |      �����      |         ���������         | ���� ���������� |  ����� �������  |\n";
	cout << "�-----------------------------------------------------------------------------------------------------------------------------------\n";
	while (k < pr.size()) {
		cout << "|" << setw(3) << k + 1 << "| " << setw(31) << pr[k].name << "| " << setw(11) << pr[k].price << "| " << setw(16) << pr[k].city << "| " << setw(26) << CATEGORIES1[pr[k].category] << "|   ";
		pr[k].getPrint();
		cout << "  | ";
		cout << setw(15) << SALETIME[time[k]] << " |";
		cout << "\n�-----------------------------------------------------------------------------------------------------------------------------------\n";
		k++;
	}
	cout << "���������� �� ������� �������:\n";
	for (j = 0; j < 4; j++) {
		choose = 0;
			cout << SALETIME[j] << " - ";
		for (i = 0; i < time.size(); i++) 
			if (time[i] == j)
				choose++;
		cout << choose << " ��.\n";
	}
}

void Product::changeProductInfo(vector <Product>& pr)	//�������������� ����������
{
	int prodNum, n, a;
	cout << "������� ����� ������: ";
	prodNum = inputNumber(1, pr.size(), 0);
	cout << "�������� ���������� ��������.\n1) �������� ������\n2) ���� ������\n3) �����\n4) ���������\n0) ������\n\n����: ";
	n = inputNumber(0, 4, 0);

	switch (n) {
	case 1:
		cout << "������� ����� ��� ������: ";
		inputNameString(pr[prodNum - 1], 0);
		break;
	case 2:
		cout << "������� ����� ���� ������: ";
		pr[prodNum - 1].price = inputNumber(0, 9999999999, 0);
		break;
	case 3:
		cout << "������� ����� ����� ������: ";
		inputCityString(pr[prodNum - 1], 0);
		break;
	case 4:
		cout << "���������:\n1 - ��������� \n2 - ������������ \n3 - ������ ���� \n4 - ��� ���� � ���� \n5 - ����������� \n6 - ����� � ����� \n7 - �������� \n8 - ������ � ������������";
		cout << "\n������� ����� ��������� ������: ";
		a = inputNumber(1, 8, 0);
		pr[prodNum - 1].category = a - 1;
		break;
	case 0:
		return;
	}
}

void Product::setSellerLogin(User us) {
	for (int i = 0; i < strlen(us.getLogin()); i++)
		sellerLogin[i] = us.getLogin()[i];
}

void Product::inputNameString(Product& pr, bool table)	//�������� ���� �� ������� ������ ����� ����
{
	while (true)
	{
		bool temp = 1;
		char c[31] = {};
		int i = 0;
		do {
			c[i] = _getch();
			if ((c[i] == '\r' || c[i] == ' ' || c[i] == '-') && i == 0)
				continue;
			if (c[i] == '\r')
				break;
			i++;
			if (c[i - 1] == 8 && i - 1 > 0)
			{
				cout << (char)8 << ' ' << (char)8;
				i--;
				i--;
				continue;
			}
			if (c[i - 1] == 8 && i - 1 == 0)
			{
				i--;
				continue;
			}
			if (i == 30) {
				i--;
				continue;
			}
			putchar(c[i - 1]);
		} while (true);
		c[i] = '\0';
		for (int i = 0; i < strlen(c) + 1; i++)
			pr.name[i] = c[i];
		for (int k = 0; k < strlen(pr.name); k++)
			if ((pr.name[k] < 'a' || pr.name[k] > 'z') && (pr.name[k] < 'A' || pr.name[k] > 'Z') && (pr.name[k] < '�' || pr.name[k] > '�') &&(pr.name[k] < '0' || pr.name[k] > '9') && pr.name[k] != '-' && pr.name[k] != ' ')
			{
				temp = 0;
				for (int i = 0; i < strlen(pr.name); i++)
					pr.name[i] = '\0';
				cout << "\n\n��������� �������.\n";
				if (table) {
					gotoxy(3, wherey() - 3);
					cout << "                              ";
					gotoxy(3, wherey());
				}
				else
					cout << "����: ";
				break;
			}
		if (temp == 0)
			continue;
		break;
	}
}
void Product::inputCityString(Product& pr, bool table)	//�������� ������� �� ������� ������ ����� ����
{

	while (true)
	{
		bool temp = 1;
		char c[16] = {};
		int i = 0;
		do {
			c[i] = _getch();
			if ((c[i] == '\r' || c[i] == ' ' || c[i] == '-') && i == 0)
				continue;
			if (c[i] == '\r')
				break;
			i++;
			if (c[i - 1] == 8 && i - 1 > 0)
			{
				cout << (char)8 << ' ' << (char)8;
				i--;
				i--;
				continue;
			}
			if (c[i - 1] == 8 && i - 1 == 0)
			{
				i--;
				continue;
			}
			if (i == 15) {
				i--;
				continue;
			}
			putchar(c[i - 1]);
		} while (true);
		c[i] = '\0';
		for (int i = 0; i < strlen(c) + 1; i++)
			pr.city[i] = c[i];
		for (int k = 0; k < strlen(pr.city); k++)
			if ((pr.city[k] < '�' || pr.city[k] > '�') && pr.city[k] != '-' && pr.city[k] != ' ')
			{
				temp = 0;
				for (int i = 0; i < strlen(pr.city); i++)
					pr.city[i] = '\0';
				cout << "\n\n��������� �������.\n";
				if (table) {
					gotoxy(49, wherey() - 3);
					cout << "               ";
					gotoxy(49, wherey());
				}
				else
					cout << "����: ";
				break;
			}
		if (temp == 0)
			continue;
		break;
	}
}

int Product::inputProdNumber(int left, int right, int table)	//�������� ����� �����
{
	int leng;
	if (table == 36)
		leng = 11;
	else
		leng = 3;
	int number;
	while (true)
	{
		char* c = new char[leng];
		int i = 0;
		do {
			c[i] = _getch();
			if ((c[i] == '\r' || c[i] == ' ') && i == 0) 
				continue;
			if (c[i] == '\r')
				break;
			i++;
			if (c[i - 1] == 8 && i - 1 > 0)
			{
				cout << (char)8 << ' ' << (char)8;
				i--;
				i--;
				continue;
			}
			if (c[i - 1] == 8 && i - 1 == 0)
			{
				i--;
				continue;
			}
			if (i == leng - 1) {
				i--;
				continue;
			}
			putchar(c[i - 1]);
		} while (true);
		c[i] = '\0';
		bool temp1 = 0;
		for (int i = 0; i < strlen(c); i++)
			if (c[i] < '0' || c[i] > '9') {
				temp1 = 1;
				break;
			}
		if (temp1 == 0) {
			number = atoi(c);
			if (isNumberRangeCorrect(number, left, right)) {
				delete[] c;
				return number;
			}
			else {
				cout << "\n\n��������� �������.\n";
				if (table > 0)
				{
					gotoxy(table, wherey() - 3);
					if (table == 36)
						cout << "         ";
					else
						cout << "  ";
					gotoxy(table, wherey());
				}
				for (int i = 0; i < strlen(c); i++)
					c[i] = '\0';
			}
		}
		else {
			cout << "\n\n��������� �������.\n";
			if (table > 0)
			{
				gotoxy(table, wherey() - 3);
				if (table == 36)
					cout << "         ";
				else
					cout << "  ";
				gotoxy(table, wherey());
			}
			for (int i = 0; i < strlen(c); i++)
				c[i] = '\0';
		}
	}
}

void Product::deleteProduct(vector <Product>& pr)	//��������
{
	int productNum;
	cout << "������� ����� ������: ";
	productNum = inputNumber(1, pr.size(), 0);
	productNum--;
	int k = 0;
	system("cls");
	showProduct(pr, productNum, k, 0);
	showProduct(pr, productNum, k, 1);
	cout << "�� ������������� ������ ������� ��� ����������? (�� - 1, ��� - 0)\n\n����: ";	//������������� ��������
	bool agree;
	agree = inputNumber(0, 1, 0);
	if (agree == 0)
		return;
	cout << "�� ����� ������� �� �������� �����?\n1 - � �� ���� ������ ��������� ���� �����\n2 - � ������ �����\n\n����: ";	//������������� ��������
	agree = inputNumber(1, 2, 0) - 1;
	if (agree) {
		cout << "�� ����� ����� ��� ������ �����?\n1 - 1-2 ���\n2 - 1-2 ������\n3 - 1 �����\n4 - ����� 1 ������\n\n����: ";	//������������� ��������
		int choose = inputNumber(1, 4, 0) - 1;
		fstream fResults;	
		fResults.open("results.txt", ios::app);
		if (!fResults.is_open())
			cout << "���� � �������� �� ������.";
		else {
		Product temp = pr[productNum];
			fResults.write((char*)&(temp), sizeof(Product));
			fResults.write((char*)&(choose), sizeof(int));
		}
		fResults.close();
	}
	pr.erase(pr.begin() + productNum);
	cout << "����� ������� �����!\n";
}

void Product::numberSorting(vector <Product>& pr, int n)	//���������� ������� �� �������� ����������
{
	for (int i = 0; i < pr.size() - 1; i++) {
		for (int j = i + 1; j < pr.size(); j++) {
			if (n == 2 && pr[i].price > pr[j].price || n == 3 && pr[i].category > pr[j].category || n == 5 && pr[i].getTime() < pr[j].getTime()) {
				Product buf = pr[i];
				pr[i] = pr[j];
				pr[j] = buf;
			}
		}
	}
}

void Product::stringSorting(vector <Product>& pr, int n, int leng)	//���������� ������� �� ��������� ����������
{
	for (int i = 0; i < pr.size() - 1; i++) {
		for (int j = i + 1; j < pr.size(); j++) {
			for (int f = 0; f < leng - 1; f++) {
				if (n == 1 && pr[i].name[f] > pr[j].name[f] || n == 4 && pr[i].city[f] > pr[j].city[f]) {
					Product buf = pr[i];
					pr[i] = pr[j];
					pr[j] = buf;
					break;
				}
				if (n == 1 && pr[i].name[f] < pr[j].name[f] || n == 4 && pr[i].city[f] < pr[j].city[f])
					break;
			}
		}
	}
}

void Product::sortProducts(vector <Product>& pr)	//���� ����������� �������
{
	system("cls");
	int n;
	cout << "�� ������ ��������� �����������?\n1) �� ��������\n2) �� ����\n3) �� ���������\n4) �� ������\n5) �� �������\n0) ������\n\n����: ";
	n = inputNumber(0, 5, 0);
	switch (n) {
	case 1:
		stringSorting(pr, n, 30);
		cout << "\n������ ������� �������������.\n";
		break;
	case 2:
		numberSorting(pr, n);
		cout << "\n������ ������� �������������.\n";
		break;
	case 3:
		numberSorting(pr, n);
		cout << "\n������ ������� �������������.\n";
		break;
	case 4:
		stringSorting(pr, n, 15);
		cout << "\n������ ������� �������������.\n";
		break;
	case 5:
		numberSorting(pr, n);
		cout << "\n������ ������� �������������.\n";
		break;
	case 0:
		return;
	}
}

void Product::chooseProduct(vector<Product> pr, vector<User> us)
{
	int productNum, i;
	cout << "������� ����� ������: ";
	productNum = inputNumber(1, pr.size(), 0);
	productNum--;
	for (i = 0; i < us.size(); i++)
		if (strcmp(us[i].getLogin(), pr[productNum].getSellerLogin()) == 0)
			break;
	cout << "����� �������� �������� ��� �����: " << us[i].getPhoneNumber();
}

void Product::searchProducts(vector <Product> pr)	//����� 
{
	system("cls");
	int intBuf1, intBuf2, kod;
	int k = 0;	//������� 
	Product charBuf{};
	cout << "�� ������ ��������� ������?\n1) �� ��������\n2) �� ����\n3) �� ���������\n4) �� ������\n0) ������\n\n����: ";
	kod = inputNumber(0, 4, 0);
	switch (kod)
	{
	case 1:
		cout << "������� ��������: ";
		inputNameString(charBuf, 0);
		cout << endl;
		for (int i = 0; i < pr.size(); i++)
			if (strcmp(pr[i].name, charBuf.name) == 0)
			{
				if (k == 0)
					showProduct(pr, i, k, 0);
				showProduct(pr, i, k, 1);
			}
		if (k == 0)
			cout << "��� ������� � ����� ���������.\n";
		break;
	case 2:
		cout << "������� ��������� ����: ";
		cin >> intBuf1;
		cout << "������� �������� ����: ";
		cin >> intBuf2;
		for (int i = 0; i < pr.size(); i++)
			if (pr[i].price > intBuf1 && pr[i].price < intBuf2)
			{
				if (k == 0)
					showProduct(pr, i, k, 0);
				showProduct(pr, i, k, 1);
			}
		if (k == 0)
			cout << "��� ������� � ����� �����.\n";
		break;
	case 3:
		cout << "���������:\n1 - ��������� \n2 - ������������ \n3 - ������ ���� \n4 - ��� ���� � ���� \n5 - ����������� \n6 - ����� � ����� \n7 - �������� \n8 - ������ � ������������";
		cout << "\n������� ���������: ";
		cin >> intBuf1;
		for (int i = 0; i < pr.size(); i++)
			if (pr[i].category == intBuf1 - 1)
			{
				if (k == 0)
					showProduct(pr, i, k, 0);
				showProduct(pr, i, k, 1);
			}
		if (k == 0)
			cout << "��� ������� � ������ ���������.\n";
		break;
	case 4:
		cout << "������� �����: ";
		inputCityString(charBuf, 0);
		cout << endl;
		for (int i = 0; i < pr.size(); i++)
			if (strcmp(pr[i].city, charBuf.city) == 0)
			{
				if (k == 0)
					showProduct(pr, i, k, 0);
				showProduct(pr, i, k, 1);
			}
		if (k == 0)
			cout << "��� ������� � ���� ������.\n";
		break;
	case 0:
		return;
	}
}

Product Product::operator =(Product obj) {
	for (int i = 0; i < 31; i++)
		name[i] = obj.name[i];
	for (int i = 0; i < 16; i++)
		city[i] = obj.city[i];
	for (int i = 0; i < 21; i++)
		sellerLogin[i] = obj.sellerLogin[i];
	price = obj.price;
	access = obj.access;
	category = obj.category;
	return *this;
}