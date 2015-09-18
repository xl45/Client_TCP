#include <iostream>
#include "WebClient.h"

int main(){
    // take command line arguments
    WebClient myWebClient("127.0.0.1", "3480", "p", "filelist.txt");
    myWebClient.client_send_recv();
}
