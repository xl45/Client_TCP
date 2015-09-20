# This file tells you how to run this tcp web client

1. compile 
put "make" in terminal

2. run
put "./tcp_client <server_host> <server_port> <conn_type> filelist.txt" in terminal

eg. > ./tcp_client 127.0.0.1 3480 p filelist.txt
(it's highly suggested to run the same port number and filelist name, otherwise you need to modify the code.)

# There are four scenario:
a. if "p" is setted to conn_type and filelist.txt only contains one file name, connection will close after that file be transfered
b. if "np" is setted to conn_type and filelist.txt contains multiple file name, then only the first file will be transfered and then connection will be cloed
c. if "p" is setted... filelist.txt contains multiple file name, then transfer all the files and then close connection
d. if "np" ... filelist.txt contains one file, no need to mention and you know what will happen.
