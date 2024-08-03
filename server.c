// Server program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
//#include<time.h>
#include<sys/socket.h>
#include<netinet/in.h>

/*void __attribute__((destructor)) end();

void end()
{
	printf("Server closed in 2 sec\n");
	sleep(2);
}*/

int main(int argc, char const* argv[])
{
	int sockfd;
	char buffer[] = "Message from server";

	struct sockaddr_in server_addr;
	socklen_t addrlen = sizeof(server_addr);

	// Socket creation
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error during socket creation");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9999);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the address
	if((bind(sockfd, (struct sockaddr *)&server_addr, addrlen)) < 0)
	{
		perror("Error during bind");
		exit(EXIT_FAILURE);
	}


	// Listen the connection
	if(listen(sockfd, 1) < 0)
	{
		perror("Error during listen");
		exit(EXIT_FAILURE);
	}

	printf("Server is listening....\n");

	// Accept the  connection
	int new_sockfd = accept(sockfd, (struct sockaddr *) &server_addr, &addrlen);

	// Send the message to client
	send(new_sockfd, buffer, sizeof(buffer), 0);

	// Close the socket
	close(new_sockfd);
	close(sockfd);



	return 0;
}
