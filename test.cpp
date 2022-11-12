#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <iostream>
#include <cerrno>
#include <cstring>

#include <unistd.h>
// using std::cout cout;
using std::cout;
using std::endl;
using std::strerror;

#define PORT_NBR 55555
#define MAX_LINE 4096
#define SA struct sockaddr

int main(void)
{
	int socketFD;
	int acceptSocket;
	int errNum;
	struct sockaddr_in serverAddress;
	int sizeServerAddress = sizeof(serverAddress);

	cout << "^^^ Stage 1: socket creation ^^^" << endl;
	
	socketFD = socket(AF_INET, SOCK_STREAM, 0); //SOCK_NONBLOCK
	
	if (socketFD == -1)
	{
		cout << "Socket error: " << std::strerror(errno) << '\n';
		return (-1);
	}
	else
	{
		cout << "Socket " << socketFD << " created!" << endl;

	}
	
	cout << "^^^ Stage 2: socket binding ^^^" << endl;

	memset(&serverAddress, 0, sizeServerAddress);
	serverAddress.sin_family		= AF_INET;
	serverAddress.sin_addr.s_addr	= htonl(INADDR_ANY);
	serverAddress.sin_port			= htons(PORT_NBR);
	errNum = bind(socketFD, (SA *) &serverAddress, sizeServerAddress);
	
	if (errNum == -1)
	{
		cout << "Socket error: " << std::strerror(errno) << '\n';
		return (-1);
	}
	else
	{
		cout << "Socket bound!"<< endl;
	}
	
	cout << "^^^ Stage 3: socket listening ^^^" << endl;
	errNum = listen(socketFD, 1024);
	if (errNum == -1)
	{
		cout << "Socket error: " << std::strerror(errno) << '\n';
		return (-1);
	}
	else
	{
		cout << "Socket listening!"<< endl;
	}
	
	cout << "^^^ Stage 4: socket accept ^^^" << endl;

	acceptSocket = accept(socketFD, (SA *)NULL, NULL);
	if (acceptSocket == -1)
	{
		cout << "Socket error: " << std::strerror(errno) << '\n';
		return (-1);
	}
	else
	{
		cout << "Socket " << acceptSocket << " created!" << endl;

	}
	return 0;
}