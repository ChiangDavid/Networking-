#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
	//Declare the variables
    int socket_two, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
	//create socket for client server
    socket_two = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_two < 0) 
        printf("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
	//copy the network address part of the structure to the 
	//sockaddr_in structure which is passed to connect() 
	memcpy(&serv_addr.sin_addr, server->h_addr_list[0], server->h_length);
	//port number
    serv_addr.sin_port = htons(portno);
	//connect
    if (connect(socket_two,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        printf("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(socket_two,buffer,strlen(buffer));
    if (n < 0) 
         printf("ERROR writing to socket");
    bzero(buffer,256);
    n = read(socket_two,buffer,255);
    if (n < 0) 
         printf("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}