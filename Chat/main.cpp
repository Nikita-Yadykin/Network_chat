#include"ConsoleChat.h"
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
 
//#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
//char message[MESSAGE_LENGTH];

auto main() -> int
{
	// Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sockert_file_descriptor == -1){
        cout << "Socket creation failed.!" << endl;
        exit(1);
    }
    // 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
    sizeof(serveraddress));
    if(bind_status == -1)  {
        cout << "Socket binding failed.!" << endl;
        exit(1);
    }
    // Поставим сервер на прием данных 
    connection_status = listen(sockert_file_descriptor, 5);
    if(connection_status == -1){
        cout << "Socket is unable to listen for new connections.!" << endl;
        exit(1);
    }  else  {
        cout << "Server is listening for new connection: " << endl;
    }

    bool flserverwork = true;
    while(flserverwork)
    {
        length = sizeof(client);
        connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
        if(connection == -1)  {
            cout << "Server is unable to accept the data from client.!" << endl;
            exit(1);
        }
        cout << "Connected new client..." << endl;

	    ConsoleChat ConsoleChat(connection);

	    ConsoleChat.start(); // Запуск чата

	    while (ConsoleChat.сhatStarted()) // Пока чат запущен
	    {
		    ConsoleChat.startMenu(); // Отображать стартовое меню
		    while (ConsoleChat.getOnlineUser()) // Пока в системе есть пользователь
		    {
		        ConsoleChat.chatMenu(); // Отображать меню чата
		    }
	    }
        cout << "Chat closed" << endl;
    }
    // закрываем сокет, завершаем соединение
    close(sockert_file_descriptor);

	return 0;

}