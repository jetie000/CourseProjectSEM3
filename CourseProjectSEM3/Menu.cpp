#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <io.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "Validation.h"
#include "Menu.h"
#include "Constants.h"
#include <iomanip>
using namespace std;

void installations()
{
	srand(time(NULL));
	SetConsoleCP(1251);	//������� ���������
	SetConsoleOutputCP(1251);
}

template<typename T>
void fileRead(fstream& fs, vector<T>& vec) {
	T temp;
	while (fs.read((char*)&temp, sizeof(T)))
		vec.push_back(temp);
}

template<typename T>
void fileWrite(fstream& ofs, vector<T>& vec) {
	for (int i = 0; i < vec.size(); i++)
		ofs.write((char*)&(vec[i]), sizeof(T));
}

void mainMenu()
{
	fstream fUsers, fProducts;
	vector <Product> pr;	//������ ���������
	vector <User> us;	//������ �������������
	int studNum = 0, userNum = 0;
	int i1 = 0, i2 = 0;
	try
	{
		fUsers.open(PATH_USERS);
		if (!fUsers.is_open())
			throw exception("���� ������������� �� ������.");
	}
	catch (exception& x) {
		cout << x.what() << endl;
		return;
	}
	if (fUsers.peek() == EOF)	//���������� �������� ��������������, ���� ���� � �������������� �� ����������
	{
		fUsers.close();
		fUsers.open(PATH_USERS);
		User temp{};
		temp.setAdmin();
		fUsers.write((char*)&(temp), sizeof(User));
		fUsers.close();
		fUsers.open(PATH_USERS);
	}
	fProducts.open(PATH_PRODUCTS);
	if (!fProducts.is_open()) {
		cout << "���� ������� �� ������.";
		return;
	}
	fileRead(fProducts, pr);
	fProducts.close();
	fileRead(fUsers, us);
	fUsers.close();
	for (int i = 0; i < us.size(); i++)
		User::makePassword(us[i]);
	int n;
	while (true)	//������� ����
	{
		system("cls");
		cout << "������� ����:\n1) �����\n2) ������������������\n0) ����� �� ���������\n\n����: ";
		n = inputNumber(0, 2, 0);
		switch (n)
		{
		case 1:
			logIn(us, pr);	//����
			break;
		case 2:
		{
			int temp = userNum;
			User::regIn(us);	//�����������
			if (temp != userNum)
				cout << "\n\n����������� ������ �������.\n����� ������������� �������� ����������������.\n";
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		}
		case 0:	//�����
			i1 = 0;
			i2 = 0;
			for (int i = 0; i < us.size(); i++)
				User::passwordClear(us[i]);
			fUsers.open(PATH_USERS, ios::out);
			fileWrite(fUsers, us);
			fUsers.close();
			fProducts.open(PATH_PRODUCTS, ios::out);
			fileWrite(fProducts, pr);
			fProducts.close();
			return;
		}
	}
}

void admin::adminMenu(vector<User>& us, vector<Product>& pr, User user)	//������� ���� ��������������
{
	int n;
	while (true)
	{
		system("cls");
		cout << "1) ���� ������ � ��������\n2) ���� ������ � ��������������\n0) ����� � ������� ����\n\n����: ";
		n = inputNumber(0, 2, 0);
		switch (n)
		{
		case 1:
			admin::adminProdMenu(pr, us, user);
			break;
		case 2:
			admin::adminUserMenu(us);
			break;
		case 0:
			return;
		}
	}
}

void logIn(vector<User>& us, vector<Product>& pr)	//����
{
	system("cls");
	char bufPassword[31] = {};
	char* bufLogin = new char[21];
	int i = 0;
	cout << "������� �����: ";
	inputString(bufLogin, 20);	//���� ������
	cout << "������� ������: ";
	do {
		bufPassword[i] = _getch();	//���� ������
		if (bufPassword[i] == '\r')
			break;
		i++;
		if (bufPassword[i - 1] == 8 && i - 1 > 0)
		{
			cout << (char)8 << ' ' << (char)8;
			i--;
			i--;
			continue;
		}
		if (bufPassword[i - 1] == 8 && i - 1 == 0)
		{
			i--;
			continue;
		}
		putchar('*');
	} while (i < 30);
	bufPassword[i] = '\0';
	for (int i = 0; i < us.size(); i++)	//�������� �� ������� ��������� � ����� ������� � �������
	{
		if (strcmp(bufLogin, us[i].getLogin()) == 0 && strcmp(bufPassword, us[i].getPassword()) == 0)
		{
			if (us[i].getAccess() == 1)	//�������� �� ������
				switch (us[i].getRole())
				{
				case 0: user::userProdMenu(pr, us, us[i]);
					return;
					break;
				case 1: case 2: admin::adminMenu(us, pr, us[i]);
					return;
					break;
				}
			else
			{
				cout << "\n� ������� �������� ��� �������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				return;
			}
		}
	}
	delete[]bufLogin;
	cout << "\n������ �������� ����� ��� ������.\n��������� �������.\n";
	cout << "\n������� ����� ������� ��� �����������...\n";
	_getch();
	return;
}

void admin::adminUserMenu(vector<User>& us)	//���� �������������� ��� ������ � ��������������
{
	int n;
	while (true) {
		system("cls");
		cout << "���� �������������� (������ � ��������������):\n1) ����������� �������������\n2) �������� ������������\n3) �������� ������ ������������\n4) ������� ������������\n0) ����� � ������� ���� ��������������\n\n����: ";
		n = inputNumber(0, 4, 0);
		switch (n)
		{
		case 1:
			User::showUsers(us);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 2:
			User::addUser(us);
			break;
		case 3:
			system("cls");
			User::showUsers(us);
			User::changeUserInfo(us);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 4:
			system("cls");
			User::showUsers(us);
			User::deleteUser(us);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 0:
			return;
		}
	}
}

void admin::adminProdMenu(vector <Product>& pr, vector<User>& us, User user)	//���� �������������� ��� ������ � ����������
{
	int n;
	fstream fResults;
	while (true) {
		system("cls");
		cout << "���� �������������� (������ � ��������):\n1) ����������� ������\n2) �������� �����\n3) �������� ������ � ������\n4) ������� �����\n5) ����������� ������\n6) ����� ������\n7) ����������� ���������� �� ��������� �������\n0) ����� � ������� ���� ��������������\n\n����: ";
		n = inputNumber(0, 7, 0);
		switch (n) {
		case 1:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::showFullProducts(pr, us);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 2:
			Product::addProduct(pr, user);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 3:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			system("cls");
			Product::showFullProducts(pr, us);
			Product::changeProductInfo(pr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 4:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::showFullProducts(pr, us);
			Product::deleteProduct(pr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 5:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::sortProducts(pr);
			Product::showFullProducts(pr, us);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 6:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::searchProducts(pr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 7:
			fResults.open("results.txt", ios::in);
			if (fResults.peek() == EOF)
			{
				cout << "\n�� ������ ������ �� �������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			if (!fResults.is_open())
				cout << "���� � �������� �� ������.";
			else {
				Product temp{};
				int timetemp;
				vector<int> time;
				vector<Product> stat;
				while (fResults.read((char*)&temp, sizeof(Product))) {
					fResults.read((char*)&timetemp, sizeof(int));
					time.push_back(timetemp);
					stat.push_back(temp);
				}
			Product::showStatProducts(stat, time);
			}
			fResults.close();
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 0:
			return;
		}
	}
}

void user::userProdMenu(vector<Product>& pr, vector<User>& us, User& user)	//���� ������������
{
	vector<Product> userPr;
	int n;
	while (true) {
		system("cls");
		cout << "���� ������������:\n1) ����������� ������ ��� �������\n2) ����������� ������\n3) ����� ������\n4) ������ �������\n0) ����� � ������� ����\n\n����: ";
		n = inputNumber(0, 4, 0);
		switch (n) {
		case 1:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::showProducts(pr);
			Product::chooseProduct(pr, us);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 2:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::sortProducts(pr);
			Product::showProducts(pr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 3:
			if (pr.size() == 0)
			{
				cout << "\n�� ������ ������ �� ���������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::searchProducts(pr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 4:
			for (int i = 0; i < pr.size(); i++)
				if (strcmp(user.getLogin(), pr[i].getSellerLogin()) == 0) {
					userPr.push_back(pr[i]);
					pr.erase(pr.begin() + i);
					i--;
				}
			user::userCabinetMenu(us, userPr, user);
			for (int i = 0; i < userPr.size(); i++) {
				pr.push_back(userPr[i]);
				userPr.erase(userPr.begin() + i);
			}
			break;
		case 0:
			return;
		}
	}
}

void user::userCabinetMenu(vector<User>& us, vector<Product>& userPr, User& user)
{
	int n;
	while (true) {
		system("cls");
		cout << "������ �������:\n1) �������� �����\n2) �������� ������ � ������\n3) ������� �����\n4) �������� ������ ��������\n0) ����� � ������� ���� ������������\n\n����: ";
		n = inputNumber(0, 4, 0);
		switch (n) {
		case 1:
			Product::addProduct(userPr, user);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 2:
			if (userPr.size() == 0)
			{
				cout << "\n�� �� �������� �� ������ ������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::showProducts(userPr);
			Product::changeProductInfo(userPr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 3:
			if (userPr.size() == 0)
			{
				cout << "\n�� �� �������� �� ������ ������.\n";
				cout << "\n������� ����� ������� ��� �����������...\n";
				_getch();
				break;
			}
			Product::showProducts(userPr);
			Product::deleteProduct(userPr);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 4:
			user::userInfoMenu(us, user);
			break;
		case 0:
			return;
		}
	}
};

void user::userInfoMenu(vector<User>& us, User& user) {
	int n;
	while (true) {
		system("cls");
		cout << "�������������� �������:\n1) �������� �����\n2) �������� ������\n3) �������� ����� ��������\n0) ����� � ������� ���� ������������\n\n����: ";
		n = inputNumber(0, 3, 0);
		switch (n) {
		case 1:
			User::setLogin(us, user);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 2:
			User::setPassword(user);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 3:
			cout << "\n����� ����� ��������: ";
			User::setPhone(user);
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
			break;
		case 0:
			return;
		}
	}
}
