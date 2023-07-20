#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 
using namespace std;
 
#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта
 
int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char message[MESSAGE_LENGTH];
int main(){
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        cout << "Creation of Socket failed!" << endl;
        exit(1);
    }
 
    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1){
        cout << "Connection with the server failed.!" << endl;
        exit(1);
    }
    // Взаимодействие с сервером
    while(1){
        bzero(message, sizeof(message));
        // Ждем ответа от сервера
        read(socket_file_descriptor, message, sizeof(message));
        if(strncmp(message, "CDATA-CIN>>", 11)==0){
            bzero(message, sizeof(message));
            cin >> message;
            ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
            // Если передали >= 0  байт, значит пересылка прошла успешно
            if(bytes >= 0){
                //cout << "Data send to the server successfully.!" << endl;
            } 
        } 
        else if(strncmp(message, "CDATA:CMD:EXIT", 14)==0){
            break;
        }
        else {
            cout << message;// << endl;
        }
    }
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    return 0;
}