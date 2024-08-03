// Client program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char const* argv[])
{
	int sockfd;
	struct sockaddr_in client_addr;
	socklen_t addrlen = sizeof(client_addr);
	// Socket Creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("Error during socket creation");
		exit(EXIT_FAILURE);
	}

	// Initialize socket address
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(9999);
	client_addr.sin_addr.s_addr = INADDR_ANY;

	// Connect to the  server
	connect(sockfd, (struct sockaddr *) &client_addr, addrlen);

	char buffer[250];

	// Receive the message from server
	recv(sockfd, buffer,sizeof(buffer), 0);
	printf("%s\n", buffer);

	// Close the socket(connection)
	close(sockfd);


	return 0;
}
