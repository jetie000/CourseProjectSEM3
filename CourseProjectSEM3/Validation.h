#pragma once

void inputString(char*, int);	//Проверка строки на длину
int inputNumber(int, int, int);	//Проверка целых чисел
double inputDouble(int, int); //Проверка дробных чисел
bool isNumberRangeCorrect(int, int, int);	//Проверка на то, находится ли число в заданных границах
bool isNumberNumeric();	//Проверка на то, является ли число числом
bool loginCheck(char[]);	//Проверка логина на разрешенные символы
bool passwordCheck(char password[]);	//Проверка пароля на размер и разрешенные символы