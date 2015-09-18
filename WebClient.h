#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILE_NUM 10
typedef unsigned char BYTE;

class WebClient
{
    public:
        WebClient(std::string serv_host, std::string serv_port, std::string conn_type, std::string filename);
        void client_send_recv();
        virtual ~WebClient();

    private:
        std::string filelist[MAX_FILE_NUM];
        int filelist_size;
        struct addrinfo hints;
        struct addrinfo *servinfo;
        int clientFD;
        bool persistent;
        std::string serv_host;
        std::string serv_port;
        std::string conn_type;
        std::string filename;

        std::string generateReq( int index );
};

#endif // WEBCLIENT_H
