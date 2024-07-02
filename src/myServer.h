#pragma once

#if defined (__linux__)

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

#elif defined(_WIN64)

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

void myServer() {
    //Key constants
    // Enter local Server IP address
    const char IP_SERV[] = "127.0.0.1";
    // Enter Open working server port
    const int PORT_NUM = 7777;
    // Maximum size of buffer for exchange info between server and client
    const short BUFF_SIZE = 1024;

    // Key variables for all program // Keeps socket errors status
    // Ключевые переменные для всех программ // Сохраняет статус ошибок сокета
    int erStat;

    //IP in string format to numeric format for socket functions. Data is in "ip_to_num"
    //IP в строковом формате в числовой формат для функций сокета. Данные в "ip_to_num"
    in_addr ip_to_num;
    erStat = inet_pton(AF_INET, IP_SERV, &ip_to_num);

    if (erStat <= 0) {
        std::cout << "Error in IP translation to special numeric format" << std::endl;
        return;
    }

    // WinSock initialization
    //Структура WSADATA содержит информацию о реализации Windows Sockets.
    WSADATA wsData;
    erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

    if (erStat != 0) {
        std::cout << "Error WinSock version initializaion #";
        std::cout << WSAGetLastError();
        return;
    }
    else
        std::cout << "WinSock initialization is OK" << std::endl;

    // Server socket initialization
    SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);

    if (ServSock == INVALID_SOCKET) {
        std::cout << "Error initialization socket # " << WSAGetLastError() << std::endl;
        closesocket(ServSock);
        WSACleanup();
        return;
    }
    else
        std::cout << "Server socket initialization is OK" << std::endl;

    // Server socket binding
    sockaddr_in servInfo;
    // Initializing servInfo structure
    ZeroMemory(&servInfo, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(PORT_NUM);

    erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));

    if (erStat != 0) {
        std::cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << std::endl;
        closesocket(ServSock);
        WSACleanup();
        return;
    }
    else
        std::cout << "Binding socket to Server info is OK" << std::endl;

    //Starting to listen to any Clients
    erStat = listen(ServSock, SOMAXCONN);

    if (erStat != 0) {
        std::cout << "Can't start to listen to. Error # " << WSAGetLastError() << std::endl;
        closesocket(ServSock);
        WSACleanup();
        return;
    }
    else {
        std::cout << "Listening..." << std::endl;
    }

    //Client socket creation and acception in case of connection
    sockaddr_in clientInfo;
    ZeroMemory(&clientInfo, sizeof(clientInfo));	// Initializing clientInfo structure

    int clientInfo_size = sizeof(clientInfo);

    SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);

    if (ClientConn == INVALID_SOCKET) {
        std::cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << std::endl;
        closesocket(ServSock);
        closesocket(ClientConn);
        WSACleanup();
        return;
    }
    else {
        std::cout << "Connection to a client established successfully" << std::endl;
        char clientIP[22];
        // Convert connected client's IP to standard string format
        inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);
        std::cout << "Client connected with IP address " << clientIP << std::endl;
    }
    //Exchange text data between Server and Client. Disconnection if a client send "end"
    // Creation of buffers for sending and receiving data
    std::vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    // The size of sending / receiving packet in bytes
    short packet_size = 0;

    while (true) {
        // Receiving packet from client. Program is waiting (system pause) until receive
        std::cout << "Client's message: " << servBuff.data() << std::endl;
        packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);

        std::cout << "Your (host) message: ";
        fgets(clientBuff.data(), clientBuff.size(), stdin);

        // Check whether server would like to stop chatting 
        if (clientBuff[0] == 'e' && clientBuff[1] == 'n' && clientBuff[2] == 'd') {
            shutdown(ClientConn, SD_BOTH);
            closesocket(ServSock);
            closesocket(ClientConn);
            WSACleanup();
            return;
        }

        packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            std::cout << "Can't send message to Client. Error # " << WSAGetLastError() << std::endl;
            closesocket(ServSock);
            closesocket(ClientConn);
            WSACleanup();
            return;
        }
    }
    closesocket(ServSock);
    closesocket(ClientConn);
    WSACleanup();
}

#endif