#include "NetWorkStream.h"

NetWorkStream::NetWorkStream(int connection){
    this->connection = connection;
}

NetWorkStream& operator<< (NetWorkStream& os, const string& s){
    bzero(os.message, MESSAGE_LENGTH);
    //check size
    strcpy(os.message, s.c_str());
    ssize_t bytes = write(os.connection, os.message, sizeof(os.message));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0)  {
        //cout << "Data successfully sent to the client.!" << endl;
    }
    return os;
}

NetWorkStream& operator>> (NetWorkStream& is, string& s){
	bzero(is.message, MESSAGE_LENGTH);
    strcpy(is.message, "CDATA-CIN>>");
    ssize_t bytes = write(is.connection, is.message, sizeof(is.message));
    bzero(is.message, MESSAGE_LENGTH);
    read(is.connection, is.message, sizeof(is.message));
    /* if (strncmp("end", message, 3) == 0) {
        cout << "Client Exited." << endl;
        cout << "Server is Exiting..!" << endl;
        break;
    } */
    //cout << "Data received from client: " <<  message << endl;
    s = string(is.message);
    return is;
}