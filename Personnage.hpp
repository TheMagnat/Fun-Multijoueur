

class Personnage{

	public:

		Personnage(std::string textu, std::vector<std::vector<sf::IntRect>> anim, sf::Vector2f pos) :
		inAir_(false), nbJump_(1), inertie_(0, 0), inverse_(false), sens_(0), frameAnnim_(0.15), anim_(anim), save_(0){
			if(!texture_.loadFromFile(textu)){
				std::cerr << "Impossible de charger " << textu << std::endl;
			}
			else{
				sprite_.setTexture(texture_);
				sprite_.setTextureRect(anim_.actuelSprite());
				sprite_.setOrigin({ sprite_.getLocalBounds().width/2, sprite_.getLocalBounds().height/2 });
				sprite_.setScale(1,1);
			}
			sprite_.setPosition(pos);

		}

		void jump(){
			if(inAir_){
				if(nbJump_ == 0 || jumpAnim_){
					return;
				}
				else{
					nbJump_ = 0;
				}
			}

			inAir_ = true;
			inertie_.y = -300;

			sens_ = 2;
			anim_.setActuelle(2);
			temps_.restart();
			save_=0;
			sprite_.setTextureRect(anim_.actuelSprite());

			frameAnnim_ = 0.07;

			jumpAnim_ = true;

		}

		void putSol(float const y){
			inertie_.y = 0;
			frameAnnim_ = 0.15;
			jumpAnim_ = false;
			nbJump_ = 1;
			sprite_.setPosition(sprite_.getPosition().x, y - sprite_.getLocalBounds().height/2);
		}

		void annulMoveHaut(float elapsedTime){
			sprite_.move(0, -inertie_.y*elapsedTime);
		}

		void annulMoveCote(float elapsedTime){
			sprite_.move(-inertie_.x*elapsedTime, 0);
		}

		void annulMove(float elapsedTime){
			sprite_.move(-inertie_.x*elapsedTime, -inertie_.y*elapsedTime);
		}

		void move(int sens, float elapsedTime){
			bool inverse(sens<0);
			//if(inverse) sens *= -1;
			if(inverse_ != inverse){
				if(sens){
					if(inverse) sprite_.setScale(-1, 1);
					else sprite_.setScale(1, 1);
					inverse_ = inverse;
				}
			}
			
			if(!inAir_){
				if(sens){
					if(sens_ != sens*sens){
						sens_ = 1;
						anim_.setActuelle(1);
						temps_.restart();
						save_=0;
						sprite_.setTextureRect(anim_.actuelSprite());
					}
				}
				else{
					if(sens_ != sens){
						sens_ = 0;
						anim_.setActuelle(0);
						temps_.restart();
						save_=0;
						sprite_.setTextureRect(anim_.actuelSprite());
					}
				}
			}

			avance(sens, elapsedTime);
		}

		void avance(int sens, float elapsedTime){

			//Deplacement vertical
			if(inAir_){
				inertie_.y += 10;

				if(sens){
					
					inertie_.x += 10*sens;

					if(inertie_.x > 200){
						inertie_.x = 200;
					}
					else if(inertie_.x < -200){
						inertie_.x = -200;
					}

				}
			}
			else{
			//Deplacement sur le coté
				if(sens == 0){
					if(inertie_.x < 0) inertie_.x += 20;
					else if(inertie_.x > 0) inertie_.x -= 20;
				}
				else{
					inertie_.x = 200*sens;
				}
			}
			sprite_.move(inertie_.x*elapsedTime, inertie_.y*elapsedTime);

		}

		sf::Vector2f getPosition() const {
			return sprite_.getPosition();
		}

		void setPosition(sf::Vector2f pos){
			sprite_.setPosition(pos);
		}

		sf::Sprite getSprite(){
			return sprite_;
		}

		void actualiseFromMessage(message const& msg){
			sprite_.setPosition(msg.x, msg.y);
			sprite_.setTextureRect(sf::IntRect(msg.left, msg.top, msg.width, msg.height));
		}

		sf::FloatRect getTeteHitBox() const{
			sf::FloatRect tempo(sprite_.getGlobalBounds());
			tempo.height = 1;
			//tempo.left += 2;
			//tempo.width -= 4;
			return tempo;
		}

		sf::FloatRect getPiedHitBox() const{
			sf::FloatRect tempo(sprite_.getGlobalBounds());
			tempo.top += tempo.height-1;
			//tempo.left += 2;
			tempo.height = 1;
			//tempo.width -= 4;
			return tempo;
		}

		sf::FloatRect getCoteHitBox() const{
			sf::FloatRect tempo(sprite_.getGlobalBounds());
			/*tempo.top += 1;
			tempo.height -= 2;*/
			return tempo;
		}	

		sf::FloatRect getHitBox() const {
			return sprite_.getGlobalBounds();
		}

		sf::Vector2f& getInertie(){
			return inertie_;
		}

		sf::IntRect getTextureRect(){
			return sprite_.getTextureRect();
		}

		void draw(sf::RenderWindow& app){
			int tempo(temps_.getElapsedTime().asSeconds()/frameAnnim_);
			if(save_ < tempo){
				save_ = tempo;
				sprite_.setTextureRect(anim_.nextSprite());
				if(jumpAnim_){
					if(anim_.getActuelleNumero() == 0){
						putInAir();
						frameAnnim_ = 0.15;
						jumpAnim_ = false;
					}
				}
			}

			app.draw(sprite_);
		}

		void putInAir(){
			inAir_ = true;
			sens_ = 3;
			anim_.setActuelle(3);
			temps_.restart();
			save_=0;
			sprite_.setTextureRect(anim_.actuelSprite());
		}

		void setInAir(bool const valeur){
			inAir_ = valeur;
		}

		bool isAir() const {
			return inAir_;
		}
		

	private:
		bool jumpAnim_;
		bool inAir_;
		uint8_t nbJump_;
		sf::Vector2f inertie_;

		bool inverse_;
		int sens_; // 0 Rien,  1 cote, 2 Jump, 3 fall
		sf::Texture texture_;
		sf::Sprite sprite_;

		float frameAnnim_;
		Animation anim_;
		sf::Clock temps_;
		int save_;
};