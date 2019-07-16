
static std::vector<std::vector<IntRect>> persoRect {{creerVect(13, 6, 20, 30, 50, 4), creerVect(16, 43, 24, 30, 50, 6), creerVect(64, 79, 24, 30, 50, 9), creerVect(13, 112, 24, 31, 50, 2), creerVect(8, 96, 22, 32, 32, 10)}};

static Vector2f POS_HERO(432, 300);



int jeu(RenderWindow& app, Map& carte){

	//Test
	std::vector<Texture> back_texture;
	std::vector<Sprite> back;

	back_texture.resize(9);
	for(int i = 1; i < 10; ++i){
		back_texture.emplace_back();
		if(!back_texture.back().loadFromFile("Ressources/Background/Layer_"+std::to_string(i)+".png")){
			std::cerr << "Impossible de charger : " << "Ressources/Background/Layer_"+std::to_string(i)+".png" << std::endl;
		}
		else{
			std::cout << "Chargé : " << "Ressources/Background/Layer_"+std::to_string(i)+".png" << std::endl;
			back.emplace_back(back_texture.back());
		}
	}

	/*for(int i = 0; i<back_texture.size(); ++i){
		back.emplace_back(back_texture.back());
	}*/

	std::cout << "taille : " << back.size() << std::endl;




	//test

	int sens;
	size_t i, taille_back(back.size());

	uint8_t save;
	Clock temps;

	float tempo;
	
	Personnage hero("Ressources/adventurer-v1.5-Sheet.png", persoRect, POS_HERO);
	CollisionManager colli_;

	colli_.setMap(&carte);

	View vue(hero.getPosition(), CAM_TAILLE);
	app.setView(vue);

	Event event;
	while(app.isOpen()){

		while(app.pollEvent(event)){
			if(event.type == Event::Closed){
				app.close();
			}
			if(event.type == Event::KeyPressed){
				switch(event.key.code){

					case Keyboard::P :
						hero.setPosition(POS_HERO);
						break;

					case Keyboard::O :
						std::cout << " x : " << hero.getPosition().x << " y : " << hero.getPosition().y << std::endl;
						break;

					case Keyboard::Escape :
						app.close();
						break;

					default:
						break;
				}
			}
		}

		tempo = temps.restart().asSeconds();

		if(Keyboard::isKeyPressed(Keyboard::Space)){
			hero.jump();
		}

		sens = 0;
		if(Keyboard::isKeyPressed(Keyboard::Q)){
			sens = -1;
		}
		if(Keyboard::isKeyPressed(Keyboard::D)){
			sens = 1;
		}
		hero.move(sens, tempo);

		if((save = colli_.verifColli(hero, tempo))){

			//hero.annulMove(tempo);
		}

		vue.setCenter(hero.getPosition());
		app.setView(vue);

		if(hero.getPosition().y < 16){
			app.clear(Color(118, 147, 179, 255));
		}
		else{
			app.clear(Color(12, 17, 34, 255));
		}

		app.setView(app.getDefaultView());
		for(i = 0; i<taille_back; ++i){
			//if(hero.getPosition().x*i)
			//std::cout << ""
			if(hero.getPosition().x<0){
				back[i].setPosition((int)-(hero.getPosition().x*i/10)%927 - 927, (int)-(hero.getPosition().y/2)-150);
			}
			else{
				back[i].setPosition((int)-(hero.getPosition().x*i/10)%927, (int)-(hero.getPosition().y/2)-150);
			}
			app.draw(back[i]);
			back[i].move(927, 0);
			app.draw(back[i]);
			back[i].move(927, 0);
			app.draw(back[i]);
		}

		app.setView(vue);
		hero.draw(app);
		carte.draw(app);

		app.display();

	}
	return 0;
}

int jeu_multi(RenderWindow& app, Map& carte, int sock){

	//Test
	std::vector<Texture> back_texture;
	std::vector<Sprite> back;

	back_texture.resize(9);
	for(int i = 1; i < 10; ++i){
		back_texture.emplace_back();
		if(!back_texture.back().loadFromFile("Ressources/Background/Layer_"+std::to_string(i)+".png")){
			std::cerr << "Impossible de charger : " << "Ressources/Background/Layer_"+std::to_string(i)+".png" << std::endl;
		}
		else{
			std::cout << "Chargé : " << "Ressources/Background/Layer_"+std::to_string(i)+".png" << std::endl;
			back.emplace_back(back_texture.back());
		}
	}

	/*for(int i = 0; i<back_texture.size(); ++i){
		back.emplace_back(back_texture.back());
	}*/

	std::cout << "taille : " << back.size() << std::endl;




	//test

	message msg;
	message send_msg;
	IntRect tempo_rect;

	int sens;
	size_t i, taille_back(back.size());
	ssize_t taille;

	uint8_t save;
	Clock temps;

	float tempo;
	
	Personnage hero("Ressources/adventurer-v1.5-Sheet.png", persoRect, POS_HERO);
	CollisionManager colli_;

	colli_.setMap(&carte);

	View vue(hero.getPosition(), CAM_TAILLE);
	app.setView(vue);

	Event event;
	while(app.isOpen()){

		while(app.pollEvent(event)){
			if(event.type == Event::Closed){
				app.close();
			}
			if(event.type == Event::KeyPressed){
				switch(event.key.code){

					case Keyboard::P :
						hero.setPosition(POS_HERO);
						break;

					case Keyboard::O :
						std::cout << " x : " << hero.getPosition().x << " y : " << hero.getPosition().y << std::endl;
						break;

					case Keyboard::Escape :
						app.close();
						break;

					default:
						break;
				}
			}
		}

		while((taille = recv(sock, &msg, sizeof(msg), MSG_DONTWAIT)) > 0){
			if(msg.type == 0){
				carte.putBlock(sf::Vector2f(msg.x, msg.y));
			}
			else if(msg.type == 1){
				carte.takeBlock(sf::Vector2f(msg.x, msg.y));
			}
			else{
				printf("TEST\n");
			}
		}
		if(taille == 0){
			return 0;
		}


		tempo = temps.restart().asSeconds();

		if(Keyboard::isKeyPressed(Keyboard::Space)){
			hero.jump();
		}

		sens = 0;
		if(Keyboard::isKeyPressed(Keyboard::Q)){
			sens = -1;
		}
		if(Keyboard::isKeyPressed(Keyboard::D)){
			sens = 1;
		}
		hero.move(sens, tempo);

		if((save = colli_.verifColli(hero, tempo))){

			//hero.annulMove(tempo);
		}

		send_msg.type = 2;
		send_msg.x = hero.getPosition().x;
		send_msg.y = hero.getPosition().y;
		tempo_rect = hero.getTextureRect();
		send_msg.left = tempo_rect.left;
		send_msg.top = tempo_rect.top;
		send_msg.width = tempo_rect.width;
		send_msg.height = tempo_rect.height;

		send(sock, &send_msg, sizeof(send_msg), 0);

		vue.setCenter(hero.getPosition());
		app.setView(vue);

		if(hero.getPosition().y < 16){
			app.clear(Color(118, 147, 179, 255));
		}
		else{
			app.clear(Color(12, 17, 34, 255));
		}

		app.setView(app.getDefaultView());
		for(i = 0; i<taille_back; ++i){
			//if(hero.getPosition().x*i)
			//std::cout << ""
			if(hero.getPosition().x<0){
				back[i].setPosition((int)-(hero.getPosition().x*i/10)%927 - 927, (int)-(hero.getPosition().y/2)-150);
			}
			else{
				back[i].setPosition((int)-(hero.getPosition().x*i/10)%927, (int)-(hero.getPosition().y/2)-150);
			}
			app.draw(back[i]);
			back[i].move(927, 0);
			app.draw(back[i]);
			back[i].move(927, 0);
			app.draw(back[i]);
		}

		app.setView(vue);
		hero.draw(app);
		carte.draw(app);

		app.display();

	}
	return 0;
}