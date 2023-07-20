#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

using namespace std;
#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных

class NetWorkStream{
    private:
        int connection;
        char message[MESSAGE_LENGTH];
    public: 
        NetWorkStream(int connection);
    friend NetWorkStream& operator<< (NetWorkStream& os, const string& s);   
    friend NetWorkStream& operator>> (NetWorkStream& is, string& s); 
};