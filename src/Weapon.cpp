#include "Weapon.hpp"

Weapon::Weapon(SDL_Renderer* renderer, Vector2<float> position, Vector2<int> inv_position, const std::string& texture) {
	this->position = position;
	this->clicked = false;
	this->inventoryPosition = inv_position;
	TextureHandler::getInstance()->addTexture(texture, this->texture, renderer);
}

void Weapon::move(Vector2<float>& direction) {
	this->position = this->position + direction;
}

void Weapon::update(double dt) {
	
}

bool Weapon::isClicked(const Vector2<float>& mousePos) {
	this->clicked = TextureHandler::getInstance()->pointInTexture(mousePos, this->position, this->texture);
	return clicked;
}

void Weapon::render(SDL_Renderer* renderer) {
	TextureHandler::getInstance()->render(renderer, this->texture, this->position);
}
