#include <iostream>
#include "Validation.h"
#include "CursorMove.h"

using namespace std;

int inputNumber(int left, int right, int table)	//Проверка целых чисел
{
	int number;
	while (true)
	{
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left, right))
			return number;
		else {
			cout << "\nПовторите попытку. ";
			if (table > 0)
			{
				gotoxy(table, wherey() - 2);
				cout << "         ";
				gotoxy(table, wherey());
			}
			else
				cout << "\nВвод: ";
		}
	}
}

double inputDouble(int left, int right)	//Проверка дробных чисел
{
	double number;
	while (true)
	{
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left, right))
			return number;
		else
			cout << "Повторите попытку: ";
	}
}

bool isNumberRangeCorrect(int number, int left, int right)	//Проверка на то, находится ли число в заданных границах
{
	if ((number >= left) && (number <= right))
		return true;
	else
		return false;
}

bool isNumberNumeric()	//Проверка на то, является ли число числом
{
	if (cin.get() == '\n')
		return true;
	else
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}

void inputString(char* c1, int a)	//Проверка строки на длину
{
	char c[100];
	do
	{
		gets_s(c);
		if (strlen(c) <= a)
			break;
		cout << "Повторите попытку: ";
	} while (true);
	int i = 0;
	for (i; i < strlen(c); i++)
		c1[i] = c[i];
	c1[i] = '\0';
}

bool loginCheck(char login[])	//Проверка логина на разрешенные символы
{
	if (strlen(login) < 5 || strlen(login) > 20)
		return 0;
	for (int i = 0; i < strlen(login); i++)
	{
		if ((login[i] < 97 || login[i] > 122) && (login[i] < 65 || login[i] > 90) && login[i] != 95 && login[i] != 45 && login[i] != 46 && (login[i] < 48 || login[i] > 57))
			return 0;
	}
	return 1;
}

bool passwordCheck(char password[])	//Проверка пароля на размер и разрешенные символы
{
	if (strlen(password) < 8 && strlen(password) > 30)
		return 0;
	for (int i = 0; i < strlen(password); i++)
	{
		if ((password[i] < 97 || password[i] > 122) && (password[i] < 65 || password[i] > 90) && password[i] != 95 && password[i] != 45 && password[i] != 46 && (password[i] < 48 || password[i] > 57) && password[i] != 33 && (password[i] < 35 || password[i] > 38) && password[i] != 43 && password[i] != 42 && password[i] != 64 && password[i] != 58 && password[i] != 94)
			return 0;
	}
	for (int i = 0; i < strlen(password); i++)
		for (int k = i + 1; k < strlen(password); k++)
			if (((password[i] >= 97 && password[i] <= 122) && (password[k] >= 65 && password[k] <= 90)) || ((password[k] >= 97 && password[k] <= 122) && (password[i] >= 65 && password[i] <= 90)))
				return 1;
	return 0;
}