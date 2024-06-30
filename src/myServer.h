#pragma once
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> //для read()
#include <netinet/in.h> //для структуры sockaddr_in

void myServer() {
    //key constants
    const char IP_SERV[] = "127.0.0.1";
    const int PORT_NUM = 7777;
    const short BUFF_SIZE = 1024;
    //Структура, описывающая адрес интернет-сокета.
    sockaddr_in serveraddress, client;
    socklen_t length;
    int socket_file_descriptor, connection, bind_status, connection_status;
    char message[BUFF_SIZE];

    // Создадим сокет // Let's create a socket
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1) {
        std::cout << "Socet creation failed!" << std::endl;
        return;
    }
    //Адрес для приема входящих сообщений //Address for receiving incoming messages.
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    //номер порта для связи
    serveraddress.sin_port = htons(PORT_NUM);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(socket_file_descriptor, (sockaddr*)& serveraddress, sizeof(serveraddress));
    if(bind_status == -1) {
        std::cout << "Soket binding failed!" << std::endl;
        return;
    }
    // Поставим сервер на прием данных // Let's set the server to receive data
    connection_status = listen(socket_file_descriptor, 5);
    if(connection_status == -1) {
        std::cout << "Socket is unable to listen for new connections!" << std::endl;
        return;
    }
    else {
        std::cout << "Server is listening... " << std::endl;
    }

    length = sizeof(client);
    //accept - Ожидание соединения на сокете FD. Когда соединение прибывает,
    //открыть новый сокет для связи с ним,
    connection = accept(socket_file_descriptor, (sockaddr*)& client, &length);
    if(connection == -1) {
        std::cout << "Server is unable to accept the data from client!" << std::endl;
        return;
    }
    // Communication Establishment // Установление связи
    while (1) {
        //обнуление буфера
        bzero(message, BUFF_SIZE);
        //Прочитать NBYTES в BUF ​​из FD. Возврат прочитанного числа, -1 для ошибок или 0 для EOF
        read(connection, message, sizeof(message));
        if(strncmp("end", message, 3) == 0) {
            std::cout << "Client Exited." << std::endl;
            std::cout << "Server is Exiting..!" << std::endl;
            break;
        }
        std::cout << "Data received from client: " <<  message << std::endl;
        //обнуление буфера
        bzero(message, BUFF_SIZE);
        std::cout << "Enter the message you want to send to the client: " << std::endl;
        std::cin >> message;
        //Записать N байт BUF в FD. Возвратить записанное число или -1.
        ssize_t bytes = write(connection, message, sizeof(message));
         // Если передали >= 0  байт, значит пересылка прошла успешно
        if(bytes >= 0) {
            std::cout << "Data successfully sent to the client.!" << std::endl;
        }
    }
     // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
}