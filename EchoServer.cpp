// EchoServer.cpp: define el punto de entrada de la aplicación de consola.
//
#include <iostream>
//#include <sys/socket.h>	Para linux
#include <sys\types.h>
#include <winsock2.h>

using namespace std;

WSADATA wsa_data;
SOCKET listen_socket, cliente;
struct sockaddr_in clientinfo, servicio;
int rtn;
char buffer[256];
const int PUERTO = 5050;


int main() {

	if ((rtn = WSAStartup(MAKEWORD(2, 2), &wsa_data)) != 0) {
		fprintf(stderr, "Error WSAStartup");
		return -1;
	}
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		fprintf(stderr, "Error en Socket");
		WSACleanup();
		return -1;
	}

	servicio.sin_family = AF_INET;
	servicio.sin_addr.S_un.S_addr = INADDR_ANY;
	servicio.sin_port = htons(PUERTO);

	if ((rtn = bind(listen_socket, (struct sockaddr*) &servicio, (int) sizeof(servicio))) == SOCKET_ERROR) {
		fprintf(stderr, "ERROR en bind");
		WSACleanup();
		return -1;
	}
	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
		fprintf(stderr, "Error en listen");
		closesocket(listen_socket);
		WSACleanup();
		return -1;
	}

	return 0;
}

