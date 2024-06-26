#include "User.h"
#include <iostream>
#include <fstream>


User::User(const std::string& login, const std::string& pass, const std::string& nick) :
	m_login(login), m_password(pass), m_nickName(nick)
{	
	userRecording(login, pass, nick);
}

std::string User::getValue()
{
	std::string str = "";
	std::cin >> str;
	return str;
}

void User::userRecording(const std::string& login, const std::string& pass, const std::string& nick)
{
	// ����� ��� ������(stream to write)
	std::ofstream out;
	//�������� ������ � ����� (adding text to a file)
	out.open("persons.txt", std::ios::app);
	if (out.is_open())
		out << login << " " << pass << " " << nick << std::endl;
	out.close();
}
