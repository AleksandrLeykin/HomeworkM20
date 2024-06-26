#pragma once
#include "User.h"
#include <vector>
#include <iostream>

class MyChat {
public:
	MyChat();
	//регистрация пользователя
	void userRegistration();
	//регистрация вход в чат(registration enter chat)
	void enterChat();
	//проверка персоны
	bool sing_in_to();
	//список пользователей
	void getPersons();

private:
	User m_user;
	//хранение пользователей (user storage)
	std::vector<User> userData;

	//очистка буфера
	void cinClear() {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	}
	//ввод строки
	std::string getLineOfText()
	{
		std::string str = "";
		std::cin >> str;
		return str;
	}
	//ввод числа
	int getint() {
		while (true) {
			int num = 0;
			std::cin >> num;
			if (std::cin.fail()) {
				cinClear();
				std::cout << "Веден не верный символ! ";
			}
			else
				return num;
		}
	}
};