#include "User.h"
#include "Validation.h"
#include "Constants.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

void User::regIn(vector<User>& us)	//�����������
{
	system("cls");
	char bufPassword[31] = {};
	char* bufLogin = new char[21];
	int i = 0;
	cout << "������� �����.\n\t������� ����� ������:\n\t1) �� 5 �� 20 ��������\n\t2) ���������:\n\t\t��������� �����\n\t\t�����\n\t\t������� (-_.)\n����: ";
	while (true)
	{
		inputString(bufLogin, 21);	//�������� �� �����
		if (loginCheck(bufLogin))	//�������� �� ��������� ������� ������
			break;
		else
			cout << "��������� �������: ";
	}
	for (int i = 0; i < us.size(); i++)
	{
		if (strcmp(bufLogin, us[i].login) == 0)	//�������� �� ������������� ������
		{
			cout << "\n��������� ����� ��� ����������.";
			return;
		}
	}
	cout << "������� ������.\n\t������� ����� ������:\n\t1) �� 8 �� 30 ��������\n\t2) ���������:\n\t\t��������� �����\n\t\t�����\n\t\t������� (!@#$%^&*_-+:.)\n\t3) ����������� ������ ���� ����� �������� � ������� ��������\n����: ";
	while (true)
	{
		do {	//����� * ������ ������, �������� * ��� �������
			bufPassword[i] = _getch();
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
		if (passwordCheck(bufPassword))	//�������� ������
			break;
		else
		{
			i = 0;
			char bufPassword[31]{};
			cout << "\n������ ����������� ������.\n����: ";
		}
	}

	User temp = {};
	cout << "\n������� ����� ��������: ";
	setPhone(temp);
	for (int i = 0; i < 20; i++)
		temp.login[i] = bufLogin[i];
	for (int i = 0; i < 30; i++)
		temp.password[i] = bufPassword[i];
	makeSalt(temp);	//�������� ���� � ������
	temp.access = 0;	//��������� �������
	temp.role = 0;	//��������� ����
	us.push_back(temp);
	delete[]bufLogin;
}

void User::setPhone(User& temp) {
	while (true)
	{
		bool temp1 = 1;
		char c[15] = {};
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
			if (i == 14) {
				i--;
				continue;
			}
			putchar(c[i - 1]);
		} while (true);
		c[i] = '\0';
		for (int i = 0; i < strlen(c) + 1; i++)
			temp.phoneNumber[i] = c[i];
		for (int k = 0; k < strlen(temp.phoneNumber); k++)
			if ((temp.phoneNumber[k] < '0' || temp.phoneNumber[k] > '9') && temp.phoneNumber[k] != '+')
			{
				temp1 = 0;
				for (int i = 0; i < strlen(temp.phoneNumber); i++)
					temp.phoneNumber[i] = '\0';
				cout << "\n\n��������� �������.\n";
				cout << "����: ";
				break;
			}
		if (temp1 == 0)
			continue;
		break;
	}
}

void User::setLogin( vector<User> us, User& user) {
	char* bufLogin = new char[21];
	bool temp = 0;
	cout << "������� �����.\n\t������� ����� ������:\n\t1) �� 5 �� 20 ��������\n\t2) ���������:\n\t\t��������� �����\n\t\t�����\n\t\t������� (-_.)\n����: ";
	while (true)
	{
		temp = 0;
		inputString(bufLogin, 21);
		for (int i = 0; i < us.size(); i++)
		{
			if (strcmp(bufLogin, us[i].getLogin()) == 0)	//�������� �� ������������� ������
			{
				cout << "\n��������� ����� ��� ����������.";
				temp = 1;
			}
		}
		if (loginCheck(bufLogin) && temp == 0)
			break;
		else
			cout << "��������� �������: ";
	}
	for (int i = 0; i < 20; i++)
		user.login[i] = bufLogin[i];
	cout << "\n����� ������� �������.\n";
	delete[]bufLogin;
}

void User::setPassword(User& user) {
	char bufPassword[31] = {};
	int i = 0;
	cout << "������� ������.\n\t������� ����� ������:\n\t1) �� 8 �� 30 ��������\n\t2) ���������:\n\t\t��������� �����\n\t\t�����\n\t������� (!@#$%^&*_-+:.)\n\t3) ����������� ������ ���� ����� �������� � ������� ��������\n����: ";
	while (true)
	{
		do {	//����� * ������ ������, �������� * ��� �������
			bufPassword[i] = _getch();
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
		if (passwordCheck(bufPassword))
			break;
		else
		{
			i = 0;
			char bufPassword[31]{};
			cout << "\n������ ����������� ������.\n����: ";
		}
	}
	for (int i = 0; i < 30; i++)
		user.password[i] = bufPassword[i];
}

void User::makeSalt(User &temp)	//�������� ���� � �������������� ������ 
{
	for (int i = 0; i < 20; i++)
		temp.salt[i] = SALT_SYMBOLS[rand() % 10];
	temp.salt[20] = '\0';
	int k;
	int i = 0;
	for (i; i < (strlen(temp.password) * 3); i++)
	{
		k = i % 20;
		temp.salted_hash_password[i] = temp.password[i / 3] + temp.salt[k] - 'a';
	}
	temp.salted_hash_password[i] = '\0';
}

void User::makePassword(User& temp)	//�������������� ������ �������
{
	int k;
	int i = 0;
	for (i; i < strlen(temp.salted_hash_password); i++)
	{
		k = i % 20;
		temp.password[i / 3] = -temp.salt[k] + 'a' + temp.salted_hash_password[i];
	}
	temp.password[i / 3] = '\0';
}

void User::passwordClear(User& temp)	//�������������� ������ �������
{
	for (int i = 0; i < strlen(temp.password); i++)
		temp.password[i] = ' ';
}

void User::showUser(vector<User> us, int userNum)	//����� ������������
{
	cout << "�---------------------------------------------------------------------------------------------\n";
	cout << "|�|       �����         |             ������             |  ����  |  ������  | ����� �������� |\n";
	cout << "�---------------------------------------------------------------------------------------------\n";
	cout << "|1|" << setw(20) << us[userNum].login << " |" << setw(31) << us[userNum].password << " |" << setw(7) << us[userNum].role << " |" << setw(9) << us[userNum].access << " |" << setw(15) << us[userNum].phoneNumber << " |";
	cout << "\n�--------------------------------------------------------------------------------------------\n";
}

void User::showUsers(vector<User> us)	//����� ���� �������������
{
	int k = 0;
	cout << "�---------------------------------------------------------------------------------------------\n";
	cout << "|�|       �����         |             ������             |  ����  |  ������  | ����� �������� |\n";
	cout << "�---------------------------------------------------------------------------------------------\n";
	while (k < us.size()) {
		cout << "|" << k + 1 << "|" << setw(20) << us[k].login;
		if (us[k].role == 2)	//�������� �� �������� ��������������
			cout << " |" << setw(31) << "********************";
		else
			cout << " |" << setw(31) << us[k].password;
		cout << " |" << setw(7) << us[k].role << " |" << setw(9) << us[k].access << " |" << setw(15) << us[k].phoneNumber << " |";
		cout << "\n----------------------------------------------------------------------------------------------\n";
		k++;
	}
}

void User::addUser(vector<User> &us)	//���������� �������������
{
	regIn(us);
	cout << "\n������� ��� ������������ (0 - ������������, 1 - �������������): ";
	int temp = inputNumber(0, 1, 0);	//����� ���� ������������
	us[us.size() - 1].role = temp;
	us[us.size() - 1].access = true;	//��������� ������� true

	cout << "\n������������ ������� ��������.";
	cout << "\n������� ����� ������� ��� �����������...\n";
	_getch();
}

void User::changeUserInfo(vector<User>& us)	//�������������� ���������� � ������������
{
	cout << "\n������� ����� ������������: \n";
	int numberOfUser, i = 0;
	numberOfUser = inputNumber(1, us.size(), 0);
	if (us[numberOfUser - 1].role == 2)	//�������� �� �������� ��������������
	{
		cout << "�� �� ������ �������� ���������� � ������� ��������������.\n";
		return;
	}
	int n;
	cout << "\n1) �������� �����\n2) �������� ������\n3) �������� ����� ��������\n4) ����������� (�������������) �������\n0) ������\n����: ";
	n = inputNumber(0, 4, 0);
	switch (n) {
	case 1: // ���� ������ ������
	{
		setLogin(us, us[numberOfUser - 1]);
		break;
	}
	case 2:	//���� ������ ������
	{
		setPassword(us[numberOfUser - 1]);
		User::makeSalt(us[numberOfUser - 1]);
		cout << "\n������ ������� �������.\n";
		break;
	}
	case 3: 
		cout << "������� ����� �����: ";
		setPhone(us[numberOfUser - 1]);
		cout << "\n����� ������� �������.\n";
		break;
	case 4:	//��������� �������
		if (us[numberOfUser - 1].access == true)	//�������� �� ������� �������
		{
			us[numberOfUser - 1].access = false;
			cout << "\n������ ������� ������.\n";
		}
		else
		{
			us[numberOfUser - 1].access = true;
			cout << "\n������ ������� ������.\n";
		}
		break;
	case 0:
		return;
	}
}

void User::deleteUser(vector<User>& us)	//�������� ������������
{
	int numberOfUser;
	cout << "������� ����� ������������: \n";
	numberOfUser = inputNumber(1, 100, 0);
	if (numberOfUser > us.size())	//�������� �� ������������� ������������
	{
		cout << "������������ � ����� ������� �� ����������.\n";
		return;
	}
	numberOfUser--;

	if (us[numberOfUser].role == 2)	//�������� �� �������� ��������������
	{
		cout << "�� �� ������ ������� �������� ��������������.\n";
		return;
	}
	system("cls");
	showUser(us, numberOfUser);
	cout << "�� ������������� ������ ������� ����� ������������? (�� - 1, ��� - 0)\n\n����: ";
	bool agree;
	agree = inputNumber(0, 1, 0);
	if (agree == 0)	//������������� ��������
		return;
	us.erase(us.begin() + numberOfUser);
	cout << "������������ ������� �����.\n";
}