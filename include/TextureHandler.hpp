#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

#include "Vectors.hpp"
#include "Helper.hpp"

#define texture_t unsigned int

class TextureHandler {
	public:
		static TextureHandler* getInstance() {
			if (mInstance == nullptr) {
				mInstance = new TextureHandler();
				return mInstance;
			}
			return mInstance;
		}
		bool addTexture(const std::string& filePath, texture_t& id, SDL_Renderer* renderer);
		SDL_Texture* getTexture(texture_t id);
		void render(SDL_Renderer* renderer, texture_t id, Vector2<float>& position, const Vector2<float>& scale = Vector2<float>(1.0f, 1.0f), float rotation = 0, const Vector2<float>& center = Vector2<float>(), SDL_RendererFlip flip = SDL_FLIP_NONE);
		bool pointInTexture(const Vector2<float>& point, const Vector2<float>& position, texture_t id);
	private:
		static TextureHandler* mInstance;
		std::unordered_map<texture_t, SDL_Texture*> mTextures;
};
