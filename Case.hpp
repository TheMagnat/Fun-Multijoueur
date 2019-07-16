

class Case{

	public:
		Case(sf::Texture *texture, sf::IntRect posTextu, sf::Vector2f pos, int type = 0) : type_(type), sprite_(*texture, posTextu){
			sprite_.setPosition(pos);
		}

		void setTextureRect(sf::IntRect const& textuPos){
			sprite_.setTextureRect(textuPos);
		}

		sf::Vector2f getPosition() const {
			return sprite_.getPosition();
		}

		sf::FloatRect getHitBox() const {
			if(type_ == 1){
				sf::FloatRect tempo(sprite_.getGlobalBounds());
				++tempo.top;
				--tempo.height;
				return tempo;
			}
			else{
				//cas de base
				return sprite_.getGlobalBounds();
			}
		}

		sf::Sprite& getSprite(){
			return sprite_;
		}

		int getType(){
			return type_;
		}


	private:
		int type_;

		sf::Texture* texture_;
		sf::Sprite sprite_;


};