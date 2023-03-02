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
	SetConsoleCP(1251);	//Русская кодировка
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
	vector <Product> pr;	//Массив студентов
	vector <User> us;	//Массив пользователей
	int studNum = 0, userNum = 0;
	int i1 = 0, i2 = 0;
	try
	{
		fUsers.open(PATH_USERS);
		if (!fUsers.is_open())
			throw exception("Файл пользователей не найден.");
	}
	catch (exception& x) {
		cout << x.what() << endl;
		return;
	}
	if (fUsers.peek() == EOF)	//Добавление главного администратора, если файл с пользователями не существует
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
		cout << "Файл товаров не найден.";
		return;
	}
	fileRead(fProducts, pr);
	fProducts.close();
	fileRead(fUsers, us);
	fUsers.close();
	for (int i = 0; i < us.size(); i++)
		User::makePassword(us[i]);
	int n;
	while (true)	//Главное меню
	{
		system("cls");
		cout << "Главное меню:\n1) Войти\n2) Зарегистрироваться\n0) Выход из программы\n\nВвод: ";
		n = inputNumber(0, 2, 0);
		switch (n)
		{
		case 1:
			logIn(us, pr);	//Вход
			break;
		case 2:
		{
			int temp = userNum;
			User::regIn(us);	//Регистрация
			if (temp != userNum)
				cout << "\n\nРегистрация прошла успешно.\nЖдите подтверждения аккаунта администраторами.\n";
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		}
		case 0:	//Выход
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

void admin::adminMenu(vector<User>& us, vector<Product>& pr, User user)	//Главное меню администратора
{
	int n;
	while (true)
	{
		system("cls");
		cout << "1) Меню работы с товарами\n2) Меню работы с пользователями\n0) Выйти в главное меню\n\nВвод: ";
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

void logIn(vector<User>& us, vector<Product>& pr)	//Вход
{
	system("cls");
	char bufPassword[31] = {};
	char* bufLogin = new char[21];
	int i = 0;
	cout << "Введите логин: ";
	inputString(bufLogin, 20);	//Ввод логина
	cout << "Введите пароль: ";
	do {
		bufPassword[i] = _getch();	//Ввод пароля
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
	for (int i = 0; i < us.size(); i++)	//Проверка на наличие аккаунтов с таким логином и паролем
	{
		if (strcmp(bufLogin, us[i].getLogin()) == 0 && strcmp(bufPassword, us[i].getPassword()) == 0)
		{
			if (us[i].getAccess() == 1)	//Проверка на доступ
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
				cout << "\nУ данного аккаунта нет доступа.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				return;
			}
		}
	}
	delete[]bufLogin;
	cout << "\nВведен неверный логин или пароль.\nПовторите попытку.\n";
	cout << "\nНажмите любую клавишу для продолжения...\n";
	_getch();
	return;
}

void admin::adminUserMenu(vector<User>& us)	//Меню администратора для работы с пользователями
{
	int n;
	while (true) {
		system("cls");
		cout << "Меню администратора (работа с пользователями):\n1) Просмотреть пользователей\n2) Добавить пользователя\n3) Изменить данные пользователя\n4) Удалить пользователя\n0) Выйти в главное меню администратора\n\nВвод: ";
		n = inputNumber(0, 4, 0);
		switch (n)
		{
		case 1:
			User::showUsers(us);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 2:
			User::addUser(us);
			break;
		case 3:
			system("cls");
			User::showUsers(us);
			User::changeUserInfo(us);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 4:
			system("cls");
			User::showUsers(us);
			User::deleteUser(us);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 0:
			return;
		}
	}
}

void admin::adminProdMenu(vector <Product>& pr, vector<User>& us, User user)	//Меню администратора для работы с продуктами
{
	int n;
	fstream fResults;
	while (true) {
		system("cls");
		cout << "Меню администратора (работа с товарами):\n1) Просмотреть товары\n2) Добавить товар\n3) Изменить данные о товаре\n4) Удалить товар\n5) Сортировать товары\n6) Поиск товара\n7) Просмотреть статистику по проданным товарам\n0) Выйти в главное меню администратора\n\nВвод: ";
		n = inputNumber(0, 7, 0);
		switch (n) {
		case 1:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::showFullProducts(pr, us);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 2:
			Product::addProduct(pr, user);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 3:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			system("cls");
			Product::showFullProducts(pr, us);
			Product::changeProductInfo(pr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 4:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::showFullProducts(pr, us);
			Product::deleteProduct(pr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 5:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::sortProducts(pr);
			Product::showFullProducts(pr, us);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 6:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::searchProducts(pr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 7:
			fResults.open("results.txt", ios::in);
			if (fResults.peek() == EOF)
			{
				cout << "\nНи одного товара не продано.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			if (!fResults.is_open())
				cout << "Файл с отчетами не найден.";
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
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 0:
			return;
		}
	}
}

void user::userProdMenu(vector<Product>& pr, vector<User>& us, User& user)	//Меню пользователя
{
	vector<Product> userPr;
	int n;
	while (true) {
		system("cls");
		cout << "Меню пользователя:\n1) Просмотреть товары для покупки\n2) Сортировать товары\n3) Поиск товара\n4) Личный кабинет\n0) Выйти в главное меню\n\nВвод: ";
		n = inputNumber(0, 4, 0);
		switch (n) {
		case 1:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::showProducts(pr);
			Product::chooseProduct(pr, us);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 2:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::sortProducts(pr);
			Product::showProducts(pr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 3:
			if (pr.size() == 0)
			{
				cout << "\nНи одного товара не добавлено.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::searchProducts(pr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
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
		cout << "Личный кабинет:\n1) Добавить товар\n2) Изменить данные о товаре\n3) Удалить товар\n4) Изменить данные аккаунта\n0) Выйти в главное меню пользователя\n\nВвод: ";
		n = inputNumber(0, 4, 0);
		switch (n) {
		case 1:
			Product::addProduct(userPr, user);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 2:
			if (userPr.size() == 0)
			{
				cout << "\nВы не добавили ни одного товара.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::showProducts(userPr);
			Product::changeProductInfo(userPr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 3:
			if (userPr.size() == 0)
			{
				cout << "\nВы не добавили ни одного товара.\n";
				cout << "\nНажмите любую клавишу для продолжения...\n";
				_getch();
				break;
			}
			Product::showProducts(userPr);
			Product::deleteProduct(userPr);
			cout << "\nНажмите любую клавишу для продолжения...\n";
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
		cout << "Редактирование профиля:\n1) Изменить логин\n2) Изменить пароль\n3) Изменить номер телефона\n0) Выйти в главное меню пользователя\n\nВвод: ";
		n = inputNumber(0, 3, 0);
		switch (n) {
		case 1:
			User::setLogin(us, user);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 2:
			User::setPassword(user);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 3:
			cout << "\nНовый номер телефона: ";
			User::setPhone(user);
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
			break;
		case 0:
			return;
		}
	}
}
