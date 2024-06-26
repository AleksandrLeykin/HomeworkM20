#include <iostream>
#include "myFunctions.h"


int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "Chat for sending messages!\nЧат для передачи сообщений" << std::endl;
	startMessengerChat();

	return 0;
}