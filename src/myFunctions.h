#pragma once
#include <iostream>
#include "User.h"

//������ �������(start of the project)
void startMessengerChat() {
	while (true)
	{
		////���������� ��� ������ � ����� (variable for working with chat)
		//std::unique_ptr<myChat> user1 = std::make_unique<myChat>();
		//user1->userRegistration("masha", "234e", "Masha");
		//user1->enterChat();
		////������ ���� �������������(list of all users)
		//user1->getPersons();
		////�������� ���� ���� ���������, ���� �������� ��������
		//	//fork either enter a message or view inbox
		//user1->MenuChoice();
		User sasha("sasha", "123", "Sasha");

		bool exit = true;
		while (exit)
		{
			std::cout << "������ ���������� ������ � ������������?" << std::endl;
			std::cout << "���� �� �� ������� - y, ���� ��� �� - n" << std::endl;
			char enterExit;
			std::cin >> enterExit;
			switch (enterExit)
			{
			case 'n':
				exit = false;
				//return;
			case 'y':
				break;
			default:
				std::cout << "������ �� ������ ������! ������ ���������� ������:)" << std::endl;
				//break;
			}
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		return;
	}
}