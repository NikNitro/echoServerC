// EchoServer.cpp: define el punto de entrada de la aplicaci�n de consola.
//

/**
 * Los WSA hay que borrarlos. En Linux dar�n error
 *
 */

//#pragma comment(lib, "ws2_32") //Para evitar errores LNK2019
#include <iostream>
#include <sys/socket.h>	//Para linux
#include <sys\types.h>				// ERROR NO EXISTE
//#include <winsock2.h>
#include <unistd.h>	
//#include <Windows.h>

using namespace std;

//WSADATA wsa_data;
int listen_socket, cliente;
struct sockaddr_in clientinfo, servicio;
int rtn;
char buffer[256];
const int PUERTO = 5050;


int main() {

/*	if ((rtn = WSAStartup(MAKEWORD(2, 2), &wsa_data)) != 0) {
		fprintf(stderr, "Error WSAStartup");
		return -1;
	}
*/	//SOCKET
	if ((listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		fprintf(stderr, "Error en Socket");
//		WSACleanup();
		return -1;
	}

	servicio.sin_family = PF_INET;
	servicio.sin_addr.S_un.S_addr = INADDR_ANY;
	servicio.sin_port = htons(PUERTO);
	//BIND
	if ((rtn = bind(listen_socket, (struct sockaddr*) &servicio, (int) sizeof(servicio))) == SOCKET_ERROR) {
		fprintf(stderr, "ERROR en bind");
//		WSACleanup();
		return -1;
	}
	//LISTEN
	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
		fprintf(stderr, "Error en listen");
		closesocket(listen_socket);
//		WSACleanup();
		return -1;
	}
//	system("ECHO Todo Correcto");
//	system("PAUSE > nul");
	//ACCEPT
	if ((rtn = accept(listen_socket, (struct sockaddr*) &servicio, (int*) sizeof(servicio))) < 0) {
		fprintf(stderr, "Error al aceptar");
//		WSACleanup();
		return -1;
	}
	//READ
	if ((rtn = read(listen_socket, *buffer, sizeof(buffer))) < 0) {
		fprintf(stderr, "Error al leer");
//		WSACleanup();
		return -1;
	}
	while (true) {
		//WRITE
		if ((rtn = write(listen_socket, *buffer, sizeof(buffer))) < 0) {
			fprintf(stderr, "Error al enviar");
//			WSACleanup();
			return -1;
		}
		//READ
		if ((rtn = read(listen_socket, *buffer, sizeof(buffer))) < 0) {
			fprintf(stderr, "Error al leer");
//			WSACleanup();
			return -1;
		}
		fprintf(stderr, "Bucle");
	}
	
	return 0;
}

