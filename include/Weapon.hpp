#include "Collectable.hpp"

class Weapon : public Collectable {
	public:
		Weapon(SDL_Renderer* renderer, Vector2<float> position, Vector2<int> inv_position, const std::string& texture);
		void move(Vector2<float>& direction) override;
		void update(double dt) override;
		bool isClicked(const Vector2<float>& mousePos) override;
		void render(SDL_Renderer* renderer) override;
};
