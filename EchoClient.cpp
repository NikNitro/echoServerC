
#include <iostream>
#include <sys/socket.h>    //socket
#include<stdio.h> //printf
#include<netinet/in.h> 
#include<arpa/inet.h>  //inet_addr
#include<netdb.h>
#include<string.h>    //strlen


using namespace std;





int main() {
	int sck, rtn;
	struct sockaddr_in server;
	char bufferIn[2000], bufferOut[2000], bufferAux[2000];
	//creamos socket
	sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sck == -1) {
		cout << "No se puede crear el socket";
	}
	puts("Socket creado");

//	bzero(&servicio, sizeof(servicio));
	server.sin_family = PF_INET;
	server.sin_port = htons(5050);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Conectando al servidor
	if (connect(sck, (struct sockaddr*) (&server), sizeof(server)) < 0) {
		perror("Conexion fallida. error");
		return 1;
	}
	puts("Conectado\n");
	
	//Obtenemos la string a enviar, la separamos en caracteres y la enviamos.
	bool noAcaba = true;
	while (noAcaba) {
		cout << "Conectado al servidor " << inet_ntoa(server.sin_addr) << ":" << server.sin_port << ".\n";
		cout << "Que desea enviar?\n";
		scanf("%s", bufferOut);
		if (!strcmp(bufferOut, "FIN")) {
			noAcaba = false;
		}
		strcat(bufferOut, "\n");
		int n = -1;

		if (write(sck, bufferOut, strlen(bufferOut)) < 0) {
			puts("envio fallido");
			return 1;
		}
		rtn = read(sck, bufferIn, 2000);
			
		cout << "\nDevuelto " ; 
		for (int i = 0; i < strlen(bufferOut); i++) {
			cout << bufferIn[i];
		}
		cout << "\n";
		strcpy(bufferIn, "\0");
		strcpy(bufferOut, "\0");

	}
	cout << "Desconectado Correctamente.";
	

	return 0;
}