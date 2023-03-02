#pragma once
#include "Product.h"
#include "User.h"
using std::vector;

void mainMenu(); // Главное меню, чтение и запись в файл
void installations(); // Установки
namespace admin {
	void adminMenu(vector<User>& us, vector<Product>& pr, User); // Меню админа
	void adminUserMenu(vector<User>&); // Меню админа 1
	void adminProdMenu(vector <Product>&, vector<User>&, User); // Меню админа 2
}
void logIn(vector<User>&, vector<Product>&);	//Вход
namespace user {
	void userProdMenu(vector<Product>&, vector<User>&, User&);	//Меню пользователя
	void userCabinetMenu(vector<User>&, vector<Product>&, User&);	// Личный кабинет
	void userInfoMenu(vector<User>&, User&); // Меню пользователя для смены данных
}