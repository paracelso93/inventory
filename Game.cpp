#include "Game.hpp"

bool Game::initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Unable to init video" << std::endl;
		return false;
	}
	
	IMG_Init(IMG_INIT_PNG);
	
	mWindow = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
	LOG(mWindow, "create window");
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	LOG(mRenderer, "create renderer");
	
	running = true;
	
	for (size_t i = 0; i < INVENTORY_WIDTH - 2; i++) {
		swords.push_back(new Weapon(mRenderer, Vector2<float>(i * 108, 0), Vector2<int>(i, 0), "sword.png"));
		inventoryObjects[0][i] = swords[i];
	}
	
	for (size_t i = 0; i < INVENTORY_HEIGHT; i++) {
		for (size_t j = 0; j < INVENTORY_WIDTH; j++) {
			inventoryRectangles[i][j] = new SDL_Rect();
			inventoryRectangles[i][j]->x = j * 108;
			inventoryRectangles[i][j]->y = i * 110;
			inventoryRectangles[i][j]->w = 98;
			inventoryRectangles[i][j]->h = 98;
		}
	}
	
	for (size_t i = 0; i < INVENTORY_HEIGHT; i++) {
		for (size_t j = 0; j < INVENTORY_WIDTH; j++) {
			inventoryObjects[i][j] = nullptr;
		}
	}
	
	dragging = false;
	
	/*rec1.x = 0;
	rec1.y = 0;
	rec1.w = 100;
	rec1.h = 60;
	
	rec2.x = 50;
	rec2.y = 40;
	rec2.w = 20;
	rec2.h = 40;*/
	
	return true;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				for (Weapon* sword : swords) {
					if (sword->isClicked(Vector2<float>(event.button.x, event.button.y))) {
						//std::cout << "Clicked sword" << std::endl;
						int x, y;
						SDL_GetMouseState(&x, &y);
						mousePosition = Vector2<int>(x, y);
						oldPosition = sword->position;
						dragging = true;
						currentCollectable = sword;
						inventoryObjects[sword->inventoryPosition.y][sword->inventoryPosition.x] = nullptr;
						currentOffset = Vector2<float>(mousePosition.x - sword->position.x, mousePosition.y - sword->position.y);
					}
				}
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (dragging) {
					
					int x, y;
					SDL_GetMouseState(&x, &y);
					mousePosition = Vector2<int>(x, y);
					dragging = false;
					float max = 0;
					int maxi = 0, maxj = 0;
					SDL_Rect* maxRect;
					SDL_Rect pos;
					pos.x = currentCollectable->position.x;
					pos.y = currentCollectable->position.y;
					SDL_QueryTexture(TextureHandler::getInstance()->getTexture(currentCollectable->texture), nullptr, nullptr, &pos.w, &pos.h);
					for (size_t i = 0; i < INVENTORY_HEIGHT; i++) {
						for (size_t j = 0; j < INVENTORY_WIDTH; j++) {
							SDL_Rect* rec = inventoryRectangles[i][j];
							SDL_Rect overlap;
							if (rectCollide(pos, *rec, &overlap)) {
								float val = recArea(overlap) / recArea(*rec);
								Collectable* coll = inventoryObjects[i][j];
								if (val > max && coll == nullptr) {
									max = val;
									maxi = i;
									maxj = j;
									maxRect = rec;
									coll = currentCollectable;
								}
							}
						}
					}
					if (max != 0) {
						currentCollectable->position = Vector2<float>(maxRect->x, maxRect->y);
						currentCollectable->inventoryPosition = Vector2<int>(maxj, maxi);
						inventoryObjects[maxi][maxj] = currentCollectable;
					} else {
						currentCollectable->position = oldPosition;
						inventoryObjects[currentCollectable->inventoryPosition.y][currentCollectable->inventoryPosition.x] = currentCollectable;
					}
				}
			}
		}
	}
	
	//const Uint8* keys = SDL_GetKeyboardState(nullptr);
	/*if (keys[SDL_SCANCODE_W]) {
		rec2.y -= 10;
	}
	if (keys[SDL_SCANCODE_S]) {
		rec2.y += 10;
	}
	if (keys[SDL_SCANCODE_A]) {
		rec2.x -= 10;
	}
	if (keys[SDL_SCANCODE_D]) {
		rec2.x += 10;
	}*/
}

void Game::update() {
	for (Weapon* sword : swords)
		sword->update(0.0);
		
	if (dragging) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		mousePosition = Vector2<int>(x, y);
		currentCollectable->position = Vector2<float>(mousePosition.x - currentOffset.x, mousePosition.y - currentOffset.y);
	}
	//if (res == nullptr) res = new SDL_Rect()
	//if (!rectCollide(rec1, rec2, &res)) {
		//delete res;
		//colliding = false; 
	//} else colliding = true;
}

void Game::render() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 200, 255);
	SDL_RenderClear(mRenderer);
	
	/*SDL_SetRenderDrawColor(mRenderer, 0, 200, 0, 255);
	SDL_RenderFillRect(mRenderer, &rec1);
	
	SDL_SetRenderDrawColor(mRenderer, 200, 0, 0, 255);
	SDL_RenderFillRect(mRenderer, &rec2);
	
	if (colliding) {
		SDL_SetRenderDrawColor(mRenderer, 200, 200, 0, 255);
		SDL_RenderFillRect(mRenderer, &res);
	} else {
		//std::cout << "none" << std::endl;
	/}*/
	
	SDL_SetRenderDrawColor(mRenderer, 100, 100, 100, 255);
	for (std::array<SDL_Rect*, INVENTORY_WIDTH>& arr : inventoryRectangles) {
		for (SDL_Rect* rec : arr) {
			SDL_RenderFillRect(mRenderer, rec);
		}
	}
	
	for (Weapon* sword : swords) 
		sword->render(mRenderer);
	
	SDL_RenderPresent(mRenderer);
}

void Game::quit() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
	
