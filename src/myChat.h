#pragma once
#include "User.h"
#include <vector>
#include <iostream>

class MyChat {
public:
	MyChat();

	//регистрация пользователя
	void userRegistration();

private:
	User m_user;
	//хранение пользователей (user storage)
	std::vector<User> userData;

	//очистка буфера
	void cinClear() {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	}

	std::string getValue()
	{
		std::string str = "";
		std::cin >> str;
		return str;
	}
};