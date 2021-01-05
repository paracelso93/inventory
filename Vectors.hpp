#pragma once

#include <SDL2/SDL.h>

#include "Helper.hpp"

template <typename T>
struct Vector2 {
	T x, y;

	Vector2() : x(T()), y(T()) {}
	Vector2(T x1, T y1) : x(x1), y(y1) {}
	Vector2(Vector2& other) {
		x = other.x;
		y = other.y;
	}

	Vector2 operator+(const Vector2& a) {
		return Vector2(a.x + x, a.y + y);
	}

	Vector2 operator-(const Vector2& a) {
		return Vector2(x - a.x, y - a.y);
	}

	Vector2 operator*(const T a) {
		return Vector2(x * a, y * a);
	}

	bool operator==(Vector2& a) {
		return (a.x == x && a.y == y);
	}

	Vector2 operator=(const Vector2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}
};

static inline bool pointInRectangle(const Vector2<float>& point, const Vector2<float>& pos, const Vector2<float>& size) {
	return pointInRectangleF(point.x, point.y, pos.x, pos.y, size.x, size.y);
}

static inline bool pointInRectangle(const Vector2<int>& point, const Vector2<int>& pos, const Vector2<int>& size) {
	return pointInRectangleI(point.x, point.y, pos.x, pos.y, size.x, size.y);
}

static inline bool rectCollide(const SDL_Rect& rec1, const SDL_Rect& rec2, SDL_Rect* result = nullptr) {
	if (rec1.x < rec2.x + rec2.w && rec1.x + rec1.w > rec2.x && rec1.y < rec2.y + rec2.h && rec1.y + rec1.h > rec2.y) {
		if (result != nullptr) {
			if (rec1.x < rec2.x) {
				if (rec1.x + rec1.w > rec2.x + rec2.w) {
					result->w = rec2.w;
					result->x = rec2.x;
				} else {
					result->w = rec1.w + rec1.x - rec2.x;
					result->x = rec2.x;
				}
			} else {
				if (rec1.x + rec1.w < rec2.x + rec2.w) {
					result->w = rec1.w;
					result->x = rec1.x;
				} else {
					result->x = rec1.x;
					result->w = rec2.x + rec2.w - rec1.x;
				}
			}
			
			if (rec1.y < rec2.y) {
				result->y = rec2.y;
				result->h = rec1.y + rec1.h - rec2.y;
			} else {
				if (rec1.y + rec1.h > rec2.y + rec2.h) {
					result->y = rec1.y;
					result->h = rec2.y + rec2.h - rec1.y;
				} else {
					result->y = rec1.y;
					result->h = rec1.h;
				}
			}
		}
		return true;
	}
	
	result = nullptr;
	//std::cout << "no collision" << std::endl;
	return false;
}

static inline float recArea(const SDL_Rect& rec) {
	return rec.w * rec.h;
}
