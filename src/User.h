#pragma once
#include <string>
//#include <vector>

class User {
public:	
	User() {};
	User(const std::string& login, const std::string& pass, const std::string& nick);
	~User() = default;
	
	std::string m_login;
	std::string m_password;
	std::string m_nickName;

	void userRecording(const std::string& login, const std::string& pass, const std::string& nick);
private:
	std::string getValue();	
};