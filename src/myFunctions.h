#pragma once
#include <iostream>
#include "User.h"

//запуск проекта(start of the project)
void startMessengerChat() {
	while (true)
	{
		////переменная для работы с чатом (variable for working with chat)
		//std::unique_ptr<myChat> user1 = std::make_unique<myChat>();
		//user1->userRegistration("masha", "234e", "Masha");
		//user1->enterChat();
		////список всех пользователей(list of all users)
		//user1->getPersons();
		////развилка либо ввод сообщения, либо просмотр входящих
		//	//fork either enter a message or view inbox
		//user1->MenuChoice();
		User sasha("sasha", "123", "Sasha");

		bool exit = true;
		while (exit)
		{
			std::cout << "Хотите продолжить работу с мессенджером?" << std::endl;
			std::cout << "Если да то нажмите - y, если нет то - n" << std::endl;
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
				std::cout << "Введен не верный символ! Значит продолжаем работу:)" << std::endl;
				//break;
			}
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		return;
	}
}