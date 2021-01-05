#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <vector>

#include "Weapon.hpp"
#include "Helper.hpp"

const unsigned int INVENTORY_WIDTH = 10;
const unsigned int INVENTORY_HEIGHT = 6;

class Game {
	public:
		bool initialize();
		void handleEvents();
		void update();
		void render();
		void quit();
	
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		bool running;
		std::vector<Weapon* > swords;
		
		std::array<std::array<SDL_Rect*, INVENTORY_WIDTH>, INVENTORY_HEIGHT> inventoryRectangles;
		std::array<std::array<Collectable*, INVENTORY_WIDTH>, INVENTORY_HEIGHT> inventoryObjects;
		Vector2<int> mousePosition;
		Vector2<float> currentOffset;
		Vector2<float> oldPosition;
		Collectable* currentCollectable;
		bool dragging;
		// TODO: remove later
		//SDL_Rect rec1;
		//SDL_Rect rec2;
		//SDL_Rect res;
		//bool colliding;
};
