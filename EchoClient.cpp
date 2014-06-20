
#include <iostream>
#include <sys/socket.h>

#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<netdb.h>

using namespace std;


int sck;
char buffer[256];



int main() {
	sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in servicio;
	bzero(&servicio, sizeof(servicio));
	servicio.sin_family = PF_INET;
	servicio.sin_port = htons(5050);
	inet_aton("127.0.0.1", &(servicio.sin_addr));

	connect(sck, (struct sockaddr*) (&servicio), sizeof(servicio));
	//Obtenemos la string a enviar, la separamos en caracteres y la enviamos.
	fgets(data, 256, stdin);
	int n = 0, m = 0;
	n = strlen(data);
	while (n > 0) {
		m = write(sck, (*buffer), sizeof(buffer));
		n = n - m;
	}

	return 0;
}