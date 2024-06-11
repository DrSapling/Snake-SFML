#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <vector>
#include <string>

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Dwmapi.h> //Header for creating a borderless window 


namespace DIR //Directions used in the game
{
	enum Direction { LEFT, RIGHT, UP, DOWN, STOP };
}

namespace DEAD //Possible reasons of death
{
	enum Dead_Reason { WALL, TAIL, UNKNOWN };
}
