#include <iostream>
#include "WebClient.h"

int main(int argc, char* argv[]){
    // take command line arguments
    if( argc !=  5 ){
        std::cout << "oops, wrong parameter format, refer README.txt for detail.\n";
        return 1;
    }
    std::string server_host = argv[1];
    std::string server_port = argv[2];
    std::string conn_type = argv[3];
    std::string filelist = argv[4];

    // initialize a web client and start to work
    WebClient myWebClient(server_host, server_port, conn_type, filelist);
    myWebClient.client_send_recv();
}
