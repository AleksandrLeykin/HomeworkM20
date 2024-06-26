#include "myChat.h"
#include <fstream>
#include <string>

MyChat::MyChat()
{
	//окрытие файла для чтения
	std::ifstream in("persons.txt");
	if (in.is_open()) {
		//User newUser;
		while (in >> m_user.m_login>> m_user.m_password >> m_user.m_nickName)
			userData.push_back(m_user);
	}
	in.close();
}

void MyChat::userRegistration()
{
	std::cout << "Введите логин: ";
	m_user.m_login = getLineOfText();
	cinClear();
	std::cout << "\n";
	std::cout << "Введите пароль: ";
	m_user.m_password = getLineOfText();
	cinClear();
	std::cout << "\n";
	std::cout << "Введите имя: ";
	m_user.m_nickName = getLineOfText();
	cinClear();
	std::cout << "\n";

	for (int i = 0; i < userData.size(); i++)
	{
		if (userData[i].m_login == m_user.m_login) {
			std::cout << "Имя занято!!" << std::endl;
			return;
		}
	}
	userData.push_back(m_user);
	
	//тестовая запись в файл
	m_user.userRecording(m_user.m_login, m_user.m_password, m_user.m_nickName);	
}

void MyChat::enterChat()
{
	while (true)
	{
		std::cout << "Для входа нажмите - 1, для регистрации - 2, для выхода 3: ";
		int number = getint();
		switch (number)
		{
		case 1:
			if (sing_in_to() == false)
			{
				std::cout << "Не верный логин или пароль!!" << std::endl;
				break;
			}
			return;
		case 2:
			userRegistration();
			return;
		case 3:
			return;
		default:
			std::cout << "Введен не верный символ!!" << "\n";
			break;
		}
	}
}

bool MyChat::sing_in_to()
{
	std::cout << "Введите свое имя:" << std::endl;
	std::string buffer_login = "";
	buffer_login = getLineOfText();
	int coincidence = 0;
	for (int i = 0; i < userData.size(); ++i) {
		if (userData[i].m_login == buffer_login) {
			std::cout << "Введите пароль:" << std::endl;
			std::string buffer_password = getLineOfText();
			if (userData[i].m_password == buffer_password) {
				std::cout << userData[i].m_nickName << ", welcome у нас в чате!" << std::endl;
				++coincidence;
			}
			++coincidence;
		}
		else
			continue;
	}
	if (coincidence != 2)
		return false;
	return true;
}

void MyChat::getPersons()
{
	std::cout << "Зарегестрированных пользователей: " << userData.size() << std::endl;
	for (int i = 0; i < userData.size(); ++i)
	{
		std::cout << (i + 1) << ")." << userData[i].m_nickName << " ";
	}
	std::cout << std::endl;
}
