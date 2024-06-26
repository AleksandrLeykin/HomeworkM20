#include "myChat.h"
#include <fstream>

MyChat::MyChat()
{
	//окрытие файла дл€ чтени€
	std::ifstream in("persons.txt");
	if (in.is_open()) {
		//User newUser;
		while (in >> m_user.m_login >> m_user.m_password >> m_user.m_nickName)
			userData.push_back(m_user);
	}
	in.close();
}

void MyChat::userRegistration()
{
	std::cout << "¬ведите логин: ";
	m_user.m_login = getValue();
	cinClear();
	std::cout << "\n";
	std::cout << "¬ведите пароль: ";
	m_user.m_password = getValue();
	cinClear();
	std::cout << "\n";
	std::cout << "¬ведите им€: ";
	m_user.m_nickName = getValue();
	cinClear();
	std::cout << "\n";

	userData.push_back(m_user);
	
	//тестова€ запись d файл
	m_user.userRecording(m_user.m_login, m_user.m_password, m_user.m_nickName);	
}
