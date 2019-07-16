
#include "multiplayer.h"

//serveur
int find_player(int *sock, int port){
	int client;
	struct sockaddr_in addr;

	*sock = socket(AF_INET , SOCK_STREAM, 0);


	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(*sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		perror("bind");
		exit(1);
	}

	listen(*sock, 8);

	client = accept(*sock, NULL, NULL);
	if(client < 0){
		perror("accept");
		exit(1);
	}

	return client;
}

int connect_to_serv(char const *name, int port){

	int sock;
	struct hostent *host;
	struct sockaddr_in addr;

	host = gethostbyname(name);
	if(host == NULL){
		perror("gethostbyname");
		exit(1);
	}

	sock = socket(AF_INET , SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = *((uint32_t *) host->h_addr);

	if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		perror("connect");
		exit(1);
	}

	return sock;
}

/*int main(int argc, char const *argv[]){
	int sock, client;

	if(argc == 2){
		client = find_player(&sock, std::stoi(argv[1]));
	}
	else if(argc == 3){
		sock = connect_to_serv(argv[1], std::stoi(argv[2]));
	}


	close(sock);
	close(client);

	return 0;
}*/