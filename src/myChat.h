#pragma once
#include "User.h"
#include <vector>
#include <iostream>

class MyChat {
public:
	MyChat();
	//����������� ������������
	void userRegistration();
	//����������� ���� � ���(registration enter chat)
	void enterChat();
	//�������� �������
	bool sing_in_to();
	//������ �������������
	void getPersons();

private:
	User m_user;
	//�������� ������������� (user storage)
	std::vector<User> userData;

	//������� ������
	void cinClear() {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	}
	//���� ������
	std::string getLineOfText()
	{
		std::string str = "";
		std::cin >> str;
		return str;
	}
	//���� �����
	int getint() {
		while (true) {
			int num = 0;
			std::cin >> num;
			if (std::cin.fail()) {
				cinClear();
				std::cout << "����� �� ������ ������! ";
			}
			else
				return num;
		}
	}
};