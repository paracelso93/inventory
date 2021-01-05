#include "Game.hpp"

int main() {
	Game game;
	if (!game.initialize()) {
		return -1;
	}
	
	while (game.running) {
		game.handleEvents();
		game.update();
		game.render();
	}
	
	game.quit();
	
	return 0;
}
