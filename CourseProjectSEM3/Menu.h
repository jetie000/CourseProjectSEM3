#pragma once
#include "Product.h"
#include "User.h"
using std::vector;

void mainMenu(); // ������� ����, ������ � ������ � ����
void installations(); // ���������
namespace admin {
	void adminMenu(vector<User>& us, vector<Product>& pr, User); // ���� ������
	void adminUserMenu(vector<User>&); // ���� ������ 1
	void adminProdMenu(vector <Product>&, vector<User>&, User); // ���� ������ 2
}
void logIn(vector<User>&, vector<Product>&);	//����
namespace user {
	void userProdMenu(vector<Product>&, vector<User>&, User&);	//���� ������������
	void userCabinetMenu(vector<User>&, vector<Product>&, User&);	// ������ �������
	void userInfoMenu(vector<User>&, User&); // ���� ������������ ��� ����� ������
}