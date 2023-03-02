#pragma once
#include <vector>
using std::vector;

class User {	//����� ������������
	char login[21];
	char password[31];
	int role;
	bool access;
	char salt[21];
	char salted_hash_password[91];
	char phoneNumber[15];
public:
	void setAdmin() {
		char temp[] = "Admin12345", temp2[] = "GGJkhlnrukirwsn42:6489<:8<5:=7", temp3[] = "ggjheibficajjfadbjec", temp4[] = "+375296543705";
		for (int i = 0; i < 11; i++)
			login[i] = temp[i];
		role = 2;
		access = 1;
		for (int i = 0; i < 31; i++)
			salted_hash_password[i] = temp2[i];
		for (int i = 0; i < 21; i++)
			salt[i] = temp3[i];
		for (int i = 0; i < 31; i++)
			password[i] = ' ';
		for (int i = 0; i < 14; i++)
			phoneNumber[i] = temp4[i];
	}
	static void setPhone(User&);
	static void setLogin(vector<User>, User&);
	static void setPassword(User&);
	inline char* getPhoneNumber() { return phoneNumber; }
	inline char* getLogin() { return login; }
	inline char* getPassword() { return password; }
	inline int getRole() { return role; }
	inline bool getAccess() { return access; }
	static void regIn(vector<User>&);	//�����������
	static void makeSalt(User&);	//�������� ���� � �������������� ������ 
	static void makePassword(User&);	//�������������� ������ �������
	static void passwordClear(User& temp);
	static void showUser(vector<User>, int); //����� ������������
	static void showUsers(vector<User>);	//����� ���� �������������
	static void addUser(vector<User>&);	//���������� �������������
	static void changeUserInfo(vector<User>&);	//�������������� ���������� � ������������
	static void deleteUser(vector<User>&);	//�������� ������������
};
