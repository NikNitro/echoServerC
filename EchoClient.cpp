
#include <iostream>
#include <sys/socket.h>

#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<netdb.h>
#include<string.h>


using namespace std;


int sck;
char bufferIn[256], bufferOut[256];



int main() {
	sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in servicio;
	bzero(&servicio, sizeof(servicio));
	servicio.sin_family = PF_INET;
	servicio.sin_port = htons(5050);
	inet_aton("127.0.0.1", &(servicio.sin_addr));
	int i = -1;
	while (i < 0) {
		i = connect(sck, (struct sockaddr*) (&servicio), sizeof(servicio));
	}
	//Obtenemos la string a enviar, la separamos en caracteres y la enviamos.
	bool noAcaba = true;
	while (noAcaba) {
		cout << "Conectado al servidor " << inet_ntoa(servicio.sin_addr) << ":" << servicio.sin_port << ".\n";
		cout << "Que desea enviar?\n";
		cin>>bufferOut;
		cout << "bajo cin";
		strcat(bufferOut, "\n");
		cout << "bajo strcat";
		int n = -1
		while (n < 0) {
			n = write(sck, bufferOut, strlen(bufferOut));
		}
		if (!strcmp(bufferOut, "FIN")) {
			noAcaba = false;
		}
		cout << "bajo write";
		int m = -1;
		while (m == -1) {
			m = read(sck, bufferIn, 256);
		}
		cout << bufferIn << "\n";
	}
	cout << "Desconectado Correctamente.";
	

	return 0;
}