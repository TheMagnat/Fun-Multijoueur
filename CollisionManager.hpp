
class CollisionManager{

	public:
		//Retour : 0 = pas de collision, 1 = collision avec le sol
		int verifColli(Personnage& hero, float elaspedTime){
			bool verifSol(false);
			size_t i, taille;
			std::vector<Case>* ptrVec;
			sf::FloatRect tempoCaseHitBox, piedHitBox(hero.getPiedHitBox()), piedHitBoxPlus1(piedHitBox),
			teteHitBox(hero.getTeteHitBox()), coteHitBox(hero.getCoteHitBox());
			++piedHitBoxPlus1.top;

			ptrVec = &mapActuelle_->getVecCases();
			taille = ptrVec->size();
			for(i=0; i<taille; ++i){
				tempoCaseHitBox = (*ptrVec)[i].getHitBox();

				if(coteHitBox.intersects(tempoCaseHitBox)){
					hero.annulMoveCote(elaspedTime);
					hero.getInertie().x = 0;
					piedHitBox = hero.getPiedHitBox();
					teteHitBox = hero.getTeteHitBox();
					coteHitBox = hero.getCoteHitBox();
					piedHitBoxPlus1 = piedHitBox;
					++piedHitBoxPlus1.top;
				}

				if(teteHitBox.intersects(tempoCaseHitBox)){
					hero.annulMoveHaut(elaspedTime);
					hero.getInertie().y = 0;
					piedHitBox = hero.getPiedHitBox();
					teteHitBox = hero.getTeteHitBox();
					coteHitBox = hero.getCoteHitBox();
					piedHitBoxPlus1 = piedHitBox;
					++piedHitBoxPlus1.top;
				}

				if(piedHitBox.intersects(tempoCaseHitBox)){
					if(hero.isAir()){
						hero.setInAir(false);
						hero.putSol(tempoCaseHitBox.top);
						piedHitBox = hero.getPiedHitBox();
						teteHitBox = hero.getTeteHitBox();
						coteHitBox = hero.getCoteHitBox();
						piedHitBoxPlus1 = piedHitBox;
						++piedHitBoxPlus1.top;
					}
				}

				if(piedHitBoxPlus1.intersects(tempoCaseHitBox)) verifSol = true;
			}
			if(!verifSol && !hero.isAir()) hero.putInAir();
			return 0;
		}

		void setMap(Map* mapAct){
			mapActuelle_ = mapAct;
		}



	private:
		Map* mapActuelle_;
};