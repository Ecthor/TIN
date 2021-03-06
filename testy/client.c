#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>

//using namespace std;

#define DATA "Half a league, half a league . . ."

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *hp, *gethostbyname();
	char buf[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("opening stream socket");
		exit(1);
	}

	/* uzyskajmy adres IP z nazwy ... */
	server.sin_family= AF_INET;
	hp =gethostbyname(argv[1] );

	/* hostbyname zwraca strukture zawierajaca adres danego hosta */
	if (hp == (struct hostent *) 0) {
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}

	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(atoi( argv[2]));
	if (connect(sock, (struct sockaddr *) &server, sizeof server) == -1){
		perror("connecting stream socket");
		exit(1);
	}

	if (write( sock, DATA, sizeof DATA ) == -1)
		perror("writing on stream socket");
	close(sock);
	exit(0);
	

}
