// EchoServer.cpp: define el punto de entrada de la aplicación de consola.
//
/*ERRORES
iknitrodeb@debian:~$ gcc '/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp'
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp: In function ‘int main()’:
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:36: error: invalid conversion from ‘int*’ to ‘socklen_t*’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:36: error:   initializing argument 3 of ‘int accept(int, sockaddr*, socklen_t*)’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:38: error: invalid conversion from ‘char’ to ‘void*’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:38: error:   initializing argument 2 of ‘ssize_t read(int, void*, size_t)’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:41: error: invalid conversion from ‘char’ to ‘const void*’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:41: error:   initializing argument 2 of ‘ssize_t write(int, const void*, size_t)’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:43: error: invalid conversion from ‘char’ to ‘void*’
/var/run/vmblock-fuse/blockdir/6ebce057/EchoServer.cpp:43: error:   initializing argument 2 of ‘ssize_t read(int, void*, size_t)’


*/
#include <iostream>
#include <sys/socket.h>	
#include <unistd.h>	

//Otros includes:
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<netdb.h>
#include<string.h>

using namespace std;

int listen_socket, cliente;
struct sockaddr_in clientinfo, server; 
int rtn;
char buffer[256];
const int PUERTO = 5050;


int main() {

	//SOCKET
	listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	

	server.sin_family = PF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PUERTO);
	//BIND
	rtn = bind(listen_socket, (struct sockaddr*) (&server), (int) sizeof(server));
	//LISTEN
	listen(listen_socket, 1); //1 es el maximo de conexiones a la vez
	while (true) {
	//ACCEPT
	//	int c = sizeof(struct sockaddr_in);
		int c = sizeof(server);
		int cl = -1;
		while (cl < 0) {
			cliente = accept(listen_socket, (struct sockaddr*) (&server), (socklen_t*)&c);
		}
	//READ
		cout << "Al menos intenta leer \n";
	//	rtn = read(listen_socket, (*buffer), sizeof(buffer));
		int lee = -1;
		while (lee <= 0) {
			lee = read(cliente, buffer, strlen(buffer));
			cout << buffer;
		}
		cout << "Al menos lee \n";
		while (true) { //strcmp(buffer, "FIN\n")) {
		//WRITE
	//		rtn = write(listen_socket, (*buffer), sizeof(buffer));
			cout << "bucle";
			strcat(buffer, "  Servidor");
			write(cliente, buffer, strlen(buffer));
		//READ
	//		rtn = read(listen_socket, (*buffer), sizeof(buffer));
			while ((read(cliente, buffer, strlen(buffer)))< 0);
		}
	}
	
	
	return 0;
}

