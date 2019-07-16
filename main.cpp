#include "head.h"

int main(int argc, char const *argv[]){

	int save, sock, client;

	RenderWindow app(VIDEO_MODE, "Fun by Magnat");
	app.setVerticalSyncEnabled(true);

	save = menu(app);
	Map carte("Ressources/terraintrans.png");
	if(save == 1){
		editeur(app, carte);
		jeu(app, carte);
	}
	if(save == 3){
		//editeur(app, carte);

		//Creation du personnage
		sock = connect_to_serv(argv[1], std::stoi(argv[2]));

		jeu_multi(app, carte, sock);

		close(sock);
	}
	else if(save == 2){
		client = find_player(&sock, std::stoi(argv[1]));

		editeur_multi(app, carte, client);

		close(sock);
		close(client);
	}
	app.close();
	return 0;
}