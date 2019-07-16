
class Map{

	public:
		Map(std::string fichier){
			texture_.loadFromFile(fichier);


			//test
			/*cases_.emplace_back(&texture_, sf::IntRect(99, 73, 32, 32), sf::Vector2f(416, 320));
			cases_.emplace_back(&texture_, sf::IntRect(99, 73, 32, 32), sf::Vector2f(416+32, 320));
			cases_.emplace_back(&texture_, sf::IntRect(99, 73, 32, 32), sf::Vector2f(416+64, 320));
			cases_.emplace_back(&texture_, sf::IntRect(99, 73, 32, 32), sf::Vector2f(416+96, 320));*/
		}

		void appliqueTexture(){
			size_t i, taille(cases_.size());

			for(i=0; i<taille; ++i){
				if(cases_[i].getType() == 0){
					cases_[i].setTextureRect(choixTexture(cases_[i].getPosition()));
				}
			}

		}


		sf::IntRect choixTexture(sf::Vector2f pos){

			int x(pos.x/32), y(pos.y/32);

			int coteX(0), coteY(0);

			std::unordered_map<int, std::unordered_map<int, size_t>>::iterator it;
			std::unordered_map<int, size_t>::iterator it2;

			if(posToIndex_.find(x-1) != posToIndex_.end() && posToIndex_[x-1].find(y) != posToIndex_[x-1].end()){
				coteX = 1;
			}
			if(posToIndex_.find(x+1) != posToIndex_.end() && posToIndex_[x+1].find(y) != posToIndex_[x+1].end()){
				if(coteX == 1) coteX = 3;
				else coteX = 2;
			}

			if(posToIndex_.find(x) != posToIndex_.end() && posToIndex_[x].find(y-1) != posToIndex_[x].end()){
				coteY = 1;
			}
			if(posToIndex_.find(x) != posToIndex_.end() && posToIndex_[x].find(y+1) != posToIndex_[x].end()){
				if(coteY == 1) coteY = 2;
			}


			//if(coteX == 0 && coteY == 0) return sf::IntRect(128, 58, 32, 32);
			if(coteX == 1 && coteY == 0) return sf::IntRect(256, 64, 32, 32);
			if(coteX == 1 && coteY == 1) return sf::IntRect(256, 128, 32, 32);
			if(coteX == 1 && coteY == 2) return sf::IntRect(256, 96, 32, 32);
			if(coteX == 2 && coteY == 0) return sf::IntRect(0, 64, 32, 32);
			if(coteX == 2 && coteY == 1) return sf::IntRect(0, 128, 32, 32);
			if(coteX == 2 && coteY == 2) return sf::IntRect(0, 96, 32, 32);
			if(coteX == 3 && coteY == 0) return sf::IntRect(128, 64, 32, 32);
			if((coteX == 3 || coteX == 0) && coteY == 1) return sf::IntRect(128, 128, 32, 32);
			if((coteX == 3 || coteX == 0) && coteY == 2) return sf::IntRect(128, 96, 32, 32);

			return sf::IntRect(128, 64, 32, 32);
		}

		void putBlock(sf::Vector2f pos, int type = 0){
			int x(pos.x/32), y(pos.y/32);

			if(x < 0) --x;
			else if(x == 0){
				if(pos.x < 0) --x;
			}
			if(y < 0) --y;
			else if(y == 0){
				if(pos.y < 0) --y;
			}


			auto got(posToIndex_.find(x));
			
			if(got != posToIndex_.end()){
				auto got2 = posToIndex_[x].find(y);
				if(got2 != posToIndex_[y].end()) return;
			}

			pos.x = x*32;
			pos.y = y*32;
			posToIndex_[x][y]=cases_.size();

			if(type == 1){
				cases_.emplace_back(&texture_, sf::IntRect(64, 0, 32, 32), pos, 1);
			}
			else{
				cases_.emplace_back(&texture_, sf::IntRect(128, 58, 32, 32), pos);
			}
		}

		void takeBlock(sf::Vector2f pos){
			int x(pos.x/32), y(pos.y/32);

			if(x < 0) --x;
			else if(x == 0){
				if(pos.x < 0) --x;
			}
			if(y < 0) --y;
			else if(y == 0){
				if(pos.y < 0) --y;
			}

			size_t save;

			auto got(posToIndex_.find(x));
			
			if(got == posToIndex_.end()){
				return;
			}
			else{
				auto got2 = posToIndex_[x].find(y);
				if(got2 == posToIndex_[y].end()) return;
			}

			save = posToIndex_[x][y];

			cases_.erase(cases_.begin()+save);
			posToIndex_[x].erase(y);

			std::unordered_map<int, std::unordered_map<int, size_t>>::iterator debut;
			std::unordered_map<int, size_t>::iterator debut2;

			for(debut = posToIndex_.begin(); debut != posToIndex_.end(); ++debut){

				for(debut2 = debut->second.begin(); debut2 != debut->second.end(); ++debut2){
					if(debut2->second > save){
						--debut2->second;
					}
				}

			}

		}


		void draw(sf::RenderWindow& app){
			size_t i, taille;

			taille = cases_.size();
			for(i=0; i<taille; ++i){
				app.draw(cases_[i].getSprite());
			}
		}

		std::vector<Case>& getVecCases(){
			return cases_;
		}

	private:
		sf::Texture texture_;

		std::vector<Case> cases_;
		std::unordered_map<int, std::unordered_map<int, size_t>> posToIndex_; //x puis y
};