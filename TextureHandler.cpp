#include "TextureHandler.hpp"

TextureHandler* TextureHandler::mInstance = nullptr;

bool TextureHandler::addTexture(const std::string& filePath, texture_t& id, SDL_Renderer* renderer) {
	id = std::hash<std::string>()(filePath);
	if (mTextures.find(id) != mTextures.end()) {
		std::cerr << "texture " << filePath << " already exists!" << std::endl;
		return false;
	}
	
	SDL_Surface* sur = IMG_Load(filePath.c_str());
	LOG(sur, "load surface " + filePath);
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
	LOG(tex, "create texture " + filePath);
	
	mTextures[id] = tex;
	return true;
}

SDL_Texture* TextureHandler::getTexture(texture_t id) {
	if (mTextures.find(id) != mTextures.end()) {
		return mTextures[id];
	} 
	std::cerr << "Unable to load " << std::to_string(id) << std::endl;
	return nullptr;
}

void TextureHandler::render(SDL_Renderer* renderer, texture_t id, Vector2<float>& position, const Vector2<float>& scale, float rotation, const Vector2<float>& center, SDL_RendererFlip flip) {
	if (mTextures.find(id) == mTextures.end()) {
		std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
		return;
	}
	
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	int w, h;
	SDL_QueryTexture(mTextures[id], nullptr, nullptr, &w, &h);
	src.w = w;
	src.h = h;
	
	SDL_Rect dst;
	dst.x = position.x;
	dst.y = position.y;
	dst.w = w * scale.x;
	dst.h = h * scale.y;
	
	SDL_Point cen;
	cen.x = center.x;
	cen.y = center.y;
	
	SDL_RenderCopyEx(renderer, mTextures[id], &src, &dst, rotation, &cen, flip);
}

bool TextureHandler::pointInTexture(const Vector2<float>& point, const Vector2<float>& position, texture_t id) {
	if (mTextures.find(id) == mTextures.end()) {
		std::cerr << "texture " << std::to_string(id) << " doesn't exists!" << std::endl;
		return false;
	}
	int w, h;
	SDL_QueryTexture(mTextures[id], nullptr, nullptr, &w, &h);
	return pointInRectangle(point, position, Vector2<float>(static_cast<float>(w), static_cast<float>(h)));
}
	
