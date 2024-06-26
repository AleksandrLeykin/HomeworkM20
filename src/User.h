#pragma once
#include <string>
//#include <vector>

class User {
	/*struct Persons {
		std::string m_login;
		std::string m_password;
		std::string m_nickName;
		std::vector<std::string> m_mail;

		Persons() :
			m_login(""),
			m_password(""),
			m_nickName("")
		{}
		~Persons() = default;
	};*/

public:
	//создание пользователя
	User() {};
	User(const std::string& login, const std::string& pass, const std::string& nick);
	~User() = default;
	//std::string getLogin() { return m_login; }
	//std::string getPass() { return m_password; }
	//std::string getNick() { return m_nickName; }
	std::string m_login;
	std::string m_password;
	std::string m_nickName;

	void userRecording(const std::string& login, const std::string& pass, const std::string& nick);
private:
	//std::string m_login;
	//std::string m_password;
	//std::string m_nickName;

	std::string getValue();	

};