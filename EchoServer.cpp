// EchoServer.cpp: define el punto de entrada de la aplicación de consola.
//

#include <iostream>
#include <sys/socket.h>	//Para linux
//#include <sys\types.h>				// ERROR NO EXISTE
#include <unistd.h>	

using namespace std;

int listen_socket, cliente;
struct sockaddr_in clientinfo, servicio;
int rtn;
char buffer[256];
const int PUERTO = 5050;


int main() {

	//SOCKET
	listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	servicio.sin_family = PF_INET;
	servicio.sin_addr.S_un.S_addr = INADDR_ANY;
	servicio.sin_port = htons(PUERTO);
	//BIND
	rtn = bind(listen_socket, (struct sockaddr*) &servicio, (int) sizeof(servicio));
	//LISTEN
	listen(listen_socket, SOMAXCONN;
	//ACCEPT
	rtn = accept(listen_socket, (struct sockaddr*) &servicio, (int*) sizeof(servicio);
	//READ
	rtn = read(listen_socket, *buffer, sizeof(buffer))
	while (true) {
		//WRITE
		irtn = write(listen_socket, *buffer, sizeof(buffer))
		//READ
		rtn = read(listen_socket, *buffer, sizeof(buffer))
		fprintf(stderr, "Bucle");
	}
	
	return 0;
}

