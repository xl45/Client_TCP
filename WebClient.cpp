#include "WebClient.h"

WebClient::WebClient(std::string serv_host, std::string serv_port, std::string conn_type, std::string filename)
{
    this->conn_type = conn_type;
    this->filename = filename;
    this->serv_port = serv_port;
    this->serv_host = serv_host;
    filelist_size = 0;

    if(conn_type == "p")
    {
        persistent = true;
    }
    else
    {
        persistent = false;
    }
    // read the file name list
    std::ifstream ifs(filename.c_str());
    if( ifs.is_open() )
    {
        int i = 0;

        while( ifs.good() )
        {
            char temp[50];
            ifs.getline(temp, 50);
            if( std::string(temp).length() == 0 ) {
                break;
            }
            filelist[i] = std::string(temp);
            // std::cout << "getline: " << filelist[i] << std::endl;

            i++;
            filelist_size++;
        }
        ifs.close();
    }
    else
    {
        perror("open file");
        exit(1);
    }
    // set network struct
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    // set server info struct
    if( getaddrinfo(serv_host.c_str(), serv_port.c_str(), &hints, &servinfo) != 0 )
    {
        perror("client: getaddrinfo");
        exit(1);
    }
    // get fd
    if( (clientFD = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        perror("client: socket()");
        exit(1);
    }
    // connect
    if( (connect(clientFD, servinfo->ai_addr, servinfo->ai_addrlen)) == -1 )
    {
        perror("client: connect()");
        exit(1);
    }
}


void WebClient::client_send_recv(){
    int i = 0;

    do {
        // generate HTTP GET request
        std::string request = generateReq(i);
        BYTE recv_msg[1024];

        if( (send(clientFD, request.c_str(), request.size(), 0)) == -1 ){
            perror("client send()");
            exit(1);
        }

        if( (recv(clientFD, recv_msg, 1024, 0)) == -1 ){
            perror("client recv()");
            exit(1);
        }

        std::cout << "****client receive msg: \n" << recv_msg << std::endl << std::endl;

        i++;
    }
    while( persistent && (i < filelist_size) );

    close(clientFD);
    exit(1);
}


std::string WebClient::generateReq(int index){
    std::string temp;
    if( index == filelist_size - 1 ){
        temp = "close";
    }
    else if( conn_type == "p" ){
        temp = "keep-alive";
    }
    else{
        temp = "close";
    }

    std::string pagename = filelist[index];
    std::string temp1 = this->serv_host;

    std::string substr1 = "GET /";
    std::string substr2 = pagename;
    std::string substr3 = " HTTP/1.1\nHost: ";
    std::string substr4 = temp1.append(":").append(serv_port).append("\n");
    std::string substr5 = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate\nConnection: ";
    std::string substr6 = temp;
    std::string request = "";
    request.append(substr1).append(substr2).append(substr3).append(substr4).append(substr5).append(substr6);

    return request;
}


WebClient::~WebClient()
{
}
