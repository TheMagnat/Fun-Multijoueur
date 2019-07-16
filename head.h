#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <list>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <poll.h>

#include "multiplayer.cpp"

#include "Case.hpp"
#include "map.hpp"
#include "Animation.hpp"
#include "Personnage.hpp"
#include "CollisionManager.hpp"

using namespace sf;

#define SPEED 75

static Vector2f CAM_TAILLE(300, 250); // 300, 250 ou 300, 200

static Vector2f TAILLE_ECRAN(800, 600);
static VideoMode VIDEO_MODE(800, 600, 32); // 800, 600 ou 1200, 700

#include "menu.cpp"
#include "jeu.cpp"
#include "editeur.cpp"
