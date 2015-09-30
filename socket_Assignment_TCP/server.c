#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//int socket(int domain, int type, int protocol);
	//file descripetos, socket_one and new_socket_onetwo which variables stores the value abd accept system call
	//addlen is to store the size of address for accept() function
	//n is the return values for send() and recv() functions 
	int socket_one, new_socket_one, addrlen, n;
	//Creates the buffers to receive the message
	int bufsize=1024;        /* a 1K buffer */
	char *buffer=malloc(bufsize);
	//structure that contains internet address
	//serv_addr will contain the address of the server
	//cli_addr will contain the address of the client which connects to the server.
	struct sockaddr_in serv_addr, cli_addr;
	//creating the socket 
	socket_one = socket(AF_INET,SOCK_STREAM,0);
	//check if able to open the socket from server
	if (socket_one == -1) 
	         printf("ERROR opening socket");
  	// type of socket created in socket() 
   	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
  	// 7000 is the port to use for connections
    serv_addr.sin_port = htons(7000);
  	// bind the socket to the port specified above 
	if (bind(socket_one, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		printf("ERROR on binding");
	//listen to the socket connection
	//listen(file descriptor, size of the backlog queue)
	listen(socket_one,1);
	//Accept the connection
	addrlen = sizeof(struct sockaddr_in);
	//Accept for incoming function
	new_socket_one = accept(socket_one, (struct sockaddr *)&cli_addr, &addrlen);
	if (new_socket_one < 0)
		    printf("ERROR on Accept connection");
	//receive from the client
	n = recv(new_socket_one,buffer,bufsize,0);
	if (n < 0) 
		printf("ERROR reading from socket");
	printf("You got the message: %s\n",buffer);
	//return the string back to the client
	char *message="world\r";
	n = send(new_socket_one,message,strlen(message),0);
	if (n < 0) 
		printf("ERROR writing to socket");
	return 0;
}