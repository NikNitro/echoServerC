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

using namespace std;

int listen_socket, cliente;
struct sockaddr_in clientinfo, servicio; 
int rtn;
char buffer[256];
const int PUERTO = 5050;


int main() {

	//SOCKET
	listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	//‘IPPROTO_TCP’ was not declared in this scope

	servicio.sin_family = PF_INET;
	servicio.sin_addr.s_addr = INADDR_ANY;						//‘INADDR_ANY’ was not declared in this scope
	servicio.sin_port = htons(PUERTO);							//'htons' was not declared in this scope
	//BIND
	rtn = bind(listen_socket, (struct sockaddr*) &servicio, (int) sizeof(servicio));
	//LISTEN
	listen(listen_socket, SOMAXCONN);
	//ACCEPT
	rtn = accept(listen_socket, (struct sockaddr*) &servicio, (int*) sizeof(servicio));
	//READ
	rtn = read(listen_socket, *buffer, sizeof(buffer));
	while (true) {
		//WRITE
		rtn = write(listen_socket, *buffer, sizeof(buffer));
		//READ
		rtn = read(listen_socket, *buffer, sizeof(buffer));
		cout<<"Bucle";
	}
	
	return 0;
}

