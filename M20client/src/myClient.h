#pragma once
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


void myClient() {
    //key constants
    const char IP_SERV1[] = "127.0.0.1";
    const int PORT_NUM1 = 7777;
    const short BUFF_SIZE1 = 1024;

    int socket_file_descriptor1, connection1;
    struct sockaddr_in serveraddress1, client1;
    char message1[BUFF_SIZE1];
    
    // Создадим сокет
      socket_file_descriptor1 = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor1 == -1) {
        std::cout << "creation of Socket failed!" << std::endl;
        return;
    }
       // Установим адрес сервера
    serveraddress1.sin_addr.s_addr = inet_addr(IP_SERV1);
    // Зададим номер порта
    serveraddress1.sin_port = htons(PORT_NUM1);
    // Используем IPv4
    serveraddress1.sin_family  = AF_INET;
    // Установим соединение с сервером
    connection1 = connect(socket_file_descriptor1, (sockaddr*)& serveraddress1, sizeof(serveraddress1));
    if(connection1 == -1) {
        std::cout << "Connection with the server failed!" << std::endl;
        return;
    }
     // Взаимодействие с сервером
    while (1)
    {
        //обнуляем хранилище сообщений
        bzero(message1, sizeof(message1));
        std::cout << "Enter the message you want to send to the server: " << std::endl;
        std::cin >> message1;
        //strncmp - сравните N символов S1 и S2.
        if(strncmp(message1, "end", 3) == 0) {
            //write - Записать N байт BUF в FD. Возврат записанного числа или -1.
            write(socket_file_descriptor1, message1, sizeof(message1));
            std::cout << "Client Exit!" << std::endl;
            break;
        }
        ssize_t bytes = write(socket_file_descriptor1, message1, sizeof(message1));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if(bytes >= 0) {
            std::cout << "Data send to the server successfully!" << std::endl;
        }
        //обнуляем хранилище сообщений
        bzero(message1, sizeof(message1));
        // Ждем ответа от сервера
        read(socket_file_descriptor1, message1, sizeof(message1));
        std::cout << "Data received from server: " << message1 << std::endl;
    }
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor1);    
}