/* CS372-Fall 2019
*  Author: Peng Zhang
*  Due:11/3/2019
*  Program Client*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	if (argc != 3){
		fprintf(stderr, "Should enter ./a.out <address> <port>\n");
		exit(1);
	}
	char name[10];
	char serve_name[10];
	printf("Enter a one-word name that up to 10 characters: ");
	scanf("%s", name);
	int adi;
	//get the address info
	//cited from https://beej.us/guide/bgnet/html/#sendtorecv
	struct addrinfo hints;
	struct addrinfo *seinf;
	memset(&hints,0,sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if ((adi = getaddrinfo(argv[1], argv[2], &hints, &seinf)) != 0) {
        fprintf(stderr, "The adress or the port doesn't match, we got error:  %s\n", gai_strerror(adi));
        return 1;
    }
    //make a socket
    //cited from https://beej.us/guide/bgnet/html/#sendtorecv
    struct addrinfo* p;
    int socketn;
    for(p = seinf; p != NULL; p = p->ai_next) {
        if ((socketn = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("Fail to connect the socket!");
       		exit(1);
        }
        break;
    }
    //Do connect
    //cited from https://beej.us/guide/bgnet/html/#sendtorecv
    if (connect(socketn, p->ai_addr, p->ai_addrlen) == -1) {
            close(socketn);
            perror("Fail to connect the client! ");
            exit(1);          
    } 
    //get and sent information
    //cited from https://beej.us/guide/bgnet/html/#cb85-36
    int sent_byte, receive_byte;
    int l = strlen(name);
    sent_byte = send(socketn, name, l, 0);
    receive_byte = recv(socketn, serve_name, 10, 0);

    //receive and send message:
    char msg_send[501]; //declare sending message: 500 characters
    char msg_recv[501]; //declare receive message: 500 characters
    fgets(msg_send, 500, stdin); //clear line for input
    while(1){
    	memset(msg_send,0,sizeof(msg_send)); //intialize sending message
    	memset(msg_recv,0,sizeof(msg_recv)); //intialize receive message
    	printf("%s> ", name); //ouput fomat: name > (input)
    	fgets(msg_send,501, stdin); //get standard input
    	if(strcmp(msg_send, "\\quit\n") == 0){//check if the input is \quit\n, if so, break
    		printf("Disconnected by enter quit\n");
    		break;
    	}
    	int len = strlen(msg_send); //get the length of sending message
    	send(socketn, msg_send, len, 0);//send messages
    	int count = recv(socketn, msg_recv, 500, 0);//receive messages
    	if (count == 0){// if nothing reveived, it is server input \quit or nothing
    		printf("Connection closed because the server enter quit or nothing.");
    		break;
    	}
    	printf("%s> %s\n", serve_name, msg_recv); //output message: (server name) > (messages)
    }
    close(socketn); //close socket
    printf("***The connection has closed***\n");
	return 0;
} 