#include "User.h"
#include "Validation.h"
#include "Constants.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

void User::regIn(vector<User>& us)	//Регистрация
{
	system("cls");
	char bufPassword[31] = {};
	char* bufLogin = new char[21];
	int i = 0;
	cout << "Введите логин.\n\tПравила ввода логина:\n\t1) от 5 до 20 символов\n\t2) допустимы:\n\t\tлатинские буквы\n\t\tцифры\n\t\tсимволы (-_.)\nВвод: ";
	while (true)
	{
		inputString(bufLogin, 21);	//Проверка на длину
		if (loginCheck(bufLogin))	//Проверка на остальные правила логина
			break;
		else
			cout << "Повторите попытку: ";
	}
	for (int i = 0; i < us.size(); i++)
	{
		if (strcmp(bufLogin, us[i].login) == 0)	//Проверка на существование логина
		{
			cout << "\nУказанный логин уже существует.";
			return;
		}
	}
	cout << "Введите пароль.\n\tПравила ввода пароля:\n\t1) от 8 до 30 символов\n\t2) допустимы:\n\t\tлатинские буквы\n\t\tцифры\n\t\tсимволы (!@#$%^&*_-+:.)\n\t3) обязательно должны быть буквы верхнего и нижнего регистра\nВвод: ";
	while (true)
	{
		do {	//Вывод * вместо пароля, стирание * при желании
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
		if (passwordCheck(bufPassword))	//Проверка пароля
			break;
		else
		{
			i = 0;
			char bufPassword[31]{};
			cout << "\nВведен некорретный пароль.\nВвод: ";
		}
	}

	User temp = {};
	cout << "\nВведите номер телефона: ";
	setPhone(temp);
	for (int i = 0; i < 20; i++)
		temp.login[i] = bufLogin[i];
	for (int i = 0; i < 30; i++)
		temp.password[i] = bufPassword[i];
	makeSalt(temp);	//Создание соли и пароля
	temp.access = 0;	//Установка доступа
	temp.role = 0;	//Установка роли
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
				cout << "\n\nПовторите попытку.\n";
				cout << "Ввод: ";
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
	cout << "Введите логин.\n\tПравила ввода логина:\n\t1) от 5 до 20 символов\n\t2) допустимы:\n\t\tлатинские буквы\n\t\tцифры\n\t\tсимволы (-_.)\nВвод: ";
	while (true)
	{
		temp = 0;
		inputString(bufLogin, 21);
		for (int i = 0; i < us.size(); i++)
		{
			if (strcmp(bufLogin, us[i].getLogin()) == 0)	//Проверка на существование логина
			{
				cout << "\nУказанный логин уже существует.";
				temp = 1;
			}
		}
		if (loginCheck(bufLogin) && temp == 0)
			break;
		else
			cout << "Повторите попытку: ";
	}
	for (int i = 0; i < 20; i++)
		user.login[i] = bufLogin[i];
	cout << "\nЛогин успешно изменен.\n";
	delete[]bufLogin;
}

void User::setPassword(User& user) {
	char bufPassword[31] = {};
	int i = 0;
	cout << "Введите пароль.\n\tПравила ввода пароля:\n\t1) от 8 до 30 символов\n\t2) допустимы:\n\t\tлатинские буквы\n\t\tцифры\n\tсимволы (!@#$%^&*_-+:.)\n\t3) обязательно должны быть буквы верхнего и нижнего регистра\nВвод: ";
	while (true)
	{
		do {	//Вывод * вместо пароля, стирание * при желании
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
			cout << "\nВведен некорретный пароль.\nВвод: ";
		}
	}
	for (int i = 0; i < 30; i++)
		user.password[i] = bufPassword[i];
}

void User::makeSalt(User &temp)	//Создание соли и преобразование пароля 
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

void User::makePassword(User& temp)	//Преобразование пароля обратно
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

void User::passwordClear(User& temp)	//Преобразование пароля обратно
{
	for (int i = 0; i < strlen(temp.password); i++)
		temp.password[i] = ' ';
}

void User::showUser(vector<User> us, int userNum)	//Показ пользователя
{
	cout << "—---------------------------------------------------------------------------------------------\n";
	cout << "|№|       Логин         |             Пароль             |  Роль  |  Доступ  | Номер телефона |\n";
	cout << "—---------------------------------------------------------------------------------------------\n";
	cout << "|1|" << setw(20) << us[userNum].login << " |" << setw(31) << us[userNum].password << " |" << setw(7) << us[userNum].role << " |" << setw(9) << us[userNum].access << " |" << setw(15) << us[userNum].phoneNumber << " |";
	cout << "\n—--------------------------------------------------------------------------------------------\n";
}

void User::showUsers(vector<User> us)	//Показ всех пользователей
{
	int k = 0;
	cout << "—---------------------------------------------------------------------------------------------\n";
	cout << "|№|       Логин         |             Пароль             |  Роль  |  Доступ  | Номер телефона |\n";
	cout << "—---------------------------------------------------------------------------------------------\n";
	while (k < us.size()) {
		cout << "|" << k + 1 << "|" << setw(20) << us[k].login;
		if (us[k].role == 2)	//Проверка на главного администратора
			cout << " |" << setw(31) << "********************";
		else
			cout << " |" << setw(31) << us[k].password;
		cout << " |" << setw(7) << us[k].role << " |" << setw(9) << us[k].access << " |" << setw(15) << us[k].phoneNumber << " |";
		cout << "\n----------------------------------------------------------------------------------------------\n";
		k++;
	}
}

void User::addUser(vector<User> &us)	//Добавление пользователей
{
	regIn(us);
	cout << "\nВведите тип пользователя (0 - пользователь, 1 - администратор): ";
	int temp = inputNumber(0, 1, 0);	//Выбор типа пользователя
	us[us.size() - 1].role = temp;
	us[us.size() - 1].access = true;	//Установка доступа true

	cout << "\nПользователь успешно добавлен.";
	cout << "\nНажмите любую клавишу для продолжения...\n";
	_getch();
}

void User::changeUserInfo(vector<User>& us)	//Редактирование информации о пользователе
{
	cout << "\nВведите номер пользователя: \n";
	int numberOfUser, i = 0;
	numberOfUser = inputNumber(1, us.size(), 0);
	if (us[numberOfUser - 1].role == 2)	//Проверка на главного администратора
	{
		cout << "Вы не можете изменить информацию о главном администраторе.\n";
		return;
	}
	int n;
	cout << "\n1) Изменить логин\n2) Изменить пароль\n3) Изменить номер телефона\n4) Подтвердить (Заблокировать) аккаунт\n0) Отмена\nВвод: ";
	n = inputNumber(0, 4, 0);
	switch (n) {
	case 1: // Ввод нового логина
	{
		setLogin(us, us[numberOfUser - 1]);
		break;
	}
	case 2:	//Ввод нового пароля
	{
		setPassword(us[numberOfUser - 1]);
		User::makeSalt(us[numberOfUser - 1]);
		cout << "\nПароль успешно изменен.\n";
		break;
	}
	case 3: 
		cout << "Введите новый номер: ";
		setPhone(us[numberOfUser - 1]);
		cout << "\nНомер успешно изменен.\n";
		break;
	case 4:	//Изменение доступа
		if (us[numberOfUser - 1].access == true)	//Проверка на наличие доступа
		{
			us[numberOfUser - 1].access = false;
			cout << "\nДоступ успешно закрыт.\n";
		}
		else
		{
			us[numberOfUser - 1].access = true;
			cout << "\nДоступ успешно открыт.\n";
		}
		break;
	case 0:
		return;
	}
}

void User::deleteUser(vector<User>& us)	//Удаление пользователя
{
	int numberOfUser;
	cout << "Введите номер пользователя: \n";
	numberOfUser = inputNumber(1, 100, 0);
	if (numberOfUser > us.size())	//Проверка на существование пользователя
	{
		cout << "Пользователя с таким номером не существует.\n";
		return;
	}
	numberOfUser--;

	if (us[numberOfUser].role == 2)	//Проверка на главного администратора
	{
		cout << "Вы не можете удалить главного администратора.\n";
		return;
	}
	system("cls");
	showUser(us, numberOfUser);
	cout << "Вы действительно хотите удалить этого пользователя? (да - 1, нет - 0)\n\nВвод: ";
	bool agree;
	agree = inputNumber(0, 1, 0);
	if (agree == 0)	//Подтверждение удаления
		return;
	us.erase(us.begin() + numberOfUser);
	cout << "Пользователь успешно удалён.\n";
}