#pragma once

#if defined (__linux__)
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

#elif defined(_WIN64)

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
//#include <inaddr.h>
#include <stdio.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

void myClient() {
    //Key constants
    // Enter IPv4 address of Server
    const char SERVER_IP[] = "127.0.0.1";
    // Enter Listening port on Server side
    const short SERVER_PORT_NUM = 7777;
    // Maximum size of buffer for exchange info between server and client
    const short BUFF_SIZE = 1024;

    // Key variables for all program // Ключевые переменные для всей программы
    // For checking errors in sockets functions // Для проверки ошибок в функциях сокетов
    int erStat;

    //Translate IP from string to numeric format for socket function. Data in "ip_to_num"
    //Перевод IP из строкового формата в числовой для функции сокета. Данные в "ip_to_num"
    in_addr ip_to_num;
    inet_pton(AF_INET, SERVER_IP, &ip_to_num); 

    // WinSock initialization
    //структурa типа WSADATA, в которую автоматически в момент создания загружаются данные 
    // о версии сокетов, используемых ОС, а также иная связанная системная информация
    WSADATA wsData;
    erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

    if (erStat != 0) {
        std::cout << "Error WinSock version initializaion #";
        std::cout << WSAGetLastError();
        return;
    }
    else
        std::cout << "WinSock initialization is OK" << std::endl;

    // Socket initialization
    SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);

    if (ClientSock == INVALID_SOCKET) {
        std::cout << "Error initialization socket # " << WSAGetLastError() << std::endl;
        closesocket(ClientSock);
        WSACleanup();
    }
    else
        std::cout << "Client socket initialization is OK" << std::endl;

    // Establishing a connection to Server //Установление соединения с сервером
    sockaddr_in servInfo;

    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(SERVER_PORT_NUM);

    erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

    if (erStat != 0) {
        std::cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << std::endl;
        closesocket(ClientSock);
        WSACleanup();
        return;
    }
    else
        std::cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" 
                  << "Соединение установлено УСПЕШНО.Готово к отправке сообщения на сервер" << std::endl;

    //Exchange text data between Server and Client. Disconnection if a Client send "end"
    // Buffers for sending and receiving data // Буферы для отправки и получения данных
    std::vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    // The size of sending / receiving packet in bytes // Размер отправляемого/принимаемого пакета в байтах
    short packet_size = 0;

    while (true) {
        std::cout << "Your (Client) message to Server: ";
        fgets(clientBuff.data(), clientBuff.size(), stdin);

        // Check whether client like to stop chatting 
        if (clientBuff[0] == 'e' && clientBuff[1] == 'n' && clientBuff[2] == 'd') {
            shutdown(ClientSock, SD_BOTH);
            closesocket(ClientSock);
            WSACleanup();
            return;
        }

        packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);
        if (packet_size == SOCKET_ERROR) {
            std::cout << "Can't send message to Server. Error # " << WSAGetLastError() << std::endl;
            closesocket(ClientSock);
            WSACleanup();
            return;
        }

        packet_size = recv(ClientSock, servBuff.data(), servBuff.size(), 0);
        if (packet_size == SOCKET_ERROR) {
            std::cout << "Can't receive message from Server. Error # " << WSAGetLastError() << std::endl;
            closesocket(ClientSock);
            WSACleanup();
            return;
        }
        else
            std::cout << "Server message: " << servBuff.data() << std::endl;
    }
    closesocket(ClientSock);
    WSACleanup();
}

#endif