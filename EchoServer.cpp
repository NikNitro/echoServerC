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
#include <unistd.h>		//write
#include <stdio.h>		//para perror
#include <stdlib.h>		// para atoi

//Otros includes:
#include<netinet/in.h> 
#include<arpa/inet.h>	//inet_addr
#include<netdb.h>
#include<string.h>		//strlen

using namespace std;




int main(int argc, char *argv[]) {

	int listen_socket, cliente, rtn;
	struct sockaddr_in server, clientinfo;
//	const int PUERTO = 5050;
	const int PUERTO = atoi(argv[1]);

	//SOCKET
	listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (listen_socket == -1) {
		perror("No se puede crear el socket");
		return 1;
	}
	cout << "Socket creado\n";

	//preparar la estructura sockaddr_in
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PUERTO);
	
	//BIND
	rtn = bind(listen_socket, (struct sockaddr*)&server, sizeof(server));
	if (rtn < 0) {
		perror("Error en el bind");
		return 1;
	}
	puts("Bind hecho");
	
	//LISTEN
	rtn = listen(listen_socket, 1); //1 es el maximo de conexiones a la vez
	cout << "Esperando conexiones entrantes en el puerto "<< PUERTO << "\n";
	/*if (rtn < 0) {
		perror("Error en el listen");
		return 1;
	}*/

	while (true) {

	sockaddr client;
	socklen_t c = sizeof(client);
	//ACCEPT
	cliente = accept(listen_socket, &client, &c);
	if (cliente < 0) {
		perror("Error en el accept");
		return 1;
	}
	cout << "Conexion aceptada en el puerto " << PUERTO << "\n";
	fflush(stdout);

	//READ
	char buffer[2000], bufferAux[2000];
//		cout << "Al menos intenta leer \n";
	bool noAcaba = true;
	while ((rtn = read(cliente, buffer, 2000)) > 0 && noAcaba) {
			cout << "Conectado en el puerto " << PUERTO << ". Esperando accion.\n";
//			cout << "RECIBIDO: " << buffer << "\n";
			if (!strcmp(buffer, "FIN")) {
				noAcaba = false;
			}
			else {
				fflush(stdout);
	//			cout << "Al menos lee \n";
	//			strcat(buffer, "  Servidor");
				for (int i = 0; i < rtn; i++) {
					buffer[i] = toupper(buffer[i]);
				}
				fflush(stdout);
				if (write(cliente, buffer, strlen(buffer)) < 0) {
					perror("Envio fallido");
					return 1;
				}
//				cout << "ENVIADO: " << buffer;
				fflush(stdout);
				//Reiniciarlo
				strcpy(buffer, "\0");
			}

			
		}
		if (rtn == 0) {
			cout << "Recibido FIN. \nCerrando la conexión con el cliente\n";
			cout<<"Cliente desconectado. Esperando conexion en el puerto "<< PUERTO << "\n";
			fflush(stdout);
		}
		else if (rtn == -1)
		{
			perror("Error en Read");
		}
		cout << "Esperando otro cliente.\n \n";

	}
	
	
	return 0;
}

