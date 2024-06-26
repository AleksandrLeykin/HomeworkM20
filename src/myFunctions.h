#pragma once
#include <iostream>
#include "myChat.h"

//������ �������(start of the project)
void startMessengerChat() {
	while (true)
	{
		//���������� ��� ������ � ����� (variable for working with chat)
		std::unique_ptr<MyChat> user1 = std::make_unique<MyChat>();		
		user1->enterChat();
		//������ ���� �������������(list of all users)
		user1->getPersons();
		////�������� ���� ���� ���������, ���� �������� ��������
		//	//fork either enter a message or view inbox
		//user1->MenuChoice();	
		
			std::cout << "������ ���������� ������ � ������������?" << std::endl;
			std::cout << "���� �� �� ������� - y, ���� ��� �� - n" << std::endl;
			char enterExit;
			std::cin >> enterExit;
			switch (enterExit)
			{
			case 'n':				
				return;
			case 'y':
				break;
			default:
				std::cout << "������ �� ������ ������! ������ ���������� ������:)" << std::endl;
				//break;
			}
			std::cin.clear();
			std::cin.ignore(32767, '\n');		
	}
}