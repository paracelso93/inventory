#pragma once

#include <SDL2/SDL.h>

#include "Vectors.hpp"
#include "TextureHandler.hpp"

class Collectable {
	public:
		Vector2<float> 	position;
		Vector2<int> 	inventoryPosition;
		bool 			clicked;
		texture_t		texture;
		
		virtual void move(Vector2<float>& direction) = 0;
		virtual void update(double dt) = 0;
		virtual bool isClicked(const Vector2<float>& mousePos) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
};
