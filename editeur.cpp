
int editeur_multi(RenderWindow& app, Map& carte, int sock){

	message msg;
	message send_msg;
	sf::Vector2f tempo;

	ssize_t taille;

	Personnage hero("Ressources/adventurer-v1.5-Sheet.png", persoRect, POS_HERO);

	View vue(POS_HERO, Vector2f(CAM_TAILLE.x*2, CAM_TAILLE.y*2));

	Event event;
	while(app.isOpen()){

		while(app.pollEvent(event)){
			if(event.type == Event::Closed){
				app.close();
			}
			if(event.type == Event::KeyPressed){
				switch(event.key.code){

					case Keyboard::Enter :
						return 1;

					case Keyboard::Escape :
						app.close();
						break;

					default:
						break;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed){
			    if (event.mouseButton.button == sf::Mouse::Left){
			    	tempo = app.mapPixelToCoords(sf::Mouse::getPosition(app));
			        carte.putBlock(tempo);
			        send_msg.type = 0;
			        send_msg.x = tempo.x;
			        send_msg.y = tempo.y;
			        send(sock, &send_msg, sizeof(send_msg), 0);
			    }
			    else if (event.mouseButton.button == sf::Mouse::Right){
			    	tempo = app.mapPixelToCoords(sf::Mouse::getPosition(app));
			    	carte.takeBlock(tempo);
			    	send_msg.type = 1;
			        send_msg.x = tempo.x;
			        send_msg.y = tempo.y;
			        send(sock, &send_msg, sizeof(send_msg), 0);
			    }
			}
		}

		carte.appliqueTexture();

		if(Keyboard::isKeyPressed(Keyboard::Z)){
			vue.move(0, -6);
		}
		if(Keyboard::isKeyPressed(Keyboard::S)){
			vue.move(0, 6);
		}
		if(Keyboard::isKeyPressed(Keyboard::D)){
			vue.move(6, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Q)){
			vue.move(-6, 0);
		}

		while((taille = recv(sock, &msg, sizeof(msg), MSG_DONTWAIT)) > 0){
			printf("taille : %lu, type : %d\n", taille, msg.type);
			if(msg.type == 2){
				hero.actualiseFromMessage(msg);
			}
		}
		if(taille == 0){
			return 0;
		}


		app.setView(vue);

		app.clear();

		app.draw(hero.getSprite());

		carte.draw(app);

		app.display();
	}
	return 0;
}


int editeur(RenderWindow& app, Map& carte){

	View vue(POS_HERO, Vector2f(CAM_TAILLE.x*2, CAM_TAILLE.y*2));

	Event event;
	while(app.isOpen()){

		while(app.pollEvent(event)){
			if(event.type == Event::Closed){
				app.close();
			}
			if(event.type == Event::KeyPressed){
				switch(event.key.code){

					case Keyboard::Enter :
						return 1;

					case Keyboard::Escape :
						app.close();
						break;

					default:
						break;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed){
			    if (event.mouseButton.button == sf::Mouse::Left){
			        carte.putBlock(app.mapPixelToCoords(sf::Mouse::getPosition(app)));
			    }
			    else if (event.mouseButton.button == sf::Mouse::Right){
			    	carte.takeBlock(app.mapPixelToCoords(sf::Mouse::getPosition(app)));
			    }
			}
		}

		carte.appliqueTexture();

		if(Keyboard::isKeyPressed(Keyboard::Z)){
			vue.move(0, -6);
		}
		if(Keyboard::isKeyPressed(Keyboard::S)){
			vue.move(0, 6);
		}
		if(Keyboard::isKeyPressed(Keyboard::D)){
			vue.move(6, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Q)){
			vue.move(-6, 0);
		}

		app.setView(vue);

		app.clear();

		carte.draw(app);

		app.display();
	}
	return 0;
}