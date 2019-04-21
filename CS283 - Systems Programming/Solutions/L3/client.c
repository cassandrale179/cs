#include "csapp.h"
#include "csapp.c"





void requestFile(char * host, int port, char * filename)
{
	char buf[MAXBUF];
	int clientfd;
	rio_t rio;

	clientfd = Open_clientfd(host, port);

	Rio_readinitb(&rio, clientfd);

	// Build the request string
	sprintf(buf, "GET /%s HTTP/1.1\r\n", filename);
	sprintf(buf, "%sHost: %s\r\n", buf, host);
	sprintf(buf, "%s\r\n", buf);

	printf("Built Buffer:\n%s\n", buf);

	// Write the request buffer to the server
	ssize_t nwritten = rio_writen(clientfd, buf, strlen(buf));
	if (nwritten < 0) // Error checking
	{
		fprintf(stderr, "Error! Unable to write to server.");
		exit(0);
	}

	// Read from the server back into the buffer, and then print
	// to the screen.
	ssize_t nread;
	while ((nread = rio_readnb(&rio, buf, MAXLINE)) != 0)
	{
		printf("%s", buf);
	}

	if (nread < 0)
	{
		fprintf(stderr, "Error reading from server!");
		exit(0);
	}

	Close(clientfd);
}

int main(int argc, char **argv)
{
  int port;
  char *host, *filename;

  if (argc != 4)
  {
    fprintf(stderr, "usage: %s <host> <port> <filename>\n", argv[0]);
    exit(0);
  }

  host = argv[1];
  port = atoi(argv[2]);
  filename = argv[3];

  requestFile(host, port, filename);

  exit(0);
}


#include<stdio.h>
#include<string.h>    
#include<sys/socket.h>
#include<arpa/inet.h>

// www.axmag.com/download/pdfurl-guide.pdf
int main(int argc , char *argv[])
{
    int socket_desc;

    char *message;
    char server_reply[10000];
    char *filename = "index.json";
    int total_len = 0;
    int file_len = 99352;

    int len; 

    FILE *file = NULL;
    struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("198.11.181.184");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    //Send request
    message = "GET /download/pdfurl-guide.pdf HTTP/1.1\r\nHost: www.axmag.com\r\n\r\n Connection: keep-alive\r\n\r\n Keep-Alive: 300\r\n";
    //message = "GET /index.html HTTP/1.1\r\nHost: www.google.com\r\n\r\n Connection: keep-alive\r\n\r\n Keep-Alive: 300\r\n";
    //message = "GET /index.html HTTP/1.1\r\nHost: www.openssl.org\r\n\r\n";

    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }

    puts("Data Send\n"); 

    remove(filename);
    file = fopen(filename, "ab");

    if(file == NULL){
        printf("File could not opened");
    }   

    while(1)
    {
        int received_len = recv(socket_desc, server_reply , sizeof server_reply , 0);

        if( received_len < 0 ){
            puts("recv failed");
            break;
        }

        total_len += received_len;

        puts(server_reply);   
        fwrite(server_reply , received_len , 1, file);

        printf("\nReceived byte size = %d\nTotal lenght = %d", received_len, total_len);

        if( total_len >= file_len ){
            break;
        }   
    }

    puts("Reply received\n");

    fclose(file);

    return 0;
}