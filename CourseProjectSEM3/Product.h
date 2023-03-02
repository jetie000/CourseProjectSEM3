#pragma once
#include "Date.h"
#include "User.h"

class Product: public Date{
	char name[31];
	int price;
	char city[16];
	bool access;
	int category;
	char sellerLogin[21];
public: 
	void setSellerLogin(User);
	void setCategory() { category = inputProdNumber(1, 8, 70) - 1; }
	void setPrice() { price = inputProdNumber(0, 9999999999, 36); }
	void setDate() { Date::setDate(); }
	char* getSellerLogin() { return sellerLogin; }
	static int inputProdNumber(int, int, int);
	static void addProduct(vector <Product>& pr, User us);
	static void showProduct(vector<Product>, int, int&, bool);	//����� 
	static void showProducts(vector<Product>);	//����� 
	static void showFullProducts(vector<Product>, vector<User>);	//����� 
	static void showStatProducts(vector<Product>, vector<int>);	//����� 
	static void chooseProduct(vector<Product>, vector<User>);
	static void changeProductInfo(vector<Product>& pr);	//�������������� ���������� 
	static void inputNameString(Product&, bool);
	static void inputCityString(Product&, bool);
	static void deleteProduct(vector<Product>&);	//�������� 
	static void stringSorting(vector<Product>&, int n, int);
	static void numberSorting(vector<Product>&, int n);
	static void sortProducts(vector<Product>&);
	static void searchProducts(vector<Product>);	//�����
	Product operator =(Product obj);
};

